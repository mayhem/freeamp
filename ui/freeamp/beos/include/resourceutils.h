/* $Id: resourceutils.h,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $ */
#ifndef _RESOURCE_UTILS_H
#define _RESOURCE_UTILS_H

#include <be/support/SupportDefs.h>

class BBitmap;

class ResourceUtils
{
public:
	static BBitmap*		GetBitmap(
								const char*	imageName,
								uint32		type,
								int32		id
								);

protected:
	static status_t		FindPathFor(
								const char*	imageName,
								char*		path
								);

private:
};

#endif // _RESOURCE_UTILS_H
// vi: set ts=4:
