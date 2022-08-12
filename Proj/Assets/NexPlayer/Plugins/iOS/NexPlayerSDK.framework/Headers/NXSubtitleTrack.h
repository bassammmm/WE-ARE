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

#define kNXSubtitleTrackLanguageAll (@"ALL")
#define kNXSubtitleTrackLanguageNone (@"NONE")

/**
 * \brief   Represents a subtitle track available for the current content.
 *
 * Note that this is not the same as the text track associated with streaming
 * content. Although the two have a similar end result, functionally they are
 * different and are implemented with different mechanisms.
 *
 * For more information on local subtitles, see NXPlayer::subtitleTracks
 *
 * For more information on text tracks for streaming content, see
 * NXPlayer::setVideoStream:audioStream:textStream:trackAttributes:
 *
 */
@interface NXSubtitleTrack : NSObject 
/**
 * \brief   The internal unique ID for this subtitle track (this should generally
 *          not be used, as it is arbitrary and could change).
 */
@property (nonatomic,readonly) unsigned int             internalId;

/**
 * \brief   The language of this track. The format of this string depends on the
 *          subtitle file format.  This may not be available for all subtitle
 *          file formats, and may be nil or @"" in some cases.
 */
@property (strong, nonatomic,readonly) NSString*                language;

/**
 * \brief   The name of this track. The format of this string depends on the
 *          subtitle file format.  This may not be available for all subtitle
 *          file formats, and may be nil or @"" in some cases.
 */
@property (strong, nonatomic,readonly) NSString*                name;

/**
 * \brief   A dictionary containing additional information about this subtitle
 *          track.
 *
 * The information available varies depending on the subtitle file format.  For
 * SMI files, the @"SMIClass" key will be set. 
 */
@property (strong, nonatomic,readonly) NSDictionary*            metadata;

/**
 * \brief   Determines whether or not this track is enabled (included in subtitle
 *          displays).
 *
 * This property can be set to YES to enable this track, or NO to disable this
 * track.  The change will take effect immediately.
 */
@property (nonatomic,readwrite,getter = isEnabled) BOOL enabled;

@end
