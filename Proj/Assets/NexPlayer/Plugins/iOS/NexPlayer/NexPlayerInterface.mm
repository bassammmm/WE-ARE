#include "Unity/IUnityGraphics.h"
#include "Unity/IUnityInterface.h"

#import <NexPlayerSDK/NexPlayerSDK.h>
#import <NexPlayerSDK/NexVideoTextureReceiver.h>
#import <NexPlayerSDK/NXStatisticsAPI.h>
#import <NexPlayerSDK/NXPlayerABRController.h>
#import <NexPlayerSDK/NXTimedMetaKeys.h>
#import <NexPlayerSDK/NxTimedMetaExtraTag.h>
#import <NexPlayerSDK/NXClosedCaption.h>
#import <NexPlayer/NexPlayerViewControllerPlugins.h>
#import <NexPlayer/NexMetalRenderer.h>
#import <NexPlayer/NexPlayerHLSTSDescrambler.h>
#import <NexPlayer/WidevineHelper.h>
#import <NexPlayer/NexUtil.h>
#import <NexPlayer/NexPlayerEnum.h>
#import <NexPlayer/NexPlayerHTTPRetrieveHandler.h>
#import <NexPlayer/NexPlayerHTTPRetrieveStoreUtils.h>
#import <NexPlayer/NexPlayerHTTPStoreHandler.h>
#import <NexPlayer/NexPlayerPluginManager.h>
#import <NexPlayer/NexPlayerTypes.h>
#import <UIKit/UIKit.h>
#import <GLKit/GLKit.h>

#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#define PIXEL_FORMAT_32BGRA  1



#define NEX_HTTP_RETRIEVE_CALLBACK 0
#define NEX_HTTP_STORE_CALLBACK 1
#define NEXPLAYER

@interface NXMediaOpenParams : NSObject
@property (nonatomic, strong) NSString* URLString;
@property (nonatomic) NXTransportType transportType;
@property (nonatomic, copy) NSDictionary *info;
@property (nonatomic) BOOL OfflinePlay;
@property (nonatomic, strong) NSString *subtitlePath;
@end

@interface NexPlayerScripting : NSObject <NXPlayerDelegate, NXABRDelegate>

@property (nonatomic, strong) NXPlayerView *playerView;
@property (nonatomic, readonly) NXPlayer *player;
@property (nonatomic, strong) NexVideoTextureReceiver *textureReceiver;
@property (nonatomic, strong) NexGLKRenderer *glkRenderer;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer;
@property (nonatomic, strong) NXStatisticsAPI *statisticsAPI;
#ifdef NEXPLAYER
@property (nonatomic, strong) WidevineHelper *widevineHelper;
@property (nonatomic, strong) WidevineHelper *widevineHelper2;
@property (nonatomic, strong) WidevineHelper *widevineHelper3;
@property (nonatomic, strong) WidevineHelper *widevineHelper4;
@property (nonatomic, strong) WidevineHelper *widevineHelper5;
@property (nonatomic, strong) WidevineHelper *widevineHelper6;
@property (nonatomic, strong) WidevineHelper *widevineHelper7;
@property (nonatomic, strong) WidevineHelper *widevineHelper8;
#endif
@property (nonatomic, strong) NXPlayerABRController *abrController;
@property (nonatomic, strong) NSString *keyServerURL;
@property (nonatomic, strong) NSString *subtitle_path;
@property (nonatomic, strong) NSString *current_subtitle;
@property (nonatomic, strong) NSDictionary *timedMetadata;
@property (nonatomic, strong) NSString *CUSTOM_TAGS;

@property (nonatomic) NSUInteger subtitle_startTime;
@property (nonatomic) NSUInteger subtitle_endTime;
@property (nonatomic) NSUInteger subtitle_type;

//MULTI 13/01/2020
@property (nonatomic) NSUInteger multiStreamScreens;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer2;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer3;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer4;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer5;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer6;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer7;
@property (nonatomic, strong) NexMetalRenderer *metalRenderer8;
//END MULTI 13/01/2020

//MARTIN OFFLINE PLAYBACK 05112019 (v5.40.0.5133+++)
@property (nonatomic, strong) NexPlayerHTTPStoreHandler *mHTTPStoreHandler;
@property (nonatomic, strong) NexPlayerHTTPRetrieveHandler *httpRetrieveHandler;
@property (nonatomic, strong) NexPlayerHTTPStoreHandler *httpStoreHandler;
@property (nonatomic, strong) NSString *storeStreamURL;
@property (nonatomic, strong) NSDictionary *info;
@property (nonatomic) NSUInteger downloadProgress;
@property (nonatomic) NSUInteger videoBitrate;
@property (nonatomic) NSUInteger numberOfStoredFiles;
@property (nonatomic) NSUInteger totalFilesToDload;
@property (nonatomic, strong) NexPlayerPluginManager *plugins;

@property (nonatomic, strong, readwrite) NXMediaOpenParams *currentMediaOpenParams;
//END MARTIN OFFLINE PLAYBACK 05112019

- (int)setupPlayer:(int)width :(int) height;
- (int)openPlayer:(NSString *)path;
- (int)openFD:(NSString *)fileName;
- (void)startPlayer:(int)msec;
- (void)pausePlayer;
- (void)resumePlayer;
- (void)seekPlayerToTime:(int)msec;
- (void)stopPlayer;
- (void)closePlayer;
- (void)shutDownPlayer;
- (void)setLogLevel:(int)log_level;
- (int)setProperty:(int)property toValue:(int)value;
- (int)getContentInfo:(int)info_index;
- (int)getBufferInfo;
- (intptr_t)glUpdateFrame;
- (intptr_t)metalUpdateFrame;
- (CGSize)videoSize;
- (int)getBufferedEndTime;
- (void)setKeyServerURI:(NSString *)keyServerURI;
- (void)setSubtitlePath:(NSString *)subtitlePath;
- (void)setSubtitleFD:(NSString *)subtitleFD;
- (void)OnOffSubtitle:(BOOL)bOnOff;
- (void)changeSubtitlePath:(NSString *)subtitlePath;
- (void)changeSubtitleFD:(NSString *)subtitleFD;
- (void)setMute:(BOOL)isMute;
- (void)setVolume:(float)volumeSize;
- (void)setWVOptionalHeader:(NSString *)wvOptionalKeyValue;
- (void)setAdditionalHttpHeader:(NSString *)httpHeaderValue;
- (int)getPlayerStatus;
- (void)setAutoPlayback:(BOOL)autoPlay;
- (void)setFirstFrame:(BOOL)isShow;
- (void)setSecretValueForSignature:(NSString *)secret;
- (void)setUseLicenseCache:(BOOL)bUse;
- (void)cleanVideoTexture;
- (void)setLowLatency:(BOOL)enable toValue:(int)value;
- (void)setProperties;
- (void)setEnabledABR:(BOOL)enable;
- (void)setPlayersEnabledABRWithProperty;
- (void)setCustomTags:(NSString*) Tags;
- (BOOL)setLicenseFilePath:(NSString *)licensePath;

//Martin 05112019 - Offline DRM HLS/DASH playback
- (int)downloadKeyServer:(NSString *)url;
- (void)downloadStream:(NSString *)url;
- (void)playOffline:(NSString *)url;
- (int)getDownloadPercentage;
//End Martin 05112019 - Offline DRM HLS/DASH playback

//Multi-instance martin 14012020
-(void)setMultiStreamScreens:(NSUInteger)multiStreamScreens;
-(void)setMultiPaths:(NSString*)multiPathz toValue:(int)index;
-(void)setMultiKeyServers:(NSString*)keyServerz toValue:(int)index;

-(void)ControlInstance:(NSUInteger)index;
-(int)getMultiSubIndex;
-(int)getMultiInitPlayer;
-(void)setMultiProperty:(int)index toValue:(int)property toValuez:(int)value;
-(void)setMultiHTTPHeader:(int)index toValue:(NSString*)header;
-(void)startChosenPlayer:(int)index toValue:(NSString*)url;
//End multi-instance martin 14012020
-(void)setTrack:(NSUInteger)bitRate;

@end

@implementation NexPlayerScripting

#pragma mark - for plugins

- (NexPlayerPluginManager *) plugins
{
	if ( _plugins == nil ) {
		_plugins = [[NexPlayerPluginManager alloc] init];
	}
	return _plugins;
}

- (void) registerPlugin:(id<NexPlayerViewControllerPlugin>) plugin
{
	[self.plugins registerPlugin:plugin];
}

- (void) dealloc
{
	[self.plugins unregisterAll];
}

NexPlayerHLSTSDescrambler *m_HLSTSDescrambler;
intptr_t frameTexture;

typedef void ( *PlayerListener )( int, int, int, int, int, int );
static PlayerListener g_playerListener = NULL;

typedef int ( *NEXPLAYERGetKeyExtCallbackFunc)(NSString *, long, NSData*, long, intptr_t, intptr_t);
static NEXPLAYERGetKeyExtCallbackFunc g_GetKeyExtCallback = NULL;

static int PLAYER_MUTE = 0;
bool m_mute = NO;
float m_volumeSize = 0;

bool m_autoPlay = NO;
bool m_showFirstFrame;
bool m_useLicneseCache;
bool m_isClose = NO;

// player preference
bool supportABR = true;
int maxBW = 0;
int minBW = 0;
int avSyncOffset = 0;
int preferLanguage = 0;
int preferBW = 0;
int bufferingTime = 0;
int enableTrackDown = 0;
int trackDwonVideoRatio = 0;
int VDispWait = 0;
int VDispSkip = 0;
int StartNearestBW = 0;
int MaxCaptionLength = 8192;
bool offlineMode = false;

int localSPDEnable = 0;
int localSPDTime = 0;
int localSPDSpeedUpSyncTime = 0;
int localSPDJumpSyncTime = 0;
int loglevel = -1;

NSUInteger m_licenseRequestTimeout = 30;

NSString* m_AlticastSecret;
NSMutableDictionary* m_OptionalHeaders = [[NSMutableDictionary alloc] init];
NSMutableArray* m_AdditionalHeaders = [[NSMutableArray alloc] init];
NSString* m_licenseFilePath = nil;

//Multi-instance martin 14012020
NSString* multiPaths[8];
NSString* multiKeyServers[8];
NSUInteger chosenPlayerMulti = 0;
bool multiPropertyLoop[8];
bool multiPropertyAutoStart[8];
bool multiPropertyMute[8];
int lastSubMultiIndex = 0;
int lastMultiInitPlayer = 0;
NSMutableArray* m_AdditionalHeaders1 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders2 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders3 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders4 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders5 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders6 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders7 = [[NSMutableArray alloc] init];
NSMutableArray* m_AdditionalHeaders8 = [[NSMutableArray alloc] init];
bool hasAdditionalHttpHeader[8];

NXPlayer* multiPlayers[8];
NXPlayerView* multiViews[8];
NexVideoTextureReceiver* multiReceiver[8];
//End multi-instance martin 14012020

- (NXPlayer *) player
{
	int _multInt = 0;

	NXPlayer *player;
	if ( _multInt == 0 ) {
		player = self.playerView.player;
	} else {
		player = multiViews[_multInt].player;
	}

	return player;
}


#pragma mark - NexPlayer utility methods
#ifdef NEXPLAYER
- (void)setupForDRM {
	if (self.keyServerURL != nil) {
		[self.widevineHelper startWidevine:self];
		[self.widevineHelper2 startWidevine:self];
		[self.widevineHelper3 startWidevine:self];
		[self.widevineHelper4 startWidevine:self];
		[self.widevineHelper5 startWidevine:self];
		[self.widevineHelper6 startWidevine:self];
		[self.widevineHelper7 startWidevine:self];
		[self.widevineHelper8 startWidevine:self];
	}
}
#endif

NSString* datFileString;

- (void) setHTTPStoreHandlerEnabled:(BOOL) enabled
{
	if ( enabled ) {
		self.httpStoreHandler = [[NexPlayerHTTPStoreHandler alloc] init];
	} else {
		self.httpStoreHandler = nil;
	}
	self.player.httpStoreDelegate = self.httpStoreHandler;
}

#define kMediaPickerOpenURLInfoKeyTitle    @"title"
#define kMediaPickerKeyURL         @"url"
#define kMediaPickerKeyDRMType       @"drmtype"
#define kMediaPickerKeyOffline       @"offline"
#define kMediaPickerKeyNXPlayer       @"nxPlayer"

