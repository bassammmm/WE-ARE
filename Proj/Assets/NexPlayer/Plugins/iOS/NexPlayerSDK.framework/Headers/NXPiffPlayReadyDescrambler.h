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
 * \brief   A protocol you can implement if you wish to implement Piff PlayReady descrambling.
 *
 * See NXPlayer::piffPlayReadyDescrambler for additional information.
 *
 * \since 5.9
 */

@protocol NXPiffPlayReadyDescrambler <NSObject>

/**
 * \brief   Called by the player when there is Piff PlayReady data available for
 *          descrambling.
 *
 * This is called every time Piff PlayReady data is received, regardless of whether or not the content is encrypted.
 * It is the responsibility of this callback to determine whether or not the data is encrypted and
 * descramble the data if necessary.
 *
 * \param player  The NXPlayer instance that this descrambler has been assigned to.
 * \param[in] pInputBuffer  	The original (possibly scrambled) input data.
 * \param uiInputBufferSize 	The size (in bytes) of the input buffer.
 * \param[out] pOutputBuffer	The location at which to write the descrambled output
 *								data.  Note that this may overlap or be the same as
 *								the input buffer location.
 * \param[out] 	puiOutputBufferSize The size of the descrambled data. The callback must
 *								set this value.  This may be equal to or smaller than
 *								\c uiInputBufferSize, but not larger.
 * \param[out] pSampleEncBox	The \c SampleEncryptionBox, as detailed in the <i>[MS-SSTR] Smooth
 *								Streaming Protocol Specification</i>.
 * \param dwSampleEncBoxLen		The length, in bytes, of the data at \c pSampleEncBox
 * \param dwSampleIDX			The index of the media object (frame or sample, depending on
 *								media format) being descrambled.
 * \param dwTrackID				Media Track ID, from \c TfhdBox, as defined in the <i>[MS-SSTR]
 *								Smooth Streaming Protocol Specification</i>.
 *
 */

- (NSInteger)descramblePiffPlayReadyForPlayer:(NXPlayer*)player
                                      inputBuffer:(unsigned char*)pInputBuffer
                                  inputBufferSize:(unsigned int)uiInputBufferSize
                                     outputBuffer:(unsigned char*)pOutputBuffer
                                 outputBufferSize:(unsigned int*)puiOutputBufferSize
                                     sampleEncBox:(unsigned char*)pSampleEncBox
                                  sampleEncBoxLen:(unsigned int)dwSampleEncBoxLen
                                      sampleIndex:(unsigned int)dwSampleIDX
                                          trackID:(unsigned int)dwTrackID;

@end
