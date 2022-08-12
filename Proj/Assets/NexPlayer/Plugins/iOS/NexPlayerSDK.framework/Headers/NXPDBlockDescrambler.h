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
 * \brief   The \c NXPDBlockDescrambler protocol must be adopted and implemented
 *          by objects that provide descrambling services for individual blocks of
 *          data received during progressive download and playback.
 *
 *
 * Any object can adopt this protocol, but it is typically adopted by either
 * the NXPlayerDelegate, or by a dedicated DRM descrambling object.
 *
 * When assigned to NXPlayer::PDBlockDescrambler, an object that adopts this protocol
 * will be called for each block of a file received via progressive download.
 *
 * This protocol comprises only one method, which is called to perform the
 * descrambling.
 *
 * \since 5.9
 *
 */
@protocol NXPDBlockDescrambler <NSObject>

/**
 * \brief   Method for descrambling encrypted blocks of data received via progressive download.
 *
 * \param[in]  player               The calling NXPlayer instance.
 *
 * \param[in,out]	data            The block of data received via progressive download.
 *                                  This should be descrambled in-place and the revised
 *                                  data should be written to the same location.
 *
 * \param[in]  size                 The size of the block, in bytes.  The output size
 *                                  and the input size must be the same, so this value
 *                                  cannot be changed.
 *                                  
 *
 * \param[out]		offset          Offset into the original file at which this block begins.
 *
 */
- (void)descramblePDBlockForPlayer:(NXPlayer*)player
                              data:(char*)data
                              size:(int)size
                            offset:(long long)offset;

@end
