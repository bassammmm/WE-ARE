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


#import <UIKit/UIKit.h>
#import <Foundation/Foundation.h>
#import "NXMediaStreamInfo.h"
#import "NXTypes.h"

/**
 * \brief   Information about specific multimedia content.
 *
 * Information about the currently loaded content is available as an
 * \c NXContentInfo object via NXPlayer::contentInfo.
 *
 */
@interface NXContentInfo : NSObject 

/**
 * \brief   The format of the file from which the content was loaded,
 *          if applicable.
 *
 * In cases where there isn't an applicable file format (such as during
 * some kinds of streaming playback) this will have the value
 * \c NXFileFormatNONE.
 *
 * \see NXFileFormat for a list of possible values.
 */
@property (nonatomic,assign) NXFileFormat				fileFormat;

/**
 * \brief   \c YES if the content includes video.
 *
 * In some cases, where the content includes video in a format that
 * NexPlayer&trade; doesn't recognize, this may be \c NO even for
 * content with video.  If this is \c YES, the content includes video, and
 * NexPlayer&trade; is capable of playing back that video.
 */
@property (nonatomic,assign) BOOL						hasVideo;

/**
 * \brief   \c YES if the content includes audio.
 *
 * In some cases, where the content includes audio in a format that
 * NexPlayer&trade; doesn't recognize, this may be \c NO even for
 * content with audio.  If this is \c YES, the content includes audio, and
 * NexPlayer&trade; is capable of playing back that audio.
 */
@property (nonatomic,assign) BOOL						hasAudio;

/**
 * \brief   The number of audio channels in the current content.
 *
 * This is 1 for mono, 2 for stereo.  Some formats may support additional
 * channels.  If the content doesn't include audio, this will be zero.
 */
@property (nonatomic,assign) unsigned int				audioChannels;

/**
 * \brief Width of the original video frames, in pixels.
 */
@property (nonatomic,assign) unsigned int				width;

/**
 * \brief Height of the original video frames, in pixels.
 */
@property (nonatomic,assign) unsigned int				height;

/**
 * \brief Pitch of the original video frames, in pixels.
 *
 * The pitch is the actual pixel width of the video frame, including
 * any hidden margin required by the decoder, and any padding needed to
 * byte-align each row.  Since NexPlayer&trade; handles the display of
 * the video image automatically on iOS, this value is really only useful
 * for diagnostic purposes.
 */
@property (nonatomic,assign) unsigned int				pitch;

/**
 * \brief The audio codec in use for decoding the content.
 *
 * If the content doesn't include audio, or the audio format is
 * not recognized or not supported, this will be zero.
 */
@property (nonatomic,assign) NXCodecID					audioCodec;

/**
 * \brief The video codec in use for decoding the content.
 *
 * If the content doesn't include video, or the video format is
 * not recognized or not supported, this will be zero.
 */
@property (nonatomic,assign) NXCodecID					videoCodec;

/** \brief The types of captions available in the current content.
 *
 * In the current version, only the types listed above will be recognized and if captions in another format exist, this will be
 * set to NXTypes::(NXCodecID)NXCodecID_UNKNOWN.
 *
 * Furthermore, if an external subtitle file is included in addition to another format, this member will be set to the external subtitle type (SMI or SRT).
 *
 * Since CEA 608 and CEA 708 closed captions cannot be identified until decoding begins, \c captionType will also be set to NXTypes::(NXCodecID)NXCodecID_UNKNOWN
 * when they are included in content.
 */
@property (nonatomic,assign) NXCodecID				captionType;

/**
 * \brief Frame rate of the video, in frames per second.
 * 
 * This is the frame rate specified in the content.
 * 
 * If the device isn't powerful enough to decode and
 * display the video stream in real-time, the actual number
 * of displayed frames may be lower than this value.
 * 
 * For the actual number of displayed frames, see
 * NXPlayer::videoPerformanceStats
 */
@property (nonatomic,assign) unsigned int				videoFrameRate;

/** \brief Audio sampling rate in samples per second. */
@property (nonatomic,assign) unsigned int				audioSampleRate;

/** \brief Approximate number of audio samples per video frame. */
@property (nonatomic,assign) unsigned int				approxSamplesPerFrame;

/** \brief Audio bit rate, in bits per second. */
@property (nonatomic,assign) unsigned int				audioBitrate;

/** \brief Video bit rate, in bits per second. */
@property (nonatomic,assign) unsigned int				videoBitrate;

/** \brief Total playing time of the media, if applicable.
 * 
 * For some streaming formats (in particular, live streams) there may
 * not be a duration available.  In this case, the total play time
 * will be \c NXDuration_Unknown.
 */
@property (nonatomic,assign) NXDuration					totalPlayTime;

