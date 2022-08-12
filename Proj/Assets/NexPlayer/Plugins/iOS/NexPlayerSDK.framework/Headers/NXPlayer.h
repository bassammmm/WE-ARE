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
#import <QuartzCore/QuartzCore.h>
#import "NXDRMDescrambler.h"
#import "NXWMDRMDescrambler.h"
#import "NXSmoothStreamFragmentDescrambler.h"
#import "NXRemoteFileIOInterface.h"
#import	"NXProperty.h"
#import "NXError.h"
#import "NXContentInfo.h"
#import "NXMediaStreamInfo.h"
#import "NXTypes.h"
#import "NXPlayerDelegate.h"
#import "NXAsfPlayReadyDescrambler.h"
#import "NXSmoothStreamPlayReadyDescrambler.h"
#import "NXHLSTSDescrambler.h"
#import "NXSubtitleTrack.h"
#import "NXHTTPCredentialsProvider.h"
#import "NXManifestAndPlaylistDescrambler.h"
#import "NXPiffPlayReadyDescrambler.h"
#import "NXPDBlockDescrambler.h"
#import "NXDeceUVDescrambler.h"
#import "NXDashDRMSessionDelegate.h"
#import "NXHTTPStoreDelegate.h"
#import "NXHTTPRetrieveDelegate.h"
#import "NXABRDelegate.h"
#import "NXHLSAES128Descrambler.h"
#import "NXPlayerCallbackDelegate.h"
#import "NXStatsInfo.h"
#import "NXDynamicThumbnailDelegate.h"
typedef int ( *NEXPLAYERGetKeyExtCallbackFunc)(NSString *, long, NSData*, long, intptr_t, intptr_t);

struct _NXInstanceData;

/**
 *
 * \brief This protocol must be adopted and implemented by the player to receive
 *        updates to content information as content is played back.
 *
 * It will be used each time information about the playing content changes,
 * for example when a track or stream changes.
 *
 * For more details about the recorded information of the current content,
 * please see \ref NXContentInfo.
 */
@protocol NXPlayerContentInfoUpdateReceiver <NSObject>
/**
 * \brief Sent when content information is updated.
 *
 * This event is sent whenever content information changes and is updated
 * for the associated instance of NexPlayer&trade;.
 *
 * \param nxplayer  The instance of NexPlayer&trade;&nbsp;where content information changed.
 *
 */
- (void)nexPlayerDidUpdateContentInfo:(id)nxplayer;
@end

/**
 * \brief  This protocol must be adopted and implemented to support and display CEA 608
 *         closed captions in content.
 *
 * Whenever CEA 608 closed caption information is updated and new caption information
 * is ready, this protocol will be used to receive the updated information event.
 *
 * For more information about CEA 608 closed captions, please see \ref NXCEA608Caption.
 *
 *
 * \since version 5.8
 */
@protocol NXPlayerCEA608CaptionUpdateReceiver <NSObject>
/**
 *
 * \brief This method receives the updated caption information for content with CEA 608 closed captions.
 *
 * \param[in] nxplayer  The calling NexPlayer&trade;&nbsp;instance.
 * \param[in] caption   The new caption information to display (see NXCEA608Caption
 *                       for details).
 * \param channel  The channel from which the caption information was received. (see
 *                 NXTypes::NXCEA608Channel and NXPlayer::selectedCEA608Channel for more information).
 *
 * \since version 5.8
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
   updatedCaption:(NXCEA608Caption*)caption
 forCEA608Channel:(NXCEA608Channel)channel;
@end

/**
 * \brief This class represents a player instance, and provides for opening,
 *		  playing and controlling both local and streaming content.
 * 
 * If the content includes video, this class requires a CAEAGLLayer in which to
 * display the video.
 *
 * The NXPlayerView class provides a CAEAGLLayer for video output, and even
 * handles the creation of an associated NXPlayer instance automatically (this
 * instance can be accessed through NXPlayerView::player).
 *
 * Alternatively, you can create your own UIView subclass with CAEAGLLayer
 * support, and assign the layer from that class to NXPlayer::renderLayer.  If
 * you do this, you should also have the \c layoutSubviews method of the custom
 * UIView subclass call NXPlayer::prepareVideoBuffers to adjust the size of the
 * OpenGL buffers to match the new size of the layer.
 * 
 * If your content does not include video, or if you do not care about
 * displaying that video, you may safely create an NXPlayer instance without
 * an associated render layer.
 */
@interface NXPlayer : NSObject

#pragma mark - properties

/**
 * \brief The delegate for the NXPlayer instance.
 * 
 * The delegate receives all of the notifications about events that occur
 * during playback.  For example, if you wish to perform an action when the
 * content has finished playing, you would do that by setting a delegate.
 * 
 * Any object may serve as a delegate, as long as it implements the
 * NXPlayerDelegate protocol.  Generally, the view controller that owns the
 * player view also serves as the delegate.  The delegate should provide a
 * method for any event it wishes to handle.
 *
 * \see NXPlayerDelegate for details on events that can be captured
 */
@property (nonatomic,weak)	id<NXPlayerDelegate>					delegate;

/**
 * \brief Specifies a receiver to be notified of changes to the
 *        current content information.
 *
 * <b>CAUTION:</b>  This is automatically set by NXPlayerView, and should
 *                  not be changed for NXPlayer instances that are connected
 *                  to NXPlayerView instances.
 *
 * Normally, the \c nexPlayerDidUpdateContentInfo: method of the delegate should
 * be used instead.  This is useful for cases such as NXPlayerView, where the
 * size of the player view is being managed by something other than the delegate.
 */
@property (nonatomic,weak)    id<NXPlayerContentInfoUpdateReceiver>   contentInfoUpdateReceiver;

/**
 * \brief Specifies a receiver to be notified of changes to the
 *        current CEA 608 closed caption information.
 *
 * <b>CAUTION:</b>  This is automatically set by NXPlayerView, and should
 *                  not be changed for NXPlayer instances that are connected
 *                  to NXPlayerView instances.
 *
 * Normally, the \c nexPlayer:updatedCaption:forCEA608Channel: method of the 
 * delegate should be used instead.  This is useful for cases such as 
 * NXPlayerView, where the size of the player view (and matching NXCEA608CaptionView)
 * is being managed by something other than the delegate.
 *
 * \since version 5.8
 */
@property (nonatomic,weak)    id<NXPlayerCEA608CaptionUpdateReceiver> CEA608CaptionUpdateReceiver;

/*
 *
*/
@property (nonatomic, weak)	id<NXABRDelegate> ABRDelegate;


/**
 * \brief An object that conforms to NXDRMDescrambler that will handle DRM descrambling.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble DRM encrypted content before NexPlayer&trade;&nbsp;
 * decodes and plays that content, you should define a class that handles the
 * descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXDRMDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXWMDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 * 
 */
@property (nonatomic,weak)	id<NXDRMDescrambler>					DRMDescrambler;

/**
 * \brief An object that conforms to NXManifestAndPlaylistDescrambler that will handle manifest and playlist descrambling.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble manifests and/or playlists before NexPlayer&trade;&nbsp;
 * processes them, you should define a class that handles the descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to process playlist
 * or manifest contents.
 *
 * \see \ref NXManifestAndPlaylistDescrambler for more information on how to implement a descrambler object of this type.
 * 
 * \since version 5.9
 *
 */
@property (nonatomic,weak)    id<NXManifestAndPlaylistDescrambler>    manifestAndPlaylistDescrambler;

/**
 * \brief An object that conforms to NXWMDRMDescrambler that will handle WM-DRM descrambling.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble WM-DRM encrypted content before NexPlayer&trade;&nbsp;
 * decodes and plays that content, you should define a class that handles the
 * descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXWMDRMDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 * 
 */
@property (nonatomic,weak)	id<NXWMDRMDescrambler>					WMDRMDescrambler;

/**
 * \brief An object that conforms to NXAsfPlayReadyDescrambler that will handle PlayReady ASF descrambling.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble PlayReady encrypted ASF content before NexPlayer&trade;&nbsp;
 * decodes and plays that content, you should define a class that handles the
 * descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXAsfPlayReadyDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXWMDRMDescrambler
 * \see NXDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXRemoteFileIOInterface
 * 
 */
@property (nonatomic,weak)	id<NXAsfPlayReadyDescrambler>			asfPlayReadyDescrambler;

/**
 *
 * \brief An object that conforms to NXDeceUVDescrambler that will handle DECE UV(Ultra Violet) descrambling.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble DECE UV encrypted content before NexPlayer&trade;&nbsp;
 * decodes and plays that content, you should define a class that handles the
 * descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXDeceUVDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXWMDRMDescrambler
 * \see NXDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXAsfPlayReadyDescrambler
 * \see NXRemoteFileIOInterface
 * 
 * \since version 5.16
 */
