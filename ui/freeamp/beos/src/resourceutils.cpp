/* $Id: resourceutils.cpp,v 1.1.2.1 1999/08/06 08:31:40 hiro Exp $ */

#include <string.h>

#define DEBUG 1
#include <be/support/Debug.h>
#include <be/kernel/image.h>
#include <be/storage/File.h>
#include <be/storage/Resources.h>
#include <be/support/DataIO.h>
#include <be/translation/TranslationUtils.h>

#include "resourceutils.h"

#if DEBUG
#include <string.h>
#define REPORT_ERROR(a) fprintf( stderr, "ERROR: %s at line %d : %s\n", __FILE__, __LINE__, strerror(a) )
#else
static inline void REPORT_ERROR( int a ) {}
#endif

BBitmap*
ResourceUtils::GetBitmap(
						const char*	imageName,
						uint32		type,
						int32		id
						)
{
	status_t	err;
	char		path[ MAXPATHLEN ];

	if ( ( err = FindPathFor( imageName, path ) ) < B_NO_ERROR )
	{
		REPORT_ERROR( err );
		return NULL;
	}

	BFile		file( path, B_READ_ONLY );
	if ( ( err = file.InitCheck() ) < B_OK )
	{
		REPORT_ERROR( err );
		return NULL;
	}

	BResources	res;
	if ( ( err = res.SetTo( &file ) ) < B_OK )
	{
		REPORT_ERROR( err );
		return NULL;
	}

	size_t		size;
	const void*	data;
	data = res.LoadResource( type, id, &size );
	if ( data == NULL )
	{
		REPORT_ERROR( B_BAD_VALUE );
		return NULL;
	}

	BMemoryIO	resIO( data, size );
	return BTranslationUtils::GetBitmap( &resIO );
}

status_t
ResourceUtils::FindPathFor( const char* imageName, char* path )
{
	status_t	err;
	image_info	info;
	int32		cookie = 0;

	while ( ( err = get_next_image_info( 0, &cookie, &info ) ) == B_OK )
	{
		if ( strstr( info.name, imageName ) != NULL )
		{
			strcpy( path, info.name );
			PRINT(( "found %s matching %s\n", path, imageName ));
			return B_NO_ERROR;
		}
	}

	if ( err == B_OK ) err = B_NAME_NOT_FOUND;
	REPORT_ERROR( err );
	return err;
}
