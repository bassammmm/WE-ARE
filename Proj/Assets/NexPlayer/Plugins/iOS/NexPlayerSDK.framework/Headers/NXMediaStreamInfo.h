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


#import <Foundation/Foundation.h>
#import "NXTypes.h"
#import "NXTrackInfo.h"

/**
 * \brief   Information about a media stream
 *
 * For some local formats, and some streaming formats, multiple alternate
 * media streams may be available.  For example, audio may be available in
 * multiple languages.
 *
 * Media streams are described by NXMediaStreamInfo objects.  The list of
 * streams available can be found in NXContentInfo::streams, and the currently
 * selected audio and video streams can be found in NXContentInfo::currentVideoStream
 * and NXContentInfo::currentAudioStream, respectively.
 *
 * Streams may contain multiple tracking comprising the same media encoded at different
 * quality levels. This allows the player to automatically switch between tracks
 * based on the quality of the network connection and the available bandwidth.
 *
 * The full list of tracks available for a stream is in the array
 * NXMediaStreamInfo::tracks; the current track that has been automatically
 * selected by the player is in NXMediaStreamInfo::currentTrack
 *
 * Some streaming formats support variations on the content (not merely the
 * encoding). Tracks that contain different content are marked with custom
 * attributes to distinguish them from tracks that are merely variations in
 * quality.
 *
 */
@interface NXMediaStreamInfo : NSObject 

/**
 * \brief   An internal numeric ID that uniquely identifies
 *          a stream.
 *
 * This can be used to determine if two different NXMediaStreamInfo objects
 * refer to the same stream:
 * \code
    if( [mediaStreamInfoA internalId] == [mediaStreamInfoB internalId] ) {
        // mediaStreamInfoA and mediaStreamInfoB refer to the same stream
    }
 * \endcode
 *
 * However, since a given NXContentInfo object can only refer to one set of
 * NXMediaStreamInfo objects (one per stream), it is generally safe to simply
 * test for identity:
 *
 * \code
 *  if( [contentInfo.streams objectAtIndex:i] == contentInfo.currentAudioStream )
 *  {
 *      // The object at index i is the current audio stream
 *  }
 * \endcode
 *
 * The actual integer value that appears here is arbitrary and may be any
 * 32-bit value.  The method for assigning the internal ID may change in future
 * versions.
 */
@property (nonatomic,assign) unsigned int	internalId;

/**
 * \brief   The type of stream (NXMediaTypeAudio or NXMediaTypeVideo).
 */
@property (nonatomic,assign) NXMediaType	type;

/**
 * \brief   The name of the stream.
 *
 * Not all streaming formats include stream names, so it is possible for the
 * stream name to be empty.
 */
@property (nonatomic,strong) NSString*		name;

/**
 * \brief   The language of the stream.
 *
 * Some stream formats may not include language information.  The exact format
 * of the language string depends on the format of the content and the options
 * chosen by the author of the stream.
 */
@property (nonatomic,strong) NSString*		language;

/**
 * \brief   The current track in use for this stream.
 */
@property (nonatomic,strong) NXTrackInfo*	currentTrack;

/**
 * \brief   The set of custom attributes associated with the current track.
 */
@property (nonatomic,strong) NSDictionary*	currentCustomAttr;

/**
 * \brief   An array of NXTrackInfo objects listing all tracks available for
 *          this stream.
 */
@property (nonatomic,strong) NSArray*		tracks;

/**
 * \brief   An array of NSDictionary objects, each representing one possible
 *          combination of valid custom attributes that can be selected for
 *          this stream.
 */
@property (nonatomic,strong) NSArray*		customAttrSets;

/**
 * \brief   Numeric IDs for each supported combination of custom attributes
 *          as an array of NSNumber objects.
 *
 * These are internal identifiers and their use is discouraged except for
 * debugging and diagnostic purposes.
 */
@property (nonatomic,strong) NSArray*		customAttrSetIDs;

/**
 * \brief  This is the INSTREAM-ID TAG of the media stream.
 *
 * This is an arbitrary value set by the
 * author, and is intended for user display (to allow users to
 * select among different alternative streams).
 *
 * \since version 5.33
 */
@property (nonatomic, strong) NSString*		inStreamID;

/**
 * \brief The type of codec available in the stream.
 *
 * it will be set to NXTypes::(NXCodecID)NXCodecID_UNKNOWN until the stream is downloaded.
 * If this is for CEA 608/708 captions embedded in the content, it will be represented as NXTypes::(NXCodecID)NXCodecID_TEXT_CC_CEA
 *
 * \since version 5.33
 */
@property (nonatomic, assign) NXCodecID		representCodecType;


/** \brief Formats the media stream information as a multi-line string that
 *          can be displayed to the user or logged for diagnostic
 *          information.
 *
 * The string includes all of the details included in NXMediaStreamInfo.
 *
 * The string should be displayed in a fixed-pitch font for best results.
 *
 * \return The media stream information formatted as a string.
 */
- (NSString*)infoAsMultiLineString;

@end
