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
#import <Foundation/Foundation.h>
#import <NexPlayerSDK/NexPlayerSDK.h>
#import "NXClientInfo.h"
#import "NexWidevineDelegate.h"


/**
 * \mainpage Widevine Integration with NexPlayer&trade;&nbsp;SDK
 *
 * \section legal Legal Notices
 *
 * \par Disclaimer for Intellectual Property
 * <i>This product is designed for general purpose, and accordingly the customer is
 * responsible for all or any of intellectual property licenses required for
 * actual application. NexPlayer Corp. does not provide any
 * indemnification for any intellectual properties owned by third party.</i>
 *
 * \par Copyright
 * Copyright for all documents, drawings and programs related with this
 * specification are owned by NexPlayer Corp.  All or any part of the
 * specification shall not be reproduced nor distributed without prior written
 * approval by NexPlayer Corp. Content and configuration of all or any
 * part of the specification shall not be modified nor distributed without prior
 * written approval by NexPlayer Corp.
 *
 * \par
 * &copy;&nbsp;Copyright 2019 NexPlayer Corp. All rights reserved.
 *
 * \section Widevine Using the Widevine Integration Framework
 *
 * From version 5.29 of the NexPlayer&trade;&nbsp;SDK, a new framework has been added to make it easier
 * to integrate Widevine DRM into applications with NexPlayer&trade;.
 *
 * For more information on how to use the NexPlayer&trade;&nbsp;SDK with Widevine DRM,
 * please see:  {@link WidevineIntegration }
 *
 *
 * \section libVar Library Variations
 *
 * Developer Version (Dev)
 * This version is designed to work using the Widevine test license service (license.uat.widevine.com). The following two builds for developer versions are provided:
 * - Insecure: This build contains basic obfuscation and is NOT for distribution. 
 * - SIM: Built to work with the simulator, however it will NOT run on any devices.
 *
 * Release Version (Release) <br>
 * This version is designed to work using the Widevine production license servers.
 * - Symbols removed with additional security. Will NOT run with debugger or on "Jailbroken" devices.
 *
 * <b>Note:</b> Unprotected dylibs (using the dev release) will not work in the Widevine production license service environment and can not be commercially released.
 *
 *
 * \section code Example Code
 *
 * -# Add WidevineIntegration.framework, which is included in the NexPlayer&trade;&nbsp;SDK delivery package to the Application project as an Embedded Binary.
 * -# Add widevine_cmd_sdk_release.framework, which is included in the NexPlayer&trade;&nbsp;SDK delivery package to the Application project as an Embedded Binary.
 * -# Import <WidevineIntegration/WidevineIntegration.h>. 
 * -# Create NXClientInfo instance and setup properties. 
 * -# Create WidevineIntegration with NXClientInfo instance. 
 * -# Invoke [widevineIntegration start] before opening content.
 * -# Invoke [widevineIntegration stop] before closing content. 
 *
 * \code
 
#import <WidevineIntegration/WidevineIntegration>

NXPlayer *player;
WidevineIntegration *widevine;
NXClientInfo* clientInfo;

- (void) initializePlayer {					
	player = .....
	self.player = player;
	
	// Create NXClientInfo and Setup
	self.clientInfo = [[NXClientInfo alloc] init];
	clientInfo.productName = @"WidevineTest";
	clientInfo.companyName = @"NexPlayer";
	clientInfo.deviceName = @"iPhone";
	clientInfo.modelName = @"6";
	clientInfo.archName = @"arm64";
	clientInfo.buildInfo = @"0.1";
	
	// Create WidevineIntegration with clientInfo
	self.widevine = [[WidevineIntegration alloc] initWithNXPlayer:player clientInfo:clientInfo];
}

- (void) openPlayer {
	// Setup LicenseServerURL
	self.widevine.licenseServerUrl = @”https://widevine-proxy.appspot.com/proxy”;

	// Start WidevineIntegration before opening the content.
	[self.widevine start];
	[self.player open:@"http://dash-001.nexstreaming.com/dash/internal/encypted_live/live.mpd"];
}

- (void) closePlayer {
	// Stop WidevineIntegration before closing content.
	[self.widevine stop];
	[self.player close];
}

\endcode
 */

/**
* \defgroup types Types
* \defgroup property Properties
*/

#ifdef __cplusplus
extern "C" {
#endif

/**
 * \brief This interface allows the Widevine DRM to integrate into NexPlayer&trade;&nbsp;.
 *
 * \since version 5.29
 */
@interface WidevineIntegration : NSObject

/** 
 * \ingroup property
 * \brief This property sets the player to offline mode. Default value is \c FALSE.
 * \since version 5.29
 * @deprecated Use offlineMode instead.
 */
@property (nonatomic) BOOL isOfflineVod;

/**
 * \ingroup property
 * \brief This property sets the player to offline mode. Default value is \c 0.
 * \since version 5.40
 */
@property (nonatomic) NSInteger offlineMode;

/** 
 * \ingroup property
 * \brief This property sets the license server URL for authentication. Default value is \link https://proxy.uat.widevine.com/proxy\endlink
 * \since version 5.29
 */
@property (nonatomic, strong) NSString* licenseServerUrl;

/**
 * \brief The designated initializer of \c WidevineIntegration.
 *
 * \param[in] nxplayer		An initialized \c NXPlayer instance. In order for the receiver to work properly, the \c nxplayer must be in the \c NXPlayerStateClose or \c NXPlayerStateNone state.
 * 
 * \param[in] clientInfo	An \c NXClientInfo instance. All the properties should be set properly.
 * 
 * \since version 5.29
 */
- (id)initWithNXPlayer:(NXPlayer *)nxplayer clientInfo:(NXClientInfo*)clientInfo;

/**
 * \brief This method starts the Widevine Integration framework.
 *
 * \since version 5.29
 */
- (void)start;

/** 
 * \brief This method stops the Widevine Integration framework.
 * 
 * \since version 5.29
 */
- (void)stop;

/**
* \brief This method adds HTTP header fields when sending requests to the Key Server.
*
* \warning  This <b>must</b> be called before \c WidevineIntegration.start.
*
* \param[in] key		Key value for the HTTP header field.
* 
* \param[in] value		Value for the key to allow a client application to provide additional message parameters to the server.
*
*/
- (void)addHeaderFieldWithKey:(NSString*)key value:(NSString*)value;

/**
 * \brief This method sets HTTP request timeout when requesting drm Server.
 *
 * \warning  This <b>must</b> be called before \c WidevineIntegration.start.
 *
 * \param[in] requestTimeout        timeout value when request drm server.
 *
 */
- (void)addLicenseRequestTimeout:(NSInteger)requestTimeout;

/**
* \brief This method removes HTTP header fields which was set by WidevineIntegration.addHeaderFieldWithKey
*
* \warning  This <b>must</b> be called before \c WidevineIntegration.start.
*
* \param[in] key		Key value for the HTTP header field.
*
*/
- (void)removeHeaderFieldWithKey:(NSString*)key;

@property (nonatomic, weak) id<NexWidevineDelegate> nexWVdelegate;

@end

#ifdef __cplusplus
}
#endif
