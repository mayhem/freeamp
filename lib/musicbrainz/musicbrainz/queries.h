/* --------------------------------------------------------------------------

   MusicBrainz -- The Intenet music metadatabase

   Copyright (C) 2000 Robert Kaye
   
   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public
   License as published by the Free Software Foundation; either
   version 2.1 of the License, or (at your option) any later version.
   
   This library is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.
   
   You should have received a copy of the GNU Lesser General Public
   License along with this library; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

     $Id: queries.h,v 1.2 2000/09/21 13:03:03 robert Exp $

----------------------------------------------------------------------------*/
#ifndef _QUERIES_H_
#define _QUERIES_H_

#define MUSICBRAINZ_VERSION "musicbrainz_client/1.0.0-pre1"

// local query names
#define MB_GetCDInfo              "@CDINFO@"
#define MB_GetCDTOC               "@LOCALCDINFO@"
#define MB_AssociateCD            "@CDINFOASSOCIATECD@"

// local query xql queries
#define MB_LocalGetId             "/rdf:RDF/MQ:Args/@id"
#define MB_LocalGetLastTrack      "/rdf:RDF/MQ:Args/@last"
#define MB_LocalGetFirstTrack     "/rdf:RDF/MQ:Args/@first"

// description context queries
#define MB_GetArtistName          "DC:Creator"
#define MB_GetArtistID            "DC:Identifier/@artistId"

#define MB_GetAlbumName           "MM:Album"
#define MB_GetAlbumID             "DC:Identifier/@albumId"

#define MB_GetTrackID             "DC:Identifier/@trackId"
#define MB_GetTrackNum            "DC:Relation/@track"
#define MB_GetTrackName           "DC:Title"
#define MB_GetNumTracks           "MM:Album/@numTracks"

#define MB_GetGUID                "DC:Identifier/@guid"
#define MB_GetFilename            "DC:Identifier/@fileName"
#define MB_GetDuration            "DC:Format/@duration"
#define MB_GetYear                "DC:Date/@issued"
#define MB_GetGenre               "MM:Genre"
#define MB_GetDescription         "DC:Description"
#define MB_GetLyricSubmittor      "DC:Contributor"
#define MB_GetLyricSubmitDate     "DC:Date"
#define MB_GetLyricType           "DC:Type/@type"
#define MB_GetLyricText           "MM:SyncText"
#define MB_GetLyricTimestamp      "MM:SyncText/@ts"

// Track selectors for queries that return an album
#define MB_SelectFirstTrack       "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[]/rdf:Description/rdf:Seq/rdf:li[0]/rdf:Description"
#define MB_SelectNextTrack        "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[]/rdf:Description/rdf:Seq/rdf:li[+1]/rdf:Description"

// Item selectors for queries that return a list of items
#define MB_SelectFirstItem        "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[0]/rdf:Description"
#define MB_SelectNextItem         "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[+1]/rdf:Description"

// Item selectors for queries that return a list of items
#define MB_SelectExchangedData    "/rdf:RDF/rdf:Description"

// Item selectors for lyric queries
#define MB_SelectTrackInfo        "/rdf:RDF/rdf:Description"
#define MB_SelectLyricInfo        "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Description"
#define MB_SelectFirstSyncEvent   "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Description/rdf:Seq/rdf:li[0]/rdf:Description"
#define MB_SelectNextSyncEvent    "/rdf:RDF/rdf:Description/MM:SyncEvents/rdf:Description/rdf:Seq/rdf:li[+1]/rdf:Description"

// GUID selectors for queries that return a list of GUIDS
#define MB_SelectFirstGUID        "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[0]/rdf:Description"
#define MB_SelectNextGUID         "/rdf:RDF/rdf:Description/MC:Collection/rdf:Bag/rdf:li[+1]/rdf:Description"

// Lookup queries
#define MB_GetCDInfoFromCDIndexID "<MQ:Query>GetCDInfoFromId</MQ:Query>\n"     \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_FindArtistByName       "<MQ:Query>FindArtistByName</MQ:Query>\n"    \
                                  "<MQ:Args artist=\"@1@\"/>\n"
#define MB_FindAlbumByName        "<MQ:Query>FindAlbumByName</MQ:Query>\n"     \
                                  "<MQ:Args album=\"@1@\" artist=\"@2@\"/>\n"
#define MB_FindAlbumsByArtistName "<MQ:Query>FindAlbumsByArtistName</MQ:Query>\n"\
                                  "<MQ:Args artist=\"@1@\"/>"      
#define MB_FindTrackByName        "<MQ:Query>FindTrackByName</MQ:Query>\n"     \
                                  "<MQ:Args album=\"@3@\" artist=\"@2@\"\n"    \
                                  "         track=\"@1@\"/>\n"
#define MB_FindDistinctGUID       "<MQ:Query>FindDistinctGUID</MQ:Query>\n"    \
                                  "<MQ:Args artist=\"@2@\"\n"    \
                                  "         track=\"@1@\"/>\n"
#define MB_GetArtistById          "<MQ:Query>GetArtistById</MQ:Query>\n"       \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetAlbumById           "<MQ:Query>GetAlbumById</MQ:Query>\n"        \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetAlbumsByArtistId    "<MQ:Query>GetAlbumsByArtistId</MQ:Query>\n" \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_GetTrackById           "<MQ:Query>GetTrackById</MQ:Query>\n"        \
                                  "<MQ:Args id=\"@1@\"/>\n"
#define MB_ExchangeMetadata       "<MQ:Query>ExchangeMetadata</MQ:Query>\n"    \
                                  "<DC:Title>@1@</DC:Title>\n"                 \
                                  "<DC:Identifier guid=\"@2@\" \n"             \
                                  "               fileName=\"@3@\"/>\n"        \
                                  "<DC:Creator>@4@</DC:Creator>\n"             \
                                  "<MM:Album>@5@</MM:Album>\n"                 \
                                  "<DC:Relation track=\"@6@\"/>\n"             \
                                  "<DC:Format duration=\"@7@\"/>\n"            \
                                  "<DC:Date issued=\"@8@\"/>\n"                \
                                  "<MM:Genre>@9@</MM:Genre>\n"                 \
                                  "<DC:Description>@10</DC:Description>\n"    
#define MB_GetLyricsById          "<MQ:Query>GetLyricsById</MQ:Query>\n"       \
                                  "<MQ:Args id=\"@1@\"/>\n"

#endif

