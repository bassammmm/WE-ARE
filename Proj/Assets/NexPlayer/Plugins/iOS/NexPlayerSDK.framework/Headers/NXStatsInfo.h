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

/**
 * \brief  This interface provides playback statistics about the current content in NexPlayer&trade;.
 * 
 * This interface can be used to retrieve playback statistics such as the decoded frame rate and the rate of frames
 * being rendered in the player over a short interval of content playback, which may be useful in monitoring player 
 * performance and user experience.
 * 
 * \see NXPlayer.h/statsInfo
 * \since version 5.20
 */
@interface NXStatsInfo : NSObject {

}
/**
 * Number of video frames decoded by NexPlayer&trade;&nbsp;during the last interval of content.
 * 
 * The default interval of content is 2 \c seconds.
 * 
 * \since version 5.20
 * \deprecated Use \c decodedVideoFramesLastInterval Instead.
 */
@property (nonatomic, readonly) NSUInteger numDecodingVideoFrames;

/**
 * Number of video frames decoded by NexPlayer&trade;&nbsp;during the last interval of content.
 *
 * The default interval of content is 2 \c seconds.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger decodedVideoFramesLastInterval;

/**
 * 
 * Number of video frames rendered and displayed by NexPlayer&trade;&nbsp;over the last interval of content.
 * 
 * Even though data for more frames of current content may be decoded during an interval, it may be necessary
 * at times for some frames to be skipped in certain circumstances, and this value provides clearer information about what is actually
 * displayed by NexPlayer&trade;.
 * 
 * \since version 5.20 
 * \deprecated Use \c renderedVideoFramesLastInterval Instead.
 */
@property (nonatomic, readonly) NSUInteger numRenderingVideoFrames;

/**
 *
 * Number of video frames rendered and displayed by NexPlayer&trade;&nbsp;over the last interval of content.
 *
 * Even though data for more frames of current content may be decoded during an interval, it may be necessary
 * at times for some frames to be skipped in certain circumstances, and this value provides clearer information about what is actually
 * displayed by the NexPlayer&trade;.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger renderedVideoFramesLastInterval;

/**
 * \brief  The average number of video frames decoded per second.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) double decodedVideoFramesPerSec;

/**
 * \brief The average number of video frames displayed per second.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) double renderedVideoFramesPerSec;

/**
 * \brief  The total number of video frames displayed during playing a video content.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger totalRenderedVideoFrames;

/**
 * \brief  The total number of video frames decoded to play a video content.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger totalDecodedVideoFrames;

/**
 * \brief  The total number of video frames skipped while playing a video content.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger totalDroppedVideoFrames;

/**
 * \brief  The average time took to decode a video frame.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger avgTimeDecodingVideoFrames;

/**
 * \brief The average time took to render a video frame.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger avgTimeRenderingVideoFrames;

/**
 * \brief The time took to decode a video frame.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger timeDecodingSingleVideoFrame;

/**
 * \brief The time took to render a video frame.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger timeRenderingSingleVideoFrame;

/**
 * \brief The average bitrate of the video currently playing.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger avgVideoBitrate;


/**
 * \brief The total size of all the video frames of a video content, in \c bytes.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger totalVideoFrameBytes;

/**
 * \brief The average bitrate of the audio content currently playing.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger avgAudioBitrate;

/**
 * \brief The total size of all the audio frames, in \c bytes.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger totalAudioFrameBytes;

/**
 * \brief The number of video frames available to be decoded during the last interval of content.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger videoFramesLastInterval;

/**
 * \brief The total number of video frames to decode.
 *
 * \since version 5.24
 */
@property (nonatomic, readonly) NSUInteger totalVideoFrames;

@end
