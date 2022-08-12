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
 * \brief This class manages information about the arbitrary session data of the HLS master playlist.
 *
 * \since version 5.33
 */
@interface NXSessionData: NSObject

/**
 * \brief unique ID for internal use.
 */
@property (nonatomic, readonly) NSUInteger uId;

/**
 * \brief This is a unique string used to identify the session data.
 */
@property (nonatomic, strong, readonly) NSString* dataID;
/**
 * \brief It is identified by a string, DATA-ID. If a LANGUAGE is specified, this attribute must be included in a human-readable form in the specified language.
 */
@property (nonatomic, strong, readonly) NSString* value;
/**
 * \brief A string containing a URI, the resource identified by this URI must be formatted using JSON (JavaScript Standard Object Notation, one of the notations, RFC 7159).
 */
@property (nonatomic, strong, readonly) NSString* uri;
/**
 * \brief Language of the VALUE, using the RFC5646 value
 */
@property (nonatomic, strong, readonly) NSString* language;
/**
 * \brief Absolute requested URI
 */
@property (nonatomic, strong, readonly) NSString* abstractUrl;
/**
 * \brief data from URI
 */
@property (nonatomic, strong, readonly) NSData* dataFromUrl;



@end
