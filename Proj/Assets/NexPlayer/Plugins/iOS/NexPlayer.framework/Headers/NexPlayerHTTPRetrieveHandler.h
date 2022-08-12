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
#import "NexPlayerHTTPRetrieveStoreUtils.h"

@interface NexPlayerHTTPRetrieveHandler : NSObject<NXHTTPRetrieveDelegate>{
    NexPlayerHTTPRetrieveStoreUtils* m_Utils;
    unsigned long long m_pDataBufSize;
    char* m_pDataBuf;
}
@property (nonatomic,strong)    NSString*     strDocumentPath;
@property (nonatomic,strong) NSString* mediaURL;

@end
