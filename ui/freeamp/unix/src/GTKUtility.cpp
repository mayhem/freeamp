/*____________________________________________________________________________

   FreeAmp - The Free MP3 Player

   Copyright (C) 1999 EMusic

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.

   $Id: GTKUtility.cpp,v 1.15.12.1 2001/02/15 06:08:01 ijr Exp $
____________________________________________________________________________*/ 

#include "config.h"

#include <stdio.h>
#include <string>

#include <gdk/gdk.h>
extern "C" {
#include <gdk/gdkx.h>
}
#include <gtk/gtk.h>
#include <X11/Xatom.h>
#include <iostream>
#include <unistd.h>

#include <vector>
#include <map>
using namespace std;

#include "thread.h"
#include "GTKUtility.h"
#include "facontext.h"
#include "gtkmessagedialog.h"

static Thread *gtkThread = NULL;
static bool weAreGTK = false;
static bool doQuitNow = false;
static FAContext *ourContext;

void WarpPointer(GdkWindow *win, int x, int y)
{
    Window window = GDK_WINDOW_XWINDOW(win);
    XWarpPointer(GDK_DISPLAY(), window, window, 0, 0, 0, 0, x, y);
}

static void *GetWindowProperty(Window win, Atom type, Atom format, int *size)
{
   unsigned char      *retval;
   Atom                type_ret;
   unsigned long       bytes_after, num_ret;
   int                 format_ret;
   void               *data = NULL;

   retval = NULL;
   if (win == 0) {
       *size = 0;
       return NULL;
   }
   XGetWindowProperty(GDK_DISPLAY(), win, type, 0, 0x7fffffffL, False, format,
                      &type_ret, &format_ret, &num_ret, &bytes_after, &retval);

   if (retval) {
       if (format_ret == 32) {
           int i;

           *size = num_ret * sizeof(unsigned int);
           data = (void *)new unsigned int[num_ret];

           for (i = 0; i < (int)num_ret; i++)
               ((unsigned int *)data)[i] = ((unsigned long *)retval)[i];
       }
       else if (format_ret == 16) {
           int i;

           *size = num_ret * sizeof(unsigned short);
           data = (void *)new unsigned short[num_ret];

           for (i = 0; i < (int)num_ret; i++)
               ((unsigned short *)data)[i] = ((unsigned short *)retval)[i];
       }
       else if (format_ret == 8) {
           *size = num_ret;
           data = (void *)new char[num_ret];

           if (data)
              memcpy(data, retval, num_ret);
        }
        XFree(retval);
        return data;
   }
   *size = 0;
   return NULL;
}


Pos GetFocusPos(void)
{
    Window win, tempwin;
    XWindowAttributes win_attr;
    int v, rx = -1, ry = -1;
    char *name;
    Pos retpos;
    static Atom atom = None;
    int *data, size;

    if (XGetInputFocus(GDK_DISPLAY(), &win, &v) &&
        XFetchName(GDK_DISPLAY(), win, &name) &&
        strncmp(name, BRANDING, strlen(BRANDING)))
    {
        if (XGetWindowAttributes(GDK_DISPLAY(), win, &win_attr)) 
            XTranslateCoordinates(GDK_DISPLAY(), win, win_attr.root,
                                  -win_attr.border_width, 
                                  -win_attr.border_width, &rx, &ry,
                                  &tempwin);
        if (atom == None)
            atom = XInternAtom(GDK_DISPLAY(), "_E_FRAME_SIZE", True);

        if (atom != None) {
            data = (int *)GetWindowProperty(win, atom, XA_CARDINAL, &size);
            if (data) {
                if (size == (4 * sizeof(int))) {
                    rx -= data[0];
                    ry -= data[2];
                }
            }
        }
    }

    retpos.x = rx;
    retpos.y = ry;

    return retpos;
}

static gint theme_timeout(void *c)
{
    ourContext->gtkRunning = true;
    if (doQuitNow)
        gtk_main_quit();

    return TRUE;
}

static void runGTK(void *c)
{
    FAContext *context = (FAContext *)c;
    gtk_init(&(context->argc), &(context->argv));
    gdk_rgb_init();
    gtk_timeout_add(250, theme_timeout, NULL);
    gtk_main();
    gdk_threads_leave();
}

