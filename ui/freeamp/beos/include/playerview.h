/* $Id: playerview.h,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $ */
#ifndef _FREEAMPUI_BEOS_PLAYERVIEW_H
#define _FREEAMPUI_BEOS_PLAYERVIEW_H

#include <be/interface/View.h>

class PlayerView : public BView
{
public:
						PlayerView( BBitmap* bitmap );
	virtual				~PlayerView();
	virtual void		AttachedToWindow( void );
	virtual void		Draw( BRect updateRect );
	virtual void		MouseDown( BPoint point );
	virtual void		MouseMoved(
									BPoint			point,
									uint32			transit,
									const BMessage*	message
									);
	virtual void		MouseUp( BPoint point );

protected:

private:
	BBitmap*			m_bitmap;

	// for window dragging
	bool				m_dragging;
	BPoint				m_hotSpot;
};

#endif // _FREEAMPUI_BEOS_PLAYERVIEW_H
// vi: ts=4
