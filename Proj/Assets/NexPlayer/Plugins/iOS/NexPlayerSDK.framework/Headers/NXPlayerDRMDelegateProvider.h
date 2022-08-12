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


#import <Foundation/Foundation.h>
#import "NXPlayer.h"

/**
 * \brief A class dedicated to provide DRM delegates to the associated \c NXPlayer instance.
 *
 * <p>Example code :</p>
 * \code
 * @interface PlayerViewController <NXPlayerGetKeyExtDelegate> : ...
 * ...
 * @end
 *
 * @implementation PlayerViewController
 * ...
 * - (void) initializePlayer
 * {
 *     ...
 *     NXPlayer *player = self.player;
 *     NXPlayerDRMDelegateProvider *drmDelegateProvider = [NXPlayerDRMDelegateProvider providerWithNXPlayer:player];
 *     drmDelegateProvider.getKeyExtDelegate = self;
 *
 *     self.drmDelegateProvider = drmDelegateProvider;
 *     ...
 * }
 *
 * - (NSData *) nexPlayer:(NXPlayer *) nxplayer getKeyExtForURLString:(NSString *) URLString result:(BOOL *) pResult
 * {
 *     ...
 * }
 * \endcode
 *
 * \since version 5.24
 */
@interface NXPlayerDRMDelegateProvider : NSObject

/**
 * \brief Delegate object that will be called with it's NXPlayerGetKeyExtDelegate::nexPlayer:getKeyExtForURLString:result:
 *  method when an encryption key retrieval is required from a HLS playlist to be passed to NexPlayer&trade;&nbsp;for descrambling.
 *
 * \see NXPlayerGetKeyExtDelegate
 *
 * \since version 5.24
 */
@property (nonatomic, weak) id<NXPlayerGetKeyExtDelegate> getKeyExtDelegate;

/**
 * \brief This method creates an instance of this class associated with the parameter \c nxplayer.
 *
 * \since version 5.24
 */
+ (id) providerWithNXPlayer:(NXPlayer *) nxplayer;
@end
