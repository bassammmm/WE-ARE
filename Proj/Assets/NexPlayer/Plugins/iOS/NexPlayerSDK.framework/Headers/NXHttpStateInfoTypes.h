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

#import "NXError.h"
#import "NXPlayer.h"

/**
 * \ingroup types
 * \brief An enumeration of the possible types of files being handled by NexPlayer&trade;&nbsp; during playback
 *
 * \since version 5.32.x
 */
typedef NS_ENUM(NSUInteger, NXHttpStateInfoFileType)
{
	NXHttpStateInfoFileTypeUnknown				= 0,
	NXHttpStateInfoFileTypeMPD					= 1,
	NXHttpStateInfoFileTypeSegment				= 2,
	NXHttpStateInfoFileTypeInitialSegment		= 3,
	NXHttpStateInfoFileTypeKey					= 4,
	NXHttpStateInfoFileTypeSegmentIndex			= 5
};

/**
 * \ingroup types
 * \brief Possible types of media which can be played by NexPlayer&trade; during playback.
 * The primary use of NXHttpStateInfoMediaType is for representing a media type of NXHttpStateInfoFileTypeSegment.
 *
 * \see \c NXHttpStateInfoDownStart for more details.
 *
 * \since version 5.32.x
 */
typedef NS_OPTIONS(NSUInteger, NXHttpStateInfoMediaType)
{
	NXHttpStateInfoMediaTypeNone				= 0,
	NXHttpStateInfoMediaTypeAudio				= 1 << 0,
	NXHttpStateInfoMediaTypeBaseVideo			= 1 << 1,
	NXHttpStateInfoMediaTypeText				= 1 << 2,
	NXHttpStateInfoMediaTypeEnhancedVideo		= 1 << 3
};


@interface NXHttpStateInfoDownStart : NSObject
	/**
	 * \brief The file type to be downloaded.
	 *
	 * \see \c NXHttpStateInfoFileType for more details.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NXHttpStateInfoFileType fileType;

	/**
	 * \brief The current segment number, as an integer.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NSUInteger segmentNumber;

	/**
	 * \brief The duration of the current segment, as an integer.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NSUInteger segmentDuration;

	/**
	 * \brief The bandwidth of the current track, as an integer.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NSUInteger trackBW;

	/**
	 * \brief The media type of the current content.
	 *
	 * \see \c NXHttpStateInfoMediaType for more details.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NXHttpStateInfoMediaType mediaType;

@end


@interface NXHttpStateInfoDataReceived: NSObject
	/**
	 * \brief The current number of bytes received, as an \c integer.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NSInteger bytesReceived;

	/**
	 * \brief The total bytes of the content to be downloaded. -1 represents unknown.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NSInteger totalSize;
	@end

	@interface NXHttpStateInfoDownEnd: NSObject

	/**
	 * \brief The current number of bytes received, as an \c integer.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NSInteger bytesReceived;

@end

@interface NXHttpStateInfoHttpError: NSObject

	/**
	 * \brief The error code.
	 *
	 * \see \c NXError for more details.
	 *
	 * \since version 5.32.x
	 */
	@property (nonatomic, readonly) NXError errorCode;

@end


/**
 * \brief   A delegate method for NXStatisticsAPI.
 * Implement this to receive HTTP state information.
 * These methods are optional; implement the methods if you wish to receive the HTTP state information.
 *
 * \since 5.32.x
 */
@protocol NXHttpStateDelegate <NSObject>

	@optional
	/**
	 * \brief	This event occurs when NexPlayer started downloading a file which is one of the NXHttpStateInfoFileType.
	 *
	 * \param[in] downStart			The detailed downStart information(see \ref NXHttpStateInfoDownStart).
	 *
	 * \since version 5.32.x
	 *
	 */
	- (void)nexPlayer:(NXPlayer*) nxplayer urlString:(NSString*)URLString stateInfoDownStart:(NXHttpStateInfoDownStart*)downStart;

	/**
	 * \brief	This event occurs when NexPlayer is downloading a file which is one of NXHttpStateInfoFileType.
	 *
	 * \param[in] dataReceived			The detailed dataReceived information(see \ref NXHttpStateInfoDataReceived).
	 *
	 * \since version 5.32.x
	 *
	 */
	- (void)nexPlayer:(NXPlayer*) nxplayer urlString:(NSString*)URLString stateInfoDataReceived:(NXHttpStateInfoDataReceived*)dataReceived;

	/**
	 * \brief	This event occurs when NexPlayer finished downloading a file which is one of NXHttpStateInfoFileType.
	 *
	 * \param[in] downEnd			The detailed downEnd information(see \ref NXHttpStateInfoDownEnd).
	 *
	 * \since version 5.32.x
	 *
	 */
	- (void)nexPlayer:(NXPlayer*) nxplayer urlString:(NSString*)URLString stateInfoDownEnd:(NXHttpStateInfoDownEnd*)downEnd;

	/**
	 * \brief	This event occurs when NexPlayer encountered an error during download.
	 *
	 * \param[in] httpError			The detailed error information(see \ref NXHttpStateInfoHttpError).
	 *
	 * \since version 5.32.x
	 *
	 */
	- (void)nexPlayer:(NXPlayer*) nxplayer urlString:(NSString*)URLString stateInfoHttpError:(NXHttpStateInfoHttpError*)httpError;

@end