/** \brief Total size of the content, in bytes, if known. */
@property (nonatomic,assign) long long int				totalContentSize;

/** \brief YES if the content is seekable; NO if it can only be played from the 
 *         beginning (or current position, in the case of live content) */
@property (nonatomic,assign,getter=isSeekable)	BOOL	seekable;

/** \brief YES if the content can be paused. */
@property (nonatomic,assign,getter=isPausable)	BOOL	pausable;

/** \brief  YES if the index table is damaged and operations such as seeking 
 *          may be problematic. 
 *
 * This allows UI components to alert the user of the problem.
 */
@property (nonatomic,assign,getter=isJunkContent) BOOL	junkContent;

/** \brief Number of IFrames encountered so far. */
@property (nonatomic,assign) unsigned int				numIFramesEncountered;

/** \brief Additional metadata associated with the content.
 *
 * The exact contents of this dictionary depend on the content and may
 * change from version to version.  ID3 tag values are an example of one
 * kind of metadata that may be associated with content.
 */
@property (nonatomic,strong) NSDictionary*				metaData;

/** \brief Information about DRM protection associated with the content.
 *
 * The exact contents of this dictionary depend on the type of DRM, and whether
 * it is being handled by NexPlayer&trade; directly.  For DRM handled using
 * custom application-provided descramblers, this dictionary will be empty.
 */
@property (nonatomic,strong) NSDictionary*				DRMInfo;

/** \brief The currently selected video stream within the content.
 *
 * This applies to content with multiple video streams.  This is one of the
 * streams from the NXContentInfo::streams array.
 */
@property (nonatomic,strong) NXMediaStreamInfo*			currentVideoStream;

/** \brief The currently selected audio stream within the content.
 *
 * This applies to content with multiple audio streams.  This is one of the
 * streams from the NXContentInfo::streams array.
 */
@property (nonatomic,strong) NXMediaStreamInfo*			currentAudioStream;

/** \brief The currently selected text stream within the content.
 *
 * This applies to content with multiple text streams.  This is one of the
 * streams from the NXContentInfo::streams array.
 */
@property (nonatomic,strong) NXMediaStreamInfo*			currentTextStream;

/** \brief An array of all audio, video and text streams associated with
 *         the content.
 *
 * Most content has only one video stream and one audio stream, but some
 * file formats and some streaming formats support multiple streams of the
 * same type (for example, to provide audio tracks in multiple languages).
 *
 * In addition, it is possible for some content that this array may be empty,
 * even though there is audio and video associated with the content. In this
 * case, there is no additional information available about the audio or video
 * beyond the basic information in NXContentInfo, and it is not possible to
 * switch to other tracks.
 *
 * Each element in this array is an NXMediaStreamInfo object.
 *
 * To get a list of only one type of media, call NXContentInfo::streamsOfType:
 * instead of using this property.
 */
@property (nonatomic,strong) NSArray*					streams;

/** \brief Formats the content information as a multi-line \c string that
 *          can be displayed to the user or logged for diagnostic
 *          information.
 *
 * The string includes all of the details included in NXContentInfo, as
 * well as details on all of the streams available within.
 *
 * The string should be displayed in a fixed-pitch font for best results.
 *
 * \return the content information formatted as a \c string.
 */
- (NSString*)infoAsMultiLineString;

/** \brief Returns a filtered list of streams containing only streams
 *          of a single specific type.
 *
 * \param[in]   type    The type of stream (NXMediaTypeAudio, NXMediaTypeVideo)
 *                      to return.
 *
 * \return              An array of NXMediaStreamInfo objects, containing only
 *                      the elements of NXContentInfo::streams that match the
 *                      specified media type.
 */
- (NSArray*)streamsOfType:(NXMediaType)type;

/** \brief Convenience method that returns a \c string representation of an NXCodecID, useful
 *          for diagnostic and log output, and for displaying to the user.  Use this for
 *          audio codec IDs. */
+ (NSString*)stringFromAudioCodecID: (NXCodecID)codec_id;

/** \brief Convenience method that returns a \c tring representation of an NXCodecID, useful
 *          for diagnostic and log output, and for displaying to the user.  Use this for
 *          video codec IDs. */
+ (NSString*)stringFromVideoCodecID: (NXCodecID)codec_id;

/** \brief Convenience method that returns a \c string representation of an NXFileFormat, useful
 *          for diagnostic and log output, and for displaying to the user. */
+ (NSString*)stringFromFileFormat: (NXFileFormat)format;

/** \brief Convenience method that returns a \c string representation of an NXCodecID, useful
 *          for diagnostic and log output, and for displaying to the user.  Use this for
 *          caption types. */
+ (NSString*)stringFromCaptionType: (NXCodecID)codec_id;


@end