@property (nonatomic,weak)	id<NXDeceUVDescrambler>			deceUVDescrambler;

/** For internal use only.  Please do not use. */
@property (nonatomic,weak)	id<NXDashDRMSessionDelegate>	dashDRMSessionDelegate;

/**
* \brief The delegate for the HLS offline storage feature in NexPlayer&tm;. 
* 
* Any application that will handle HLS offline storage must implement this property. 
* \since version 5.24 
*/
@property (nonatomic,weak)	id<NXHTTPStoreDelegate> httpStoreDelegate;

/**
* \brief The delegate for the retrieval and offline playback of HLS content stored with NexPlayer&tm;. 
* 
* Any application that will handle retrieval of HLS content stored for offline playback must implement this property.
* \since version 5.24 
*/
@property (nonatomic,weak)	id<NXHTTPRetrieveDelegate> httpRetrieveDelegate;
/**
 * \brief An object that conforms to NXHLSAES128Descrambler that will handle descrambling of HLS AES128 encrypted content.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble HLS AES128 encrypted content before NexPlayer&trade;&nbsp;
 * decodes and plays that content, you should define a class that handles the
 * descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXHLSAES128Descrambler for more information on how to implement a descrambler object of this type.
 * \see NXDeceUVDescrambler
 * \see NXWMDRMDescrambler
 * \see NXDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXAsfPlayReadyDescrambler
 * \see NXRemoteFileIOInterface
 * 
 * \since version 5.16
 */
@property (nonatomic,weak)	id<NXHLSAES128Descrambler>		hlsAESDescrambler;

/**
 * \brief An object that conforms to NXSmoothStreamFragmentDescrambler that will handle descrambling of Smooth Streaming fragments.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble fragments of encrypted Smooth Streaming
 * content before NexPlayer&trade;&nbsp;decodes and plays that content, you should
 * define a class that handles the descrambling operation and assign an instance
 * of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXSmoothStreamFragmentDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXDRMDescrambler
 * \see NXWMDRMDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 * 
 */
@property (nonatomic,weak)	id<NXSmoothStreamFragmentDescrambler>	smoothStreamFragmentDescrambler;


/**
 * \brief An object that conforms to NXPiffPlayReadyDescrambler that will handle descrambling of Piff PlayReady content.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble Piff PlayReady
 * content before NexPlayer&trade;&nbsp;decodes and plays that content, you should
 * define a class that handles the descrambling operation and assign an instance
 * of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \since version 5.9
 *
 * \see \ref NXPiffPlayReadyDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXDRMDescrambler
 * \see NXWMDRMDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 *
 *
 */
@property (nonatomic,weak)    id<NXPiffPlayReadyDescrambler>          piffPlayReadyDescrambler;

/**
 * \brief An object that conforms to NXPDBlockDescrambler that will handle descrambling of Progressive Download content.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble blocks of Progressive Download before NexPlayer&trade;&nbsp;
 * decodes and plays that content, you should define a class that handles the
 * descrambling operation and assign an instance of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \since version 5.9
 *
 * \see \ref NXPDBlockDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXWMDRMDescrambler
 * \see NXDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 *
 *
 */
@property (nonatomic,weak)    id<NXPDBlockDescrambler>          PDBlockDescrambler;

/**
 * \brief An object that conforms to NXSmoothStreamPlayReadyDescrambler that will handle descrambling of Smooth Streaming PlayReady content.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble Smooth Streaming PlayReady
 * content before NexPlayer&trade;&nbsp;decodes and plays that content, you should
 * define a class that handles the descrambling operation and assign an instance
 * of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXSmoothStreamPlayReadyDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXDRMDescrambler
 * \see NXWMDRMDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 * 
 */
@property (nonatomic,weak)    id<NXSmoothStreamPlayReadyDescrambler>   smoothStreamPlayReadyDescrambler;

/**
 * \brief An object that conforms to NXHLSTSDescrambler that will handle descrambling of HTTP Live Streaming TS segments.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your application needs to descramble HTTP Live Streaming TS segments
 * before NexPlayer&trade;&nbsp;decodes and plays that content, you should
 * define a class that handles the descrambling operation and assign an instance
 * of that class to this property.
 *
 * If there is an object assigned to this property, the player will call methods
 * of that object to perform descrambling prior to attempting to decode the content
 * for playback.
 *
 * \see \ref NXHLSTSDescrambler for more information on how to implement a descrambler object of this type.
 * \see NXDRMDescrambler
 * \see NXWMDRMDescrambler
 * \see NXRemoteFileIOInterface
 * \see NXAsfPlayReadyDescrambler
 * 
 */
@property (nonatomic,weak)    id<NXHLSTSDescrambler>  HLSTSDescrambler;

/**
 * \brief An object that conforms to NXRemoteFileIOInterface that will handle file input and output.
 *
 * \note Like a delegate, this is <em>not retained</em>.
 *
 * If your are playing back local content that is not available via the standard
 * operating system file APIs, you can provide your own replacement functions which
 * NexPlayer&trade;&nbsp;will use for opening and reading your file.
 *
 * These replacement functions are provided as methods of a class that the application provides.
 *
 * \see \ref NXRemoteFileIOInterface for more information on how to implement a class 
 *				that replaces that standard file input and output functions.
 * \see NXDRMDescrambler
 * \see NXWMDRMDescrambler
 * \see NXSmoothStreamFragmentDescrambler
 * \see NXAsfPlayReadyDescrambler
 * 
 */
@property (nonatomic,weak)	id<NXRemoteFileIOInterface>				remoteFileIOInterface;

/**
 * \brief  An object that will handle requests for HTTP credentials.
 *
 * Whenever NexPlayer&trade;&nbsp;receives an HTTP 401 or 407 response during 
 * streaming play, it calls the appropriate method of NXHTTPCredentialsProvider
 * to get additional HTTP headers to use when retrying the failed request.
 *
 * This is an opportunity to add, for example, authentication credentials such as
 * a user name or password.
 */
@property (nonatomic,weak)    id<NXHTTPCredentialsProvider>   HTTPCredentialsProvider;

/**
 * \brief  NexPlayer&trade;'s output volume (gain).
 *
 * This property can be adjusted to modify the output volume of the player.  This
 * affects the output of the player before it is mixed with other sounds.  Normally,
 * this should be left at the default setting of 1.0, and the volume should be 
 * controlled by the user via the hardware buttons on the device.  However, if the
 * application contains multiple audio sources (or if there is other audio being
 * played on the device), this property can be used to reduce the NexPlayer&trade;
 * volume in relation to other sounds.
 *
 * The valid range for this property is 0.0 ~ 1.0.  A value of 0.0 will silence
 * the output of the player, and a value of 1.0 (the default) plays the audio at
 * the original level, affected only by the device master volume setting (controlled
 * by the hardware buttons).
 *
 * Do not use this setting for volume controlled by the user.  Instead, use
 * the MPVolumeView class provided by iOS, in order to conform to the iOS
 * Human Interface Guidelines.  The MPVolumeView provides a volume slider that
 * controls the device master volume (the same volume adjusted by the hardware
 * volume buttons) and allows the user to select the output destination for the
 * audio (the audio route) if multiple output devices are available.
 */
@property (nonatomic)    float                                   gain;

/**
 * \brief The current playback position, in milliseconds.
 *
 * For local and streaming on-demand content, this is the number of milliseconds
 * from the beginning of the content.
 *
 * For live streaming content, this is the number of milliseconds from the 
 * seek base.
 */
@property (nonatomic,readonly)	NXDuration								currentTimeStamp;

/**
 * \brief The current seek base.
 *
 * If content is seekable, this indicates the beginning of the portion of content
 * where seek can be performed.  For local and progressive download content, this will
 * be zero, but in the case of live content, this will be a constantly shifting
 * value that indicates the start of the "seekable window" within the live content.
 * The end of the  seekable window can be determined using the property \c seekableLength.
 *
 * These two properties allow live content to be timeshifted based on the amount of content
 * available on the server.
 *
 * See NXPlayerDelegate::nexPlayer:seekableStateChangedTo:seekBase:seekableLength:
 * for additional information.
 *
 * \since version 5.8
 *
 */
@property (nonatomic,readonly)  uint64_t                      seekBase;

