//
//  AlticastUtil.h
//  Unity-iPhone
//
//  Created by DINO1 on 2018. 11. 15..
//

#import <Foundation/Foundation.h>
#import "NexUtil.h"

@interface AlticastUtil : NSObject{}

- (void)initAlticast:(NSMutableDictionary *)optionalHeader Secret :(NSString*)secret;
- (void)setAlticastSecretKey:(NSString*)secret;
- (void)setAlticastOptionalHeader:(NSMutableDictionary*)optionalHeader;
- (NSString*)generateHashForAlticast:(NSString*)licenseChallenge;
- (NSString*)getAlticastSecretKey;

@end
