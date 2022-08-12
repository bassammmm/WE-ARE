/******************************************************************************
 ______________________________________________________________________________
 |                                                                            |
 |                                                                            |
 |          Copyrightⓒ 2002-2019 NexPlayer Corp. All rights reserved.      |
 |                        http://www.nexsplayer.com                         |
 |                                                                            |
 |____________________________________________________________________________|
 
 ******************************************************************************
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *****************************************************************************/


#import <UIKit/UIKit.h>

/**
 * \brief   A protocol you can implement if you wish to implement ASF
 *          PlayReady descrambling.
 *
 * See NXPlayer::asfPlayReadyDescrambler for additional information.
 */
@protocol NXAsfPlayReadyDescrambler

/**
 * \brief   Must return one of \c NXDRMTypePayload, \c NXDRMTypePacket or
 *          \c NXDRMTypeFrame.  This is the type of input that will be
 *          passed to the descrambling function.
 */
- (NXDRMType) DRMType;

/**
 * \brief   Called by the player when there is data available for
 *          descrambling.
 *
 * Note that the descramble method will be called for all data of
 * the requested type (specified by NXAsfPlayReadyDescrambler::DRMType)
 * even if the data is not encrypted.  This is because the player has
 * no way to determine if the data is cleartext or encrypted.  This
 * method must make that determination separately.
 *
 * \param player                    The NXPlayer instance that this descrambler 
 *                                  has been assigned to.
 * \param[in] pInputBuffer          The original (possibly scrambled) input data.
 * \param[in] uiInputBufferSize     The size (in bytes) of the input buffer.
 * \param[out] pOutputBuffer        The location at which to write the descrambled
 *                                  output data. Note that this may overlap or
 *                                  be the same as the input buffer location.
 * \param[out] puiOutputBufferSize  The size of the descrambled data.  The callback
 *                                  must set this value.  This may be equal to or
 *                                  smaller than \c uiInputBufferSize, but not larger.
 * \param[in] pIVBuffer             The initial vector.
 * \param[in] dwIVBufferSize        The size (in bytes) of the initial vector
 * \return                          0 if successful, -1 if there was an error
 */
- (int) descramblePlayReadyAsfForPlayer:(NXPlayer*)player
							inputBuffer:(unsigned char*)pInputBuffer
						inputBufferSize:(unsigned int)uiInputBufferSize
						   outputBuffer:(unsigned char*)pOutputBuffer
					   outputBufferSize:(unsigned int*)puiOutputBufferSize
						  initialVector:(unsigned char*)pIVBuffer
					  initialVectorSize:(unsigned int)dwIVBufferSize;

@end

