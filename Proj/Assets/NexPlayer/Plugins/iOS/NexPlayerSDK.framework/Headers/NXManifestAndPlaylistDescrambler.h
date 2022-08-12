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
 * \brief   The \c NXManifestAndPlaylistDescrambler protocol must be adopted and implemented
 *          by objects that provide manifest/playlist descrambling services.
 *
 * Any object can adopt this protocol, but it is typically adopted by either
 * the NXPlayerDelegate, or by a dedicated descrambling object.
 *
 * When assigned to NXPlayer::manifestAndPlaylistDescrambler, an object that
 * adopts this protocol will be called whenever a top-level playlist or
 * manifest is obtained, and at that point can perform any descrambling
 * that is necessary.
 *
 * This protocol comprises only one method, which is called to perform the
 * descrambling.
 *
 * \since version 5.9
 */
@protocol NXManifestAndPlaylistDescrambler <NSObject>

/**
 * \brief   Method for descrambling top-level playlists and manifests.
 *
 * \param[in]       player          The calling NXPlayer instance.
 *
 * \param[in]       url             The URL from which this top-level playlist 
 *                                  or manifest was retrieved (in the case of
 *                                  redirection, this will be the URL before 
 *                                  redirection).
 *
 * \param[in,out]   pData           The contents of the playlist.  Descrambling 
 *                                  should be done in-place, so on input this is 
 *                                  the scrambled playlist, and on output it is 
 *                                  the descrambled playlist.
 *
 * \param[in,out]   pdwDataLen      On input, the size of the original (scrambled)
 *                                  playlist; on output, the size of the descrambled
 *                                  playlist.  Note that the output size must be 
 *                                  equal to or smaller than the input size.
 *
 * \returns                         The method should return zero if the data
 *                                  was successfully descrambled.  In the case of
 *                                  an error, it should return -1.
 */
- (int)descrambleForPlayer:(NXPlayer*)player
                       URL:(NSURL*)url
    manifestOrPlaylistData:(char*)pData
                    length:(unsigned int*)pdwDataLen;

@end