void InitializeGTK(FAContext *context)
{
    ourContext = context;

    if (gtkThread)
        return;

    context->gtkLock.Acquire();
    if (!context->gtkInitialized) {
        context->gtkInitialized = true;
	g_thread_init(NULL);
        gtk_set_locale();
	weAreGTK = true;
    }
    context->gtkLock.Release();
    
    if (weAreGTK) {
        gtkThread = Thread::CreateThread();
        gtkThread->Create(runGTK, context);
    }

    bool running = false;

    while (!running) {
        context->gtkLock.Acquire();
        running = context->gtkRunning;
        context->gtkLock.Release();
        usleep(50);
    }

    bool reclaimFileTypes, askBeforeReclaiming;
    context->prefs->GetPrefBoolean(kReclaimFiletypesPref, &reclaimFileTypes);
    context->prefs->GetPrefBoolean(kAskToReclaimFiletypesPref, &askBeforeReclaiming);

    if (reclaimFileTypes)
        ReclaimFileTypes(context, askBeforeReclaiming);
}

void ShutdownGTK(void)
{
    if (weAreGTK && gtkThread) {
        gdk_threads_enter();
        gtk_main_quit();
        gdk_threads_leave();
        weAreGTK = false;
        doQuitNow = true;
        gtkThread->Join();
        delete gtkThread;
        gtkThread = NULL;
    }
}

void PixbufDrawRectFill(GdkPixbuf *pb, gint x, gint y, gint w, gint h,
                        gint r, gint g, gint b, gint a)
{
    gint p_alpha;
    gint pw, ph, prs;
    guchar *p_pix;
    guchar *pp;
    gint i, j;

    if (!pb) 
        return;

    pw = gdk_pixbuf_get_width(pb);
    ph = gdk_pixbuf_get_height(pb);

    if (x < 0 || x + w > pw) 
        return;
    if (y < 0 || y + h > ph) 
        return;

    p_alpha = gdk_pixbuf_get_has_alpha(pb);
    prs = gdk_pixbuf_get_rowstride(pb);
    p_pix = gdk_pixbuf_get_pixels(pb);

    for (i = 0; i < h; i++)
    {
        pp = p_pix + (y + i) * prs + (x * (p_alpha ? 4 : 3));
        for (j = 0; j < w; j++)
        {
            *pp = (r * a + *pp * (256-a)) >> 8;
            pp++;
            *pp = (g * a + *pp * (256-a)) >> 8;
            pp++;
            *pp = (b * a + *pp * (256-a)) >> 8;
            pp++;
            if (p_alpha) pp++;
        }
    }
}

