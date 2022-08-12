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
#import "NexPlayerViewControllerPlugins.h"

@interface NexPlayerPluginManager : NSObject
- (void) registerPlugin:(id<NexPlayerViewControllerPlugin>) plugin;
- (void) unregisterPlugin:(id<NexPlayerViewControllerPlugin>) plugin;
- (void) unregisterAll;

- (void) viewDidLoad:(UIViewController *)viewController nexPlayer:(NXPlayer *)player;
- (NSArray *) settingItems;
- (void) sender:(id) sender settingChangedKey:(NSString *)key value:(id)value;
- (id) sender:(id)sender settingValueForKey:(NSString *) key;
- (void) sender:(id) sender event:(NexPlayerPluginEvent)  event userInfo:(NSDictionary *) userInfo;
- (BOOL) needHardResume;
- (void) resetToDefaultSettings;
- (void) sender:(id)sender didSelectRowFor:(NSString *)key;

@end
