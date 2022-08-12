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
#import "NXCEA608Caption.h"

/**
 *
 * \brief  This view receives and displays CEA 608 closed captions.
 *
 * This interface must be implemented in order for CEA 608 closed captions to be displayed.
 *
 * Please see \ref NXCEA608Caption and \ref NXPlayerView for more information.
 *
 * \since version 5.8
 */
@interface NXCEA608CaptionView : UIView {
@private
    NXCEA608Caption *m_caption;
    NXOnOffDefault m_bold;
}

@property NXOnOffDefault bold;

/**
 *
 * \brief This method displays CEA 608 closed captions on the screen.
 *
 * Once a view has been created to display CEA 608 closed captions,
 * this method sets and displays the captions as new caption data becomes available.
 *
 * \param[in] caption  The captions to be displayed.
 *
 * Please see \ref NXCEA608Caption for more information about CEA 608 closed captions.
 *
 * \since version 5.8
 */
- (void)setCaption:(NXCEA608Caption*)caption;

- (void)clearScreen;

@end
