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

/* Allow Doxygen to detect NS_ENUM as enum */
#ifndef _DOC_ENUM
#define _DOC_ENUM(name)
#endif

/**
 * \ingroup types
 * \brief NexPlayer&trade; connection types.
 *
 * \since version 5.24
 */
typedef NS_ENUM(NSUInteger, NXDeviceInfoConnectionType) {
	NXDeviceInfoConnectionTypeUnknown,		///< Unknown connection type.
	NXDeviceInfoConnectionTypeNone,			///< Not connected. 
	NXDeviceInfoConnectionTypeWWAN,			///< Cellular connection.
	NXDeviceInfoConnectionTypeWiFi			///< WiFi connection.
} _DOC_ENUM(NXDeviceInfoConnectionType);



/**
 * \brief This class provides information about the current device.
 *
 * \since version 5.24
 */
@interface NXDeviceInfo : NSObject
/**
 * \brief The ID of a device.
 *
 * \since version 5.24
 */
- (NSString*) deviceId;

/**
 * \brief  The IP address of a device.
 *
 * \since version 5.24
 */
- (NSString*) ipAddress;
/**
 * \brief The device type name.
 *
 * \since version 5.24
 */
- (NSString*) deviceType;
/**
 * \brief The current iOS version of a device.
 *
 * \since version 5.24
 */
- (NSString*) platformVersion;

/**
 * \brief The type of current data connection of a device.
 *
 * \since version 5.24
 */
- (NXDeviceInfoConnectionType) dataConnectionType;
@end
