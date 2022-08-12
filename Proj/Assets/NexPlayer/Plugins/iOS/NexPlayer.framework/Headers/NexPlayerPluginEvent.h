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

typedef NS_ENUM(NSUInteger, NexPlayerPluginEvent)
{
	NexPlayerPluginEventPlaybackWillOpen,
	NexPlayerPluginEventPlaybackDidBegin,
	NexPlayerPluginEventPlaybackWillStop,
	NexPlayerPluginEventPlaybackDidStop,
	NexPlayerPluginEventPlaybackWillClose,
	NexPlayerPluginEventPlaybackDidClose,
	NexPlayerPluginEventPlaybackDidPause,
	NexPlayerPluginEventPlaybackDidResume,
	NexPlayerPluginEventPlaybackDidReceiveError,
	NexPlayerPluginEventPlaybackWillSeek,
	NexPlayerPluginEventPlaybackWillOpenForStore,
	NexPlayerPluginEventPlaybackDidStopForStore,
};

#define NexPlayerPluginEventUserInfoKeyErrorCode @"errorCode"
#define NexPlayerPluginEventUserInfoKeyErrorDesc @"errorDesc"
#define NexPlayerPluginEventUserInfoKeyTimestamp @"timestamp"
#define NexPlayerPluginEventUserInfoKeyTargetTime @"targetTime"
#define NexPlayerPluginEventUserInfoKeyHardResume @"hardResume"

@interface NexPlayerPluginEventTool : NSObject
+ (NSString *) eventName:(NexPlayerPluginEvent) event;
+ (NSString *) shortEventName:(NexPlayerPluginEvent) event;

@end
