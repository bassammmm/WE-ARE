//
//  NexPlayerEnum.h
//  Unity-iPhone
//
//  Created by DINO1 on 2018. 10. 17..
//

#ifndef NexPlayerEnum_h
#define NexPlayerEnum_h
const static NXLogLevel _UILogLevels[] = {
    NXLogLevelError,
    NXLogLevelWarning,
    NXLogLevelInformation,
    NXLogLevelDebug,
    NXLogLevelVerbose,
    NXLogLevelAboveVerbose,
    NXLogLevelExtraVerbose
};

const static NSInteger LogLevelExtraVerbose = 6;

enum NexPlayer_EVENT_TYPE {
    
    NEXUNITY_EVENT_ASYNC_COMPLETE         = 1,
    NEXUNITY_EVENT_END_OF_CONTENT         = 2,
    NEXUNITY_EVENT_UPDATE_CONTENT_INFO = 3,
    NEXUNITY_EVENT_TIME                 = 4,
    NEXUNITY_EVENT_BUFFERING            = 5,
    NEXUNITY_EVENT_ERROR                 = 6,
    NEXUNITY_EVENT_LOADSTART             = 7,
    NEXUNITY_EVENT_TEXT_INIT            = 255,
    NEXUNITY_EVENT_TEXT_RENDER            = 256,
    NEXUNITY_EVENT_TIMED_METADATA_RENDER            = 0x90002
    
};


enum NexPlayerASYNC_EVENT_TYPE {
    
    NEXUNITY_ASYNC_CMD_OPEN_LOCAL = 1,
    NEXUNITY_ASYNC_CMD_OPEN_STREAMING = 2,
    NEXUNITY_ASYNC_CMD_START_LOCAL = 5,
    NEXUNITY_ASYNC_CMD_START_STREAMING = 6,
    NEXUNITY_ASYNC_CMD_STOP = 8,
    NEXUNITY_ASYNC_CMD_PAUSE = 9,
    NEXUNITY_ASYNC_CMD_RESUME = 10,
    NEXUNITY_ASYNC_CMD_SEEK = 11,
    
};

enum NexPlayer_PROPERTY_TYPE {
    
    
    NEXUNITY_NXPropertyInitialBufferingDuration = 9,
    NEXUNITY_NXPropertyReBufferingDuration = 10,
    NEXUNITY_NXPropertyDRMLicenseTimeout = 12,
    NEXUNITY_NXPropertyTimestampDifferenceVDispWait = 13,
    NEXUNITY_NXPropertyTimestampDifferenceVDispSkip = 14,
    NEXUNITY_NXPropertySupportABR = 116,
    NEXUNITY_NXPropertyMaxBW = 117,
    NEXUNITY_NXPropertyAVSyncOffset = 124,
    NEXUNITY_NXPropertyPreferBandwidth = 129,
    NEXUNITY_NXPropertyEnableTrackdown = 131,
    NEXUNITY_NXPropertyTrackdownVideoRatio = 132,
    NEXUNITY_NXPropertyMinBW = 516,
    NEXUNITY_NXPropertyPreferLanguage = 531,
    NEXUNITY_NXPropertyStartNearestBW = 555,
    NEXUNITY_NXPropertyMaxCaptionLength = 901,
    NEXUNITY_NXPropertySPDEnable = 591,
    NEXUNITY_NXPropertySPDTime = 590,
    NEXUNITY_NXPropertySPDSpeedUpSyncTime = 592,
    NEXUNITY_NXPropertySPDJumpSyncTime = 593
    
};

enum NexPlayer_CONTENT_INFO {
    
    MEDIA_TYPE = 0,
    MEDIA_DURATION = 1,
    VIDEO_CODEC = 2,
    VIDEO_WIDTH = 3,
    VIDEO_HEIGHT = 4,
    VIDEO_FRAMERATE = 5,
    VIDEO_BITRATE = 6,
    AUDIO_CODEC = 7,
    AUDIO_SAMPLINGRATE = 8,
    AUDIO_NUMOFCHANNEL = 9,
    AUDIO_BITRATE = 10,
    MEDIA_ISSEEKABLE = 11,
    MEDIA_ISPAUSABLE = 12,
    VIDEO_FOURCC = 13,
    VIDEO_CODEC_CLASS = 14,
    VIDEO_PROFILE = 15,
    VIDEO_LEVEL = 16,
    VIDEO_CODEC_ERROR = 17,
    VIDEO_RENDER_AVG_FPS = 1000,
    VIDEO_RENDER_AVG_DSP = 1001,
    VIDEO_RENDER_COUNT = 1002,
    VIDEO_RENDER_TOTAL_COUNT = 1003,
    VIDEO_CODEC_DECODING_COUNT = 1004,
    VIDEO_CODEC_DECODING_TOTAL_COUNT = 1005,
    VIDEO_CODEC_AVG_DECODE_TIME = 1006,
    VIDEO_CODEC_AVG_RENDER_TIME = 1007,
    VIDEO_CODEC_DECODE_TIME = 1008,
    VIDEO_CODEC_RENDER_TIME = 1009,
    VIDEO_AVG_BITRATE = 1010,
    VIDEO_FRAMEBYTES = 1011,
    AUDIO_AVG_BITRATE = 1012,
    AUDIO_FRAMEBYTES = 1013,
    VIDEO_FRAME_COUNT = 1014,
    VIDEO_TOTAL_FRAME_COUNT = 1015
    
};


const int PLAYER_ERROR_NONE = 0;
const int PLAYER_ERROR_GENERAL = -1;
const int PLAYER_INIT_FAILURE = -2;
const int PLAYER_TEXTURE_FAILURE = -3;

const int INVALID_SUBTITLE_PATH = 10;
#endif /* NexPlayerEnum_h */