- (int)openPlayer:(NSString *)path
{
	[self setPlayersEnabledABRWithProperty];

	m_isClose = NO;
#ifdef NEXPLAYER
	[self setupForDRM];
#endif
	[self.player setAESKeyExtFunc:g_GetKeyExtCallback];

	for(int i = 1; i < self.multiStreamScreens; i++){
		[multiViews[i].player setAESKeyExtFunc:g_GetKeyExtCallback];
	}

	if(offlineMode){
		[self closePlayer];
		m_isClose = NO;
		self.videoBitrate = 3000;
		NSUInteger videoBits = self.videoBitrate;
		[self.player setVideoBitrates:&videoBits len:1 withOption:NexAvailableBitrateNearest];
		self.player.delegate = self;
		return [self.player open:path
							mode:NXOpenModeStoreStream
					   subtitles:nil
					   transport:NXTransportTypeTCP
						autoPlay:NO];
		offlineMode = false;
	}else{
		BOOL isDir;
		//if we already have this file
		if([[NSFileManager defaultManager] fileExistsAtPath:[self filePathWithURL:path] isDirectory:&isDir]){
			m_isClose = NO;
			self.videoBitrate = 3000;
			NSUInteger videoBits = self.videoBitrate;
			self.player.delegate = self;

			[self setHTTPRetrieveHandlerEnabled:YES];
			self.httpRetrieveHandler.mediaURL = path;

			NSMutableDictionary *fullInfo;
			self.currentMediaOpenParams.URLString = path;
			self.currentMediaOpenParams.transportType = NXTransportTypeTCP;
			self.currentMediaOpenParams.OfflinePlay = YES;
			fullInfo[kMediaPickerKeyURL] = path;
			fullInfo[kMediaPickerKeyNXPlayer] = self.player;
			self.subtitle_path = nil;
			[self.player setVideoBitrates:&videoBits len:1 withOption:NexAvailableBitrateNearest];
			[self.plugins sender:self event:NexPlayerPluginEventPlaybackWillOpen userInfo:fullInfo];
		}else{
			[self Log:4 toValue:@"OpenPlayer could not find local file: " value5: path];
		}
		if(self.multiStreamScreens > 1){ //multi stream startup
			return [self.player open:multiPaths[0]
								mode:NXOpenModeAuto
						   subtitles:self.subtitle_path
						   transport:NXTransportTypeTCP
							autoPlay:multiPropertyAutoStart[0]];
		}
		NXError result = [self.player open:path
									  mode:NXOpenModeAuto
								 subtitles:self.subtitle_path
								 transport:NXTransportTypeTCP
								  autoPlay:NO];
		if (result != PLAYER_ERROR_NONE){
			[self nexPlayer:self.player encounteredError:result];
		}
		return result;
	}
}

- (int)openFD:(NSString *)fileName
{
	[self setPlayersEnabledABRWithProperty];

	m_isClose = NO;
#ifdef NEXPLAYER
	[self setupForDRM];
#endif
	NSString *filePath = [NexUtil getFileInformation:fileName];

	[self.player setAESKeyExtFunc:g_GetKeyExtCallback];

	if(filePath) {
		NXError result = [self.player open:filePath
									  mode:NXOpenModeAuto
								 subtitles:self.subtitle_path
								 transport:NXTransportTypeTCP
								  autoPlay:NO];
		if (result != PLAYER_ERROR_NONE){
			[self nexPlayer:self.player encounteredError:result];
		}
		return result;
	} else {
		if(g_playerListener) {
			g_playerListener(NEXUNITY_EVENT_ERROR,NXErrorMediaNotFound,0,0,0,0);
		}
		return -1;
	}
}


- (int)setupPlayer:(int)width :(int)height
{
	int result = [self setupPlayer];

	if(result == PLAYER_ERROR_NONE){
		if(UnitySelectedRenderingAPI() == apiMetal){
			result = [self createMetalTexture];
		}
		else
			result = 0;
	}

	return result;
}


