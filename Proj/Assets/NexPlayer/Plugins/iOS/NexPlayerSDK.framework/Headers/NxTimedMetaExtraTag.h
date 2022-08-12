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


/**
 * \brief The properties in this interface define the different details of a custom tag in ID3 metadata.
 *  
 * \since version 5.17
 */

@interface NxTimedMetaExtraTag : NSObject

/**
 * \brief This property is the tag ID of the custom tag in ID3 metadata. 
 */
@property (strong, nonatomic, readonly)NSString *tagID;

/**
 * \brief This property is the text of the custom tag in ID3 metadata. 
 */
@property (strong, nonatomic, readonly)NSString *text;

/**
 * \brief This property is the data of the custom tag in ID3 metadata. 
 */
@property (strong, nonatomic, readonly)NSData *data;

 /**
 * \brief This property checks whether the current tag contains any picture data and if they are accessible through the \c data \c property. 
 *
 * If YES, the picture data format is in \c mimeType \c property and the \c data \c property contains the binary data of the image.
 * If NO, the tag only includes text data and is accessible through \c text \c property.
 */
@property (nonatomic, readonly)BOOL isPicture;

/**
 * \brief This property is the MimeType of the custom tag in ID3 metadata.
 */
@property (strong, nonatomic, readonly)NSString * mimeType;

@end