/**
 * \brief The current seekable length.
 *
 * If content is seekable, this property provides the length of the portion
 * of the content that is seekable.  While this will be the entire length
 * of a local seekable file, or the downloaded portion of a progressively
 * downloaded file, this value may also be used with \c seekBase to determine
 * which portion of a live stream is within the seekable window.
 *
 * For more information, please see the introductory section on \ref timeshift "server-side timeshifting".
 *
 * \since version 5.8
 */
@property (nonatomic,readonly)  NSUInteger                            seekableLength;

/**
 * \brief Contains information on the content that is currently playing.
 *
 * See the NXContentInfo class for details on the information that is available.
 *
 * The first time that content information becomes available, and any time 
 * thereafter that the content information has been updated, the
 * NXPlayerDelegate::nexPlayerDidUpdateContentInfo: method will be called
 * on the delegate.
 *
 * In addition, when the asynchronous open command has completed and the 
 * NXPlayerDelegate::nexPlayer:completedAsyncCmdOpenWithResult:playbackType:
 * method on the delegate is called, content information will be available
 * (unless the open command failed).
 * 
 * The content info object is re-created any time that the content information
 * is updated (the object is never updated in-place).  If the application has 
 * retained a previous content information object, that older object will
 * remain valid (albeit obsolete) until the application releases it.
 */
@property (nonatomic,readonly)	NXContentInfo*							contentInfo;

/**
 * \brief The current state of the player (paused, stopped, etc.)
 *
 * \see NXPlayerState for possible values.
 * 
 */
@property (nonatomic,readonly)	NXPlayerState							state;

/**
 * \brief Indicates if the player is currently in a seek operation.
 *
 * Note that during seek operations, the player is automatically placed in
 * a paused state.
 *
 * <b>Values</b>
 * - \c YES if the player is seeking.
 * - \c NO if the player is not seeking.
 */
@property (nonatomic,readonly)  BOOL                                    seeking;

/**
 * \brief Indicates the player status before seeking.
 *
 * When seeking, NXPlayerState will be set (NXPlayerStatePause -> seek action -> NXPlayerStatePlay) internally.
 * So, this property keeps the original (before seek action) NXPlayerState.
 *
 * This property is only valid when (BOOL)seeking is TRUE.
 * ex) In the nexPlayer:completedAsyncCmdSeekWithResult:
 *
 * \since version 5.34
 */
@property (nonatomic,readonly)  NXPlayerState                           stateBeforeSeek;

/**
 * \brief This is the CAEAGLLayer (a layer supporting OpenGLES rendering) that
 *			the player will render video into.
 *
 * \note If you are using NXPlayerView, this will have been automatically set, 
 * and should not be changed.  
 *
 * If you are using your own UIView subclass, the CAEAGLLayer from that
 * subclass must be assigned here so that the player can access it to render
 * video output.
 *
 * This should be set when NXPlayer is initially created, and before opening
 * any content.  This may be changed later as long as no content is currently
 * playing at the time.  
 *
 * You must call NXPlayer::prepareVideoBuffers once after assigning the
 * render layer, and again any time the dimensions of the render layer have
 * changed.
 *
 * \warning Changing this during playback will have unpredictable results.
 *
 * \see NXPlayer::prepareVideoBuffers
 */
@property (nonatomic,weak)	CAEAGLLayer*							renderLayer;

/**
 * \brief Available subtitle tracks.
 *
 * This is an array of NXSubtitleTrack instances listing all of the available
 * caption languages for the currently open content.
 *
 * Note that this is not the same as the text track associated with streaming
 * content. Although the two have a similar end result, functionally they are
 * different and are implemented with different mechanisms.  For streaming
 * content, the text track is selected with NXPlayer::setVideoStream:audioStream:textStream:trackAttributes:
 *
 * At present, the only way to make caption languages available is to specify
 * a subtitle file when opening the content.
 *
 * Subtitle tracks may be turned on and off individually; it is possible to 
 * turn on multiple subtitle tracks at the same time.
 *
 * For example, to turn on all subtitle tracks:
 * \code
 for( NXSubtitleTrack *track in hNexPlayer.subtitleTracks ) {
     track.enabled = YES;
 }
 * \endcode
 *
 * To turn off all subtitle tracks:
 * \code
 for( NXSubtitleTrack *track in hNexPlayer.subtitleTracks ) {
     track.enabled = NO;
 }
 * \endcode
 *
 * Each track has a variety of additional data associated with it, including a
 * track name, language, and dictionary of metadata.  It is important to note
 * that track name and language are not available for all subtitle formats; in
 * some cases, the track number (as an index in the \c subtitleTracks array) is
 * the only identification available, especially for formats that only support
 * one track.
 *
 * For SMI subtitle files, the SMI class name is provided in the metadata for
 * each track.
 *
 * The default behavior, if an NXSubtitleTrack is displayed as a string
 * (using \code [NSString stringWithFormat:@"%@", subtitleTrack] \endcode) is
 * to display the name, and if the name is not available, the language.  If
 * neither are available, the SMI class name is used.  If none of those are
 * available "Subtitle Track N" is used, where N is the 1-based index of the
 * track.
 *
 * Since SMI class names may be purely arbitrary, the best approach for an SMI
 * file is to read the file itself and parse the header to determine the actual
 * language information for each class name.
 *
 * However, if this is not an option, another method is to heuristically check
 * the string.  Many SMI files follow an ad-hoc standard of naming classes
 * using the format:
 *
 * - \c (language)(country)(type)
 * 
 * where each of these fields is a two-character uppercase code, and country
 * may be omitted.  For example:
 * 
 * - \c ENUSCC English, United State, Closed Caption
 * - \c KRCC Korean, Closed Caption
 * - \c FRFRCC French, France, Closed Caption
 *
 * Therefore, it is possible to check if the language string is a 4- or 6-letter
 * uppercase code, and if so, to parse it for language and country.  The language
 * generally an ISO 639 short (two-character) language code, and the country is
 * generally an ISO 3166-1 two-character country code.
 *
 * Since the exact heuristics that will be suitable for a given application
 * depend on the needs of the application, NexPlayer&trade;&nbsp;simply provides the
 * raw language string and does not attempt to interpret it in any way.
 *
 * If a given string is not recognized by the application, it is generally best
 * to fall back to displaying the raw string.
 */
@property (nonatomic,readonly) NSArray* subtitleTracks;

/**
 *
 * \brief Adjusts the brightness of video being played.
 *
 * This property may be set to a value between -1.0 and +1.0,
 * where -1.0 represents the darkest the video can be displayed,
 * and +1.0 represents the brightest the video can be displayed.
 * This may property may be provided in an application UI to allow
 * users to adjust this setting directly.
 *
 * The default value for this property is 0.0 which is the
 * original brightness of the video.
 *
 * \note Setting value to this property has no effect when the video toolbox hardware 
 *       accelerated decoding service is used.
 *
 * \since version 5.8
 */
@property (nonatomic) float brightnessAdjustment;

/**
 *
 * \brief Adjusts the contrast of video being displayed.
 *
 * This property may be set to a value between -1.0 and +1.0,
 * where -1.0 represents the lowest contrast at which the video can be displayed,
 * (essentially a grey screen) and +1.0 represents the highest contrast at which
 * the video can be displayed.  This may property may be provided in an application UI to allow
 * users to adjust this setting directly.
 *
 * The default value for this property is 0.0 which is the
 * original contrast of the video.
 *
 * \note Setting value to this property has no effect when the video toolbox hardware
 *       accelerated decoding service is used.
 *
 * \since version 5.8
 *
 */
@property (nonatomic) float contrastAdjustment;

/**
 *
 * \brief Selects the channel to use to receive CEA 608 closed captions.
 * 
 * The default setting is \c NXCEA608Channel_None which indicates no channel
 * is selected and the captions are turned off or disabled.
 *
 * These channels offer different caption information for the same content, often
 * different language captions which could be selected by the user of the application
 * if desired.
 *
 * Other values are \c NXCEA608Channel_Ch1, \c NXCEA608Channel_Ch2, \c NXCEA608Channel_Ch3,
 * and \c NXCEA608Channel_Ch4, but channels 1 and 3 are the most commonly used.
 *
 * \see NXCEA608Caption
 *
 * \since version 5.8
 */
@property (nonatomic) NXCEA608Channel selectedCEA608Channel;

/**
 * \brief The name of the current SDK.
 *
 * This property provides the current name of the SDK in use, which
 * may be helpful in debugging or if multiple versions of the SDK
 * have be used.
 *
 * \since version 5.8
 *
 */
@property (nonatomic,readonly) NSString* SDKName;

/**
 * \brief  Retrieves statistical information about how content is currently being handled by NexPlayer&trade;.
 *
 * If statistics like the rate of video frames being dropped or of frames being rendered are desired, this property can 
 * be used to retrieve the FPS (frames per second) for short intervals (about 2 seconds) of content, as well as the total
 * number of decoded video frames and the number of frames rendered during that interval of content. 
 * 
 * \see NXStatsInfo
 * \since version 5.20
 */
