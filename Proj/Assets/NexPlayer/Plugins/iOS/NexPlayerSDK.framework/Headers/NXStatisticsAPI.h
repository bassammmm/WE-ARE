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
#import "NXRTStreamingInfo.h"
#import "NXBufferInfo.h"
#import "NXDeviceInfo.h"
#import "NXHttpStateInfoTypes.h"


/**
 *
 * \brief This class manages the playback statistics of the content.
 *
 * \since version 5.24
 */
@interface NXStatisticsAPI : NSObject
 
/**
 * \brief  Information about the current HLS content.
 *
 * \see NXRTStreamingInfo
 * \since version 5.24
 */
@property (strong, nonatomic, readonly) NXRTStreamingInfo* RTStreamingInfo;

/**
 * \brief Instance of \c NXBufferInfo class to access buffer information related methods such as \c NSUInteger. 
 *
 * \see NXBufferInfo
 * \since version 5.24
 */
@property (strong, nonatomic, readonly) NXBufferInfo* bufferInfo;


/**
 * \brief  The information about the current device streaming a HLS content. 
 *
 * \see NXDeviceInfo
 * \since version 5.24
 */
@property (strong, nonatomic, readonly) NXDeviceInfo* deviceInfo;

/**
 * \brief An object that conforms to NXHttpStateDelegate which delivers HTTP state information.
 *
 * \see NXHttpStateDelegate
 * \since version 5.32
 */
@property (nonatomic,weak)	id<NXHttpStateDelegate> httpStateDelegate;

/**
 * \brief  Designated initializer.
 * \param player The \c NXPlayer instance.
 * \returns An instance of \c NXStatisticsAPI class.  
 * \since version 5.24
 */
- (id) initWithPlayer:(NXPlayer*)player;
@end
