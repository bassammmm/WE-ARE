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

/**
 * \brief   A protocol to implement if DECE Ultra Violet descrambling should be implemented.
 *
 * \see NXPlayer::deceUVDescrambler for additional information.
 * 
 * \since 5.16
 */
@protocol NXDeceUVDescrambler


/**
 * \brief   Called by the player when there is DECE Ultra Violet data available for
 *          descrambling.
 *
 * Note that the descramble method will be called for all data of
 * the requested type (specified by NXDRMType)
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
 * \param[in] pSampleEncBox         The \c SampleEncryptionBox, as detailed in <em>[UV] Ultra Violet Protocol Specification</em>.
 * \param[in] dwSampleEncBoxLen     The length, in bytes, of the data in \c pSampleEncBox.
 * \param[in] dwSampleIDX           The index of the media object (frame or sample, depending on the media format) being descrambled. 
 * \param[in] dwTrackID             The Media Track ID, from \c TfhdBox, as defined in <em>[UV] Ultra Violet Protocol Specification</em>.
 * 
 * \return                          0 if successful, -1 if there was an error.
 * 
 * \since 5.16
 */
- (int) descrambleDeceUVForPlayer:(NXPlayer*)player
							inputBuffer:(unsigned char*)pInputBuffer
						inputBufferSize:(unsigned int)uiInputBufferSize
						   outputBuffer:(unsigned char*)pOutputBuffer
					   outputBufferSize:(unsigned int*)puiOutputBufferSize
                    sampleEncryptionBox:(unsigned char*)pSampleEncBox
                        sampleEncBoxLen:(unsigned int)dwSampleEncBoxLen
                              sampleIDX:(unsigned int)dwSampleIDX
                                trackID:(unsigned int)dwTrackID;

@end