@property (nonatomic,readonly) NXStatsInfo* statsInfo;

/**
 * \brief Set Enable/Disable playback in background.
 * It is strongly recommended for audio only channel.
 *
 * \note If you want to use this option, you should set the capability of your Application as follows:
 * App target -> capabilities -> Background Modes (On) -> Audio, AirPlay and Picture in Picture (check)
 *
 * <b>Values</b>
 * - \c YES : The player plays current content continuously although App is running in background.
 * - \c NO : The player stops or pauses when App is running in background.
 *
 * \since version 5.30
 */
@property (nonatomic) BOOL backgroundMode;

/**
 * \brief Check whether AirPlay is active.
 *
 * \note This SDK use AVPlayer internally for AirPlay.
 * Return Value is AVPlayer.isExternalPlaybackActive.
 *
 * \since version 5.34
 */
@property (nonatomic, readonly) BOOL isAirPlayActive;


#pragma mark - methods

/**
 * \brief Set to use native AV player for AirPlay internally
 *
 * \note set to use native iOS's AVPlayer for airplay.
 *
 * AV Player is only activated when using AirPlay.
 * If you use this option, it means that you couldn't use NexPlayer's advantages (DASH, MSS, 3rd party package...etc)
 * This is a class method. It's good to be set before NXPlayer init.
 * The default value for this is NO.
 *
 * \param[in] bUse use it or not.
 * - \c YES : use airplay internally
 * - \c NO : don't use airplay internally (default)
 * \returns The result value.
 *
 * \since version 5.34
 */
+(void) setAVPlayerForAirPlay:(BOOL)bUse;

/**
 * \brief Get the value for using native AV player for AirPlay internally
 *
 * \returns The result value.
 * - \c YES : use airplay internally
 * - \c NO : don't use airplay internally (default)
 *
 * \since version 5.34
 */
+(BOOL) useAVPlayerForAirPlay;

/**
 * \brief Return current play rate of AirPlay.
 *
 * This value is to check current AirPlay player's status.
 *
 * \returns
 * - \c -111.0 : invalid not activated AirPlay
 * - \c  0.0 : pause state of AirPlay
 * - \c  above 0.1 : playing of AirPlay
 *
 * \since version 5.34
 */
- (float) getAirPlayRate;

/**
 * \brief Sets the value of a NexPlayer&trade;&nbsp;property.
 *
 * See \ref prop for details.
 * 
 * \param[in] property Identifies the property to be changed.
 * \param[in] value The new value for the property.
 * \returns  NXErrorNone if successful, or another NXError value in case of failure.
 */
- (NXError)setProperty:(NXProperty)property
			   toValue:(NSInteger)value;

/**
 * \brief Sets the value of a NexPlayer&trade;&nbsp;property.
 *
 * See \ref prop for details.
 *
 * \param[in] property Identifies the property to be changed.
 * \param[in] value The new value for the property.
 * \returns  NXErrorNone if successful, or another \cNXError value in case of failure.
 *
 *\since version 5.24
 */
- (NXError)setProperty:(NXProperty)property
			   value:(NSObject *)value;

/**
 * \brief Gets the value of a NexPlayer&trade;&nbsp;property.
 *
 * See \ref prop for details.
 *
 * This returns an NXError value to indicate success or failure, and returns
 * the property value at the location pointed to by the \c value argument.
 *
 * Since the only error that can occur is an invalid property identifier,
 * in many cases it is simpler to just use NXPlayer::getProperty: instead, which
 * directly returns the property value and indicates an error by raising an
 * exception.
 * 
 * \param[in] property Identifies the property to be retrieved
 * \param[out] value Points to a location to receive the value of the property
 * \returns  NXErrorNone if successful, or another NXError value in case of failure.
 */
- (NXError)getProperty:(NXProperty)property
				 value:(NSInteger*)pValue;

/**
 * \brief Gets the value of a NexPlayer&trade;&nbsp;property
 * 
 * In the event of an error (for example, an invalid property identifier), an
 * exception is raised.
 *
 * This is the value as set with NXPlayer::setProperty:toValue:
 *
 * For a few properties, the actual value in effect may be different (for example,
 * it a property is set to a default that varies based on the protocol or
 * device).  If the actual value is needed, NXPlayer::getEffectiveProperty:
 * can be called.
 * 
 * See \ref prop for details.
 *
 * \param[in] property Identifies the property to be retrieved.
 *
 * \returns The value of the property.
 */
- (NSInteger)getProperty:(NXProperty)property;

/**
 * \brief Gets the effective value of a NexPlayer&trade;&nbsp;property.
 * 
 * In the event of an error (for example, an invalid property identifier), an
 * exception is raised.
 *
 * This is usually the value as set with NXPlayer::setProperty:toValue: but
 * it may be different for properties with defaults that change automatically.
 * 
 * See \ref prop for details.
 *
 * \param[in] property Identifies the property to be retrieved.
 *
 * \returns The effective value of the property.
 */
- (NSInteger)getEffectiveProperty:(NXProperty)property;

/**
 * \brief Specifies additional fields to be sent along with the normal headers
 *			in RTSP requests.
 *
 * RTSP requests are very similar to HTTP requests, and include a header consisting
 * of a set of required fields.  This method adds additional fields that will be
 * sent as part of future RTSP requests.
 *
 * One possible use of this, for example, is to set a user agent identifier
 * to be used in RTSP requests.
 *
 * Each call to this method adds one field.  To add multiple fields, call this
 * method multiple times.  There is currently no way to delete a field once it
 * has been added, although the value could be set to an empty string.  
 *
 * If the specified field already exists, the current value of that field and 
 * the set of RTSP methods to which it applies will be overwritten.  That is, 
 * if this method is called more than once with the same header field specified,
 * only the most recent call will be used for the value and RTSP method set of
 * that header field.
 * 
 * There are several request types that are part of the RTSP protocol,
 * and when a header is added, you must specify with which request types
 * it will be included.  This is done by performing a bitwise OR on one
 * or more of the following values, and specifying the result in the 
 * \c methodCombination parameter:
 *
 * - NXRTSPMethodNone			
 * - NXRTSPMethodDescribe		
 * - NXRTSPMethodSetup			
 * - NXRTSPMethodPlay			
 * - NXRTSPMethodPause			
 * - NXRTSPMethodTeardown		
 * - NXRTSPMethodOptions		
 * - NXRTSPMethodRedirect		
 * - NXRTSPMethodSetParameter	
 * - NXRTSPMethodGetParameter	
 * - NXRTSPMethodAnnounce		
 * - NXRTSPMethodPlaylist		
 * - NXRTSPMethodAll			
 *
 * For example:
 * \code
    [hNexPlayer addRTSPHeaderField:@"User-Agent: NexStreaming Android Player"
                        forMethods:NXRTSPMethodSetup|NXRTSPMethodPlay];
 * \endcode
 * 
 * \param[in] headerFieldString		The field to add; this should include both the 
 *									field name and the value for the field, separated
 *									by a colon character, in the normal RTSP header
 *									field format.
 *
 * \param[in] methodCombination		The combination of methods for which this header
 *									will be sent.  This is one or more of the possible
 *									values for NXRTSPMethod combined using a bitwise
 *									OR operation.
 *
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 */
- (NXError)addRTSPHeaderField:(NSString*)headerFieldString
				   forMethods:(NXRTSPMethod)methodCombination;

/**
 * \brief   This function adds additional header fields to be sent along with the HTTP headers
 *          when sending streaming requests for HLS and Smooth Streaming content.
 *
 * \param[in] headerFieldString		The field to add; this should include both the
 *									field name and the value for the field, separated
 *									by a colon character, in the normal HTTP header
 *									field format.
 *
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *
 * \since version 5.25
 */

- (NXError)addHTTPHeaderFields:(NSString*)headerFieldString;

/**
 * \brief Opens the specified content.
 *
 * This is a convenience function, and is equivalent to calling 
 * NXPlayer::open:mode:subtitles:transport:startAtTime:autoPlay:
 * with a startAtTime of zero.
 *
 * \param[in] path				Local path or local or remote URL to the content to be opened.
 * \param[in] mode				Controls how the content is opened.  See \ref NXOpenMode for details.
 * \param[in] subtitlePath		Local path to a subtitle file containing subtitles or captions to 
 *								 display with the content.  Supported formats include SMI, SRT and SUB.
 * \param[in] transport			Specifies the transport type for streaming protocols such as RTSP that 
 *								 support multiple transports.  For local content or streaming content 
 *								 that doesn't support multiple transports, this is ignored.  If unsure, 
 *								 set this to \c NXTransportTypeTCP. See \ref NXTransportType for details.
 * \param[in] autoPlay			If this is set to YES, NexPlayer automatically manages playback as follows:
 *									- Upon successfully opening content, automatically call NXPlayer::start to begin playback.
 *									- Upon reaching the end of content, automatically call NXPlayer::stop to stop playback.
 *									- Upon successfully stopping playback, automatically call NXPlayer::close to close the player instance.
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicates success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 *
 */
