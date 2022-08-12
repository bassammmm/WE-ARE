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

#define NXBufferInfoValueNotAvailable NSNotFound
/**
 * \ingroup types
 * \brief  This enumeration defines the possible stream type for \c NXBufferInfoMediaType. 
 *
 * \since version 5.24
 */
typedef NS_ENUM(NSUInteger, NXBufferInfoMediaType)
{
	NXBufferInfoMediaTypeVideo = 0x0,	///< Video stream type
	NXBufferInfoMediaTypeAudio = 0x2,	///< Audio stream type
	NXBufferInfoMediaTypeText = 0x3		///< Text stream type
} _DOC_ENUM(NXBufferInfoMediaType);

/**
 * \ingroup types
 * \brief  This enumeration defines the possible buffering state for \c NXBufferingState. 
 *
 * \since version 5.24
 */
typedef NS_ENUM(NSUInteger, NXBufferingState)
{
	NXBufferingStatePaused = 0x0,	// Buffering state : paused
	NXBufferingStateResume = 0x1,	// Buffering state : resume
	
} _DOC_ENUM(NXBufferingState);

/**
 * \brief This class retrieves the specified buffer information.
 * 
 * \note Do not create instance of this class directly. Instead, use the
 *		\c NXStatisticsAPI::bufferInfo property. 
 *
 * <p> Example code: </p>
 * \code
	NXStatisticsAPI *statisticsAPI = [[NXStatisticsAPI alloc] initWithPlayer:player];
	NSUInteger bufferSize = [statisticsAPI.bufferInfo bufferSize:NXBufferInfoMediaTypeAudio];
	...

 * \endcode
 *
 * \see NXStatisticsAPI::bufferInfo
 * \since version 5.24
 */
@interface NXBufferInfo : NSObject

/**
 * \brief  This method gets the buffer size of current media stream. 
 *
 * \param mediaType  The type of current media stream. 
 * \returns The buffer size of current media stream.
 *
 * \since version 5.24
 */
- (NSUInteger) bufferSize:(NXBufferInfoMediaType) mediaType;
/**
 * \brief This method gets the initial buffering size of current media stream. 
 *
 * \param mediaType The type of current media stream.
 * \returns The Initial buffering size of current media stream. 
 * 
 * \since version 5.24
 */
- (NSUInteger) initialBufferingSize:(NXBufferInfoMediaType) mediaType;
/**
 * \brief This method gets the initial buffering time of current media stream.
 * 
 * \param mediaType The type of current media stream.
 * \returns The initial buffering time of current media stream. 
 * 
 * \since version 5.24
 */
- (NSUInteger) initialBufferingTime:(NXBufferInfoMediaType) mediaType;

/**
 * \brief This method gets the buffered size of current media stream.
 *
 * \param mediaType The type of current media stream. 
 *
 * \returns The buffered size.  
 * \since version 5.24
 */
- (NSUInteger) bufferedSize:(NXBufferInfoMediaType) mediaType;

/**
 * \brief This method gets the buffer rate : (Buffered size) * 100 / (Total buffer size), or how much percentage full the current buffer is. 
 * 
 * \param mediaType The type of current media stream. 
 * \returns The buffer rate of current media stream. 
 * 
 * \since version 5.24
 */
- (NSUInteger) bufferRate:(NXBufferInfoMediaType) mediaType;

/**
 * \brief  This method gets the CTS of first frame in the buffer. 
 *
 * \param mediaType The type of current media stream. 
 * \returns The CTS of first frame in the buffer. If there is no frame, return \c NXBufferInfoValueNotAvailable.
 * 
 * \since version 5.24
 */
- (NSUInteger) firstFrameCTS:(NXBufferInfoMediaType) mediaType;

/**
 * \brief  This method gets the CTS of last frame in the buffer.
 *
 * \param mediaType The type of current media stream. 
 * \returns The CTS of last frame in the buffer. If there is no frame, return \c NXBufferInfoValueNotAvailable.
 *
 * \since version 5.24
 */
- (NSUInteger) lastFrameCTS:(NXBufferInfoMediaType) mediaType;
/**
 * \brief This method gets the total duration of frames in the buffer. 
 *
 * \param mediaType The type of current media stream. 
 * \returns The total duration of all the frames in the buffer, in \c milliseconds.
 *
 * \since version 5.24
 */
- (NSUInteger) totalDuration:(NXBufferInfoMediaType) mediaType;

/**
 * \brief This method gets the total count of frames in the buffer.
 * 
 * \param mediaType The type of current media stream. 
 * \returns The  total count of all the frames in the buffer. 
 * 
 * \since version 5.24
 */
- (NSUInteger) totalFrameCount:(NXBufferInfoMediaType) mediaType;
/**
 * \brief  This method gets the buffering state of current media content. 
 *
 * \param mediaType The type of current media stream. 
 * \returns The buffering state of the current media content. 
 * 
 * \since version 5.24
 */
- (NXBufferingState) bufferingState:(NXBufferInfoMediaType) mediaType;

@end


