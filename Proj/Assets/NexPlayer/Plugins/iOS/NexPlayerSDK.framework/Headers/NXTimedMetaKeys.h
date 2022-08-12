/******************************************************************************
 ______________________________________________________________________________
 |                                                                            |
 |                                                                            |
 |          Copyrightⓒ 2002-2019 NexPlayer Corp. All rights reserved.         |
 |                        http://www.nexplayer.com                            |
 |                                                                            |
 |____________________________________________________________________________|
 
 ******************************************************************************
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *****************************************************************************/


#ifndef NexPlayerSDK_NXTimedMetaKeys_h
#define NexPlayerSDK_NXTimedMetaKeys_h

/**
 * \defgroup tmkey Timed Metadata Keys
 */

/**
 * \ingroup tmkey
 * \brief  ID3 tags which are stored in the NS Dictionary and can be retrieved using their c\ keys.
 */

/**
 * \ingroup tmkey
 * \brief This key gets the content session information if available. 
 */
static NSString* kNXTimedMetaKeySessionInfo = @"SessionInfo";

/**
 * \ingroup tmkey
 * \brief This key gets the content title if available. 
 */
static NSString* kNXTimedMetaKeyTitle = @"Title";

/**
 * \ingroup tmkey
 * \brief This key gets the content artist, if available. 
 */
static NSString* kNXTimedMetaKeyArtist = @"Artist";

/**
 * \ingroup tmkey
 * \brief This key gets content album information, if available. 
 */
static NSString* kNXTimedMetaKeyAlbum = @"Album";

/**
 * \ingroup tmkey
 * \brief This key gets the content genre if available. 
 */
static NSString* kNXTimedMetaKeyGenre = @"Genre";

/**
 * \ingroup tmkey
 * \brief This key gets the year of content, if available. 
 */
static NSString* kNXTimedMetaKeyYear = @"Year";

/**
 * \ingroup tmkey
 * \brief This key gets content lyrics, if available. 
 */
static NSString* kNXTimedMetaKeyLyrics = @"Lyrics";

/**
 * \ingroup tmkey
 * \brief This key gets the track number, if available. 
 */
static NSString* kNXTimedMetaKeyTrackNum = @"TrackNumber";

/**
 * \ingroup tmkey
 * \brief This key gets the image associated with the content, if available. 
 */
static NSString* kNXTimedMetaKeyImage = @"Picture";

/**
 * \ingroup tmkey
 * \brief This key gets a comment associated with the content, if available. 
 */
static NSString* kNXTimedMetaKeyComment = @"Comment";

/**
 * \ingroup tmkey
 * \brief This key gets text associated with the content, if available. 
 */
static NSString* kNXTimedMetaKeyText = @"Text";

/**
 * \ingroup tmkey
 * \brief This key gets the data from extra tags in metadata if available.
 */
static NSString* kNXTimedMetaKeyPrivateFrame = @"PrivateFrame";

/**
 * \ingroup tmkey
 * \brief This key gets the data from extra tags in metadata if available. 
 */
static NSString* kNXTimedMetaKeyExtraData = @"extraTagData";
#endif
