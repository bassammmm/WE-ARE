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
#import "NXClosedCaption.h"
#import <UIKit/UIKit.h>


/**
 * \brief  This enumeration defines the possible edge styles that can be applied to the captions.
 *
 * \since 5.20
 */
typedef enum{
	NXCaptionEdgeStyle_None,
	NXCaptionEdgeStyle_DropShadow,
	NXCaptionEdgeStyle_Raised,
	NXCaptionEdgeStyle_Depressed,
	NXCaptionEdgeStyle_Uniform
	
} NXCaptionEdgeStyle;


/**
 * \brief  This enumeration defines the possible states that can be applied to fontBold, fontUnderline, fontItalic.
 *
 * \since 5.31.x
 */
typedef enum {
	NXTriState_Default,
	NXTriState_Enable,
	NXTriState_Disable
} NXTriState;


/**
 * This structure is used to store the BoundingBox information which overrides default caption positions.
 *
 * \since version 5.31.x
 */
typedef struct NXBoundingBox {
	NSUInteger topPercent; /// Top position using percent based on the top display edge of caption view.
	NSUInteger leftPercent; /// Left position using percent based on the left display edge of caption view.
	NSUInteger widthPercent; /// Width using percent of caption view.
	NSUInteger heightPercent; /// height using percent of caption view.
} NXBoundingBox;


/**
 * \brief  This struct defines the possible values that are used for vertical alignment.
 *
 * \since 5.31.x
 */
typedef enum {
	NXVerticalAlignment_Default,
	NXVerticalAlignment_Top,
	NXVerticalAlignment_Middle,
	NXVerticalAlignment_Bottom,
} NXVerticalAlignment;


/**
 * \brief  This struct defines the possible values that are used for horizontal alignment.
 *
 * \since 5.31.x
 */
typedef enum {
	NXHorizontalAlignment_Default,
	NXHorizontalAlignment_Left,
	NXHorizontalAlignment_Center,
	NXHorizontalAlignment_Right,
} NXHorizontalAlignment;



/**
 * \brief   This interface represents the values of the caption attributes for captions.
 *
 * The caption style attributes set with this interface can be used to change the caption text appearance in the application UI,
 * to allow users to change how caption text is displayed.
 *
 * \since 5.31.x
 */

@interface NXCaptionAttribute : NSObject


/**
 * \brief This property sets the window color.
 *
 * If the value is \c nil, the window color will be rendered in the default content defined value or transparent if it is not defined.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \since 5.31.x
 */
@property (nonatomic, strong) UIColor* windowColor;


/**
 * \brief This property sets the background color.
 *
 * If this value is \c nil, the background color will be rendered in the default content defined value or transparent if it is not defined.
 *
 * \since 5.31.x
 */
@property (nonatomic, strong) UIColor* backgroundColor;


/**
 * \brief This property sets the font color.
 *
 * If this value is \c nil, the font color will be rendered in the default content defined value or transparent if it is not defined.
 *
 * Default value is content described
 *
 * \since 5.31.x
 */
@property (nonatomic, strong) UIColor* fontColor;


/**
 * \brief This property sets the shadow or edge color.
 *
 * If this value is \c nil, the shadow or edge style of the caption text will be rendered in default content defined value or transparent if it is not defined.
 * 
 * \note  To ensure that the chosen edge styles are displayed, set \c shadowColor to the desired color value, taking into account the colors of the font/
 * background and font/shadow color opacity( \c fontColor and \c backgroundColor, \c fontColorOpacity, \c shadowColorOpacity).
 *
 * \see  The \c edgeStyle property
 * \since 5.31.x
 */
@property (nonatomic, strong) UIColor* shadowColor;


/**
 * \brief This property sets the font size (in points).
 *
 *  If this value is \c NAN, the caption will be rendered in the default content defined value.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * Default value is NAN.
 *
 * \since 5.31.x
 */
@property (nonatomic) CGFloat fontSize;


