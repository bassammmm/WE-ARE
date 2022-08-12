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


#ifndef NXDynamicThumbnailDelegate_h
#define NXDynamicThumbnailDelegate_h


#import <UIKit/UIKit.h>

@class NXPlayer;

/**
 *
 * \brief  This protocol defines a delegate protocol for the application to receive
 *  Dynamic Thumbnail events from NexPlayer&trade;&nbsp;.
 *
 * NexPlayer&trade;&nbsp;will call the methods provided in this interface
 * automatically during playback to notify the application when various
 * Dynamic Thumbnail events have occurred.
 *
 * In most cases, the handling of these events is optional; NexPlayer&trade;&nbsp;
 * will continue play content back normally without the application doing anything
 * special in response to the events received.
 *
 * \since version 5.27
 */
@protocol NXDynamicThumbnailDelegate <NSObject>

/**
 *
 * \brief This method will be called by the NexPlayer&trade;&nbsp; when thumbnail data is created.
 *
 * If the \c NXPlayer::enableDynamicThumbnail: method is called before HLS & Smooth Streaming content is in the \c open state,
 * then this method will be called and gets the thumbnail information associated with the content.
 *
 * @param player	The NexPlayer&trade;&nbsp; object generating the event.
 * @param width		The width of the thumbnail image.
 * @param height	The height of the thumbnail image.
 * @param cts		The current timestamp of the thumbnail image.
 * @param thumbImage UIImage instance of the thumbnail image.
 *
 * \since version 5.27
 */
- (void)onDynamicThumbnailData:(NXPlayer*) player
						 width:(NSInteger) width
						height:(NSInteger) height
						   cts:(NSInteger) cts
					thumbImage:(UIImage*) thumbImage;

/**
 *
 * \brief This method will be called by the NexPlayer&trade;&nbsp; when the end of thumbnail data is received.
 *
 * @param player  The NexPlayer&trade;&nbsp; object generating the event.
 *
 * \since version 5.27
 */
-(void) onDynamicThumbnailRecvEnd:(NXPlayer*) player;

@end


#endif /* NXDynamicThumbnailDelegate_h */
