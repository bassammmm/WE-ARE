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
#define INVALID_8BYTE 0xFFFFFFFFFFFFFFFF
#define INVALID_4BYTE 0xFFFFFFFF

#define _EXTIF_SUCCESS 0
#define _EXTIF_ERROR 1
#define MAX_BUF_SIZE 5*1024*1024

@interface NexPlayerHTTPRetrieveStoreUtils : NSObject{
    
}

+ (NSString*) applicationDocumentsDirectory;
+ (NSString*) _convURLtoMD5:(NSString*)URL
                     offset:(unsigned long long)dwOffset
                     length:(unsigned long long)dwLength
                  storePath:(NSString*)path;
+ (NSString *) storePath;
+ (NSString *) pathForMediaURL:(NSString *) mediaURL;
@end
