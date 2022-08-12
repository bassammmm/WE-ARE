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
 * \brief   A protocol you can implement if you wish to implement Smooth
 *          Streaming fragment descrambling.
 *
 * See NXPlayer::smoothStreamFragmentDescrambler for additional information.
 */
@protocol NXSmoothStreamFragmentDescrambler <NSObject>

@optional

/**
 * \brief   Called by the player when there is data available for
 *          descrambling.
 *
 * \deprecated Please use NXSmoothStreamFragmentDescrambler::descrambleSmoothStreamingFragmentForPlayer:inputBuffer:inputBufferSize:outputBuffer:outputBufferSize:mediaFileURL:parentPlaylistURL: instead.
 *
 * \param player  The NXPlayer instance that this descrambler has been assigned to.
 * \param[in] pInputBuffer  	The original (possibly scrambled) input data.
 * \param uiInputBufferSize 	The size (in bytes) of the input buffer.
 * \param[out] pOutputBuffer	The location at which to write the descrambled output
 *								data.  Note that this may overlap or be the same as
 *								the input buffer location.
 * \param[out] puiOutputBufferSize
 *								The size of the descrambled data. The callback must
 *								set this value.  This may be equal to or smaller than
 *								\c uiInputBufferSize, but not larger.
 */
- (unsigned long)descrambleSmoothStreamingFragmentForPlayer:(NXPlayer*)player
												inputBuffer:(unsigned char*)pInputBuffer
											inputBufferSize:(unsigned int)uiInputBufferSize
											   outputBuffer:(unsigned char*)pOutputBuffer
										   outputBufferSize:(unsigned int*)puiOutputBufferSize;


/**
 * \brief   Called by the player when there is data available for
 *          descrambling.
 *
 * This function is called every time a Smooth Streaming fragment is received,
 * regardless of whether or not the fragment is encrypted.  It is the responsibility
 * of this callback to determine whether or not the fragemnt is encrypted and
 * descramble the fragment if necessary.
 *
 * \param[in] player            The NXPlayer instance that this descrambler has been assigned to.
 * \param[in] pInputBuffer  	The original (possibly scrambled) input data.
 * \param[in] uiInputBufferSize The size (in bytes) of the input buffer.
 * \param[out] pOutputBuffer	The location at which to write the descrambled output
 *								data.  Note that this may overlap or be the same as
 *								the input buffer location.
 * \param[out] puiOutputBufferSize
 *								The size of the descrambled data. The callback must
 *								set this value.  This may be equal to or smaller than
 *								\c uiInputBufferSize, but not larger.
 * \param[in] mediaFileURL      The URL of the media file that this fragment belongs to.
 * \param[in] parentPlaylistURL The URL of the parent playlist that \c mediaFileURL belongs to.
 *
 * \since version 5.9
 */
- (unsigned long)descrambleSmoothStreamingFragmentForPlayer:(NXPlayer*)player
												inputBuffer:(unsigned char*)pInputBuffer
											inputBufferSize:(unsigned int)uiInputBufferSize
											   outputBuffer:(unsigned char*)pOutputBuffer
										   outputBufferSize:(unsigned int*)puiOutputBufferSize
                                               mediaFileURL:(char*)mediaFileURL
                                          parentPlaylistURL:(char*)parentPlaylistURL;


@end
