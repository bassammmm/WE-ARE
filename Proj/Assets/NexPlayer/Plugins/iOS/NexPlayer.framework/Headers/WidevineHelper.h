//
//  WidevineIntegration.h
//  Unity-iPhone
//
//  Created by NexStreamingCorp on 31/03/2017.
//
//

#import <Foundation/Foundation.h>
#import <NexPlayerSDK/NexPlayerSDK.h>
#import <WidevineIntegration/WidevineIntegration.h>
#import "NexUtil.h"
#import "AlticastUtil.h"

@interface WidevineHelper : NSObject {}

- (id)initWithPlayer:(NXPlayer *)player with :(NSString*)path;
- (void)startWidevine:(id)sender;
- (void)stopWidevine:(id)sender;

- (void)addOptionHeader:(NSDictionary*)headerValue;
- (void)setSecretKey:(NSString*)secret;

- (void)setUseLicenseCache:(BOOL)bUse;
- (void)setLicenseRequestTimeout:(NSUInteger)value;
@end