/**
 * \brief  This property sets the edge style of the CEA 608 closed caption or WebVTT text track text.
 *
 *  Available edge styles are defined by the \c NXCaptionEdgeStyle enumeration and include:
 *      - \c NXCaptionEdgeStyle_None:  No edge style.
 *      - \c NXCaptionEdgeStyle_DropShadow:  Caption text displayed with a drop shadow effect.
 *      - \c NXCaptionEdgeStyle_Raised:  Caption text displayed as if embossed or "raised" out of the screen.
 *      - \c NXCaptionEdgeStyle_Depressed:  Caption text displayed as if pressed or "depressed" into the screen.
 *      - \c NXCaptionEdgeStyle_Uniform:  Caption text displayed with a uniform edge effect.
 *      
 * \note  In order to an edge style or shadow to be displayed, the property \c shadowColor must be set in addition to setting the \c edgeStyle with this property.  If \c shadowColor is \c nil, no edge style will be displayed.
 *
 * \see The \c shadowColor property.
 *
 * \since 5.20
 */
@property (nonatomic) NXCaptionEdgeStyle edgeStyle;


/**
 * \brief   Sets the font size scale as a percentage.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * Default value is \c 100
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NSUInteger fontSizeScale;


/**
 * \brief   Enable/Disable bold font.
 *
 * If the value is \c NXTriState_Default, the fontBold will be rendered in the default content defined value or non-bold if it is not defined.
 *
 * Default value is NXTriState_Default.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \see NXCaptionAttribute::NXTriState
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NXTriState fontBold;


/**
 * \brief   Enable/Disable underlined font.
 *
 * If the value is \c NXTriState_Default, fontUnderline will be rendered in the default content defined value or non-underline if it is not defined.
 *
 * Default value is NXTriState_Default.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *  \note  If the edge style is uniform, underline color will be the same as font color
 *
 * \see NXCaptionAttribute::NXTriState
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NXTriState fontUnderline;


/**
 * \brief   Enable/Disable italic font.
 *
 * If the value is \c NXTriState_Default, fontItalic will be rendered in the default content defined value or non-italic if it is not defined.
 *
 * Default value is NXTriState_Default.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \see NXCaptionAttribute::NXTriState
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NXTriState fontItalic;


/**
 * \brief This property sets the font color opacity.
 *
 * If the value is \c NAN, font color opacity will be rendered in the default content defined value or Opaque(100) if it is not defined.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \since 5.31.x
 */
@property (nonatomic) CGFloat fontColorOpacity;


/**
 * \brief This property sets the background color opacity.
 *
 * If the value is \c NAN, background color opacity will be rendered in the default content defined value or Opaque(100) if it is not defined.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \since 5.31.x
 */
@property (nonatomic) CGFloat backgroundColorOpacity;


/**
 * \brief This property sets the window color opacity.
 *
 * If the value is \c NAN, window color opacity will be rendered in the default content defined value or Opaque(100) if it is not defined.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \since 5.31.x
 */
@property (nonatomic) CGFloat windowColorOpacity;


/**
 * \brief This property sets the shadow color opacity.
 *
 * If the value is \c NAN, shadow color opacity will be rendered in the default content defined value or Opaque(100) if it is not defined.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * \since 5.31.x
 */
@property (nonatomic) CGFloat shadowColorOpacity;


/**
 * \brief This property sets the fontName.
 *
 * If the value is \c nil, font will be rendered in the default content defined value or system font if it is not defined.
 *
 *  \note  The possible value will be the one of value in [UIFont familyNames].
 *
 * \since 5.31.x
 */
@property (nonatomic, strong) NSString* fontName;


/**
 * \brief   Sets the BoundingBox information for captions.
 *
 *  If one of the values is \c NAN, captions will be rendered in the default content defined area.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * Default value is \c NAN for all the attribute.
 *
 * \see NXCaptionAttribute::NXBoundingBox
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NXBoundingBox boundingBox;


/**
 * \brief   Sets the vertical alignment for captions.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * Default value is \c NXVerticalAlignment_Default
 *
 * \see NXCaptionAttribute::NXVerticalAlignment
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NXVerticalAlignment verticalAlignment;


/**
 * \brief   Sets the horizontal alignment for captions.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * Default value is \c NXHorizontalAlignment_Default
 *
 * \see NXCaptionAttribute::NXHorizontalAlignment
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) NXHorizontalAlignment horizontalAlignment;


/**
 * \brief   Sets the automatic adjustment for the caption position.
 *
 *  \note  In case of CEA608 caption, NXCaptionView::useCEA608CustomView should be set to YES to use this property.
 *
 * Default value is \c YES
 *
 * \since version 5.31.x
 *
 */
@property (nonatomic) BOOL autoAdjustment;





@end