-(int)setupPlayer {
	if(UnityGetGLView() != nil){
		CGRect bounds = UnityGetGLView().bounds;

		if(bounds.size.width > 0 && bounds.size.height > 0)
		{
			if(nil != m_licenseFilePath)
			{
				NXError ret = [NXPlayer setLicenseKeyFile:m_licenseFilePath];
				if(NXErrorNone != ret){
					//Error about Read License File
				}
			}

			if(self.playerView == nil)
			{
				self.playerView = [[NXPlayerView alloc] initWithFrame: bounds];
			}

			if(self.playerView != nil && self.playerView.player != nil){
				self.playerView.autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
				self.playerView.backgroundColor = [UIColor blackColor];
				self.playerView.autoScaling = NXScale_FitInView;
				self.player.delegate = self;
				self.player.ABRDelegate = self;

				// set player preferecne
				[self setProperties];

				// set additional Http Headers
				for(NSString *header in m_AdditionalHeaders){
					[[self player] addHTTPHeaderFields:header];
				}

				if(self.multiStreamScreens > 1){
					if(m_AdditionalHeaders1 != nil){
						for(NSString *header in m_AdditionalHeaders1){
							[[self player] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders2 != nil){
						for(NSString *header in m_AdditionalHeaders2){
							[multiPlayers[1] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders3 != nil){
						for(NSString *header in m_AdditionalHeaders3){
							[multiPlayers[2] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders4 != nil){
						for(NSString *header in m_AdditionalHeaders4){
							[multiPlayers[3] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders5 != nil){
						for(NSString *header in m_AdditionalHeaders3){
							[multiPlayers[4] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders6 != nil){
						for(NSString *header in m_AdditionalHeaders4){
							[multiPlayers[5] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders7 != nil){
						for(NSString *header in m_AdditionalHeaders3){
							[multiPlayers[6] addHTTPHeaderFields:header];
						}
					}
					if(m_AdditionalHeaders8 != nil){
						for(NSString *header in m_AdditionalHeaders4){
							[multiPlayers[7] addHTTPHeaderFields:header];
						}
					}

				}

				[[self player] setProperty:NXPropertySetHWdecoderPixelFormat toValue:PIXEL_FORMAT_32BGRA];

				self.statisticsAPI = [[NXStatisticsAPI alloc] initWithPlayer:self.player];

				if(self.multiStreamScreens < 2){
					self.textureReceiver = [NexVideoTextureReceiver receiverWithPlayer:self.player
																	   receivedTexture:^(NexVideoTexture *texture)
											{
						self.metalRenderer.videoTexture = texture;

					}];
				}

				return PLAYER_ERROR_NONE;
			}else{
				return PLAYER_INIT_FAILURE;
			}
		}else{
			return PLAYER_INIT_FAILURE;
		}
	}else{
		return PLAYER_INIT_FAILURE;
	}
}

-(int)createMetalTexture {
	int result = PLAYER_ERROR_NONE;
	self.metalRenderer = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
	if(self.multiStreamScreens > 1){
		for(int i = 1; i < self.multiStreamScreens;i++){
			if(i == 1)
				self.metalRenderer2 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
			else if (i == 2)
				self.metalRenderer3 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
			else if (i == 3)
				self.metalRenderer4 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
			else if (i == 4)
				self.metalRenderer5 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
			else if (i == 5)
				self.metalRenderer6 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
			else if (i == 6)
				self.metalRenderer7 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
			else if (i == 7)
				self.metalRenderer8 = [[NexMetalRenderer alloc] initWithDevice:UnityGetMetalDevice()];
		}
	}

	if(self.metalRenderer == nil){
		result = PLAYER_TEXTURE_FAILURE;
	}
	return result;
}

/*-(int)createOpenGLTexture {
 int result = PLAYER_ERROR_NONE;
 /*self.glkRenderer = [[NexGLKRenderer alloc] initWithEAGLContext:UnityGetMainScreenContextGLES()];
 for(int i = 1; i < self.multiStreamScreens;i++){
 multiGL[i] = [[NexGLKRenderer alloc] initWithEAGLContext:UnityGetMainScreenContextGLES()];
 }

 if(self.glkRenderer == nil){
 result = PLAYER_TEXTURE_FAILURE;
 }else{
 self.glkRenderer.autoRotationOn = NO;
 }
 return result;
 }*/

-(void)startPlayer:(int)msec {
	if(self.player) {
		[self.player startFromTime:msec];
	}
}

-(void)startPlayer:(int)msec pauseAfterReady:(bool) pause{
	if(self.player && self.player.state != NXPlayerStatePlay)
		[self.player startFromTime:msec pauseAfterReady:pause];
}

- (void)pausePlayer {
	if(self.multiStreamScreens > 1){
		if(chosenPlayerMulti == 0){
			[self.player pause];
		}
		else{
			[multiViews[chosenPlayerMulti].player pause];
		}

		return;
	}

	NXError result = [self.player pause];
	if (result != PLAYER_ERROR_NONE){
		[self nexPlayer:self.player encounteredError:result];
	}
}

- (void)resumePlayer {
	if(chosenPlayerMulti == 0){
		NXError result = [self.player resume];
		if (result != PLAYER_ERROR_NONE){
			[self nexPlayer:self.player encounteredError:result];
		}
	}
	else{
		if(multiViews[chosenPlayerMulti].player.state == NXPlayerStatePause)
			[multiViews[chosenPlayerMulti].player resume];
		else
			[multiViews[chosenPlayerMulti].player start];
	}
}
- (void)seekPlayerToTime:(int)msec {
	if(chosenPlayerMulti == 0) {
		NXError result = [self.player seekTo:msec];
		if (result != PLAYER_ERROR_NONE){
			[self nexPlayer:self.player encounteredError:result];
		}
	}
	else{
		NXPlayerState state = multiViews[chosenPlayerMulti].player.state;
		if(state == NXPlayerStatePlay || state == NXPlayerStatePause) {
			[multiViews[chosenPlayerMulti].player seekTo:msec];
		}
	}
}

- (void)stopPlayer {
	if(self.player){
		if([self.player state] == NXPlayerStateStop){ // manually handling stop while the player is stopped since the native stop doesn't return the error
			[self nexPlayer:self.player encounteredError:NXErrorOperationNotValidInCurrentState];
		}
		NXError result = [self.player stop];
		if (result != PLAYER_ERROR_NONE){
			[self nexPlayer:self.player encounteredError:result];
		}

		for(int i = 1; i < self.multiStreamScreens;i++){
			[multiPlayers[i] stop];
		}
	}
}

#ifdef NEXPLAYER
- (void)closeDRM {
	if (self.keyServerURL != nil) {
		[self.widevineHelper stopWidevine:self];
		[self.widevineHelper2 stopWidevine:self];
		[self.widevineHelper3 stopWidevine:self];
		[self.widevineHelper4 stopWidevine:self];
		[self.widevineHelper5 stopWidevine:self];
		[self.widevineHelper6 stopWidevine:self];
		[self.widevineHelper7 stopWidevine:self];
		[self.widevineHelper8 stopWidevine:self];
	}
}
#endif
- (void)closePlayer {
#ifdef NEXPLAYER
	if ( self.player.state == NXPlayerStateClose ){
		[self closeDRM];
	}
#endif
	if(self.abrController != nil)
		self.abrController = nil;

	NXPlayerState stateBeforeClose = self.player.state;
	NXError result = [self.player close];
	if (result != PLAYER_ERROR_NONE){
		[self nexPlayer:self.player encounteredError:result];
	}

	for(int i = 1; i < self.multiStreamScreens;i++){
		[multiPlayers[i] close];
	}
	NXPlayerState stateAfterClose = self.player.state;
#ifdef NEXPLAYER
	if ( stateAfterClose == NXPlayerStateClose ) {
		if ( stateBeforeClose > NXPlayerStateClose ) {
			[self closeDRM];
		}
	}
#endif
}

- (void)shutDownPlayer {
	if(self.player){
		if([self.player state] >= NXPlayerStateClose){
			[self closePlayer];
		}
	}
}
- (int)getTrackCount{
	return self.player.contentInfo.currentVideoStream.tracks.count;
}

- (NexPlayerTrack)getTrack:(int)index{
	NXTrackInfo * trackInfo = self.player.contentInfo.currentVideoStream.tracks[index];
	NexPlayerTrack track;
	if(index >=  self.player.contentInfo.currentVideoStream.tracks.count)
		return track;
	track.width = [trackInfo width];
	track.height = [trackInfo height];
	track.framerate = (int)[trackInfo frameRate];

	return track;
}
- (int)getContentInfo:(int)info_index {
	int nValue = -1;

	if(!self.player)
	{
		[self Log:4 toValue:@"getContent Info - player is null"];
		return nValue;
	}
	switch((NexPlayer_CONTENT_INFO)info_index) {

		case MEDIA_DURATION:
			nValue = (int)self.player.contentInfo.totalPlayTime;
			break;
		case VIDEO_CODEC:
			nValue = self.player.contentInfo.videoCodec;
			break;
		case VIDEO_WIDTH:
			nValue = self.player.contentInfo.width;
			break;
		case VIDEO_HEIGHT:
			nValue =self.player.contentInfo.height;
			break;
		case VIDEO_FRAMERATE:
			nValue =self.player.contentInfo.videoFrameRate;
			break;
		case VIDEO_BITRATE:
			nValue = self.player.contentInfo.videoBitrate;
			break;
		case AUDIO_CODEC:
			nValue = self.player.contentInfo.audioCodec;
			break;
		case AUDIO_SAMPLINGRATE:
			nValue = self.player.contentInfo.audioSampleRate;
			break;
		case AUDIO_NUMOFCHANNEL:
			nValue = self.player.contentInfo.audioChannels;
			break;
		case AUDIO_BITRATE:
			nValue = self.player.contentInfo.audioBitrate;
			break;
		case MEDIA_ISSEEKABLE:
			nValue = self.player.contentInfo.isSeekable;
			break;
		case MEDIA_ISPAUSABLE:
			nValue = self.player.contentInfo.isPausable;
			break;
		case VIDEO_FOURCC:
			nValue = -1;
			break;
		case VIDEO_CODEC_CLASS:
			nValue = -1;
			break;
		case VIDEO_PROFILE:
			nValue = -1;
			break;
		case VIDEO_LEVEL:
			nValue = -1;
			break;
		case VIDEO_CODEC_ERROR:
			nValue = -1;
			break;
		case VIDEO_RENDER_AVG_FPS:
			nValue = (int)self.player.statsInfo.renderedVideoFramesPerSec;
			break;
		case VIDEO_RENDER_AVG_DSP:
			nValue = (int)self.player.statsInfo.decodedVideoFramesLastInterval;
			break;
		case VIDEO_RENDER_COUNT:
			nValue = (int)self.player.statsInfo.numRenderingVideoFrames;
			break;
		case VIDEO_RENDER_TOTAL_COUNT:
			nValue = (int)self.player.statsInfo.numRenderingVideoFrames;
			break;
		case VIDEO_CODEC_DECODING_COUNT:
			nValue = (int)self.player.statsInfo.totalVideoFrames;
			break;
		case VIDEO_CODEC_DECODING_TOTAL_COUNT:
			nValue = (int)self.player.statsInfo.totalVideoFrames;
			break;
		case VIDEO_CODEC_AVG_DECODE_TIME:
			nValue = (int)self.player.statsInfo.avgTimeDecodingVideoFrames;
			break;
		case VIDEO_CODEC_AVG_RENDER_TIME:
			nValue = (int)self.player.statsInfo.avgTimeRenderingVideoFrames;
			break;
		case VIDEO_CODEC_DECODE_TIME:
			nValue = (int)self.player.statsInfo.timeDecodingSingleVideoFrame;
			break;
		case VIDEO_CODEC_RENDER_TIME:
			nValue = (int)self.player.statsInfo.timeRenderingSingleVideoFrame;
			break;
		case VIDEO_AVG_BITRATE:
			nValue = (int)self.player.statsInfo.avgVideoBitrate;
			break;
		case VIDEO_FRAMEBYTES:
			nValue = (int)self.player.statsInfo.totalVideoFrameBytes;
			break;
		case AUDIO_AVG_BITRATE:
			nValue = (int)self.player.statsInfo.avgAudioBitrate;
			break;
		case AUDIO_FRAMEBYTES:
			nValue = (int)self.player.statsInfo.totalAudioFrameBytes;
			break;
		case VIDEO_FRAME_COUNT:
			nValue = (int)self.player.statsInfo.totalVideoFrames;
			break;
		case VIDEO_TOTAL_FRAME_COUNT:
			nValue = (int)self.player.statsInfo.totalVideoFrames;
			break;
		default:
			[self Log:4 toValue:@"getContent Info - not right index"];
			break;

	}

	return nValue;
}

-(int)getBufferInfo {

	NXDuration lastBufferedTime = [self.statisticsAPI.bufferInfo lastFrameCTS:NXBufferInfoMediaTypeVideo];

	return (int)lastBufferedTime;

}

- (intptr_t)metalUpdateFrame {
	if(self.metalRenderer){
		if(self.multiStreamScreens > 1){
			self.textureReceiver = [NexVideoTextureReceiver receiverWithPlayer:self.player
															   receivedTexture:^(NexVideoTexture *texture0)
									{
				if(texture0 != nil)
					self.metalRenderer.videoTexture = texture0;
			}];
		}

		return [self.metalRenderer curFrameTexture];
	}else return 0;
}

- (intptr_t)metalUpdateFrameMulti:(int)index {
	if(self.multiStreamScreens > 1)
	{
		if(self.metalRenderer2){
			multiReceiver[1] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[1]
														   receivedTexture:^(NexVideoTexture *texture1)
								{
				if(texture1 != nil)
					self.metalRenderer2.videoTexture = texture1;
			}];
		}
		if(self.metalRenderer3){
			multiReceiver[2] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[2]
														   receivedTexture:^(NexVideoTexture *texture2)
								{
				if(texture2 != nil)
					self.metalRenderer3.videoTexture = texture2;
			}];
		}
		if(self.metalRenderer4){
			multiReceiver[3] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[3]
														   receivedTexture:^(NexVideoTexture *texture3)
								{
				if(texture3 != nil)
					self.metalRenderer4.videoTexture = texture3;
			}];
		}
		if(self.metalRenderer5){
			multiReceiver[4] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[4]
														   receivedTexture:^(NexVideoTexture *texture4)
								{
				if(texture4 != nil)
					self.metalRenderer5.videoTexture = texture4;
			}];
		}
		if(self.metalRenderer6){
			multiReceiver[5] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[5]
														   receivedTexture:^(NexVideoTexture *texture5)
								{
				if(texture5 != nil)
					self.metalRenderer6.videoTexture = texture5;
			}];
		}
		if(self.metalRenderer7){
			multiReceiver[6] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[6]
														   receivedTexture:^(NexVideoTexture *texture6)
								{
				if(texture6 != nil)
					self.metalRenderer7.videoTexture = texture6;
			}];
		}
		if(self.metalRenderer8){
			multiReceiver[7] = [NexVideoTextureReceiver receiverWithPlayer:multiPlayers[7]
														   receivedTexture:^(NexVideoTexture *texture7)
								{
				if(texture7 != nil)
					self.metalRenderer8.videoTexture = texture7;
			}];
		}

		if(index == 1)
			return [self.metalRenderer2 curFrameTexture];
		if(index == 2)
			return [self.metalRenderer3 curFrameTexture];
		if(index == 3)
			return [self.metalRenderer4 curFrameTexture];
		if(index == 4)
			return [self.metalRenderer5 curFrameTexture];
		if(index == 5)
			return [self.metalRenderer6 curFrameTexture];
		if(index == 6)
			return [self.metalRenderer7 curFrameTexture];
		if(index == 7)
			return [self.metalRenderer8 curFrameTexture];
		else return 0;
	}else
		return 0;
}

- (void)cleanVideoTexture{
	if(UnitySelectedRenderingAPI() == apiMetal) {
		self.metalRenderer.videoTexture = nil;
		if(self.multiStreamScreens > 1){
			self.metalRenderer2.videoTexture = nil;
			self.metalRenderer3.videoTexture = nil;
			self.metalRenderer4.videoTexture = nil;
			self.metalRenderer5.videoTexture = nil;
			self.metalRenderer6.videoTexture = nil;
			self.metalRenderer7.videoTexture = nil;
			self.metalRenderer8.videoTexture = nil;

		}
	}
}
- (void)setProperties{
	if(self.player)
	{
		if(maxBW > 0)
			[self.player setProperty:NXPropertyMaxBW toValue:maxBW];
		if(minBW > 0)
			[self.player setProperty:NXPropertyMinBW toValue:minBW];

		if(avSyncOffset > 0)
			[self.player setProperty:NXPropertyAVSyncOffset toValue:avSyncOffset];
		if(preferLanguage > 0)
			[self.player setProperty:NXPropertyPreferLanguage toValue:preferLanguage];
		if(preferBW > 0 )
			[self.player setProperty:NXPropertyPreferBandwidth toValue:preferBW];
		if(bufferingTime)
		{
			[self.player setProperty:NXPropertyInitialBufferingDuration toValue:bufferingTime];
			[self.player setProperty:NXPropertyReBufferingDuration toValue:bufferingTime];
		}

		if(enableTrackDown > 0)
		{
			[self.player setProperty:NXPropertyEnableTrackdown toValue:enableTrackDown];
			[self.player setProperty:NXPropertyTrackdownVideoRatio toValue:trackDwonVideoRatio];
		}

		if(VDispWait > 0)
			[self.player setProperty:NXPropertyTimestampDifferenceVDispWait toValue:VDispWait];
		if(VDispSkip > 0)
			[self.player setProperty:NXPropertyTimestampDifferenceVDispSkip toValue:VDispSkip];
		if(StartNearestBW > 0)
			[self.player setProperty:NXPropertyStartNearestBW toValue:StartNearestBW];
		/*if(MaxCaptionLength > 0)
		 [self.player setProperty:NXPropertySetMaxCaptionLength toValue:MaxCaptionLength];*/


		if(localSPDEnable != 0 && localSPDTime != 0){

            [self.player setProperty:NXPropertyEnableSpdSyncToGlobalTime toValue:1];
            [self.player setProperty:NXPropertySuggestedPresentationDelayTime toValue:localSPDTime];
            [self.player setProperty:NXPropertyLiveViewOption toValue:NXPropertyLiveViewLowLatency];
            [self.player setProperty:NXPropertyPartialPrefetch toValue:1];

			if(localSPDSpeedUpSyncTime != 0){
				[self.player setProperty:NXPropertySpdSyncDiffTime toValue:localSPDSpeedUpSyncTime];
			}
			else{
				[self.player setProperty:NXPropertySpdSyncDiffTime toValue:300];
			}

			if(localSPDJumpSyncTime != 0){
				[self.player setProperty:NXPropertySpdTooMuchDiffTime toValue:localSPDJumpSyncTime];
				printf("\n");
			}
			else{
				[self.player setProperty:NXPropertySpdTooMuchDiffTime toValue:5000];
			}

		}


		[self.player setProperty:NXPropertyEnableWebVTT toValue:true];

		if(self.CUSTOM_TAGS != nil)
		{
			const char *value = [self.CUSTOM_TAGS UTF8String];
			[self.player setProperty:NXPropertyTimedID3MetaKey toValue:(size_t)value];
		}
	}
	for(int i = 1; i < self.multiStreamScreens ;i++)
		if(multiPlayers[i])
		{
			if(maxBW > 0)
				[multiPlayers[i] setProperty:NXPropertyMaxBW toValue:maxBW];
			if(minBW > 0)
				[multiPlayers[i] setProperty:NXPropertyMinBW toValue:minBW];

			if(avSyncOffset > 0)
				[multiPlayers[i] setProperty:NXPropertyAVSyncOffset toValue:avSyncOffset];
			if(preferLanguage > 0)
				[multiPlayers[i] setProperty:NXPropertyPreferLanguage toValue:preferLanguage];
			if(preferBW > 0 )
				[multiPlayers[i] setProperty:NXPropertyPreferBandwidth toValue:preferBW];
			if(bufferingTime)
			{
				[multiPlayers[i] setProperty:NXPropertyInitialBufferingDuration toValue:bufferingTime];
				[multiPlayers[i] setProperty:NXPropertyReBufferingDuration toValue:bufferingTime];
			}

			if(enableTrackDown > 0)
			{
				[multiPlayers[i] setProperty:NXPropertyEnableTrackdown toValue:enableTrackDown];
				[multiPlayers[i] setProperty:NXPropertyTrackdownVideoRatio toValue:trackDwonVideoRatio];
			}

			if(VDispWait > 0)
				[multiPlayers[i] setProperty:NXPropertyTimestampDifferenceVDispWait toValue:VDispWait];
			if(VDispSkip > 0)
				[multiPlayers[i] setProperty:NXPropertyTimestampDifferenceVDispSkip toValue:VDispSkip];
			if(StartNearestBW > 0)
				[multiPlayers[i] setProperty:NXPropertyStartNearestBW toValue:StartNearestBW];
			/*if(MaxCaptionLength > 0)
			 [self.player setProperty:NXPropertySetMaxCaptionLength toValue:MaxCaptionLength];*/


			if(localSPDEnable != 0 && localSPDTime != 0){
                [multiPlayers[i] setProperty:NXPropertyEnableSpdSyncToGlobalTime toValue:1];
                [multiPlayers[i] setProperty:NXPropertySuggestedPresentationDelayTime toValue:localSPDTime];
                [multiPlayers[i] setProperty:NXPropertyLiveViewOption toValue:NXPropertyLiveViewLowLatency];
                [multiPlayers[i] setProperty:NXPropertyPartialPrefetch toValue:1];

				if(localSPDSpeedUpSyncTime != 0){
					[multiPlayers[i] setProperty:NXPropertySpdSyncDiffTime toValue:localSPDSpeedUpSyncTime];
				}
				else{
					[multiPlayers[i] setProperty:NXPropertySpdSyncDiffTime toValue:300];
				}

				if(localSPDJumpSyncTime != 0){
					[multiPlayers[i] setProperty:NXPropertySpdTooMuchDiffTime toValue:localSPDJumpSyncTime];
				}
				else{
					[multiPlayers[i] setProperty:NXPropertySpdTooMuchDiffTime toValue:5000];
				}
			}


			[multiPlayers[i] setProperty:NXPropertyEnableWebVTT toValue:true];

			if(self.CUSTOM_TAGS != nil)
			{
				const char *value = [self.CUSTOM_TAGS UTF8String];
				[multiPlayers[i] setProperty:NXPropertyTimedID3MetaKey toValue:(size_t)value];
			}
		}

}



-(void) setEnabledABR:(BOOL)enable {
	if(chosenPlayerMulti == 0) {
		self.abrController = [[NXPlayerABRController alloc] initWithPlayer:self.player];
		if(nil == self.abrController)
		{
			[self Log:4 toValue:@"create abrController is fail.\n"];
		} else {
			[[self abrController] setABREnabled:enable];
		}
	}
	else {
		self.abrController = [[NXPlayerABRController alloc] initWithPlayer:multiPlayers[chosenPlayerMulti]];
		if(nil == self.abrController)
		{
			[self Log:4 toValue:@"create abrController is fail.\n"];
		} else {
			[[self abrController] setABREnabled:enable];
		}
		/*for(int i = 1; i < self.multiStreamScreens; i++){
		 self.abrController = [[NXPlayerABRController alloc] initWithPlayer:multiPlayers[i]];

		 if(nil == self.abrController)
		 {
		 //NSLog(@"create abrController is fail.\n");
		 } else {
		 [[self abrController] setABREnabled:true];
		 }
		 }*/
	}
}

-(void) setPlayersEnabledABRWithProperty {
	self.abrController = [[NXPlayerABRController alloc] initWithPlayer:self.player];
	if(nil == self.abrController)
	{
		[self Log:4 toValue:@"create abrController is fail.\n"];
	} else {
		[[self abrController] setABREnabled:true];
	}

	for(int i = 1; i < self.multiStreamScreens; i++){
		self.abrController = [[NXPlayerABRController alloc] initWithPlayer:multiPlayers[i]];
		if(nil == self.abrController)
		{
			[self Log:4 toValue:@"create abrController is fail.\n"];
		} else {
			[[self abrController] setABREnabled:true];
		}
	}
}

-(CGSize)videoSize {

	if(self.player) {
		return CGSizeMake(self.player.contentInfo.width, self.player.contentInfo.height);
	}

	return CGSizeMake(0, 0);

}
- (void)Log:(int) level toValue:(NSString *) message{
	if(level <= loglevel)
	{
		NSLog(@"%@",message);
	}
}

- (void)Log:(int) level toValue:(NSString *) message value3:(int) value1{
	if(level <= loglevel)
	{
		NSLog(@"%@%d",message,value1);
	}
}

- (void)Log:(int) level toValue:(NSString *) message value3:(int) value1 value4:(int) value2{
	if(level <= loglevel)
	{
		NSLog(@"%@%d%d",message, value1, value2);
	}
}
- (void)Log:(int) level toValue:(NSString *) message value5:(NSString * ) value1{
	if(level <= loglevel)
	{
		NSLog(@"%@%@",message, value1);
	}
}

- (void)setLogLevel:(int)log_level {

    if(self.player) {
      [self.player setProperty:NXPropertyLogLevel toValue:log_level];
      loglevel = log_level;
    }
}

- (int)setProperty:(int)property toValue:(int)value {
	[self Log:4 toValue:@"property : %d value : %d " value3:property value4:value];

	switch(property) {
		case NEXUNITY_NXPropertySupportABR:
			if(value > 0)
				supportABR = true;
			else
				supportABR = false;
			break;
		case NEXUNITY_NXPropertyMaxBW:
			maxBW = value;
			break;
		case NEXUNITY_NXPropertyMinBW:
			minBW = 0;
			break;
		case NEXUNITY_NXPropertyAVSyncOffset:
			avSyncOffset = value;
			break;
		case NEXUNITY_NXPropertyPreferLanguage:
			preferLanguage = value;
			break;
		case NEXUNITY_NXPropertyPreferBandwidth:
			preferBW = value;
			break;
		case NEXUNITY_NXPropertyInitialBufferingDuration:
			bufferingTime = value;
			break;
		case NEXUNITY_NXPropertyReBufferingDuration:
			bufferingTime = value;
			break;
		case NEXUNITY_NXPropertyEnableTrackdown:
			enableTrackDown = value;
			break;
		case NEXUNITY_NXPropertyTrackdownVideoRatio:
			trackDwonVideoRatio = value;
			break;
		case NEXUNITY_NXPropertyTimestampDifferenceVDispWait:
			VDispWait = value;
			break;
		case NEXUNITY_NXPropertyTimestampDifferenceVDispSkip:
			VDispSkip = value;
			break;
		case NEXUNITY_NXPropertyStartNearestBW:
			StartNearestBW = value;
			break;
		case NEXUNITY_NXPropertyMaxCaptionLength:
			MaxCaptionLength = value;
			break;


		case NEXUNITY_NXPropertySPDEnable:
			localSPDEnable = value;
			break;

		case NEXUNITY_NXPropertySPDTime:
			localSPDTime = value;
			break;

		case NEXUNITY_NXPropertySPDSpeedUpSyncTime:
			localSPDSpeedUpSyncTime = value;
			break;

		case NEXUNITY_NXPropertySPDJumpSyncTime:
			localSPDJumpSyncTime = value;
			break;



		case NEXUNITY_NXPropertyDRMLicenseTimeout:
			m_licenseRequestTimeout = value;
#ifdef NEXPLAYER
			if(self.widevineHelper != nil){
				[self.widevineHelper setLicenseRequestTimeout:value];
				[self.widevineHelper2 setLicenseRequestTimeout:value];
				[self.widevineHelper3 setLicenseRequestTimeout:value];
				[self.widevineHelper4 setLicenseRequestTimeout:value];
			}
#endif
			break;
		default:
			[self Log:4 toValue:@"property not listed"];
			break;
	}
	return 0;

}

- (void)setLowLatency:(BOOL)enable toValue:(int)value{
	if(enable){

		if(self.player != nil){
			[self.player setProperty:NXPropertyInitialBufferingDuration toValue:value];
			[self.player setProperty:NXPropertyReBufferingDuration     toValue:value];
			[self.player setProperty:NXPropertyPartialPrefetch       toValue:TRUE];
			[self.player setProperty:NXPropertyApplsLiveViewOption     toValue:NXPropertyLiveViewLowLatency];
		}
	}
}

bool isAlticast = false;
#ifdef NEXPLAYER
- (void)setKeyServerURI:(NSString *)keyServerURL {
	self.keyServerURL = keyServerURL;

	if(multiPlayers[0] != nil) {
		[self Log:4 toValue:@"KEYSERVER 0 \n" value5:multiKeyServers[0]];
		self.widevineHelper = [[WidevineHelper alloc] initWithPlayer:multiPlayers[0] with:multiKeyServers[0]];
		if([m_OptionalHeaders count] > 0){
			[self.widevineHelper addOptionHeader:m_OptionalHeaders];
			isAlticast = true;
		}
	}else {

		if(self.player != nil) {
			[self Log:4 toValue:@"KEYSERVER 0 \n" value5:multiKeyServers[0]];
			self.widevineHelper = [[WidevineHelper alloc] initWithPlayer:self.player with:self.keyServerURL];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}


		if(multiPlayers[1] != nil) {
			[self Log:4 toValue:@"KEYSERVER 1 \n" value5:multiKeyServers[1]];
			self.widevineHelper2 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[1] with:multiKeyServers[1]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}

		if(multiPlayers[2] != nil) {
			[self Log:4 toValue:@"KEYSERVER 2 \n" value5:multiKeyServers[2]];
			self.widevineHelper3 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[2] with:multiKeyServers[2]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}

		if(multiPlayers[3] != nil) {
			[self Log:4 toValue:@"KEYSERVER 3 \n" value5:multiKeyServers[3]];
			self.widevineHelper4 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[3] with:multiKeyServers[3]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}

		if(multiPlayers[4] != nil) {
			[self Log:4 toValue:@"KEYSERVER 4 \n" value5:multiKeyServers[4]];
			self.widevineHelper5 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[4] with:multiKeyServers[4]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}
		if(multiPlayers[5] != nil) {
			[self Log:4 toValue:@"KEYSERVER 5 \n" value5:multiKeyServers[5]];
			self.widevineHelper6 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[5] with:multiKeyServers[5]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}
		if(multiPlayers[6] != nil) {
			[self Log:4 toValue:@"KEYSERVER 6 \n" value5:multiKeyServers[6]];
			self.widevineHelper7 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[6] with:multiKeyServers[6]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}
		if(multiPlayers[7] != nil) {
			[self Log:4 toValue:@"KEYSERVER 7 \n" value5:multiKeyServers[7]];
			self.widevineHelper8 = [[WidevineHelper alloc] initWithPlayer:multiPlayers[3] with:multiKeyServers[3]];
			if([m_OptionalHeaders count] > 0){
				[self.widevineHelper addOptionHeader:m_OptionalHeaders];
				isAlticast = true;
			}
		}




		if(m_AlticastSecret)
			[self.widevineHelper setSecretKey:m_AlticastSecret];
		if(m_useLicneseCache)
			[self.widevineHelper setUseLicenseCache:m_useLicneseCache];
		if(m_licenseRequestTimeout > 0)
			[self.widevineHelper setLicenseRequestTimeout:m_licenseRequestTimeout];
	}
}
#endif
- (void)setSubtitlePath:(NSString *)subtitlePath {
	if(subtitlePath != nil){
		BOOL subtitleCheck = [NexUtil CheckSubtitleFile:subtitlePath];
		if(subtitleCheck){
			self.subtitle_path = [[NSString alloc] initWithString:subtitlePath];
			[self Log:4 toValue:@"set subtitle path :\n" value5:self.subtitle_path];
		}else{
			g_playerListener(NEXUNITY_EVENT_TEXT_INIT,INVALID_SUBTITLE_PATH,0,0,0,0);
			self.subtitle_path = nil;
			[self Log:4 toValue:@"wrong subtitle path"];
		}
	}
}

- (void)setSubtitleFD:(NSString *)subtitleFD {
	NSString *temp = [NexUtil getFileInformation:subtitleFD];
	if(temp != nil){
		self.subtitle_path = [[NSString alloc] initWithString:temp];
		[self Log:4 toValue:@"[FD] set subtitle path :\n" value5:self.subtitle_path];
	}
}

- (void)changeSubtitlePath:(NSString *)subtitlePath{
	if(subtitlePath != nil){
		[self.player setExternalSubtitle:subtitlePath];
		[self Log:4 toValue:@"change subtitle path :\n" value5:subtitlePath];
	}

}
- (void)changeSubtitleFD:(NSString *)subtitleFD{
	NSString *subtitlePath = [NexUtil getFileInformation:subtitleFD];
	if(subtitlePath != nil){
		[self.player setExternalSubtitle:subtitlePath];
		[self Log:4 toValue:@"[FD]change subtitle path :\n" value5:subtitlePath];
	}

}

- (void)OnOffSubtitle:(BOOL) bOnOff {

	if(self.player != nil){
		[self.player setMediaOnOff:bOnOff mediaType:NXMediaTypeText];
	}
}

- (void)setWVOptionalHeader:(NSString *)wvOptionalKeyValue{
	NSArray* headerValue = [wvOptionalKeyValue componentsSeparatedByString:@","];
	NSString* keyValue = [headerValue objectAtIndex:0];
	NSString* Value = [headerValue objectAtIndex:1];

	[m_OptionalHeaders setObject:Value forKey:keyValue];
}

- (void)setAdditionalHttpHeader:(NSString *)httpHeaderValue{
	[self Log:4 toValue:@"Add Additional Header : \n" value5:httpHeaderValue];
	[m_AdditionalHeaders addObject:httpHeaderValue];
}

- (void)setMute:(BOOL)isMute
{
	if(chosenPlayerMulti == 0){
		m_mute = isMute;
	}
	else{
		multiPropertyMute[chosenPlayerMulti] = isMute;
	}

	[self setVolumeSize];
}

- (void)setVolume:(float)volumeSize
{
	[self Log:4 toValue:@"volume size : %f" value3: volumeSize];

	m_volumeSize = volumeSize;

	[self setVolumeSize];
}

- (void)setVolumeSize
{
	if(self.player) {
		if(m_volumeSize > 1)
			m_volumeSize = 1;
		else if(m_volumeSize < 0)
			m_volumeSize = 0;

		if(self.multiStreamScreens > 1) {
			if(chosenPlayerMulti == 0) {
				m_mute ? [self.player setGain:PLAYER_MUTE]:[self.player setGain:m_volumeSize];
			}
			else {
				multiPropertyMute[chosenPlayerMulti] ? [multiViews[chosenPlayerMulti].player setGain:PLAYER_MUTE]:[multiViews[chosenPlayerMulti].player setGain:m_volumeSize];
			}
			return;
		}

		if(m_mute) {
			[self.player setGain:PLAYER_MUTE];
		}
		else {
			[self.player setGain:m_volumeSize];
		}
	}
}


- (int)getPlayerStatus
{
	int playerState = 0;
	if(chosenPlayerMulti == 0)
		playerState = [self.player state];
	else
		playerState = [multiViews[chosenPlayerMulti].player state];

	return playerState;
}

- (void)setAutoPlayback:(BOOL)autoPlay
{
	m_autoPlay = autoPlay;
}

- (void)setFirstFrame:(BOOL)isShow
{
	m_showFirstFrame = isShow;
}

- (void)setThumbnail
{
	int showFrame;
	if(m_showFirstFrame){
		showFrame = 1;
	}else{
		showFrame = 0;
	}
	[self.player setProperty:NXPropertyFirstDisplayVideoFrame toValue:showFrame];
}

- (void)setUseLicenseCache:(BOOL)bUse
{
	m_useLicneseCache = bUse;
}

//NEW MARTIN 21-10-2019
-(int)getCurrentAudioStreamID {
	NXMediaStreamInfo *curStream = self.player.contentInfo.currentAudioStream;
	return (int)curStream.internalId;
}
-(NSString*)getCurrentAudioStreamName {
	NXMediaStreamInfo *curStream = self.player.contentInfo.currentAudioStream;
	return (NSString*)curStream.name;
}
-(NSString*)getCurrentAudioStreamLanguage {
	NXMediaStreamInfo *curStream = self.player.contentInfo.currentAudioStream;
	return (NSString*)curStream.language;
}
-(int)getAudioStreamCount {
	int count = 0;
	count = [[self.player.contentInfo streamsOfType:NXMediaTypeAudio] count];
	return count;
}
-(int)getAudioStreamID:(int)index {
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeAudio] objectAtIndex:index];
	return (int)chosenStream.internalId;
}
-(int)getAudioIndexOfID:(int)ID {
	int audioCount = [[self.player.contentInfo streamsOfType:NXMediaTypeAudio] count];
	int chosenIndex = -1;
	for(int i = 0; i < audioCount; i++){
		NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeAudio] objectAtIndex:i];
		if(chosenStream.internalId == ID){
			chosenIndex = i;
		}
	}
	return chosenIndex;
}
-(NSString*)getAudioStreamName:(int)index {
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeAudio] objectAtIndex:index];
	return (NSString*)chosenStream.name;
}
-(NSString*)getAudioStreamLanguage:(int)index {
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeAudio] objectAtIndex:index];
	return (NSString*)chosenStream.language;
}
-(void)setAudioStream:(int)index {
	NXError ret = NXErrorNone;
	NXMediaStreamInfo *chosenStream = [self.player.contentInfo.streams objectAtIndex:index];
	ret = [self.player setVideoStream:nil audioStream:chosenStream textStream:nil trackAttributes:nil];
	if (ret != NXErrorNone) {
		//NSLog(@"ERROR: [%s %d] Failed changing stream:%lx", __PRETTY_FUNCTION__, __LINE__, (unsigned long)ret);
	}
}



