/* $Id: tristatebutton.h,v 1.1.2.2 1999/08/14 08:06:05 hiro Exp $ */
#ifndef _TRI_STATE_BUTTON_H
#define _TRI_STATE_BUTTON_H

#include <be/interface/Control.h>

class TriStateButton : public BControl
{
public:
					TriStateButton(
								BRect		frame,
								const char*	name,
								BBitmap*	offBitmap,
								BBitmap*	onBitmap,
								BBitmap*	glowBitmap,
								bool		ownsBitmaps,
								BMessage*	message
								);
	virtual			~TriStateButton();
	virtual void	AttachedToWindow( void );
	virtual void	Draw( BRect updateRect );
	virtual void	MouseDown( BPoint point );
	virtual void	MouseMoved(
							BPoint			point,
							uint32			transit,
							const BMessage*	message
							);
	virtual void	MouseUp( BPoint point );

	status_t		SetBitmaps(
							BBitmap*	offBitmap,
							BBitmap*	onBitmap,
							BBitmap*	glowBitmap,
							bool		ownsBitmaps
							);

	enum button_state { OFF, ON, GLOW };

protected:
	status_t		CleanBitmaps( void );

private:
	BBitmap*		m_offBitmap;
	BBitmap*		m_onBitmap;
	BBitmap*		m_glowBitmap;
	bool			m_ownsBitmaps;
	button_state	m_state;
	bool			m_mouseDown;
};

#endif // _TRI_STATE_BUTTON_H
