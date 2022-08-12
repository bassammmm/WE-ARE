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
#import <NexPlayerSDK/NexPlayerSDK.h>
#import "NexPlayerPluginEvent.h"


@protocol NexPlayerViewControllerPlugin <NSObject>
- (void) viewDidLoad:(id) sender nexPlayer:(NXPlayer *) player;
@optional
- (void) registered:(id) sender;
- (void) unregistered:(id) sender;
- (void) sender:(id) sender settingChangedKey:(NSString *) key value:(id)value;
- (id) sender:(id) sender settingValueForKey:(NSString *) key;
- (BOOL) needHardResume;
- (void) resetToDefaultSettings;
- (void) sender:(id)sender didSelectRowFor:(NSString *)key;

/* NSArray<NSDictionary>, SettingsSupplyRowMakeXXX() results. see SettingsTableViewSupply for details. */
- (NSArray *) settingItems:(id) sender;

- (void) sender:(id) sender event:(NexPlayerPluginEvent) event userInfo:(NSDictionary *) userInfo;
@end

@interface NexPlayerViewControllerPlugins : NSObject

+ (NSArray *) list;
@end