-(int)getCaptionIndexOfID:(int)ID {
	int captionCount = [[self.player.contentInfo streamsOfType:NXMediaTypeText] count];
	int chosenIndex = 0;
	for(int i = 0; i < captionCount; i++){
		NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeText] objectAtIndex:i];
		if(chosenStream.internalId == ID){
			chosenIndex = i;
		}
	}
	return chosenIndex;
}
-(void)setCaptionStream:(int)index {
	NXError ret = NXErrorNone;
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeText] objectAtIndex:index];
	ret = [self.player setVideoStream:nil audioStream:nil textStream:chosenStream trackAttributes:nil];
	if (ret != NXErrorNone) {
		//NSLog(@"ERROR: [%s %d] Failed changing stream:%lx", __PRETTY_FUNCTION__, __LINE__, (unsigned long)ret);
	}
}
-(int)getCaptionStreamCount {
	int count = 0;
	count = [[self.player.contentInfo streamsOfType:NXMediaTypeText] count];
	return count;
}
-(int)getCaptionStreamID:(int)index {
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeText] objectAtIndex:index];
	return (int)chosenStream.internalId;
}
-(NSString*)getCaptionStreamName:(int)index {
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeText] objectAtIndex:index];
	return (NSString*)chosenStream.name;
}
-(NSString*)getCaptionStreamLanguage:(int)index {
	NXMediaStreamInfo *chosenStream = [[self.player.contentInfo streamsOfType:NXMediaTypeText] objectAtIndex:index];
	return (NSString*)chosenStream.language;
}
//END NEW MARTIN 21-10-2019

