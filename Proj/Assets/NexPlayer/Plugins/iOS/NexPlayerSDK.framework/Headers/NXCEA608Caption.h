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
#import <UIKit/UIKit.h>
#import "NXTypes.h"

typedef enum {
    NXCEA608EdgeType_Normal     = 0,
    NXCEA608EdgeType_Shadow,
    NXCEA608EdgeType_Raised,
    NXCEA608EdgeType_Depressed
} NXCEA608EdgeType;

/**
 * \brief   Represents a complete CEA 608 caption display.
 *
 * CEA 608 closed captions, unlike other subtitle formats, do not merely include
 * text captions associated with the playing content but also support numerous
 * other attributes including caption color (text and background), text effects
 * (italics, flashing characters, and underlining), and text positioning on the screen
 * as well as supporting an animated "rolling up" display of the captions.
 *
 * While NexPlayer&trade;&nbsp;handles and displays these closed captions according
 * to the specification in NXCEA608CaptionView if they are turned on using \ref NXPlayer::selectedCEA608Channel,
 * this interface can also be used to handle and display the captions independently if another view is provided.
 *
 * \since version 5.8
 */
@interface NXCEA608Caption : NSObject {
@private
    NSData *m_captionData;
    NXCEA608Channel m_channel;
}

/**
 * \brief   The channel (1~4) to which this CEA 608 caption pertains.
 *
 * While CEA 608 closed captions can be received from one of four channels,
 * since channels 1 and 2 share field 1 in the NTSC line 21 data, and channels 3 and 4
 * share field 2, the most commonly used channels are channel 1 and channel 3.
 * These channels also often represent different language captions which may be
 * best selected from the user interface.
 *
 * Note that if this property is set to ZERO, no channel is selected and the captions
 * are effectively disabled or turned off.
 *
 * \since version 5.8
 */
@property (nonatomic,readonly) NXCEA608Channel channel;

/**
 * \brief   The base row (0-14) for roll-up captioning in CEA 608 closed captions.
 *
 * When closed captions are to be displayed "rolling up" on the screen,
 * this value sets the horizontal position of the lowest "base" row in the
 * roll up display.  Captions to first be displayed in this base row,
 * and then will be "rolled up" as new rows of captions are added.
 *
 * \since version 5.8
 */
@property (nonatomic,readonly) int rollupBaseRow;

/**
 * \brief   The number of rows (2-4) of roll-up captioning, or zero if
 *          not in roll-up captioning mode
 *
 * For CEA 608 closed captions, a roll-up display of captions is supported.  If
 * these captions are to roll up on the screen, captions will always begin by
 * appearing in the base row indicated by \c rollupBaseRow, and will then
 * roll up for the number of row set here.
 *
 * This property indicates the number of rows to be rolled up and is a number
 * between 2 and 4.
 *
 * This property as well as \c rollupBaseRow can be used to position the rows
 * rolling up, and the property \c timeSinceRollupStart should be used to help
 * animate the roll-up display, if animated independently.
 *
 * \since version 5.8
 */
@property (nonatomic,readonly) int rollupRows;

/**
 * \brief   The time (milliseconds) that has passed since the start of the
 *          most recent rollup operation.
 *
 * In order to animate the rolling up of captions when they are to be displayed
 * in "roll up" mode, this value can be used to determine where to display the rows
 * of text being rolled-up (including the the row of text being "rolled out" of view
 * into row -1).
 *
 * Based on this number and the amount of time to be taken to roll the rows up to the
 * next position, the rows of captions can be displayed in progressively higher positions
 * until the animation is finished and the new caption can begin to be displayed in the
 * base row.
 *
 *
 * \since version 5.8
 */
@property (nonatomic,readonly) unsigned long timeSinceRollupStart;

/**
 * \brief   YES if this caption is empty (contains no data).
 *
 *
 * This is a property that can be used for convenience if a CEA 608 closed caption
 * cell is empty.  Instead of drawing an entire caption object of empty values, if this is true,
 * it's possible to merely erase the captions currently displayed on the screen.
 *
 * \since version 5.8
 */
@property (nonatomic,readonly) BOOL isEmpty;

/**
 * \brief   Gets the recommended UIColor to use for the specified
 *          NXCEA608Color, in a foreground color context.
 *
 * Based on the color specified by \c NXCEA608Color, this determines the UIColor
 * to use to display the text of captions in the cell.  Note that text colors
 * do not include transparency, unlike the background colors of captions.
 *
 * \param color The text color to use for the given caption cell.
 *
 * \returns The recommended UIColor for the specified text caption color.
 *
 * \since version 5.8
 */
+ (UIColor*)recommendedUIColorForFG:(NXCEA608Color)color;

/**
 * \brief   Gets the recommended UIColor to use for the specified
 *          NXCEA608Color, in a background color context.
 *
 * Based on the color specified by \c NXCEA608Color, this determines the UIColor
 * to use to display the background of captions in the cell.
 *
 * \param color  The background color to use for the given caption cell.
 *
 * \returns The recommended UIColor for the specified caption color.
 *
 * \see NXCEA608Color for supported colors.
 *
 *
 * \since version 5.8
 */
+ (UIColor*)recommendedUIColorForBG:(NXCEA608Color)color;

/**
 * \brief   Gets information on the character and attributes of a caption cell.
 *
 * This method gets the caption cell information for CEA 608 close captions for
 * display.  These captions are generally displayed by NexPlayer&trade;&nbsp;in
 * the NXCEA608CaptionView, and the captions to display are chosen by setting
 * the channel to receive captions with NXPlayer::selectedCEA608Channel.
 *
 * \param[out]  cellInfo  The CEA 608 closed caption information to be displayed.
 * \param size  The size of the caption cell, namely sizeof(NXCEA608CellInfo)
 * \param row   The row position of the caption cell.  This will be an integer from
 *              0 to 14, or -1 for a row that has "rolled-off" the screen.
 * \param col   The column position of the caption cell.  This will be
 *              an integer from 0 to 31.
 *
 *
 * \since version 5.8
 */
- (void)getCellInfo:(NXCEA608CellInfo*)cellInfo
               size:(int)size
              atRow:(int)row
             andCol:(int)col;

/**
 * \brief   Draws the captions represented by this object in the specified
 *          rectangle.
 *
 * This generally should be called from within \c drawRect method of a
 * \c UIView subclass.
 *
 * \param rect  What area to draw in within the context.
 *
 * \param cgx	The context in which to draw on.
 *
 * \param[out]  redrawTime      The maximum number of milliseconds to wait before
 *                              the caption display should be redrawn, even if
 *                              there are no updates.  The two cases where the
 *                              caption display may need to be redrawn are if
 *                              there are flashing items to display or if there is
 *                              a roll-up animation in progress.  If this value
 *                              is zero, it means no redraw is necessary until
 *                              new subtitle data is received.
 *
 *
 * \since version 5.8
 */
- (void)drawCaptionsInRect:(CGRect)rect 
                 inContext:(CGContextRef)cgx
                redrawTime:(unsigned int*)redrawTime;

- (void)drawCaptionsInRect:(CGRect)rect
                 inContext:(CGContextRef)cgx
                redrawTime:(unsigned int*)redrawTime
                   fgColor:(UIColor*)fgcolor
                   bgColor:(UIColor*)bgcolor
                 edgeStyle:(NXCEA608EdgeType)edge
                      bold:(NXOnOffDefault)bold;

-(void)clearCaptionData;


@end
