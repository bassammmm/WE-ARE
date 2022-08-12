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
 * \brief Provides a view in which NexPlayer&trade;&nbsp;video output can be
 *			displayed, creates an associated NXPlayer object, and
 *			binds it to the view.
 * 
 * This is similar to NXPlayerView, except that NXPlayerView scales the
 * video to maintain the aspect ratio, and handles resizing and rotation,
 * whereas NXPlayerRenderView simply stretches the video to fill the view.
 *
 * This is the recommended way to render video with NexPlayer&trade;&nbsp;if you
 * wish to calculate scaling values yourself.
 *
 * The layer associated with this class is a CAEAGLLayer, suitable for use
 * with NXPlayer.  Each NXPlayerLayer creates and manages an associated
 * NXPlayer object, including assigning the view's layer to the \c renderLayer
 * of the player, and updating the NXPlayer video render buffers if
 * the size of the view changes.
 *
 * This provides all of the usual UIView methods and properties.
 *
 * In addition, you can use the NXPlayerRenderView::player property to access the
 * NXPlayer object and control the player.  For example, to play a local
 * video file named "test.wmv" in a NXPlayerRenderView, you could simply write:
 *
 * \code
 [hPlayerView.player openAndPlayFromBundle: @"test.wmv"];
 * \endcode
 */
@interface NXPlayerRenderView : UIView
/**
 * \brief The NXPlayer instance associated with this view.
 * 
 * This can be used to control playback within this view.
 */
@property (strong, nonatomic,readonly) NXPlayer* player;

@end
