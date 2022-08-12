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

@class NexVideoTexture;

/**
 * \ingroup types
 * \brief This method is called when a new video texture is available to be rendered from the caller. 
 *
 * \param texture The new video texture available for rendering.
 *
 * \since version 5.25
 */
typedef void(^UpdatedTextureBlock)(NexVideoTexture *texture);

#define NEXVIDEORAWBITS_NUM_MAX_PLANES	3
#define NEXVIDEORAWBITS_NUM_PLANES_YUV420P	3

/**
 * \ingroup types
 * \brief This data structure contains information of YUV420 planar video planes (three planes including Y, U and V), pixel resolution and line stride.
 *
 * \since version 5.25
 */
typedef struct NexVideoRawBits {
	uint8_t *planes[NEXVIDEORAWBITS_NUM_MAX_PLANES];	///< Pointers to video planes up to 'numPlanes'
	size_t numPlanes;							///< Number of video planes in 'planes'
	size_t width;								///< Width in pixels of the Y plane, planes[0]
	size_t height;								///< Height in pixels of the Y plane, planes[0]
	size_t pitch;								///< Line stride in bytes of the Y plane, planes[0]
} NexVideoRawBits;

/** 
 * \brief This class represents data of decoded video picture. 
 *
 * \since version 5.25
 */

@interface NexVideoTexture : NSObject

/**
 * \brief This property determines whether or not the video picture is in \c rawbits property or \c pixelBuffer property.
 *
 * \c YES if the video picture can be retrieved with \c rawbits property.
 * \c NO if the video picture can be retrieved with \c pixelBuffer property.
 *
 * \since version 5.25
 */
@property (nonatomic) BOOL isRawbits;

/** 
 * \brief This property contains the information of a decoded video picture in \c CVPixelBufferRef type.  
 *
 * Valid only if \c isRawbits is \c NO.
 *
 * \since version 5.25
 */
@property (nonatomic, readonly) CVPixelBufferRef pixelBuffer;

/**
 * \brief This property contains the information of a decoded video picture in \c NexVideoRawBits type.  
 *
 * Valid only if \c isRawbts is \c YES.
 *
 * \since version 5.25
 */
@property (nonatomic) NexVideoRawBits rawbits;
@end

/**
 * \brief This class provides a way to receive decoded video pictures when a video frame is decoded and becomes available for rendering.
 *
 * \since version 5.25
 */
@interface NexVideoTextureReceiver : NSObject

/**
 * \brief The latest video texture received from the NXPlayer instance.
 *
 * \since version 5.25
 */
@property (nonatomic, strong, readonly) NexVideoTexture *videoTexture;

/**
 * \brief This method instantiates a \c NexVideoTextureReceiver instance and requests for the video texture update through the \c receivedTexture block. 
 *
 * @param player          The NXPlayer instance to request updated video textures.
 * @param receivedTexture The block will be invoked with updated video textures.
 *
 * \see UpdatedTextureBlock
 * \since version 5.25
 */
+ (id) receiverWithPlayer:(NXPlayer *) player
		   receivedTexture:(UpdatedTextureBlock) receivedTexture;
@end