//Martin 05112019 - Offline DRM HLS/DASH playback

-(int)downloadKeyServer:(NSString *)url
{
	//Set download keyServer
	self.keyServerURL = url;
	self.keyServerURI = url;

	return -123;
}
-(void)downloadStream:(NSString *)url
{
	[self Log:4 toValue:@"Starting download"];

	//Set mode
	offlineMode = true;

	//Set download URL
	self.storeStreamURL = url;

	self.videoBitrate = 3000;

	[self setupOfflinePlayback];

	[self checkIfFileExistsAtPath:url];

	//If folder exists delete it
	/*BOOL isDir;
	 if([[NSFileManager defaultManager] fileExistsAtPath:[self filePathWithURL:url] isDirectory:&isDir]){
	 NSString *path = [self filePathWithURL:url];
	 BOOL result = [[NSFileManager defaultManager] removeItemAtPath:path error:nil];
	 if(result) {
	 //NSLog(@"Content at path %@ deleted",path);
	 }
	 }*/

	self.numberOfStoredFiles = 0;

	//Begin download
	if(self.player) {
		self.player.delegate = self;

		//Opening a new player
		[self openPlayer:self.storeStreamURL];

	}
}
- (void) setHTTPRetrieveHandlerEnabled:(BOOL) enabled
{
	if ( enabled ) {
		self.httpRetrieveHandler = [[NexPlayerHTTPRetrieveHandler alloc] init];
	} else {
		self.httpRetrieveHandler = nil;
	}
	self.player.httpRetrieveDelegate = self.httpRetrieveHandler;
}
-(void)playOffline:(NSString *)url
{
	if(!self.player)
	{
		//return -999;
	}  else {

		//Set mode
		offlineMode = false;
		[self setHTTPRetrieveHandlerEnabled:YES];
		self.httpRetrieveHandler.mediaURL = url;

		[self openPlayer:url];
	}
}
-(int)getDownloadPercentage
{
	[self checkIfFileExistsAtPath:self.storeStreamURL];

	return self.downloadProgress;
}
- (void)setupOfflinePlayback
{
	NSUInteger bitRate = self.videoBitrate;

	[self setHTTPRetrieveStoreCallbackEnabled:YES];

	[self.player setVideoBitrates:&bitRate len:1 withOption:NexAvailableBitrateNearest];
}
- (void)setHTTPRetrieveStoreCallbackEnabled:(BOOL) enabled
{
	if(enabled) {
		if(self.mHTTPStoreHandler == nil)
		{
			self.mHTTPStoreHandler = [[NexPlayerHTTPStoreHandler alloc] init];
		}
		self.mHTTPStoreHandler.mediaURL = self.storeStreamURL;
		[self Log:4 toValue:@"Set storeHandler mediaURL:" value5:self.storeStreamURL];
		self.player.httpStoreDelegate = self.mHTTPStoreHandler;
	} else {
		self.mHTTPStoreHandler = nil;
		self.player.httpStoreDelegate = nil;
		[self Log:4 toValue:@"Removed handler and delegate"];
	}
}

//Multi-instance Martin 14012020
-(void) setMultiStream:(int)totalScreens {
	self.multiStreamScreens = totalScreens;

	[self setupMulti];//Setup multi

	//[self openMulti];//Open ALL multi
	[self Log:4 toValue:@"Set totalScreens to: " value3:totalScreens];
}
-(void) setMultiPaths:(NSString*)multiPathz toValue:(int)index {
	multiPaths[index] = multiPathz;
	[self Log:4 toValue:@"Set multiPaths index to:" value5:multiPathz];
}
-(void) setMultiKeyServers:(NSString*)keyServerz toValue:(int)index {
	multiKeyServers[index] = keyServerz;
	[self Log:4 toValue:@"Set multiKeyServers index to:" value5:keyServerz];
}
-(void) ControlInstance:(NSUInteger)index {
	chosenPlayerMulti = index;
	[self Log:4 toValue:@"Set ControlInstance"];
}
-(int) getMultiSubIndex {
	[self Log:4 toValue:@"Set getMultiSubIndex"];
	return lastSubMultiIndex;
}
-(int) getMultiInitPlayer {
	[self Log:4 toValue:@"Set getMultiInitPlayer"];
	return lastMultiInitPlayer;
}

-(void) setMultiProperty:(int)index toValue:(int)property toValuez:(int)value {
    switch(property){
        case 1:
            if (localSPDEnable == false)
                if(value != 0)
                    multiPropertyAutoStart[index] = true;
            break;
        case 2:
            if(value != 0)
                multiPropertyLoop[index] = true;
            break;
        case 3:
            if(value != 0)
                multiPropertyMute[index] = true;
            break;
        default :
//            if(value != 0)
//               [multiPlayers[index] setProperty:(NXProperty)property toValue:value];
            break;
    }

	[self Log:4 toValue:@"Set setMultiProperty"];
}

-(void) setMultiHTTPHeader:(int)index toValue:(NSString*)header {
	[self Log:4 toValue:@"Set setMultiHTTPHeader"];

	//Before-setup and runtime update
	if(index == 0){
		[m_AdditionalHeaders1 addObject:header];
		if(self.player != nil) [self.player addHTTPHeaderFields:header];
	}
	if(index == 1){
		[m_AdditionalHeaders2 addObject:header];
		if(multiPlayers[1] != nil) [multiPlayers[1] addHTTPHeaderFields:header];
	}
	if(index == 2){
		[m_AdditionalHeaders3 addObject:header];
		if(multiPlayers[2] != nil) [multiPlayers[2] addHTTPHeaderFields:header];
	}
	if(index == 3){
		[m_AdditionalHeaders4 addObject:header];
		if(multiPlayers[3] != nil) [multiPlayers[3] addHTTPHeaderFields:header];
	}
	if(index == 4){
		[m_AdditionalHeaders4 addObject:header];
		if(multiPlayers[4] != nil) [multiPlayers[4] addHTTPHeaderFields:header];
	}
	if(index == 5){
		[m_AdditionalHeaders5 addObject:header];
		if(multiPlayers[5] != nil) [multiPlayers[5] addHTTPHeaderFields:header];
	}
	if(index == 6){
		[m_AdditionalHeaders6 addObject:header];
		if(multiPlayers[6] != nil) [multiPlayers[6] addHTTPHeaderFields:header];
	}
	if(index == 7){
		[m_AdditionalHeaders7 addObject:header];
		if(multiPlayers[7] != nil) [multiPlayers[7] addHTTPHeaderFields:header];
	}


	//For when updateHttpHeaderFields is ready
	/*if(index == 0){
	 if(self.player != nil){
	 if(hasAdditionalHttpHeader[0] != true){
	 [[self player] addHTTPHeaderFields:header];
	 hasAdditionalHttpHeader[index] = true;
	 }else [[self player] updateHttpHeaderFields:header];
	 }
	 }else{
	 if(multiPlayers[index] != nil){
	 if(hasAdditionalHttpHeader[index] != true){
	 [multiPlayers[index] addHTTPHeaderFields:header];
	 hasAdditionalHttpHeader[index] = true;
	 }else [multiPlayers[index] updateHttpHeaderFields:header];
	 }
	 }*/
}
-(void) startChosenPlayer:(int)index toValue:(NSString*)url {
	multiPaths[index] = url;
	[self openChosenMulti:index];
	[self Log:4 toValue:@"Set startChosenPlayer"];
}

