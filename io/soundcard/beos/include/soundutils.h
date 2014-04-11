// $Id: soundutils.h,v 1.2 1999/10/19 07:13:02 elrod Exp $
#ifndef INCLUDED_SOUND_UTILS_H
#define INCLUDED_SOUND_UTILS_H

#include "config.h"
#include <support/SupportDefs.h> 

class OutputInfo;

status_t get_audio_format( const OutputInfo* info, media_raw_audio_format* format );

#endif // _SOUND_UTILS_H
