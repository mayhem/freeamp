/* $Id: playerwindow.h,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $ */
#ifndef _FREEAMPUI_BEOS_PLAYER_WINDOW_H
#define _FREEAMPUI_BEOS_PLAYER_WINDOW_H

#include <be/interface/Window.h>

const uint32	kBeOSUIMsg_PlayStop		= 'plsp';
const uint32	kBeOSUIMsg_Pause		= 'paus';
const uint32	kBeOSUIMsg_Prev			= 'prev';
const uint32	kBeOSUIMsg_Next			= 'next';
const uint32	kBeOSUIMsg_Close		= 'clse';

const uint32	kBeOSUIMsg_InfoPlaying	= 'Iply';
const uint32	kBeOSUIMsg_InfoStopped	= 'Istp';
const uint32	kBeOSUIMsg_InfoPaused	= 'Ipsd';

class FreeAmpUI;

class PlayerWindow : public BWindow
{
public:
						PlayerWindow( const char* title );
	virtual				~PlayerWindow();
	virtual void		MessageReceived( BMessage* message );
	void				SetTarget( FreeAmpUI* target );

protected:
	void				TogglePlayStop( bool isPlaying );

private:
	FreeAmpUI*			m_target;
	BBitmap*			m_bitmapPlayOff;
	BBitmap*			m_bitmapPlayOn;
	BBitmap*			m_bitmapPlayGlow;
	BBitmap*			m_bitmapStopOff;
	BBitmap*			m_bitmapStopOn;
	BBitmap*			m_bitmapStopGlow;
	bool				m_isPlaying;
};

#endif // _FREEAMPUI_BEOS_PLAYER_WINDOW_H
// vi: set ts=4:
