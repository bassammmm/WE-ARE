//
//  NexMetalRenderer.h
//  NexPlayerSample2_devel
//
//  Created by derrick on 2017. 3. 16..
//  Copyright © 2017년 NexStreaming. All rights reserved.
//

#import "NexPlayer.h"
#import "UnitySharedDecls.h"
#import "UnityForwardDecls.h"
#import "UnityInterface.h"
#import "UnityMetalSupport.h"
#import "UnityRendering.h"
#import "NexGLKRenderer.h"

@interface NexMetalRenderer : NexGLKRenderer 
- (id) initWithDevice:(id <MTLDevice>)device;

@end