- (NXError)open:(NSString *)path
		   mode:(NXOpenMode)mode
	  subtitles:(NSString *)subtitlePath
	  transport:(NXTransportType)transport
	   autoPlay:(BOOL)autoPlay;

/**
 * \brief Opens the specified content.
 *
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdOpenWithResult:playbackType:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 *
 * After content has successfully been opened, you may call NXPlayer::start to
 * begin playback, or specify \c autoPlay:YES when opening the content to begin
 * playback automatically when opening is successful.
 *
 * \code
 // Open the file "test.wmv" that has been added directly to the
 // application's project in Xcode (that is, it will appear in the
 // bundle)
 NXError result = [hNexPlayer open:@"test.wmv"
 mode:NXOpenModeLocalBundle
 subtitlePath:nil
 transport:NXTransportTypeTCP
 startAtTime:0
 autoPlay:YES];
 * \endcode
 *
 * \note There are several convenience methods that simplify the opening of content
 *		 by using default values for most of the arguments.  You may use these instead
 *       of \c open:mode:subtitles:transport:autoPlay if they suit your requirements:
 *			- NXPlayer::open:
 *			- NXPlayer::openFromBundle:
 *			- NXPlayer::openAndPlay:
 *			- NXPlayer::openAndPlayFromBundle:
 *
 * \param[in] path				Local path or local or remote URL to the content to be opened.
 * \param[in] mode				Controls how the content is opened.  See \ref NXOpenMode for details.
 * \param[in] subtitlePath		Local path to a subtitle file containing subtitles or captions to 
 *								 display with the content.  Supported formats include SMI, SRT and SUB
 * \param[in] transport			Specifies the transport type for streaming protocols such as RTSP that 
 *								 support multiple transports.  For local content or streaming content 
 *								 that doesn't support multiple transports, this is ignored.  If unsure, 
 *								 set this to \c NXTransportTypeTCP. See \ref NXTransportType for details.
 * \param[in] startAtTime		The offset (in milliseconds) from the beginning of the content at which
 *                               to begin playback, if autoPlay is true.  Has no effect if autoPlay is
 *                               false.
 * \param[in] autoPlay			If this is set to YES, NexPlayer automatically manages playback as follows:
 *									- Upon successfully opening content, automatically call NXPlayer::start to begin playback.
 *									- Upon reaching the end of content, automatically call NXPlayer::stop to stop playback.
 *									- Upon successfully stopping playback, automatically call NXPlayer::close to close the player instance.
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)open:(NSString *)path 
           mode:(NXOpenMode)mode 
      subtitles:(NSString *)subtitlePath 
      transport:(NXTransportType)transport 
        startAt:(NXDuration)startAtTime 
       autoPlay:(BOOL)autoPlay;

/**
 * \brief Opens the specified content.
 *
 * This is a convenience function, and is equivalent to calling 
 * NXPlayer::open:mode:subtitles:transport:startAtTime:autoPlay:
 * with a mode of NXOpenModeAuto, a transport of NXTransportTypeTCP,
 * no subtitle path, and \c autoPlay set to \c NO
 *
 * \param[in] path Local path or local or remote URL to the content to be opened.
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)open:(NSString *)path;

/**
 * \brief Opens the specified local content from the application bundle.
 * 
 * This is a convenience function, and is equivalent to calling 
 * NXPlayer::open:mode:subtitles:transport:startAtTime:autoPlay:
 * with a mode of NXOpenModeLocalBundle, a transport of NXTransportTypeTCP,
 * no subtitle path, and \c autoPlay set to \c NO
 *
 * \param[in] path Local path relative to application bundle (usually, just a filename).
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)openFromBundle:(NSString*)path;

/**
 * \brief Opens and begins playing content.
 *
 * This is a convenience function, and is equivalent to calling 
 * NXPlayer::open:mode:subtitles:transport:startAtTime:autoPlay:
 * with a mode of NXOpenModeAuto, a transport of NXTransportTypeTCP,
 * no subtitle path, and \c autoPlay set to \c YES
 *
 * \param[in] path Local path or local or remote URL to the content to be opened.
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)openAndPlay:(NSString *)path;

/**
 * \brief Opens the specified local content from the application bundle and begins playing it.
 * 
 * This is a convenience function, and is equivalent to calling 
 * NXPlayer::open:mode:subtitles:transport:startAtTime:autoPlay:
 * with a mode of NXOpenModeLocalBundle, a transport of NXTransportTypeTCP,
 * no subtitle path, and \c autoPlay set to \c YES
 *
 * \param[in] path Local path relative to application bundle (usually, just a filename).
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)openAndPlayFromBundle:(NSString*)path;

/**
 * \brief Closes any currently open content.
 *
 * If the content is currently playing or paused, the content will be stopped first
 * before it is closed.  (This behavior differs from the old API, where the content
 * must be stopped before closing it to avoid unpredictable behavior).
 *
 * Note that in some cases (such as when this is called while content is already
 * playing, or if an open method is called while there is already open content)
 * the content we automatically be closed when the NXPlayerDelegate::nexPlayer:completedAsyncCmdStopWithResult:
 * even occurs.  In this very particular case, an additional (redundant)
 * call to the close method inside the NXPlayerDelegate::nexPlayer:completedAsyncCmdStopWithResult:
 * handler will be ignored.
 *
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 * To determine actual success or failure, check the result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)close;

/**
 * \brief Begins playback of content from the beginning.
 *
 * Content must have been opened with NXPlayer::open:mode:subtitles:transport:startAt:autoPlay:
 * (or one of the related convenience functions) and the open operation must have completed
 * (NXPlayerDelegate::nexPlayer:completedAsyncCmdOpenWithResult:playbackType: method
 * of delegate called) before playback can be started.
 *
 * If \c autoPlay was \c YES when the content was opened, playback will start
 * automatically, and it is not necessary to call this method.
 * 
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdStartWithResult:playbackType:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 *
 * Do not use this to resume paused content; use NXPlayer::resume for that, instead.
 *
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)start;

/**
 * \brief Begins playback of content from the specified time.
 *
 * Content must have been opened with NXPlayer::open:mode:subtitles:transport:startAt:autoPlay:
 * (or one of the related convenience functions) and the open operation must have completed
 * (NXPlayerDelegate::nexPlayer:completedAsyncCmdOpenWithResult:playbackType: method
 * of delegate called) before playback can be started.
 *
 * If \c autoPlay was \c YES when the content was opened, playback will start
 * automatically, and it is not necessary to call this method.
 * 
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdStartWithResult:playbackType:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 *
 * Do not use this to resume paused content; use NXPlayer::resume for that, instead.
 *
 * \param[in] startTime The offset in milliseconds from the beginning of the 
 *              content from which to start playing.
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError) startFromTime:(NXDuration)startTime;

- (NXError) startFromTime:(NXDuration)startTime pauseAfterReady:(BOOL)pause;
/**
 * \brief Stops playback of content.
 *
 * Content must be in either the playing or paused state.  If \c autoPlay was
 * specified when the content was opened, stopping the content will also cause
 * it to automatically be closed.
 *
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdStopWithResult:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 * 
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)stop;

/**
 * \brief Pauses playback of content.
 *
 * Content must be in a playing state or this has no effect.
 * 
 * Playback can be resumed by calling NXPlayer::resume.
 *
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdPause:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 *
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)pause;

/**
 * \brief Resumes playback of content that was paused with NXPlayer::pause.
 *
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdResume:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 * 
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)resume;

/**
 * \brief Seeks to the specified time in the content.
 * 
 * If the content is currently playing, it will continue playing after the seek; if
 * it is paused, it will be paused after the seek operation.
 *
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::nexPlayer:completedAsyncCmdSeek:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 * 
 * Note that seeking is not possible on all types of content.  For live content,
 * seeking may or may not be available.  To determine if seeking is possible, check
 * the \c isSeekable member of NXPlayer::contentInfo.
 *
 * In the case of live content that is seekable, the seek timestamp is relative to the seek base, \c seekBase
 * and the window within which seek can be performed in the content can be determined with the property
 * \c seekableLength.
 * 
 * \param[in] timestamp The offset in milliseconds from the beginning of the content to which to seek.
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicate success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)seekTo: (NXDuration)timestamp;

/**
 * \brief Moves to the current live position after the actual playback position. 
 *
 * Normally, when playing live content, previously recorded data (for example, a few seconds earlier than the actual live position) to avoid buffering. 
 * This method however ignores this concept and moves directly to the latest loaded playback position (where the server is currently being encoded).
 *
 * \param[in] exact If \c exact is \c YES, the player will seek exactly to the time specified by \c msec. 
 *         		  Otherwise, the playhead will seek to the nearest approximate position for faster seeking performance.
 *  
 * \return Zero for success, or a non-zero NexPlayer&trade;&nbsp;error code in the event of a failure.
 *
 * \since version 5.25
 */
