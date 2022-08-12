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

//
//  CAUTION: The API described by this header is experimental and subject
//           to change.  It may not be stable and should not be used in
//           production applications.
//

#import <Foundation/Foundation.h>
#import "NXPlayerView.h"

@protocol NXThumbnailMakerDelegate <NSObject>
- (void)thumbnailMaker:(id)sender madeThumbnail:(UIImage*)thumbnail forContentPath:(NSString*)contentPath;
- (void)thumbnailMaker:(id)sender failedWithError:(NSError*)error forContentPath:(NSString*)contentPath;
@end

@interface NXThumbnailMaker : NSObject <NXPlayerDelegate> 

@property (nonatomic,weak) id<NXThumbnailMakerDelegate> delegate;
@property (nonatomic,readonly) BOOL makingThumbnail;

- (void)makeThumbnailForPath:(NSString*)contentPath
                       width:(unsigned int)width
                      height:(unsigned int)height
                 frameNumber:(unsigned int)frameNumber;

- (void)cancelMakingThumbnail;

@end
