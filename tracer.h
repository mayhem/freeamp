#ifndef __TRACER_H_
#define __TRACER_H_

#include <iostream>
#include <glib.h>

inline void _real_assert(bool b,const char *file,int line,
                         const char *func, const char *msg) 
{
    if (!b) {
	cerr << endl << "! " << msg << " failed : " << file 
             << " : " << line << " : " << func << endl << flush;
	exit(1);
    }
}

inline void _real_message(const char *file,int line,
                          const char *func, const char *msg) 
{
    cerr << "$ Message : " << file << " : "
         << line << " : " << func << " : " << msg << endl << flush;
}

// Macros to help debug that call the above functions

#define _assert(__f__) _real_assert((__f__),__FILE__,__LINE__, \
 G_GNUC_PRETTY_FUNCTION,"_assert " #__f__)

#define _nullChk(__p__) _real_assert(NULL!=(__p__),__FILE__,__LINE__, \
 G_GNUC_PRETTY_FUNCTION,"_nullChk " #__p__)

#define _message(__m__) _real_message(__FILE__,__LINE__, \
 G_GNUC_PRETTY_FUNCTION,__m__)

#define _never_get_here _real_assert(false,__FILE__,__LINE__, \
 G_GNUC_PRETTY_FUNCTION,"_never_get_here")

// Execution tracing macros for debugging
#define _you_are_here do { cerr << "@ " << __FILE__ << " : " << __LINE__ \
 << " : " << G_GNUC_PRETTY_FUNCTION << endl; } while(0)

#define _show_args0() _you_are_here;

#define _show_args1(Arg1)  do { _you_are_here; cerr << "args: " \
 << #Arg1 << "=" << (Arg1) \
 << endl << flush; } while (0)

#define _show_args2(Arg1,Arg2)  do { _you_are_here; cerr << "args: " \
 << #Arg1 << "=" << (Arg1)  \
 << ", " << #Arg2 << "=" << (Arg2) \
 << endl << flush; } while (0)

#define _show_args3(Arg1,Arg2,Arg3) do { _you_are_here; \
 cerr << "args: " \
 << #Arg1 << "=" << (Arg1)  \
 << ", " << #Arg2 << "=" << (Arg2) \
 << ", " << #Arg3 << "=" << (Arg3) \
 << endl << flush; } while (0)

#define _show_args4(Arg1,Arg2,Arg3,Arg4) do { _you_are_here; \
 cerr << "args: " \
 << #Arg1 << "=" << (Arg1)  \
 << ", " << #Arg2 << "=" << (Arg2) \
 << ", " << #Arg3 << "=" << (Arg3) \
 << ", " << #Arg4 << "=" << (Arg4) \
 << endl << flush; } while (0)

#define _show_args5(Arg1,Arg2,Arg3,Arg4,Arg5) do { _you_are_here; \
 cerr << "args: " \
 << #Arg1 << "=" << (Arg1)  \
 << ", " << #Arg2 << "=" << (Arg2) \
 << ", " << #Arg3 << "=" << (Arg3) \
 << ", " << #Arg4 << "=" << (Arg4) \
 << ", " << #Arg5 << "=" << (Arg5) \
 << endl << flush; } while (0)

#endif






