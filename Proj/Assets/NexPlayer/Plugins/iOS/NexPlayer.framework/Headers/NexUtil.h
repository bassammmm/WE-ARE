//
//  NexUtil.h
//  Unity-iPhone
//
//  Created by derrick on 2017. 3. 13..
//
//

#import <Foundation/Foundation.h>
#import <CommonCrypto/CommonDigest.h>

@interface NexUtil : NSObject{}
+ (NSString*)getFileInformation:(NSString *)fileName;
+ (void) simpleAlertWithTitle:(NSString *) title message:(NSString *) message;
+ (NSString*)MD5String:(NSString *) string;
+ (NSArray*)localSubtitleFiles;
+ (NSArray*)localVideoFiles;
+ (NSString*)applicationDocumentsDirectory;
+ (NSArray*)localFiles;
+ (BOOL)CheckSubtitleFile :(NSString *) title;
+ (BOOL)CheckVideoFile :(NSString *) title;
+ (NSString*)base64EncodeToString:(NSData *)receivedData;
+ (NSString*)convertToHex:(NSData*)data;
+ (NSData*)sha1HashGenerator:(NSString *)message;
@end
