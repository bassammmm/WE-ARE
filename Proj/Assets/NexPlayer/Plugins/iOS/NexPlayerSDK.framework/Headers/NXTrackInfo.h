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

/**
 * \brief   Information about a track in a media stream.
 *
 * For any given stream, the list of available tracks is in
 * NXMediaStreamInfo::tracks.
 *
 * Any given stream may have multiple tracks containing the same content
 * encoded at different quality levels to support different network
 * conditions.
 *
 */
@interface NXTrackInfo : NSObject

/**
 * \brief   An internal numeric ID that uniquely identifies
 *          a track.
 *
 * This can be used to determine if two different NXTrackInfo objects
 * refer to the same track:
 * \code
 if( [trackInfoA internalId] == [trackInfoB internalId] ) {
    // trackInfoA and trackInfoB refer to the same stream
 }
 * \endcode
 *
 * However, since a given NXMediaStreamInfo object can only refer to one set of
 * NXTrackInfo objects (one per track), it is generally safe to simply
 * test for identitiy:
 *
 * \code
 *  if( [mediaStreamInfo.tracks objectAtIndex:i] == mediaStreamInfo.currentTrack )
 *  {
 *      // The object at index i is the current track
 *  }
 * \endcode
 *
 * The actual integer value that appears here is arbitrary and may be any
 * 32-bit value.  The method for assigning the internal ID may change in future
 * versions.
 */
@property (nonatomic,assign) unsigned int	internalId;

/**
 * \brief   The set of custom attributes associated with this particular track.
 */
@property (nonatomic,strong) NSDictionary*	customAttributes;

/**
 * \brief   The bandwidth of this track in bit per second.
 */
@property (nonatomic,assign) int			bandwidth;

/**
 * \brief   YES if this track includes audio data; NO if not.
 */
@property (nonatomic,assign) BOOL			hasAudio;

/**
 * \brief   YES if this track includes video data; NO if not.
 */
@property (nonatomic,assign) BOOL			hasVideo;

/**
 * \brief	This indicates the codec used for the given track.
 * \warning Do not trust this value in HLS, DASH and MS Smooth Streaming mode, as invalid values are sometimes provided.
 *
 * \since version 5.33
 */
@property (nonatomic, assign) NXCodecID		codecID;

/**
 * \brief   YES if this track is valid (that is, if the
 *          codecs and bit rates and so on are supported by NexPlayer).
 */
@property (nonatomic,assign) BOOL			valid;

/**
 * \brief   Indicates if the track is a track of IFrames for the video content or not.
 *
 * Possible Values:
 *  - 0: \c FALSE. Not a track of IFrames.
 *  - 1: \c TRUE. A track of IFrames.
 */
@property (nonatomic,assign) BOOL			iFrameTrack;

/**
 * \brief   These indicate if track includes video track, native passes its Width and Height :
 */
@property (nonatomic,assign) unsigned int			width;
@property (nonatomic,assign) unsigned int			height;

/**
 * This indicates if track includes video track and AVC, native passes its Profile and Level :
 */
@property (nonatomic,assign) unsigned int			avcProfile;
@property (nonatomic,assign) unsigned int			avcLevel;

@property (nonatomic,assign) double			frameRate;

@end