- (NXError)goToCurrentLivePosition:(BOOL)exact;

/**
 * \brief Clears the render layer to black.
 *
 * When the player is paused, stopped, or even closed, the last frame that
 * was displayed will remain visible on the render layer.  This is done in
 * case an application wishes to play additional content on the same layer
 * without it flashing to black in between.  However, in many applications,
 * it is desirable to clear the render layer to black when playback is
 * stopped.  In this case, simply call this method in response to the
 * \c nexPlayer:completedAsyncCmdStopWithResult: callback of the delegate.
 *
 * This should not be called while video is actually playing, because the
 * next frame will immediately be drawn, and the black frame will merely be
 * shown for a fraction of a second, causing the video to flicker.
 * 
 * \returns  NXErrorNone if successful, or another NXError value in case of failure.
 */
- (NXError)clearToBlack;

/**
 * \brief Creates or adjusts the buffers used for rendering video to match the
 *			current dimensions of the render layer.
 *
 * \note It is not necessary to call this if you are using NXPlayerView, because
 *			that class automatically manages the render layer.
 *
 * If you provide your own UIView subclass and set up NXPlayer::renderLayer 
 * manually, you must call this function once after \c renderLayer has been set
 * up, and again any time the dimensions of the layer change.  This is usually
 * done in the \c layoutSubviews method of the UIView subclass, as follows:
 *
 * \code
	- (void) layoutSubviews {
		[player prepareVideoBuffers];
	}
 * \endcode
 * 
 * \returns  NXErrorNone if successful, or another NXError value in case of failure.
 *
 * \see NXPlayer::renderLayer
 * 
 */
- (NXError)prepareVideoBuffers;

/**
 * \brief For media with multiple streams, selects the streams that 
 * will be presented to the user.
 * 
 * The full list of available streams (if any) can be found in the
 * \ref NXContentInfo::streams member in NXPlayer::contentInfo.
 * 
 * Each stream listed in the array in content information is either an
 * audio stream or a video stream.  One stream of each type may be
 * selected for presentation to the user.
 *
 * There can be multiple tracks associated with each stream, providing
 * different levels of quality. The player switches among these strings
 * as necessary to provide the best possibly quality for the available
 * bandwidth.
 *
 * \par Custom Attributes
 * In addition to providing different levels of quality, the tracks
 * associated with a video stream can also provide different types of
 * content (for example, different camera angles). These tracks are
 * labeled with custom attributes.
 * 
 * \par
 * Custom attributes consist of key/value pairs, and zero or more may be
 * associated with any given track.  Each unique combination of custom
 * attributes makes up one \em attribute \em set.  The list of possible attribute 
 * sets available for a given stream can be found in NXMediaStreamInfo::customAttrSets.
 *
 * \par
 * You may limit the selection of tracks to only those that share a particular
 * set of custom attributes by specifying the set of key/value pairs as an
 * NSDictionary in the \c trackAttr argument.
 *
 * \note
 * This is an asynchronous operation that completes in the background.  When it is
 * finished, the NXPlayerDelegate::completedAsyncCmdSetMediaStreamWithResult:
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 *
 * 
 * \param[in] videoStream	The video stream to select.  This may be any one of the elements of
 *							NXContentInfo::streams where NXMediaStreamInfo::type is NXMediaTypeVideo.
 *							Specify \c nil to leave the video stream unchanged.
 *
 * \param[in] audioStream	The audio stream to select.  This may be any one of the elements of
 *							NXContentInfo::streams where NXMediaStreamInfo::type is NXMediaTypeAudio.
 *							Specify \c nil to leave the audio stream unchanged.
 *
 * \param[in] textStream	The text stream to select.  This may be any one of the elements of
 *							NXContentInfo::streams where NXMediaStreamInfo::type is NXMediaTypeText.
 *							Specify \c nil to leave the text stream unchanged.
 *
 * \param[in] trackAttr		A dictionary specifying the custom attributes by which to select a video
 *							track within the stream.  Only video tracks that match ALL specified
 *							attributes (both name and value) will be used.  Names and values must all
 *							be given as \c NSString instances.  Specify \c nil to use the first
 *							available combination of custom attributes (the first available attribute
 *							set) in the selected video stream.
 *
 * \returns					NXErrorNone if successful, or another NXError value in case of failure.
 *				Even if the return value indicates success, the operation may still
 *				fail later, because it completes asynchronously in the background.
 *				To determine actual success or failure, check the \c result
 *				argument of the appropriate delegate callback method.
 */
- (NXError)setVideoStream:(NXMediaStreamInfo*)videoStream
			  audioStream:(NXMediaStreamInfo*)audioStream
               textStream:(NXMediaStreamInfo*)textStream
		  trackAttributes:(NSDictionary*)trackAttr;


/**
 * \brief   Convenience function for setting audio and video streams.
 *
 * This is a convenience function, and is equivalent to calling 
 * NXPlayer::setVideoStream:audioStream:textStream:trackAttributes:
 * with \c textStream specified as \c nil.
 *
 * \param[in] videoStream	The video stream to select.
 *
 * \param[in] audioStream	The audio stream to select.
 *
 * \param[in] trackAttr		A dictionary specifying the custom attributes by which to select a video
 *							track within the stream.
 *
 * \returns					NXErrorNone if successful, or another NXError value in case of failure.
 */
- (NXError)setVideoStream:(NXMediaStreamInfo*)videoStream
			  audioStream:(NXMediaStreamInfo*)audioStream
		  trackAttributes:(NSDictionary*)trackAttr;

/**
 * \brief This method "turns" On/Off media of each Audio, Video, or Text.
 *
 * This method is only valid when the state of content is between Open and Close.
 * If you wish to apply it after play begins, call from completedAsyncCmdOpenWithResult: .
 *
 * \note This is an asynchronous operation that completes in the background. When it is
 * finished, the NXPlayerDelegate::completedAsyncCmdMediaOnOffWithResult:mediaType:bOnOff
 * method of the delegate will be called (and the \c result argument will indicate
 * success or failure).
 *
 * \param[in] bOnOff		if you want to disable the media, set to \c NO.
 * if you want to enable the media, set to \c YES.
 *
 * \param[in] mediaType		The mediaType to disable or enable.
 * The method uses NXMediaType and values below only are valid. 
 * NXMediaTypeAudio
 * NXMediaTypeVideo
 * NXMediaTypeText
 * NXMediaTypeAV		=> not recommended. Return value is not guaranteed.
 *
 * \returns NXErrorNone if successful, or another NXError value in case of failure.
 *
 * \since version 5.29
 */
- (NXError) setMediaOnOff:(BOOL)bOnOff mediaType:(NXMediaType) mediaType;

/**
 * \brief This returns the current enable state of media for Audio, Video, and Text.
 *
 * \see NXPlayer::setMediaOnOff:mediaType: This is related to the method and returns the current On/Off state of the mediaType.
 *
 *
 * \param[in] mediaType		The mediaType to disable or enable.
 * The method uses NXMediaType and only values below are valid. 
 * NXMediaTypeAudio
 * NXMediaTypeVideo
 * NXMediaTypeText
 *
 * \returns \c YES if media of mediaType is enabled; \c NO if not.
 * For invalid mediaType, it also returns \c YES, which is default value for the type.
 *
 * \since version 5.29
 */
- (BOOL) isMediaOnOff:(NXMediaType) mediaType;

