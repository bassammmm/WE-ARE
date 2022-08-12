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
#import "NXPlayer.h"

@interface NexClientTimeShiftParams : NSObject

- (id) initWithBufferPath:(NSString*)bufferPath;

/*
 \brief The folder name where temporary data for time shifting will be stored when there is no more storage available in the memory buffer.
 If there is enough memory and no folder is needed, this parameter will be \c NULL.
*/
@property (nonatomic, strong) NSString* fileBufferPath;

/*
 \brief Size of the memory buffer for the the time shift feature in \c megabytes (MB). If the size set to this parameter is bigger than the actual
 memory available, extra realtime data will be saved in the folder set by the parameter fileBufferPath.
*/
@property (nonatomic) NSUInteger timeshiftBufferSize;

/*
 \brief Maximum duration for the time shift feature, or how much time the user can shift back in live content in \c minutes.
*/
@property (nonatomic) NSUInteger timeshiftDuration;

/* \brief Maximum duration for the streaming data backup feature, or how much time (of streamed data files preceding the current TS file) can be stored.
 Normally, streamed data files preceding the latest TS file will be deleted to maintain the allowed memory buffer size.
 However, this parameter allows the streamed data files preceding the latest TS file to be kept and stored if there is free space available.
 For example, when the available memory buffer is larger than the value set for the parameters uiTimeShiftBufferSize or timeshiftDuration,
 this parameter allows users to seek backwards in live content during playback for the specified amount of time.
 If this parameter is set to the default value 1, streamed data files for the 1 minute preceding the latest TS file will be kept.
 If this parameter is set to 0, all remaining storage space will be available to keep previously streamed data files.
 When this parameter is set to 0 and the parameter strFileBufferPath is set to save streamed data in another storage folder, this parameter will be automatically set to 1.
*/
@property (nonatomic) NSUInteger maxBackwardDuration;

@end


@interface NexClientTimeShiftController:NSObject

- (id) initWithNexPlayer:(NXPlayer*) nexplayer param:(NexClientTimeShiftParams*)params;

/*
 This method enables the client time shift feature in the NexPlayer&trade;&nbsp;SDK.
*/
- (void) enable;

/*
 This method disables the client time shift feature in the NexPlayer&trade;&nbsp;SDK.
*/
- (void) disable;

@end

