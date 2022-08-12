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
#import "NXPlayer.h"

@class NXPlayer;

/**
 * \brief   The \c NXWMDRMDescrambler protocol must be adopted and implemented
 *          by objects that provide WM-DRM descrambling services.
 *
 * Any object can adopt this protocol, but it is typically adopted by either
 * the NXPlayerDelegate, or by a dedicated DRM descrambling object.
 *
 * An object that implements this protocol should be assigned to 
 * NXPlayer::WMDRMDescrambler.
 *
 * This protocol supports both payload-level and packet-level descrambling.  The
 * method NXWMDRMDescrambler::DRMType must return a value indicating the type of
 * DRM that an objecting implementing this protocol will provide descrambling
 * services for.
 */
@protocol NXWMDRMDescrambler <NSObject>

/**
 * \brief   Returns a value indicating the type of DRM that the descrambling
 *          method expects.  
 *
 * This may be \c NXDRMTypePayload or \c NXDRMTypePacket (\c NXDRMTypeFrame is
 * not supported).
 */
- (NXDRMType) DRMType;

/**
 * \brief   Descrambles WM-DRM content.
 *
 * The type of data passed for descrambling depends on the value that was
 * returned by NXWMDRMDescrambler::DRMType, but can be either packet data
 * or payload data.
 *
 * \param[in]  player               The calling NXPlayer instance.
 *
 * \param[in]  pInputBuffer         The data to be descrambled
 *
 * \param[in]  uiInputBufferSize    The size of the data, in bytes
 *
 * \param[out] pOutputBuffer        The location at which to place the descrambled 
 *                                  output data.  This may point to the same
 *                                  location as the input buffer, or it may point
 *                                  to a separate location. The size available for
 *                                  the output buffer is the same as the size of
 *                                  the input buffer.  That is, the descrambled data
 *                                  may be smaller than the original data, but
 *                                  not larger.
 *
 * \param[out] puiOutputBufferSize  The size of the descrambled data.  The callback
 *                                  must set this value.  This may be equal to or
 *                                  smaller than \c uiInputBufferSize, but not larger.
 * \param[in] pIVBuffer				The initialization vector.
 * \param dwIVBufferSize			The size (in bytes) of the initialization vector.
 *
 * \returns                         The method should return zero if the data
 *                                  was successfully descrambled.  In the case of
 *                                  an error, it should return -1.  
 */
- (int) descrambleWMDRMForPlayer:(NXPlayer*)player
					 inputBuffer:(unsigned char*)pInputBuffer
				 inputBufferSize:(unsigned int)uiInputBufferSize
					outputBuffer:(unsigned char*)pOutputBuffer
				outputBufferSize:(unsigned int*)puiOutputBufferSize
                   initialVector:(unsigned char*)pIVBuffer
               initialVectorSize:(unsigned int)dwIVBufferSize;

@end
