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
#import "NXCaptionAttribute.h"

@interface NXCaptionRenderController: NSObject

/**
 * \brief  This property changes caption attributes (including font color, background color, and edge style) to user-defined settings.
 *
 *  While caption attributes are often defined in content specifications, this property can be used to allow users to change the
 *  way CEA 608 closed caption and WebVTT text track text are displayed in content (similar support for other caption specifications
 *  is currently being developed).
 *
 *  Users can be allowed to set the colors of caption text and background and the edge style to use on text (drop shadow, raised, depressed, or uniform),
 *  as well as setting the window color and font size on WebVTT text track captions (not available for CEA 608).
 *
 * \since version 5.22
 */
@property (nonatomic, copy) NXCaptionAttribute *captionAttribute;

/**
 * \brief This property sets visibility state of captions available in content.
 *
 * Assigning \c NO hides captions (CEA 608 and CEA 708 closed captions, 3GPP and TTML timed text, and WebVTT text tracks)
 * in the current NXPlayerView.
 *
 * Default value is \c NO.
 *
 * \since version 5.22
 */
@property (nonatomic) BOOL captionHidden;

/**
 * \brief This property clears all the captions currently rendered on the screen.
 *
 * \since version 5.22
 */
- (void) clearCaptionView;
@end
