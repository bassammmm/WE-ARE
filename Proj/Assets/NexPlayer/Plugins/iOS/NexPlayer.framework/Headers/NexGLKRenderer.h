
#import <Foundation/Foundation.h>
#import <GLKit/GLKit.h>
#import <NexPlayerSDK/NexVideoTextureReceiver.h>
#import <CoreMedia/CMTime.h>


@interface NexGLKRenderer : NSObject
@property (nonatomic, strong) NexVideoTexture *videoTexture;
@property (nonatomic) BOOL autoRotationOn;

- (id) initWithEAGLContext:(EAGLContext *) context;
- (intptr_t)curFrameTexture;

@end