- (void) setupMulti {
	CGRect bounds = UnityGetGLView().bounds;

	for(int i = 1; i < self.multiStreamScreens; i++){
		multiViews[i] = [[NXPlayerView alloc] initWithFrame: bounds];
		multiPlayers[i] = multiViews[i].player;
		multiPlayers[i].delegate = self;
		multiViews[i].autoresizingMask = UIViewAutoresizingFlexibleWidth|UIViewAutoresizingFlexibleHeight;
		multiViews[i].backgroundColor = [UIColor blackColor];
		multiViews[i].autoScaling = NXScale_FitInView;
		[multiPlayers[i] setProperty:NXPropertySetHWdecoderPixelFormat toValue:PIXEL_FORMAT_32BGRA];
	}
}
-(void) openChosenMulti:(int)index {
	[multiPlayers[index] open:multiPaths[index]
						 mode:NXOpenModeAuto
					subtitles:self.subtitle_path
					transport:NXTransportTypeTCP
					 autoPlay:multiPropertyAutoStart[index]];
	[multiViews[index].player startFromTime:0 pauseAfterReady:!multiPropertyAutoStart[index]];

}
//End multi-instance Martin 14012020

#pragma mark - NXPlayerDelegate

- (void) nexPlayer:(NXPlayer *)nxplayer didUpdateDownloadProgressWithFileCount:(NSUInteger)current totalFileCount:(NSUInteger)total
{
	[self Log:4 toValue:@"Downloaded current: " value3:current];
	[self Log:4 toValue:@"Downloaded total: " value3:total];

	CGFloat downloadPercent = 0;

	self.totalFilesToDload = total;

	if (self.numberOfStoredFiles == 0)
		self.numberOfStoredFiles = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:self.mHTTPStoreHandler.strDocumentPath error:nil] count];

	if(total > 0 && self.numberOfStoredFiles >= total) {
		//[self.player stop];
		return;
	}

	if (current < self.numberOfStoredFiles)
		current = self.numberOfStoredFiles;

	downloadPercent = 100.0f * current/total;

	self.downloadProgress = downloadPercent;
}
- (NSString *) filePathWithURL:(NSString *)path
{
	return [NexPlayerHTTPRetrieveStoreUtils pathForMediaURL:path];
}

- (void) checkIfFileExistsAtPath:(NSString *)path
{
	BOOL isDir;
	BOOL result = [[NSFileManager defaultManager] fileExistsAtPath:[self filePathWithURL:path] isDirectory:&isDir];
	self.numberOfStoredFiles = [[[NSFileManager defaultManager] contentsOfDirectoryAtPath:[self filePathWithURL:path] error:nil] count];
	if(self.numberOfStoredFiles >= self.totalFilesToDload) self.downloadProgress = 100;
}

//End Martin 05112019 - Offline DRM HLS/DASH playback

#pragma mark - NXPlayerDelegate methods

// Finished Async OPEN
- (void) nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdOpenWithResult:(NXError)result playbackType:(NXPlaybackType)type {
	if(!m_isClose)
	{
		//Multi-instance martin 17/01/2020
		if(self.player == nxplayer) lastMultiInitPlayer = 0;
		else for(int i = 1; i < self.multiStreamScreens; i++) if(multiPlayers[i] == nxplayer) lastMultiInitPlayer = i;
		//End multi-instance martin 17/01/2020

		if(nxplayer != self.player)
			return;
		[self Log:4 toValue:@"completedAsyncCmdOpenWithResult"];
		if( result==NXErrorNone ) {
			g_playerListener(NEXUNITY_EVENT_ASYNC_COMPLETE,NEXUNITY_ASYNC_CMD_OPEN_STREAMING,0,0,0,0);

			[self setThumbnail];

			[self startPlayer:0 pauseAfterReady:!m_autoPlay];

		} else {
			[self nexPlayer:nxplayer encounteredError:result];
			[self Log:4 toValue:@"ERROR completedAsyncCmdOpenWithResult"];
		}
	}
}


// Finished Async Start
- (void) nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdStartWithResult:(NXError)result playbackType:(NXPlaybackType)type {
	if(!m_isClose && nxplayer == self.player)
	{
		[self Log:4 toValue:@"completedAsyncCmdStartWithResult"];
		if( result==NXErrorNone ) {
			g_playerListener(NEXUNITY_EVENT_ASYNC_COMPLETE,NEXUNITY_ASYNC_CMD_START_STREAMING,0,0,0,0);

		} else {
			[self nexPlayer:nxplayer encounteredError:result];
			[self Log:4 toValue:@"ERROR completedAsyncCmdStartWithResult"];
		}
	}
}

- (void) nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdPauseWithResult:(NXError)result
{
	[self Log:4 toValue:@"completedAsyncCmdPauseWithResult"];
	if(!m_isClose && nxplayer == self.player)
	{
		if( result==NXErrorNone ) {
			g_playerListener(NEXUNITY_EVENT_ASYNC_COMPLETE,NEXUNITY_ASYNC_CMD_PAUSE,0,0,0,0);
		}else{
			[self nexPlayer:nxplayer encounteredError:result];
		}
	}
}

- (void) nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdResumeWithResult:(NXError)result
{
	[self Log:4 toValue:@"completedAsyncCmdResumeWithResult"];
	if(!m_isClose && nxplayer == self.player)
	{
		if( result==NXErrorNone ){
			g_playerListener(NEXUNITY_EVENT_ASYNC_COMPLETE,NEXUNITY_ASYNC_CMD_RESUME,0,0,0,0);
		}else{
			[self nexPlayer:nxplayer encounteredError:result];
		}
	}
}

- (void)nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdStopWithResult:(NXError)result {
	[self Log:4 toValue:@"completedAsyncCmdStopWithResult"];
	[self.plugins sender:self event:NexPlayerPluginEventPlaybackDidStopForStore userInfo:nil];

	if(!m_isClose && nxplayer == self.player)
	{
		if( result==NXErrorNone ) {
			g_playerListener(NEXUNITY_EVENT_ASYNC_COMPLETE,NEXUNITY_ASYNC_CMD_STOP,0,0,0,0);
		} else {
			[self Log:4 toValue:@"ERROR completedAsyncCmdStopWithResult"];
			[self nexPlayer:nxplayer encounteredError:result];
		}
	}
}

- (void)nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdSeekWithResult:(NXError)result {
	[self Log:4 toValue:@"completedAsyncCmdSeekWithResult"];

	if(!m_isClose && nxplayer != nil) // TODO Add this to every other Async event to ensure it works for multistream
	{
		if( result==NXErrorNone ) {
			g_playerListener(NEXUNITY_EVENT_ASYNC_COMPLETE,NEXUNITY_ASYNC_CMD_SEEK,0,0,0,0);
		} else {
			[self nexPlayer:nxplayer encounteredError:result];
		}
	}
}

- (void) nexPlayerDidReachEndOfContent:(NXPlayer *)nxplayer {
	[self Log:4 toValue:@"nexPlayerDidReachEndOfContent"];

	//Multi loop
	if(self.multiStreamScreens > 1){
		if(self.player == nxplayer && multiPropertyLoop[0] == true){
			[self.player open:multiPaths[0]
						 mode:NXOpenModeAuto
					subtitles:self.subtitle_path
					transport:NXTransportTypeTCP
					 autoPlay:multiPropertyAutoStart[0]];
		}
		for(int i = 1; i < self.multiStreamScreens; i++)
			if(multiPlayers[i] == nxplayer && multiPropertyLoop[i] == true) [self openChosenMulti:i];

		return;
	}

	if(!m_isClose)
	{
		g_playerListener(NEXUNITY_EVENT_END_OF_CONTENT,0,0,0,0,0);
	}

	//[nxplayer stop];
}

- (int)getBufferedEndTime{
	NXStatisticsAPI *statisticsAPI = [[NXStatisticsAPI alloc] initWithPlayer: self.player];
	NSUInteger bufferSize = self.player.currentTimeStamp + [statisticsAPI.bufferInfo totalDuration:
															NXBufferInfoMediaTypeVideo];
	return (int) bufferSize;
}


- (void) nexPlayer:(NXPlayer *)nxplayer encounteredError:(NXError)errorCode
{
	if(g_playerListener) {
		g_playerListener(NEXUNITY_EVENT_ERROR,errorCode,0,0,0,0);
	}
}

-(void)nexPlayerDidUpdateContentInfo:(NXPlayer *)nxplayer {
	if(!m_isClose && nxplayer == self.player)
	{
		if(g_playerListener) {
			g_playerListener(NEXUNITY_EVENT_UPDATE_CONTENT_INFO,0,0,0,0,0);
		}
	}
}

-(void)nexPlayerDidBeginBuffering:(NXPlayer *)nxplayer {
	if(!m_isClose && nxplayer == self.player)
	{
		if(g_playerListener) {
			g_playerListener(NEXUNITY_EVENT_BUFFERING,0,0,0,0,0);
		}
	}
}

-(void)nexPlayerDidFinishBuffering:(NXPlayer *)nxplayer {
	if(!m_isClose && nxplayer == self.player)
	{
		if(g_playerListener) {
			g_playerListener(NEXUNITY_EVENT_BUFFERING,2,100,0,0,0);
		}
	}
}

-(void)nexPlayer:(NXPlayer *)nxplayer bufferingProgress:(NSInteger)percent {
	if(!m_isClose && nxplayer == self.player)
	{
		if(g_playerListener) {
			g_playerListener(NEXUNITY_EVENT_BUFFERING,1,(int)percent,0,0,0);
		}
	}
}

- (void) nexPlayer:(NXPlayer *)nxplayer subTitleChange:(NSString *)subtitleText start:(NSUInteger)startTime end:(NSUInteger)endTime {
	[self Log:4 toValue:@"caption: text:\n" value5:subtitleText];

	if(self.multiStreamScreens > 1){
		if(nxplayer == self.player) lastSubMultiIndex = 0;
		for(int i = 1; i < self.multiStreamScreens; i++)
			if(nxplayer == multiPlayers[i]) lastSubMultiIndex = i;
	}
	[self Log:4 toValue:@"caption: text:\n" value5:subtitleText];
	//NSLog(@"caption Info : %lu %lu \n",startTime,endTime);
	self.current_subtitle = subtitleText;
	self.subtitle_startTime = 0;
	self.subtitle_endTime = 0;
	if(!m_isClose)
	{
		if(g_playerListener){
			if(!isAlticast)
				g_playerListener(NEXUNITY_EVENT_TEXT_RENDER,0,0,0,0,0);
		}
	}
}

- (void)nexPlayer:(NXPlayer*)nxplayer updatedCaption:(NXClosedCaption *)caption {
	if(caption == nil)
		return;

	[self Log:4 toValue:@"caption: text:\n" value5: caption.text];

	if(self.multiStreamScreens > 1){
		if(nxplayer == self.player) lastSubMultiIndex = 0;
		for(int i = 1; i < self.multiStreamScreens; i++)
			if(nxplayer == multiPlayers[i]) lastSubMultiIndex = i;
	}

	if ( caption.type == NXCaptionTypeWebVTT) {
		int length = [caption.text length];
		self.current_subtitle = caption.text;
		self.subtitle_startTime = 0;
		self.subtitle_endTime = 0;
		self.subtitle_type = 0x50000001;

		if(!m_isClose)
		{
			if(self.current_subtitle == NULL)
				self.current_subtitle = @"";
			//NSLog(@"caption: type:0x%02x\n text:%@ \n length:%d \n", caption.type, self.current_subtitle, length);
			if(g_playerListener){
				g_playerListener(NEXUNITY_EVENT_TEXT_RENDER,0,0,0,0,0);
			}
		}
	} else if ( caption.type == NXCaptionTypeTTML) {
		// render caption.plainText
	}

}