GdkPixbuf *PixbufFromRootWindow(gint x, gint y, gint w, gint h, gint get_all)
{
    GdkPixbuf *pb;
    GdkVisual *gdkvisual;
    GdkWindow *rootwindow;
    gint screen_w;
    gint screen_h;
    gint screen_x;
    gint screen_y;

    if (w < 1 || h < 1 ) 
        return NULL;

    pb = gdk_pixbuf_new(GDK_COLORSPACE_RGB, FALSE, 8, w, h);
    PixbufDrawRectFill(pb, 0, 0, w, h, 0, 0, 0, 255);

    screen_w = gdk_screen_width();
    screen_h = gdk_screen_height();

    if (x >= screen_w || y >= screen_h || x + w < 0 || y + h < 0) 
        return pb;

    screen_x = x;
    if (screen_x < 0)
    {
        w += screen_x;
        screen_x = 0;
    }
    if (screen_x + w > screen_w)
    {
        w -= screen_x + w - screen_w;
    }

    screen_y = y;
    if (screen_y < 0)
    {
        h += screen_y;
        screen_y = 0;
    }
    if (screen_y + h > screen_h)
    {
        h -= screen_y + h - screen_h;
    }

    if (w < 1 || h < 1) 
        return pb;

    rootwindow = (GdkWindow *) gdk_window_lookup(GDK_ROOT_WINDOW());
    if (!rootwindow) 
        return NULL;

    gdkvisual = gdk_window_get_visual(rootwindow);
    if (gdkvisual != gdk_visual_get_system()) 
        return pb;

    if (!get_all)
    {
        Atom prop, type;
        int format;
        unsigned long length, after;
        unsigned char *data;
        Window desktop_window;

        gdk_error_trap_push();

        desktop_window = GDK_ROOT_WINDOW();

        prop = XInternAtom(GDK_DISPLAY(), "_XROOTPMAP_ID", True);

        if (prop != None)
        {
            XGetWindowProperty(GDK_DISPLAY(), desktop_window, prop, 0L, 1L, 
                               False, AnyPropertyType, &type, &format, &length,
                               &after, &data);

            if (type == XA_PIXMAP)
            {
                Pixmap p;
                p = *((Pixmap *)data);

                if (p != None)
                {
                    GdkPixmap *pp;
                    GdkColormap *cmap;
                    gint p_w, p_h;

                    pp = gdk_pixmap_foreign_new(p);
                    cmap = gdk_window_get_colormap(rootwindow);

                    gdk_drawable_set_colormap(pp, cmap);

                    gdk_window_get_size(pp, &p_w, &p_h);

                    if (p_w < screen_x + w || p_h < screen_y + h)
                    {
                        gint i, j;

                        for (j = (screen_y / p_h) * p_h; j < screen_y + h; 
                             j += p_h)
                            for (i = (screen_x / p_w) * p_w; i < screen_x + w; 
                                 i += p_w)
                            {
                                gint offset_x, offset_y;
                                gint offset_w, offset_h;

                                if (j < screen_y)
                                {
                                    offset_y = screen_y - j;
                                }
                                else
                                {
                                    offset_y = 0;
                                }

                                offset_h = p_h - offset_y;
                                if (j + offset_y + offset_h >= screen_y + h) 
                                    offset_h = (screen_y + h) - (j + offset_y);

                                if (i < screen_x)
                                {
                                    offset_x = screen_x - i;
                                }
                                else
                                {
                                    offset_x = 0;
                                }

                                offset_w = p_w - offset_x;
                                if (i + offset_x + offset_w >= screen_x + w) 
                                    offset_w = (screen_x + w) - (i + offset_x);

                                 gdk_pixbuf_get_from_drawable(pb, pp, cmap,
                                                              offset_x, 
                                                              offset_y,
                                                      (i + offset_x) - screen_x,
                                                      (j + offset_y) - screen_y,
                                                              offset_w, 
                                                              offset_h);
                            }
                    }
                    else
                    {
                        gdk_pixbuf_get_from_drawable(pb, pp, cmap,
                                                     screen_x, screen_y,
                                                     screen_x - x, screen_y - y,
                                                     w, h);
                    }
                }
            }
        }
        gdk_error_trap_pop();
    }
    else
    {
        gdk_pixbuf_get_from_drawable(pb, rootwindow, NULL,
                                     screen_x, screen_y,
                                     screen_x - x, screen_y - y, w, h);
    }

    return pb;
}

const char *kMimeTypes[] = {
    "audio/x-mpeg",
    "audio/x-mp3",
    "audio/x-mpegurl",
    "audio/x-scpls",
    "audio/mpeg",
    "audio/mp3",
    "audio/mpegurl",
    "audio/scpls",
    "application/vnd.rn-rn_music_package",
    "application/x-freeamp-theme",
    NULL
};
#define kNumMime 10

const char* kNotifyStolen = "Music files normally associated with "the_BRANDING "\n"
                            "have been associated with another application.\n"
                            "Do you want to reclaim these music files?";