/**
 * \brief  This method returns the range of the current content that is seekable.
 * 
 * This method is used to allow NexPlayer&trade;&nbsp;to support timeshifting playback within HLS Live and 
 * Smooth Streaming content.  Based on the amount of content available from the server at a particular time,
 * it determines the seekable range within the playing content which also indicates the range where playback may
 * be timeshifted.  This range will be constantly shifting as the live streaming content available from the server
 * changes in real time, so this method will need to be repeatedly called to ensure accurate shifting of playback.
 *   
 * For local content this method will always return the same two values, and the second value indicating the end 
 * of the seekable range will continuously change in progressive download (PD) content, but this method is 
 * most relevant when playing live streaming content, as with HLS and Smooth Streaming.
 *
 * For more information about how this method may be used to timeshift playback in live content, please
 * also refer to the introductory section on \ref timeshift "time shift support".
 * 
 * \param startTime[in,out]   A pointer to a \c long that is the timestamp indicating the start of the seekable range.
 * \param endTime[in, out]   A pointer to a \c long that is the timestamp indicating the end of the seekable range.
 * 
 * \since version 5.15
 */
- (void) getSeekableRange:(int32_t *) startTime
				  endTime:(int32_t *) endTime;


/**
 * \brief This method gets the date and time information in HLS content when the HLS tag, #EXT-X-PROGRAM-DATE-TIME, is included. 
 * 
 * It can be used to determine the current time of the frame and help when syncing content and text or when determining when to play text.
 *
 * \param dwOffset The time offset of the currently decoding frame's timestamp with respect to the #EXT-X-PROGRAM-DATE-TIME tag time, in milliseconds.
 * \param pValue   The playtime of the playlist. 
 *
 * \returns Always zero.
 *
 * \since version 5.17
 */
- (NSInteger) getProgramDateTime:(NSInteger*)dwOffset
					buffer:(char*)pValue;

/**
 * \brief This method sets a user cookie to be used while playing content.
 *
 *  In prior versions of the NexPlayer&trade;&nbsp; SDK, it was only possible to set a user cookie before content was opened in the player
 *  but this method makes it possible to set a cookie while content is playing. The cookie set with this method may also be 
 *  different than an initial cookie set.
 *
 * \param strCookie  The user cookie to set, as a String.
 *
 * \returns  Zero if successful, non-zero if there was an error.
 * 
 * \since version 5.17
 */
- (NXError) setUserCookie:(NSString*)strCookie;

/**
 * \brief This method allows specific subtracks to be selected and played based on the bitrates of the tracks in HLS content.
 * 
 * Only the tracks with the bitrates passed on this method with the parameter \c bitrates will be played by NexPlayer&trade;&nbsp;. 
 * However, choosing a different option with the parameter \c option allows NexPlayerTM to choose and play the selected subtracks 
 * based on the passed bitrates differently.
 * 
 * \param bitrates The bitrates of the HLS content subtracks to play, as an integer array.
 * \param option   How HLS subtracks should be played based on the bitrates selected in bitrates. This will be one of:
 *                       - NexAvailableBitrateNone:                No restriction on subtracks other than the bitrates selected in \c bitrates.
 *                       - NexAvailableBitrateMatch                Only use subtracks which have exact same bitrate as the selected bitrates passed in \c bitrates.
 *                       - NexAvailableBitrateNearest:             Only use subtracks which have the nearest bitrates to the target bitrates
 *                                                                 described in the list passed in \c bitrates. For example, if the target bitrates 
 *                                                                 passed are [300K, 600K] and the HLS playlist includes 100K, 200K, 500K, 700K tracks,
 *                                                                 only the 200K (close to 300K) and 500K (close to 600K) tracks will be used.
 *                       - NexAvailableBitrateHigh:                Only use subtracks which have bitrates equal to or higher than the target bitrate.
 *                                                                 The first bitrate in the list passed in \c bitrates is the target bitrate, the rest will
 *                                                                 be ignored.
 *                       - NexAvailableBitrateLow:                 Only use subtracks which have bitrates equal to or lower than the target bitrate.
 *                                                                 The first bitrate in the list passed in \c bitrates is the target bitrate, the rest will 
 *                                                                 be ignored.
 *                       - NexAvailableBitrateInsideRange:         Only use subtracks which have bitrates inside the range defined by the bitrates
 *                                                                 passed in \c bitrates. The first bitrate in the list is taken as the lower boundary, 
 *                                                                 the second as the upper boundary, and the rest of the list will be ignored. Subtracks 
 *                                                                 with bitrates between the lower and upper boundaries will be used.
 * \returns  Zero if successful, non-zero if there was an error.
 *
 * \since version 5.17
 */
- (NXError) setVideoBitrates:(NSUInteger *) bitrates len:(NSInteger) len withOption:(NexAvailableBitrate) option;

/**
 * \brief This method retrieves the SAR (Sample Aspect Ratio) of H.264 content when specified.
 * 
 * The sample aspect ratio (SAR) returned by this method is expressed as a ratio of the width of the sample size to the height of the sample size.
 *
 * It can be used to appropriately display content to the user.
 *
 * This sample aspect ratio will be one of the following ratios:
 * 1:1, 4:3, 3:2, 2:1, 12:11, 10:11, 40:33, 24:11, 20:11, 32:11, 80:33, 18:11, 15:11, 64:33, or 160:99.
 *
 * Note that if SAR information is not specified for given H.264 content, the returned ratio will also be 1:1.
 *
 * For more information about the SAR information included in H.264 content, 
 * please consult Table E-1 - Meaning of Sample Aspect Ratio Indicator on page 374 of the H.264 specifications (Rec. ITU-T H.264 (03/2010).
 * 
 * \param strSAR   Returns the sample aspect ratio, as a string. 
 *
 * \since version 5.17
 */
- (NXSARInfo) getSARInfo;

/**
 * \brief Registers custom ID3 metadata tags to NexPlayer&tm;.
 *
 * To set custom tags, custom ID3 tags should be registered to NexPlayer&tm;.
 *
 * In prior versions of the NexPlayer&trade;&nbsp;SDK, it was only possible to input values of the address where 
 * the required custom tag data was stored (to set any custom tags) but this method makes it possible to register the custom metadata tags
 * with the custom tag IDs passed as an array. 
 * 
 * \param tags  Custom ID3 tags as an array. 
 *
 * \returns  Always zero. 
 *
 * \since version 5.17
 */
- (NXError) setCustomID3Tags:(NSArray*)tags;

/**
 * \brief This method allows NexPlayer&trade;&nbsp;to reconnect to the media server in the case of streaming content.
 *
 * It allows NexPlayer&trade;&nbsp;to reconnect to a media server when network conditions may have
 * closed a connection.
 *
 *  \warning This is <b>only</b> supported in HLS, DASH, SmoothStreaming and PD streaming content.
 *
 * \return NXErrorNone if successful.
 *
 * \since version 5.24
 */
- (NXError) reconnectNetwork;


/**
 *
 * \brief This method allows the subtitles for particular content to be switched during playback.
 *
 * A new subtitle file can be loaded from the device's storage or
 * from a given URL as passed in the parameter \c path.
 * For example, the user can switch the subtitles to a different language while playing particular content.
 *
 * \param path		The path or the URL to the new subtitle file to use.
 *
 *
 * \since version 5.26
 */
- (void) setExternalSubtitle:(NSString *)path;

/**
 * \brief This method sets the path to the specific license file included with the NexPlayer&trade;&nbsp;SDK.
 *
 * This should be called before NXPlayer::init.
 * The license file will be included with the NexPlayer&trade;&nbsp;SDK files and when called with this API,
 * an application will be able to input the license file information to run NexPlayer&trade;.
 *
 * \warning The license file will be updated regularly, so please
 * always check for updates and be sure to replace and use the latest license file in applications built with the NexPlayer&trade;&nbsp;SDK.
 *
 * \param strKeyPath Path to the license file, as a \c String.
 *
 * \see NXPlayer::setLicenseKeyBuffer
 *
 * \since version 5.27
 */
+ (NXError)setLicenseKeyFile:(NSString *)strKeyPath;

/**
 * \brief This method inputs the license file information into a NexPlayer&trade;&nbsp; buffer.
 *
 * This should be called before NXPlayer::init.
 *
 * \param strBuffer  Information in the license file, as a \c String.
 *
 * \see NXPlayer::setLicenseKeyFile for more information.
 *
 * \since version 5.27
 */
+ (NXError)setLicenseKeyBuffer:(NSString *)strKeyBuffer;

/**
 * \brief Returns the current logging state for NexPlayer&tm;.
 * 
 * The current logging state is set with NXPlayer::setLogging:.
 *
 * \deprecated This has been replaced with NXPlayer::logLevel:.  Please use that instead.
 *
 * \returns <tt>YES</tt> if logging is enabled; <tt>NO</tt> if logging is disabled.
 */
+ (BOOL)logging;

