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

/**
 * \ingroup types
 * \brief  This enumeration defines the possible return values from a NXHLSTSDescrambler method.
 *
 * \since version 5.x
 */
typedef NS_ENUM(uint32_t, NexHLSTSDescrambleResult)
{
	NexHLSTSDescrambleResultSucceed = 0,
	NexHLSTSDescrambleResultNeedMoreBuffer = 1,
	NexHLSTSDescrambleResultError
}_DOC_ENUM(NexHLSTSDescrambleResult);

@class NXPlayer;
/**
 * \brief A protocol you can implement if you wish to implement HTTP Live Streaming TS segment descrambling.
 *
 */
@protocol NXHLSTSDescrambler <NSObject>

/**
 * \brief   Called by the player when there is data available for descrambling.
 *
 * \param[in]  player               The calling NXPlayer instance.
 * \param[in]  pInputBuffer         The encrypted data to be descrambled.
 *
 * \param  uiInputBufferSize    The size of the encrypted data, in bytes
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
 * \returns  NexHLSTSDescrambleResultSucceed if successful, NexHLSTSDescrambleResultError 
 *           if there was an error, or NexHLSTSDescrambleResultNeedMoreBuffer if 
 *           uiInputBufferSize is smaller than the output data in bytes.
 *
 * \see NexHLSTSDescrambleResult
 */

@optional
- (NexHLSTSDescrambleResult)descrambleHLSTS:(NXPlayer*)player
                     inputBuffer:(unsigned char*)pInputBuffer
                 inputBufferSize:(unsigned int)uiInputBufferSize
                    outputBuffer:(unsigned char*)pOutputBuffer
                outputBufferSize:(unsigned int*)puiOutputBufferSize;

/**
 * \brief   Called by the player when there is data available for descrambling.
 *
 * \param[in]  player               The calling NXPlayer instance.
 * \param[in]  pInputBuffer         The encrypted data to be descrambled.
 *
 * \param  uiInputBufferSize    The size of the encrypted data, in bytes.
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
 * \param[in] pMediaFileURL			The URL of the media file.
 * \param[in] pPlaylistURL			The URL of the playlist.
 *
 * \returns  NexHLSTSDescrambleResultSucceed if successful, NexHLSTSDescrambleResultError
 *           if there was an error, or NexHLSTSDescrambleResultNeedMoreBuffer if
 *           uiInputBufferSize is smaller than the output data in bytes.
 *
 * \see NexHLSTSDescrambleResult
 */

@optional
- (NexHLSTSDescrambleResult)descrambleHLSTS:(NXPlayer*)player
                     inputBuffer:(unsigned char*)pInputBuffer
                 inputBufferSize:(unsigned int)uiInputBufferSize
                    outputBuffer:(unsigned char*)pOutputBuffer
                outputBufferSize:(unsigned int*)puiOutputBufferSize
                    mediaFileURL:(char*)pMediaFileURL
                     playlistURL:(char*)pPlaylistURL;

@end