- (void)nexPlayer:(NXPlayer*)nxplayer
  updatedMetaData:(NSDictionary*)metaData{
	[self Log:4 toValue:@"Update Metadta \n"];
	if(metaData != nil)
		self.timedMetadata = metaData;

	if(g_playerListener)
		g_playerListener(NEXUNITY_EVENT_TIMED_METADATA_RENDER,0,0,0,0,0);


}

- (void) setCustomTags:(NSString *)Tags{
	self.CUSTOM_TAGS = [[NSString alloc] initWithString:Tags];
}

- (void)nexPlayer:(NXPlayer*)nxplayer playheadAdvancedTo:(NXDuration)newPosition{

	if(g_playerListener)
		g_playerListener(NEXUNITY_EVENT_TIME,(int)self.player.currentTimeStamp,0,0,0,0);
}

#pragma mark - NXABRDelegate

- (NSUInteger)nexPlayer:(NXPlayer *)nxplayer willChangeABRTrackWithParams:(NXPlayerABRControllerTrackChangeParams)params
{
	//NSLog(@"Track change current:%lu next:%lu net:%lu", (unsigned long)params.curTrackBW, (unsigned long)params.nextTrackBW, (unsigned long)params.netBW);
	return params.nextTrackBW;
}

- (void)setSecretValueForSignature:secret{
	if(secret)
		m_AlticastSecret = secret;
}

- (BOOL)setLicenseFilePath:licensePath{
	BOOL licenseExists = NO;
	if(licensePath){
		BOOL licenseFileExists = [[NSFileManager defaultManager] fileExistsAtPath:licensePath];
		if(licenseFileExists){
			m_licenseFilePath = licensePath;
			licenseExists = YES;
		}
	}
	return licenseExists;
}

-(void)setTrack:(NSUInteger)bitRate{
	if(chosenPlayerMulti == 0){
		self.abrController = [[NXPlayerABRController alloc] initWithPlayer:self.player];
		[self.abrController setTargetBandwidth:bitRate segmentOption:NexBandwidthSegmentOptionDefault targetOption:NexBandwidthTargetOptionMatch];
	}
	else {
		self.abrController = [[NXPlayerABRController alloc] initWithPlayer:multiPlayers[chosenPlayerMulti]];
		[self.abrController setTargetBandwidth:bitRate segmentOption:NexBandwidthSegmentOptionDefault targetOption:NexBandwidthTargetOptionMatch];
	}

}
@end

static NexPlayerScripting* _GetPlayer()
{
	static NexPlayerScripting* _Player = nil;
	if(!_Player){
		_Player = [[NexPlayerScripting alloc] init];
	}

	frameTexture = 0;

	return _Player;
}

static NSString* _GetUrl(const char* filename)
{

	return [NSString stringWithUTF8String:filename];
}

static void* g_TexturePointer = NULL;
static bool alreadyInit = false;

enum NexPlayerEventType {
	NEXPLAYER_INIT = 0,
	NEXPLAYER_SHUTDOWN = 1,
	NEXPLAYER_UPDATE = 2
};



// --------------------------------------------------------------------------
// UnitySetInterfaces

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType);

static IUnityInterfaces* s_UnityInterfaces = NULL;
static IUnityGraphics* s_Graphics = NULL;
static UnityGfxRenderer s_DeviceType = kUnityGfxRendererNull;

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginLoad(IUnityInterfaces* unityInterfaces)
{
	[_GetPlayer() Log:4 toValue:@"UnityPluginLoad \n"];
	s_UnityInterfaces = unityInterfaces;
	s_Graphics = s_UnityInterfaces->Get<IUnityGraphics>();
	s_Graphics->RegisterDeviceEventCallback(OnGraphicsDeviceEvent);

	// Run OnGraphicsDeviceEvent(initialize) manually on plugin load
	OnGraphicsDeviceEvent(kUnityGfxDeviceEventInitialize);
}

extern "C" void UNITY_INTERFACE_EXPORT UNITY_INTERFACE_API UnityPluginUnload()
{
	s_Graphics->UnregisterDeviceEventCallback(OnGraphicsDeviceEvent);
	[_GetPlayer() Log:4 toValue:@"UnityPluginUnload \n"];

}

// --------------------------------------------------------------------------
// GraphicsDeviceEvent

static void UNITY_INTERFACE_API OnGraphicsDeviceEvent(UnityGfxDeviceEventType eventType)
{
	UnityGfxRenderer currentDeviceType = s_DeviceType;

	switch (eventType)
	{
		case kUnityGfxDeviceEventInitialize:
		{
			[_GetPlayer() Log:4 toValue:@"OnGraphicsDeviceEvent(Initialize).\n"];
			s_DeviceType = s_Graphics->GetRenderer();
			currentDeviceType = s_DeviceType;
			if (s_DeviceType == kUnityGfxRendererNull) {
				s_DeviceType = currentDeviceType;
			}
			[_GetPlayer() Log:4 toValue:@"Native log | currentDeviceType %u" value3:currentDeviceType];
			break;
		}

		case kUnityGfxDeviceEventShutdown:
		{
			[_GetPlayer() Log:4 toValue:@"OnGraphicsDeviceEvent(Shutdown).\n"];
			s_DeviceType = kUnityGfxRendererNull;
			g_TexturePointer = NULL;
			break;
		}

		case kUnityGfxDeviceEventBeforeReset:
		{
			[_GetPlayer() Log:4 toValue:@"OnGraphicsDeviceEvent(BeforeReset).\n"];
			break;
		}

		case kUnityGfxDeviceEventAfterReset:
		{
			[_GetPlayer() Log:4 toValue:@"OnGraphicsDeviceEvent(AfterReset).\n"];
			break;
		}
	};

}

extern "C" int SetTextureFromUnity(void* texturePtr,int w, int h, int loglevel) {

    [_GetPlayer() Log:4 toValue:@"iOS - SetTextureFromUnity \n"];

    [NXPlayer setLogLevel:(NXLogLevel)loglevel];
    
    int result = [_GetPlayer() setupPlayer:w :h];
     
    alreadyInit = YES;
     
    return result;
}


static void UNITY_INTERFACE_API OnRenderEvent(int eventID) {

	[_GetPlayer() Log:4 toValue:@"OnRenderEvent \n"];

	switch (eventID) {
		case NEXPLAYER_INIT:
		{
			[_GetPlayer() Log:4 toValue:@"initNexPlayer \n"];
			break;
		}
		case NEXPLAYER_SHUTDOWN:
		{
			[_GetPlayer() shutDownPlayer];
			break;
		}
		case NEXPLAYER_UPDATE: {
			[_GetPlayer() Log:4 toValue:@"OnRenderEvent | update"];
			break;
		}

		default:
			break;
	}


}

extern "C" UnityRenderingEvent NexPlayerUnityRenderEvent() {
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnityRenderEvent \n"];
	return OnRenderEvent;
}

extern "C" void NEXPLAYERUnity_Pause() {

	//printf("iOS - NEXPLAYERUnity_Pause \n");
	[_GetPlayer() pausePlayer];
}

extern "C" void NEXPLAYERUnity_Resume() {

	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_Resume \n"];
	[_GetPlayer() resumePlayer];
}


extern "C" void NEXPLAYERUnity_Stop() {

	//printf("iOS - NEXPLAYERUnity_Stop \n");
	[_GetPlayer() stopPlayer];
}


extern "C" int NEXPLAYERUnity_Open(const char* url)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_Open \n"];
	return [_GetPlayer() openPlayer:_GetUrl(url)];
}

extern "C" void NEXPLAYERUnity_Start(int msec)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_Start \n"];
	[_GetPlayer() startPlayer:msec];
}

extern "C" void NEXPLAYERUnity_Seek(int msec)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_Seek \n"];
	[_GetPlayer() seekPlayerToTime:msec];
}

extern "C" void NEXPLAYERUnity_Close()
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_Close \n"];
	[_GetPlayer() closePlayer];
}


extern "C" int NEXPLAYERUnity_GetContentInfoInt(int info_index) {

	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetContentInfoInt \n"];
	return [_GetPlayer() getContentInfo:info_index];
}

extern "C" int NEXPLAYERUnity_GetBufferInfo() {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetBufferInfo \n"];
	return [_GetPlayer() getBufferInfo];
}


extern "C" void setPlayerListener(PlayerListener l) {
	[_GetPlayer() Log:4 toValue:@"iOS - setPlayerListener \n"];
	g_playerListener = l;

}

extern "C" void NEXPLAYERUnity_VideoSize(int* w, int* h) {

	CGSize sz = [_GetPlayer() videoSize];
	*w = (int)sz.width;
	*h = (int)sz.height;

}

extern "C" intptr_t NEXPLAYERUnity_CurFrameTexture() {
	if(UnitySelectedRenderingAPI() == apiMetal) {
		return [_GetPlayer() metalUpdateFrame];
	}
}


extern "C" void NEXPLAYERUnity_SetLogLevel(int log_level) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_SetLogLevel \n"];
	return [_GetPlayer() setLogLevel:log_level];
}

extern "C" int NEXPLAYERUnity_SetProperty(int property, int value) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_SetProperty \n"];
	return [_GetPlayer() setProperty:property toValue:value];
}

extern "C" int NEXPLAYERUnity_GetBufferedEndTime () {
	return [_GetPlayer() getBufferedEndTime];
}

extern "C" void UpdateTextureFromUnity(void* texturePtr,int w, int h) {
	[_GetPlayer() Log:4 toValue:@"iOS - UpdateTextureFromUnity \n"];
}
extern "C" int NEXPLAYERUnity_OpenFD(const char* fileName) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_OpenFD \n"];
	return [_GetPlayer() openFD:_GetUrl(fileName)];
}

extern "C" void NEXPLAYERUnity_SetKeyServerUri(const char* uri)
{
	if(uri != nil || multiKeyServers != nil)
		return [_GetPlayer() setKeyServerURI:_GetUrl(uri)];

	return;
}

extern "C" void NexPlayerUnity_SetWVDRMOptionalHeaders(const char* wvOptionalKeyValue)
{
	return [_GetPlayer() setWVOptionalHeader:_GetUrl(wvOptionalKeyValue)];
}

extern "C" void NexPlayerUnity_SetAdditionalHttpHeader(const char* httpHeaderValue)
{
	return [_GetPlayer() setAdditionalHttpHeader:_GetUrl(httpHeaderValue)];
}

extern "C" void NexPlayerUnity_SetMute(bool mute)
{
	[_GetPlayer() setMute: mute];
}

extern "C" void NexPlayerUnity_SetVolume(float volumeSize)
{
	[_GetPlayer() setVolume:volumeSize];
}

extern "C" int NEXPLAYERUnity_GetPlayerStatus()
{
	return [_GetPlayer() getPlayerStatus];
}

extern "C" void NexPlayerUnity_SetAutoPlayback(bool autoPlay)
{
	[_GetPlayer() setAutoPlayback:autoPlay];
}

extern "C" void NexPlayerUnity_SetFirstFrame(bool isShow)
{
	[_GetPlayer() setFirstFrame:isShow];
}

extern "C" int NEXPLAYERUnity_GetCurrentSubtitleByteArray(unsigned char* buffer)
{
	NSString *temp = [_GetPlayer() current_subtitle];
	const char* string = [temp UTF8String];

	int length = (int)strlen(string);
	memcpy(buffer, string, length);

	return length;
}

extern "C" char* NEXPLAYERUnity_GetCurrentSubtitleString()
{
	NSString *temp = [_GetPlayer() current_subtitle];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}

extern "C" int NEXPLAYERUnity_GetCurrentSubtitleType()
{
	int type = [_GetPlayer() subtitle_type];
	return type;
}

extern "C" int NEXPLAYERUnity_GetCurrentSubtitleStartTime()
{
	NSUInteger startTime = [_GetPlayer() subtitle_startTime];

	return (int)startTime;

}
extern "C" int NEXPLAYERUnity_GetCurrentSubtitleEndTime()
{

	NSUInteger endTime = [_GetPlayer() subtitle_endTime];


	return (int)endTime;

}

extern "C" void NEXPLAYERUnity_OnOffSubtitle(bool bOnOff)
{
	[_GetPlayer() OnOffSubtitle:bOnOff];
}

extern "C" void NEXPLAYERUnity_SetSubtitlePath(const char* subtitlePath)
{
	return [_GetPlayer() setSubtitlePath:_GetUrl(subtitlePath)];
}

extern "C" void NEXPLAYERUnity_SetSubtitleFD(const char* subtitleURI)
{
	return [_GetPlayer() setSubtitleFD:_GetUrl(subtitleURI)];
}

