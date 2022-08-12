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
#import "NXTypes.h"
#import "NXPlayer.h"

@class NXPlayer;

/**
 * \ingroup types
 * \brief   Type of data being passed for DRM descrambling.
 *
 * The NXDRMDescrambler protocol handles both audio and video data; this
 * enumeration is used to distinguish between the two when data is passed
 * to the descrambling method.
 *
 * \see NXDRMDescrambler for more details.
 */
typedef enum NXDRMDataType_ {
	NXDRMDataTypeVideo = 0,
	NXDRMDataTypeAudio = 1
} NXDRMDataType;

/**
 * \brief   The \c NXDRMDescrambler protocol must be adopted and implemented
 *          by objects that provide general DRM descrambling services.
 *
 * Any object can adopt this protocol, but it is typically adopted by either
 * the NXPlayerDelegate, or by a dedicated DRM descrambling object.
 *
 * When assigned to NXPlayer::DRMDescrambler, an object that adopts this protocol
 * will be called for each frame of audio or video data before that frame is 
 * decoded.  This provides a general opportunity for descrambling the frame.  
 * For types of DRM where descrambling must occur at a different point in the 
 * playback process or where additional information is needed, more specific
 * descrambling protocols are provided, and should be used instead of this one 
 * where necessary.
 *
 * This protocol comprises only one method, which is called to perform the
 * descrambling.
 */
@protocol NXDRMDescrambler <NSObject>

/**
 * \brief   General method for descrambling  DRM encrypted content.
 *
 * \param[in]  player               The calling NXPlayer instance.
 *
 * \param[in]  type                 The type of frame to be descrambled:
 *                                      - <b>NXDRMDataTypeVideo (0):</b> Video
 *                                      - <b>NXDRMDataTypeAudio (1):</b> Audio
 *
 * \param[in]  pInputBuffer         The encrypted data to be descrambled
 *
 * \param[in]  uiInputBufferSize    The size of the encrypted data, in bytes
 *
 * \param[out] pOutputBuffer        The location at which to place the descrambled 
 *                                  output data.  This may point to the same
 *                                  location as the input buffer, or it may point
 *                                  to a separate location. The size available for
 *                                  the output buffer is the same as the size of
 *                                  the input buffer.  That is, the decrypted data
 *                                  may be smaller than the encrypted data, but
 *                                  not larger.
 *
 * \param[out] puiOutputBufferSize  The size of the decrypted data.  The callback
 *                                  must set this value.  This may be equal to or
 *                                  smaller than \c uiInputBufferSize, but not larger.
 *
 * \returns                         The method should return zero if the data
 *                                  was successfully descrambled.  In the case of
 *                                  an error, it should return -1.
 */
- (int)descrambleDRMForPlayer:(NXPlayer*)player
					 dataType:(NXDRMDataType)type
				  inputBuffer:(unsigned char*)pInputBuffer
			  inputBufferSize:(unsigned int)uiInputBufferSize
				 outputBuffer:(unsigned char*)pOutputBuffer
			 outputBufferSize:(unsigned int*)puiOutputBufferSize;

@end
