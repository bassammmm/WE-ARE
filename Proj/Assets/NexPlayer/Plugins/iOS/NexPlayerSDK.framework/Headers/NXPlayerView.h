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
#import "NXPlayerRenderView.h"
#import "NXCEA608CaptionView.h"
#import "NXCaptionAttribute.h"
#import "NXCaptionRenderController.h"

/**
 * \brief Provides a view in which NexPlayer&trade; video output can be
 *			displayed, and creates an associated NXPlayer object and
 *			binds it to the view.
 * 
 * This is the recommended way to render video with NexPlayer&trade;.
 *
 * Each NXPlayerView creates and manages an associated NXPlayer object, 
 * including assigning the view's layer to the \c renderLayer
 * of the player, and updating the NXPlayer video render buffers if
 * the size of the view changes.
 *
 * Each NXPlayerView also creates and maintains an NXPlayerRenderView
 * in which the actual player output is displayed.  The NXPlayerRenderView is
 * managed automatically to maintain the correct scaling.  In the case
 * of content with CEA 608 closed captions, if the captions are turned on,
 * the NXPlayerView also creates and maintains a NXCEA608CaptionView to
 * receive and display caption information as it is received.
 *
 * This provides all of the usual UIView methods and properties.
 *
 * In addition, you can use the NXPlayerView::player property to access the
 * NXPlayer object and control the player.  For example, to play a local
 * video file named "test.wmv" in an NXPlayerView, you could simply write:
 *
 * \code
 [hPlayerView.player openAndPlayFromBundle: @"test.wmv"];
 * \endcode
 */
@interface NXPlayerView : UIView <NXPlayerContentInfoUpdateReceiver>

/**
 * \brief The NXPlayer instance associated with this view.
 * 
 * This can be used to control playback within this view.
 */
@property (nonatomic, weak, readonly) NXPlayer* player;

/**
 * \brief The NXPlayerRenderView contained within this view.
 * 
 * There is generally not much reason to access this directly.
 */
@property (nonatomic, strong, readonly) NXPlayerRenderView* renderView;

/**
 * \brief The NXCEA608CaptionView contained within this view.
 *
 * If closed captions are turned on, and the current captions are CEA 608 closed caption standard,
 * they will be displayed in this view whenever caption data is updated by NexPlayer&trade;.
 *
 * If a developer wishes to handle and display CEA 608 closed captions
 * independently, the \c captionHidden property must be set \c NO and a
 * separate view should be implemented to receive and display captions in the application.
 *
 * \deprecated If a developer wishes to handle and display CEA 608 closed captions
 * independently, \c captionHidden property must be set to \c NO instead of using \c CEA608CaptionView.hidden.
 *
 * \see captionHidden
 */
@property (nonatomic, strong, readonly) NXCEA608CaptionView* CEA608CaptionView;

/**
 * \brief   Controls automatic scaling of the video image when
 *          the view is resized.
 *
 * Set this to \c NXScale_None to disable auto scaling (the video image
 * will remain in its original size and position regardless of layout or
 * rotation changes).
 *
 * Set this to any other legal value (listed below) to automatically rescale
 * the video whenever the view size changes.  The video is also rescaled to
 * the appropriate size as soon as this value is changed.
 *
 * Changes to the scale can be animated using the usual UIView animation
 * technqiues (begin and commit).
 *
 * Possible values:
 * - <b>NXScale_None:</b>           The video size will not be changed; the size  
 *                                  and location can be set by assigning values 
 *                                  to the \c videoRect property.
 *
 * - <b>NXScale_OriginalSize:</b>   The video will be displayed at its original 
 *                                  size, centered in the view.  The original
 *                                  video dimensions are calculated using 
 *                                  regular (normal resolution) pixels in order
 *                                  to maintain consistency between normal and
 *                                  retina displays.
 *      
 * - <b>NXScale_FitInView:</b>      Fit video to container (as large as possible 
 *                                  without cropping).  The aspect ratio of the
 *                                  video is maintained.  There may be black
 *                                  bars if the aspect ratio of the video doesn't
 *                                  precisely match the aspect ratio of the view.
 *
 * - <b>NXScale_FillView:</b>       NexPlayer&trade;&nbsp;will fill the parent container.
 *                                  If the video dimensions don't match the view
 *                                  dimensions, the video will be cropped to
 *                                  avoid black bars.  The aspect ratio is
 *                                  maintained.
 *
 * - <b>NXScale_Stretch:</b>        Stretch the video to match the dimensions of
 *                                  the view (does not maintain the aspect ratio)
 *                                  of the original video.
 *
 * The default for this is NXScale_Stretch.
 *
 * \warning Changing this should be done while the NXPlayerView instance is visible on the screen.
 *
 */
@property (nonatomic) NXScale autoScaling;

/**
 * \brief   Sets the rectangle in which the video image will be drawn.
 *          
 * Dimensions are in pixels, and coordinates are relative to the NXPlayerView.
 *
 * Changing this property automatically forces \c autoScaling to be set to \c NXScale_None.
 *
 * Enabling automatic scaling (setting \c autoScaling to a value other than
 * \c NXScale_None ) causes the value of \c videoRect to change automatically when the
 * layout or rotation of a parentFrame changes.
 */
@property (nonatomic) CGRect videoRect;

/**
 * \brief   Sets visibility state of captions available in content.
 *
 * Assigning \c NO hides captions (CEA 608 and CEA 708 closed captions, 3GPP and TTML timed text, and WebVTT text tracks)
 * in the current NXPlayerView.
 *
 * Default value is \c NO.
 *
 * \see CEA608CaptionView
 *
 * \since version 5.16
 *
 */
@property (nonatomic) BOOL captionHidden;

/**
 * \brief The \c NXCaptionRenderController object returned by this property allows the rendering options set for captions to be rendered on the screen.
 *
 * \since version 5.22
 */
@property (nonatomic, strong, readonly) NXCaptionRenderController* captionRenderController;



/**
 * \brief  This property allows the rendering mode of the CEA 608 closed captions.
 *
 * NO means basic CEA 608 rendering, meeting the specifications of the CEA 608 standard,
 * and YES means an enhanced rendering mode that makes possible for CEA 608 closed captions to be rendered with additional display settings.
 * (including the changing of the foreground and background colors, the font size, the font type, etc).
 *
 * Default value is \c NO.
 *
 * \since version 5.31.x
 */
@property (nonatomic) BOOL useCEA608CustomView;



@end