/**
 * \brief Enables or disables log output of diagnostic information by NexPlayer&tm;
 *
 * Disabling logging is the same as setting the log level to -1, and enabling
 * logging is the same as setting the log level to zero.  Since other log levels
 * are possible, it is better to set the log level directly rather than use
 * this method.
 *
 * \deprecated This has been replaced with NXPlayer::setLogLevel:.  Please use that instead.
 *
 * \param[in] logging Specify \c YES to enable log output, \c NO to disable log output.
 */
+ (void)setLogging: (BOOL)logging;

/**
 * \brief Returns the current logging level for NexPlayer&tm;.
 * 
 * The logging level is set with NXPlayer::setLogLevel:.
 *
 * If logging is turned off, the log level will be \c NXLogLevelDisabled.
 *
 * \returns The current log level if logging is enabled, \c NXLogLevelDisabled if logging is disabled.
 *
 * \since version 5.8
 */
+ (NXLogLevel)logLevel;

/**
 * \brief Controls the amount of diagnostic information output by NexPlayer&tm;.
 *
 * This should be set before creating the NXPlayer instance.  Log data is output
 * as part of initialization, so if this is set after creating the instance, some
 * log data may be lost.
 * 
 * \param[in] logLevel The logging level to set.  This determines the amount of diagnostic information
 *                     the SDK sends to the log. Refer to NXTypes::NXLogLevel:
 *                          - <b>NXLogLevelDisabled</b> : Disables logging. Does not output any log messages.
 *                          - <b>NXLogLevelError</b> : Output basic log messages only (recommended).
 *                          - <b>NXLogLevelWarning~NXLogLevelExtraVerbose</b> : Outputs detailed log messages; higher numbers result in more verbose
 *                                      log entries, but may cause performance issues in some cases and are
 *                                      not recommended for general release code.
 *
 * \since version 5.8
 */
+ (void)setLogLevel: (NXLogLevel)logLevel;

/**
 * \brief This method sets setLogLevel regardless of performance. 
 *
 * From version 5.28 and up, legacy setLogLevel API only sets settings that do not affect the performance. 
 * If the user needs a debugging log regardless of performance, set the forced parameter to \c TRUE and call setLogLevel:forced: to set. 
 *
 * \param[in] logLevel The logging level to set.  This determines the amount of diagnostic information
 *                     the SDK sends to the log. Refer to NXTypes::NXLogLevel:
 *                          - <b>NXLogLevelDisabled</b> : Disables logging. Does not output any log messages.
 *                          - <b>NXLogLevelError</b> : Output basic log messages only (recommended).
 *                          - <b>NXLogLevelWarning~NXLogLevelExtraVerbose</b> : Outputs detailed log messages; higher numbers result in more verbose
 *                                      log entries, but may cause performance issues in some cases and are
 *                                      not recommended for general release code.
 * \param[in] bForced Whether or not to force set logLevel regardless of device performance.
 *
 * \returns \c YES if it is set according to the logLevel parameter, \c NO if it is force down-set due to performance issues. 
 *
 * \since version 5.28
 */
+ (BOOL)setLogLevel: (NXLogLevel)logLevel forced:(BOOL) bForced;

/**
 * \brief Resets the logging level to the default.
 *
 * If used, it is best to call this before creating the NXPlayer instance.  
 * Log data is output as part of initialization, so if this is called after 
 * creating the instance, some log data may be lost.
 *
 * \since version 5.8
 */
+ (void)setLogLevelToDefault;

/**
 * \brief The delegate for the Dynamic Thumbnail feature in NexPlayer&tm;.
 *
 * Any application that will handle Dynamic Thumbnail must implement this property.
 * \since version 5.27
 */
@property (nonatomic,assign)	id<NXDynamicThumbnailDelegate> dynamicThumbnailDelegate;

/**
 * \brief This method is used to enable and apply the Dynamic Thumbnail feature for HLS & Smooth Streaming content.
 *
 * Refer to the following steps to use this method accurately:
 *
 * -# The \c enableDynamicThumbnail: method should be called before \c NXPlayer::open:.
 * -# When \c open: is successful, use the \c NXPlayer::contentInfo to get the total playtime of the content.
 *    By dividing the extracted total playtime value by the number of the thumbnail buffer array from the UI (the number of available thumbnails), the interval time is determined.
 *    The interval time can then be used with the \c setOptionDynamicThumbnail: method to get thumbnail information.
 * -# If the setting above works normally, NexPlayer&trade;&nbsp;will use the \c onDynamicThumbnailData() method to send thumbnail data to the UI.
 * -# The \c disableDynamicThumbnail: method should be called before \c NXPlayer::close: when closing content.
 * -# If a video track is changed while content is playing, these methods should be called in the following order:
 *       - FIRST, \c disableDynamicThumbnail:
 *       - SECOND, \c enableDynamicThumbnail: to enable Dynamic Thumbnails for the new content, and
 *       - LASTLY, \c setOptionDynamicThumbnailwithOption: NexDynamicThumbnailOption::NexDynamicThumbnailOptionInterval andParam1:interval_time andParam2:0 to set the appropriate interval for the new thumbnails.
 *
 * \return Zero for success, or a non-zero NexPlayer&trade;&nbsp; error code in the event of a failure.
 *
 * \since version 5.27
 */
- (NXError) enableDynamicThumbnail;

/**
 *
 * \brief This method disables the Dynamic Thumbnail feature, if enabled.
 *
 * \warning The Dynamic Thumbnail feature <em>must</em> be disabled by calling this method before calling \c NXPlayer::close when a player is being closed.
 *
 * \returns Zero for success, or a non-zero NexPlayer&trade;&nbsp; error code in the event of a failure.
 *
 * \since version 5.27
 */
- (NXError) disableDynamicThumbnail;

/**
 *
 * \brief This method sets option parameters related to the Dynamic Thumbnail feature in HLS & Smooth Streaming when handling thumbnail data.
 *
 * \param[in] option	The \c option property to set thumbnail data.
 * \param[in] param1	The first parameter of the \c option property.
 * \param[in] param2	The second parameter of the \c option property. If the option being set only needs one parameter, \c param2 will be \c 0.
 *
 * \return Zero for success, or a non-zero NexPlayer&trade;&nbsp; error code in the event of a failure.
 *
 * \since version 5.27
 */
- (NXError) setOptionDynamicThumbnailwithOption:(NexDynamicThumbnailOption)option andParam1:(NSUInteger)param1 andParam2:(NSUInteger)param2;


/**
 * \brief This method adds an event receiver.
 *
 * \note  If the developer wants to register several delegates, they can register receivers with this method.
 *
 * Events will be forwarded in sequence from receivers to delegate.
 *
 * \param[in] receiver	The object that implements NXPlayerDelegate to which methods will be called when events occur.
 *
 * \see NXPlayerDelegate
 *
 * \since version 5.30
 */
- (void) addEventReceiver:(id<NXPlayerDelegate>)receiver;

/**
 * \brief  This removes a receiver which was added with addEventReceiver.
 *
 * \param[in] receiver	The object that implements NXPlayerDelegate to which methods won't be called anymore.
 *
 * \see NXPlayer::addEventReceiver
 *
 * \since version 5.30
 */
- (void) removeEventReceiver:(id<NXPlayerDelegate>)receiver;

/**
 * \brief  This method is used to change the playback rate.
 *
 * \note  Speed Control is an optional feature.
 * This method makes it possible to allow users to adjust the playback rate, from 0.1 of the original speed to 4x speed, by changing the value of the parameter \c playRate.
 * For example, to play content at half-speed, \c playRate should be set to 0.5
 *
 * This method doesn't work if it is called when NexPlayer&trade;&nbsp;is stopped.
 *
 * \param playRate
 *            This float represents the rate by which to change the playback rate.
 *            It must be in the range of 0.1 to 4.0, which adjusts the playback speed from 0.1x to 4x the original speed of the content with HW decoder.
 *            It must be in the range of 0.1 to 2.0, which adjusts the playback speed from 0.1x to 2x the original speed of the content with SW decoder.
 * 			  It must be in the range of 0.5 to 2.0, when you use AirPlay mode. (isAirPlayActive is YES)
 *
 * \warning  When using this method with HLS or Smooth Streaming content, playing multitrack content may cause unstable performance.
 *           Therefore, playing content as a single track is encouraged.
 *			 When using this method with Live content, beffering may occur more frequently.
 *
 * \since version 5.38
 */
- (NXError) setPlaybackRate:(float)playRate;

/**
 * \brief Return current playback rate
 *
 * This value is to check current the playback rate.
 *
 * \returns
 * - \c 0.1 ~ 5.0 : The value of current playback rate.
 *
 * \since version 5.38
 */
- (float) getPlaybackRate;

- (void)setAESKeyExtFunc:(NEXPLAYERGetKeyExtCallbackFunc)extFunc;

@end
