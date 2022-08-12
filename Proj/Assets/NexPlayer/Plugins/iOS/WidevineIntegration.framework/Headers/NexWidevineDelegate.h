/******************************************************************************
 * File Name        : NexWidevineDelegate.h
 * Description      : WidevineIntegration
 *******************************************************************************
 * Copyright (c) 2002-2019 NexPlayer Corp. All rights reserved.
 * http://www.nexplayer.com
 *
 * THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 * KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 * PURPOSE.
 ******************************************************************************/

#import <UIKit/UIKit.h>

/**
 * \brief A protocol you can implement if you wish to manipulate the Widevine data.
 *
 * \since version 5.35.x
 */
@protocol NexWidevineDelegate <NSObject>


/**
 *
 * NexPlayer&trade;&nbsp; will call the methods provided in this interface
 * automatically during playback to notify the application when NexPlayer receives the key data
 * sent from Widevine license key server.
 *
 * In most cases, the handling of this event is optional; NexPlayer&trade;&nbsp;
 * will continue to play content normally without the application doing anything
 * special in response to the event received.
 *
 * \param receivedData	The received data from Widevine license key server.
 *
 * \return  The final license key data to be used when NexPlayer decrypts the Widevine data.
 *
 * \since version 5.35.x
 */
@optional
- (NSData*)processAfterLicenseServer:(NSData*)receivedData;
- (NSData*)onLicenseRequest:(NSData*)receivedData;
@end
