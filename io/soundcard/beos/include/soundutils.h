// $Id: soundutils.h,v 1.1.12.1 1999/09/09 02:42:08 elrod Exp $
#ifndef INCLUDED_SOUND_UTILS_H
#define INCLUDED_SOUND_UTILS_H

#include "config.h"
#include <support/SupportDefs.h> 

class OutputInfo;

status_t get_audio_format( const OutputInfo* info, media_raw_audio_format* format );

#endif // _SOUND_UTILS_H
