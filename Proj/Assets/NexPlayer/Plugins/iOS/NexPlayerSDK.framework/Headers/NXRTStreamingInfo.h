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
#import "NXPlayer.h"

/**
 * \brief This class manages information about the current streaming content.
 *
 * \since version 5.24
 */
@interface NXRTStreamingInfo: NSObject
/**
 * \brief  Full content of a master manifest file.
 *
 * \since version 5.24
 */
@property (nonatomic, strong, readonly) NSString* masterMpd;
/**
 * \brief  Master manifest URL.
 *
 * \since version 5.24
 */
@property (nonatomic, strong, readonly) NSString* masterMpdUrl;
/**
 * \brief Full content of an initial manifest file.
 *
 * \since version 5.24
 */
@property (nonatomic, strong, readonly) NSString* initialMpd;
/**
 * \brief The actual URI (after all the redirects) for the request of a manifest file.
 *
 * \since version 5.24
 */
@property (nonatomic, strong, readonly) NSString* initialMpdUrl;
/**
 * \brief The description of an initially selected profile.
 *
 * \since version 5.24
 */
@property (nonatomic, strong, readonly) NSString* startSegUrl;
/**
 * \brief The number of times that a content profile has changed to a profile with a higher bitrate. 
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfTrackSwitchUp;
/**
 * \brief The number of times that a content profile has changed to a profile with a lower bitrate.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfTrackSwitchDown;

/**
 * \brief The number of requested segments from the server by the player. 
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentRequest;

/**
 * \brief The number of received segments from the server by the player.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentRecv;
/**
 * \brief The number of segments failed to receive from the server.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentFailToRecv;

/**
 * \brief The bitrate, in \c bps, as specified in the segment profile.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger curTrackBw;

/**
 * \brief  The actual bitrate, in \c bps, of the read segments. The read bitrate is the average speed at which the streaming segments are read from the network server.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger curNetworkBw;

/**
 * \brief The number of the segments with a lower read bitrate than the bitrate specified on the profile.
 *	The read bitrate is the average speed at which the streaming segments are read from the network server.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentDownRate;


/**
 * \brief The number of segments that resulting a timeout.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentTimeout;

/**
 * \brief The number of segments failed to receive during the streaming.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentFailToParse;

/**
 * \brief The total number of redirects. This includes redirects for both the manifest file and the individual segments.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfRedirect;

/**
 * \brief  The total number of segments in the buffer. 
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger numOfSegmentInBuf;

 
/**
 * \brief The number of bytes received from the server by the player.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) uint64_t numOfBytesRecv;
@end
