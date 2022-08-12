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
 * \brief A protocol you can implement if you wish to implement decrypting AES128 an encrypted HTTP Live Streaming content.
 *        When registered to NXPlayer::hlsAESDescrambler property, the method defined in this protocol called every time AES128 encrypted HLS content is received.
 *
 * \since version 5.16
 */
@protocol NXHLSAES128Descrambler

/**
 * \brief   Called every time an AES128 encrypted HLS content is received.
 *
 * \param[in]  player               The calling NXPlayer instance.
 * \param[in]  pInBuf               The encrypted data to be descrambled.
 *
 * \param[in]  dwInBufSize          The size of the encrypted data, in \c bytes.
 *
 * \param[out] pOutBuf              The location at which to place the decrypted
 *                                  output data.  This may point to the same
 *                                  location as the input buffer, or it may point
 *                                  to a separate location. The size available for
 *                                  the output buffer is the same as the size of
 *                                  the input buffer. That is, the decrypted data
 *                                  may be smaller than the encrypted data, but
 *                                  not larger.
 *
 * \param[out] pdwOutBufSize        The size of the decrypted data.  The callback
 *                                  must set this value.  This may be equal to or
 *                                  smaller than \c dwInBufSize, but not larger.
 *
 * \param[in]  pSegmentUrl		    A pointer to the URL of the segment of content.
 * \param[in]  pMpdUrl			    A pointer to the original URL of the content playlist.
 * \param[in]  pKeyAttr			    A pointer to the decryption Key information.
 * \param[in]  dwSegmentSeq		    The sequence number of the TS segment file.
 * \param[in]  pKey				    A pointer to the decryption Key.  This parameter is only meaningful when \c dwKeySize is greater than 0 (i.e. a key has been downloaded).
 * \param  dwKeySize			    The size of the decryption Key.  This parameter will be zero if no key has been downloaded.
 *
 * \returns  1 if successful; 0 if there was an error.
 *
 * \see NXPlayer::hlsAESDescrambler
 * \since version 5.16
 */
- (int) HLSAES128Descrambler:(NXPlayer*)player
				 inputBuffer:(unsigned char*)pInBuf
			 inputBufferSize:(unsigned int)dwInBufSize
				outputBuffer:(unsigned char*)pOutBuf
			outputBufferSize:(unsigned int*)pdwOutBufSize
				  segmentURL:(char*)pSegmentUrl
					  MpdUrl:(char*)pMpdUrl
				KeyAttribute:(char*)pKeyAttr
				  segmentSeq:(unsigned int)dwSegmentSeq
						 key:(unsigned char*)pKey
					 keySize:(unsigned int)dwKeySize;

@end
