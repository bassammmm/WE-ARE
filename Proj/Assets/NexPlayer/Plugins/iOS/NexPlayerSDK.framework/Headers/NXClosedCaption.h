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

typedef enum {
    NXCaptionTypeUnknown,        // Can't be detected.
    NXCaptionTypeGeneral,        // Plain Text
    NXCaptionTypeCEA608,
    NXCaptionTypeWebVTT,
    NXCaptionType3GPPTT,
    NXCaptionTypeTTML,
    NXCaptionTypeEIA708,
} NXCaptionType;

typedef enum {
	NXCaptionFontItalic,
	NXCaptionFontBold,
	NXCaptionFontUnderline,
	NXCaptionFontNormal
} NXCaptionFont;

@interface CaptionFontAttribute : NSObject
	@property (nonatomic) NXCaptionFont fontType;
	@property (nonatomic) NSRange fontAdjustRange;
@end

/**
 * \brief   Represents Closed Caption.
 *
 * Contains caption data for rendering on the screen. 
 *
 * \since version 5.17
 */

static NSString* kNXTTMLBackgroundImagePNG = @"backgroundImage";

@interface NXClosedCaption : NSObject
/**
 * \brief Type of the caption.
 *
 */
@property (nonatomic, readonly) NXCaptionType type;
/**
 * \brief Caption text that may contain HTML formatting depending on the value of type property.
 *
 */
@property (nonatomic, strong, readonly) NSString *text;
/**
 * \brief Caption text without formatting.
 *
 */
@property (nonatomic, strong, readonly) NSString *plainText;


@property (nonatomic, strong, readonly) NSDictionary* extraInfo;


@end