extern "C" void NEXPLAYERUnity_ChangeSubtitlePath(const char* subtitlePath)
{
	return [_GetPlayer() changeSubtitlePath:_GetUrl(subtitlePath)];
}

extern "C" void NEXPLAYERUnity_ChangeSubtitleFD(const char* subtitleURI)
{
	return [_GetPlayer() changeSubtitleFD:_GetUrl(subtitleURI)];

}

extern "C" void NEXPLAYERUnity_setSecretValueForSignature(const char* secret)
{
	return [_GetPlayer() setSecretValueForSignature:_GetUrl(secret)];
}

extern "C" void NexPlayerUnity_SetUseLicenseCache(bool bUse)
{
	return [_GetPlayer() setUseLicenseCache:bUse];
}

extern "C" void NEXPLAYERUnity_CleanVideoTexture()
{
	return [_GetPlayer() cleanVideoTexture];
}

extern "C" void NexPlayerUnity_SetLowLatency(bool enable, int value)
{
	return [_GetPlayer() setLowLatency:enable toValue:value];
}

extern "C" int NEXPLAYERUnity_GetTimedMetadata_Data(int nType, const char* TagID, unsigned char* TagData)
{
	NSDictionary *TimedMetadata = [_GetPlayer() timedMetadata];
	NSString *text;
	const char* string_tagData;
	NSString* string_tagID;
	int length = 0;
	NSDictionary* extraTags;
	NxTimedMetaExtraTag *extraTag;

	switch(nType)
	{
		case 0:   //Title
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyTitle];
			break;
		case 1:   //Album
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyAlbum];
			break;
		case 2:   //Artist
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyArtist];
			break;
		case 4:   //Genre
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyGenre];
			break;
		case 6:   //Track Number
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyTrackNum];
			break;
		case 7:   //Year
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyYear];
			break;
		case 10:  //Comment
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyComment];
			break;
		case 11:  //Text
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyText];
			break;
		case 12:  //Extra Tag
			extraTags = [TimedMetadata objectForKey:kNXTimedMetaKeyExtraData];
			string_tagID = _GetUrl(TagID);
			for(NSString *key in [extraTags keyEnumerator]){

				if([key isEqualToString:string_tagID] == YES)
				{
					extraTag = extraTags[key];
					text = [extraTag text];
					break;
				}
			}
			break;
		default:
			break;

	}
	if(text != nil)
	{
		string_tagData = [text UTF8String];
		length = (int)strlen(string_tagData);
		memcpy(TagData, string_tagData, length);
	}
	return length;
}

extern "C" int NEXPLAYERUnity_GetTimedMetadata_Data_Length(int nType, const char* TagID)
{
	NSDictionary *TimedMetadata = [_GetPlayer() timedMetadata];
	NSString *text;
	const char* string_tagData;
	NSString* string_tagID;
	int length = 0;
	NSDictionary* extraTags;
	NxTimedMetaExtraTag *extraTag;

	switch(nType)
	{
		case 0:   //Title
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyTitle];
			break;
		case 1:   //Album
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyAlbum];
			break;
		case 2:   //Artist
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyArtist];
			break;
		case 4:   //Genre
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyGenre];
			break;
		case 6:   //Track Number
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyTrackNum];
			break;
		case 7:   //Year
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyYear];
			break;
		case 10:  //Comment
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyComment];
			break;
		case 11:  //Text
			text = [TimedMetadata objectForKey:kNXTimedMetaKeyText];
			break;
		case 12:  //Extra Tag
			extraTags = [TimedMetadata objectForKey:kNXTimedMetaKeyExtraData];
			string_tagID = _GetUrl(TagID);
			for(NSString *key in [extraTags keyEnumerator]){

				if([key isEqualToString:string_tagID] == YES)
				{
					extraTag = extraTags[key];
					text = [extraTag text];
					break;
				}
			}
			break;
		default:
			break;

	}
	if(text != nil)
	{
		string_tagData = [text UTF8String];
		length = (int)strlen(string_tagData);

	}
	return length;
}


extern "C" int NEXPLAYERUnity_GetTimedMetadata_EncodingType(int nTyoe, const char* TagID)
{
	//only utf-8 in iOS
	return 3;
}

extern "C" int NEXPLAYERUnity_SetTimedMetadata_CustomTags(const char* Tags)
{
	[_GetPlayer() setCustomTags:_GetUrl(Tags)];

	return 0;
}

extern "C" BOOL NEXPLAYERUnity_setLicenseFile(const char* licenseFilePath)
{
	return [_GetPlayer() setLicenseFilePath:_GetUrl(licenseFilePath)];
}

extern "C" void NEXPLAYERUnity_SetCB_GetExtKey(NEXPLAYERGetKeyExtCallbackFunc getKeyExtCallback)
{
	g_GetKeyExtCallback = getKeyExtCallback;
}

//START NEW MARTIN 21-10-2019
extern "C" int NEXPLAYERUnity_GetAudioStreamCount() {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetAudioStreamCount \n"];
	return [_GetPlayer() getAudioStreamCount];
}
extern "C" void NEXPLAYERUnity_SetAudioStream(int ID) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_SetAudioStream \n"];
	int indexOfThisID = [_GetPlayer() getAudioIndexOfID:ID]; //We get an id, find its index
	[_GetPlayer() setAudioStream:indexOfThisID]; //Set audio to this index
}
extern "C" int NEXPLAYERUnity_GetCurrentAudioStreamID() {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCurrentAudioStreamID \n"];
	return [_GetPlayer() getCurrentAudioStreamID];
}
extern "C" char* NEXPLAYERUnity_GetCurrentAudioStreamName() {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCurrentAudioStreamName \n"];
	NSString *temp = [_GetPlayer() getCurrentAudioStreamName];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}
extern "C" char* NEXPLAYERUnity_GetCurrentAudioStreamLanguage() {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCurrentAudioStreamLanguage \n"];
	NSString *temp = [_GetPlayer() getCurrentAudioStreamLanguage];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}
extern "C" int NEXPLAYERUnity_GetAudioStreamID(int index) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetAudioStreamID \n"];
	return [_GetPlayer() getAudioStreamID:index];
}
extern "C" char* NEXPLAYERUnity_GetAudioStreamName(int index) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetAudioStreamName \n"];
	NSString *temp = [_GetPlayer() getAudioStreamName:index];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}
extern "C" char* NEXPLAYERUnity_GetAudioStreamLanguage(int index) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetAudioStreamLanguage \n"];
	NSString *temp = [_GetPlayer() getAudioStreamLanguage:index];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}




extern "C" void NEXPLAYERUnity_SetCaptionStream(int ID) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_SetCaptionStream. \n"];
	int indexOfThisID = [_GetPlayer() getCaptionIndexOfID:ID]; //We get an id, find its index
	[_GetPlayer() setCaptionStream:indexOfThisID]; //Set caption to this index
}
extern "C" int NEXPLAYERUnity_GetCaptionStreamCount() {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCaptionStreamCount \n"];
	return [_GetPlayer() getCaptionStreamCount];
}
extern "C" int NEXPLAYERUnity_GetCaptionStreamID(int index) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCaptionStreamID \n"];
	return [_GetPlayer() getCaptionStreamID:index];
}
extern "C" char* NEXPLAYERUnity_GetCaptionStreamName(int index) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCaptionStreamName \n"];
	NSString *temp = [_GetPlayer() getCaptionStreamName:index];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}
extern "C" char* NEXPLAYERUnity_GetCaptionStreamLanguage(int index) {
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetCaptionStreamLanguage \n"];
	NSString *temp = [_GetPlayer() getCaptionStreamLanguage:index];
	const char* string = [temp UTF8String];
	char* result = strdup(string);

	return result;
}
//END NEW MARTIN 21-10-2019



//Martin 05112019 - Offline DRM HLS/DASH playback

extern "C" int NEXPLAYERUnity_DownloadKeyServer(const char* url)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_DownloadKeyServer \n"];
	return [_GetPlayer() downloadKeyServer:_GetUrl(url)];
}

extern "C" void NEXPLAYERUnity_DownloadStream(const char* url)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_DownloadStream \n"];
	[_GetPlayer() downloadStream:_GetUrl(url)];
}

extern "C" void NEXPLAYERUnity_PlayOffline(const char* url)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_PlayOffline \n"];
	[_GetPlayer() playOffline:_GetUrl(url)];
}

extern "C" int NEXPLAYERUnity_GetDownloadPercentage()
{
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_GetDownloadPercentage \n"];
	return [_GetPlayer() getDownloadPercentage];
}

//End Martin 05112019 - Offline DRM HLS/DASH playback

//Multi-instance Martin 14012020
extern "C" void NexPlayerUnity_SetMultiStream(int totalScreens)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_SetMultiStream \n"];
	[_GetPlayer() setMultiStream:totalScreens];
}
extern "C" void NexPlayerUnity_SetMultiPaths(char* multiPath,int index)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_SetMultiPaths \n"];
	[_GetPlayer() setMultiPaths:_GetUrl(multiPath) toValue:index];
}
extern "C" void NexPlayerUnity_SetMultiKeyServers(char* keyServer, int index)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_SetMultiKeyServers \n"];
	[_GetPlayer() setMultiKeyServers:_GetUrl(keyServer) toValue:index];
}

extern "C" void NexPlayerUnity_ControlInstance(int index)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_ControlInstance \n"];
	[_GetPlayer() ControlInstance:index];
}
extern "C" int NEXPLAYERUnity_GetMultiSubIndex()
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_GetMultiSubindex \n"];
	return [_GetPlayer() getMultiSubIndex];
}
extern "C" int NEXPLAYERUnity_GetMultiInitPlayer()
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_GetMultiSubindex \n"];
	return [_GetPlayer() getMultiInitPlayer];
}
extern "C" void NexPlayerUnity_SetMultiProperty(int index, int property, int value)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_SetMultiProperty \n"];
	[_GetPlayer() setMultiProperty:index toValue:property toValuez: value];
}
extern "C" void NexPlayerUnity_SetMultiHTTPHeader(int index, char* header)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_SetMultiHTTPHeader \n"];
	[_GetPlayer() setMultiHTTPHeader:index toValue:_GetUrl(header)];
}
extern "C" void NexPlayerUnity_StartChosenPlayer(int index, char* url)
{
	[_GetPlayer() Log:4 toValue:@"iOS - NexPlayerUnity_StartChosenPlayer \n"];
	[_GetPlayer() startChosenPlayer:index toValue:_GetUrl(url)];
}

extern "C" intptr_t NEXPLAYERUnity_GetMultiPtr(int index) {
	if(UnitySelectedRenderingAPI() == apiMetal) {
		return [_GetPlayer() metalUpdateFrameMulti:index];
	}
}
//End multi-instance Martin 14012020

extern "C" void NEXPLAYERUnity_SetTrack(int bitrate){
	[_GetPlayer() setTrack:bitrate];
}

extern "C" void NEXPLAYERUnity_EnableABR(bool enable){
	[_GetPlayer() setEnabledABR:enable];
}

extern "C" int NEXPLAYERUnity_GetTrackCount(){
	return [_GetPlayer() getTrackCount];
}

extern "C" NexPlayerTrack NEXPLAYERUnity_GetTrack(int index){
	return [_GetPlayer() getTrack:index];
}

extern "C" void NexPlayerUnity_ReleasePlayer() {
}

extern "C" int NEXPLAYERUnity_AsyncCmdResult(){
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_AsyncCmdResult \n"];
	return 0;
}

extern "C" int NEXPLAYERUnity_AsyncCmdType(){
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_AsyncCmdType \n"];
	return 0;
}

extern "C" bool NEXPLAYERUnity_QueueIsEmpty(){
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_QueueIsEmpty \n"];
	return true;
}

extern "C" int NEXPLAYERUnity_AsyncCmdValue(){
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_AsyncCmdValue \n"];
	return 0;
}

extern "C" int NEXPLAYERUnity_Init(){
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_Init \n"];
	return 0;
}

extern "C" int NEXPLAYERUnity_SetWebGLKey(char * key){
	[_GetPlayer() Log:4 toValue:@"iOS - NEXPLAYERUnity_SetWebGLKey \n"];
	return 0;
}

extern "C" char * NativeGetVersion(){
    NSString *temp = @"1.0";
    const char* string = [temp UTF8String];
    char* result = strdup(string);
    return result;
}

extern "C" int NEXPLAYERUnity_NativeGetVersionMajor() { return -1; }
extern "C" int NEXPLAYERUnity_NativeGetVersionMinor() { return -1; }
extern "C" int NEXPLAYERUnity_NativeGetVersionPatch() { return -1; }
