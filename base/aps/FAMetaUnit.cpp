/*____________________________________________________________________________
        
        FreeAmp - The Free MP3 Player

        Portions Copyright (C) 2000 Relatable

        This program is free software; you can redistribute it and/or modify
        it under the terms of the GNU General Public License as published by
        the Free Software Foundation; either version 2 of the License, or
        (at your option) any later version.

        This program is distributed in the hope that it will be useful,
        but WITHOUT ANY WARRANTY; without even the implied warranty of
        MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
        GNU General Public License for more details.

        You should have received a copy of the GNU General Public License
        along with this program; if not, Write to the Free Software
        Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA.
        
        $Id: FAMetaUnit.cpp,v 1.1.6.1 2000/09/28 13:13:27 ijr Exp $
____________________________________________________________________________*/


// FAMetaUnit.cpp: implementation of the FAMetaUnit class.
//
//////////////////////////////////////////////////////////////////////

#include "FAMetaUnit.h"
#include "aps.h"
#include "apsmetadata.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

FAMetaUnit::FAMetaUnit()
{
}

// Takes the MetaData and URL structures to initialize data
FAMetaUnit::FAMetaUnit(MetaData* pMetaData, const char* pczURL)
{
    if ((pMetaData != NULL) && ( pczURL != NULL))
        FillData(pMetaData, pczURL);
}

// takes only the PlaylistItem structure to initialize data
FAMetaUnit::FAMetaUnit(PlaylistItem* pPlayItem)
{
    if (pPlayItem != NULL)
        FillData(pPlayItem);
}

FAMetaUnit::~FAMetaUnit()
{
    // Nothing
}

// copies data to the APSMetaData structure
uint32 FAMetaUnit::FillData(MetaData* pMetaData, const char* pczURL )
{
    if ((pMetaData == NULL) || ( pczURL == NULL)) 
        return APS_PARAMERROR;

    SetAlbum(pMetaData->PeekAlbum());
    SetArtist(pMetaData->PeekArtist());
    SetTitle(pMetaData->PeekTitle());
    SetGenre(pMetaData->PeekGenre());
    SetComment(pMetaData->PeekComment());
    SetFilename(pczURL);
    SetGUID(pMetaData->PeekGUID());
    SetLength(pMetaData->Time());
    SetPlayCount(pMetaData->PlayCount());
    SetTrack(pMetaData->Track());
    SetYear(pMetaData->Year());

    return APS_NOERROR;
}

// copies data to the APSMetaData structure
uint32 FAMetaUnit::FillData(PlaylistItem* pPlayItem)
{
    if (pPlayItem == NULL) 
        return APS_PARAMERROR;

    MetaData mdTemp = pPlayItem->GetMetaData();

    SetAlbum(mdTemp.PeekAlbum());
    SetArtist(mdTemp.PeekArtist());
    SetTitle(mdTemp.PeekTitle());
    SetGenre(mdTemp.PeekGenre());
    SetComment(mdTemp.PeekComment());
    SetFilename(pPlayItem->URL().c_str());
    SetGUID(mdTemp.PeekGUID());
    SetLength(mdTemp.Time());
    SetPlayCount(mdTemp.PlayCount());
    SetTrack(mdTemp.Track());
    SetYear(mdTemp.Year());

    return APS_NOERROR;
}

// Fills the pMetaData structure with information from FAMetaUnit
uint32 FAMetaUnit::GetMetaData(MetaData *pMetaData)
{
    if (pMetaData == NULL) 
        return APS_PARAMERROR;

    pMetaData->SetAlbum(Album().c_str());
    pMetaData->SetArtist(Artist().c_str());
    pMetaData->SetTitle(Title().c_str());
    pMetaData->SetGenre(Genre().c_str());
    pMetaData->SetComment(Comment().c_str());
    pMetaData->SetGUID(GUID().c_str());
    pMetaData->SetPlayCount(PlayCount());
    pMetaData->SetTime(Length());
    pMetaData->SetTrack(Track());
    pMetaData->SetYear(Year());
	
    return APS_NOERROR;
}