void AddMissingMimeTypes(void)
{
    FILE *f;
    char *buffer, *mime;
    uint32 index;
    bool needRewrite = false; 
    vector<string> oldfile;
    bool found[kNumMime];

    for (index = 0; index < kNumMime; index++)
        found[index] = false;

    buffer = new char[1024];
    mime = new char[1024];

    string mimeTypes = string(getenv("HOME")) + string("/.mime.types");

    f = fopen(mimeTypes.c_str(), "r");

    if (f) {
        while (fgets(buffer, 1024, f)) 
            oldfile.push_back(buffer);
        fclose(f);

        vector<string>::iterator i;
        for (i = oldfile.begin(); i != oldfile.end(); i++) {
            strcpy(buffer, (*i).c_str());
            if (!strncmp("type", buffer, 4)) {
                sscanf(buffer, "type=%s", mime);
                if (*mime) {
                    for (index = 0; ; index++) {
                        if (kMimeTypes[index] == NULL)
                            break;
                        if (!strcmp(mime, kMimeTypes[index])) {
                            found[index] = true;
                            break;
                        }
                    }
                }
            }
        }  
    }
    else {
        oldfile.push_back("#--Netscape Communications Corporation MIME Information\n"); 
        oldfile.push_back("#Do not delete the above line. It is used to identify the file type.\n");
        oldfile.push_back("#\n");
    }

    for (index = 0; index < kNumMime; index++) {
        if (!found[index]) {
            sprintf(buffer, "type=%s\n", kMimeTypes[index]);
            needRewrite = true;
            oldfile.push_back(buffer);
        }
    }            

    if (needRewrite) {
        f = fopen(mimeTypes.c_str(), "w");
        if (!f)
            goto failed_open;
        
        vector<string>::iterator i;
        for (i = oldfile.begin(); i != oldfile.end(); i++) {
             strcpy(buffer, (*i).c_str());
             fputs(buffer, f);
        }
        fclose(f);
    }

failed_open:
    delete [] buffer;
    delete [] mime;
}

void ReclaimFileTypes(FAContext *context, bool askBeforeReclaiming)
{
    AddMissingMimeTypes();

    FILE *f;
    char *buffer, *mime, *app;
    uint32 index;
    bool needRewrite = false;
    map<string, string> oldfile;
    bool found[kNumMime];

    for (index = 0; index < kNumMime; index++)
        found[index] = false;

    buffer = new char[1024];
    mime = new char[1024];
    app = new char[1024];

    string mimeTypes = string(getenv("HOME")) + string("/.mailcap");

    f = fopen(mimeTypes.c_str(), "r");

    if (f) {
        while (fgets(buffer, 1024, f)) {
            if (buffer[0] == '#')
                continue;
            sscanf(buffer, "%[^;];%[^\n]", mime, app);
            oldfile[mime] = app;
        }
        fclose(f);
    }

    for (index = 0; index < kNumMime; index++) {
        string tempstr = kMimeTypes[index];
        if (oldfile.find(tempstr) != oldfile.end()) {
            if (strncmp(oldfile[tempstr].c_str(), BRANDING_APP_NAME,
                        strlen(BRANDING_APP_NAME)))
                needRewrite = true;
            else
                found[index] = true;
        }
        else
            needRewrite = true;
        
    }

    if (needRewrite) {
        if (askBeforeReclaiming) {
            gdk_threads_enter();

            GTKMessageDialog *oBox = new GTKMessageDialog();
            string oMessage(kNotifyStolen);

            MessageDialogReturnEnum answer;

            answer = oBox->Show(oMessage.c_str(), "Reclaim File Types?",
                                kMessageYesNo, false, false, 
                                "Don't ask me this again");

            if (oBox->GetCheckStatus()) {
                bool setFileTypes = false;

                if (answer == kMessageReturnYes) {
                    setFileTypes = true;
                }
                else {
                    setFileTypes = false;
                }

                context->prefs->SetPrefBoolean(kReclaimFiletypesPref, 
                                               setFileTypes);
                context->prefs->SetPrefBoolean(kAskToReclaimFiletypesPref, 
                                               false);
            }

            delete oBox;
            gdk_threads_leave();

            if (answer == kMessageReturnNo)
                goto failed_reclaim_open;
        }

        sprintf(buffer, "%s %%s\n", BRANDING_APP_NAME); 
        for (index = 0; index < kNumMime; index++) {
            if (found[index])
                continue;
            oldfile[kMimeTypes[index]] = string(buffer);
        }

        f = fopen(mimeTypes.c_str(), "w");
        if (!f)
            goto failed_reclaim_open;

        map<string, string>::iterator i;
        for (i = oldfile.begin(); i != oldfile.end(); i++) {
            if (i->first.size() > 0 && i->first.c_str()[0] != '\n') {
                sprintf(mime, "%s;%s", i->first.c_str(), i->second.c_str());
                fputs(mime, f);
                fputs("\n", f);
            }
        }
        fclose(f);
    }

failed_reclaim_open:
    delete [] buffer;
    delete [] mime;
    delete [] app;   
}
