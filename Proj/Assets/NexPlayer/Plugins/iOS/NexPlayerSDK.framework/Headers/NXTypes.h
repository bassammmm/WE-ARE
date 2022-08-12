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

/* Allow Doxygen to detect NS_ENUM as enum */
#ifndef _DOC_ENUM
#define _DOC_ENUM(name)
#endif

/** \defgroup types Types
 *
 */

/**
 * \ingroup types
 * \brief Represents the duration of the content as a span of time in \c milliseconds.
 *
 */
typedef NSUInteger NXDuration;

/**
 * \ingroup types
 * \brief For live streams where duration of content cannot be determined, this
 * type can be passed in place of \c NXDuration.
 *
 */
#define NXDuration_Unknown      (0xFFFFFFFFU)

/**
 * \ingroup types
 * \brief Open modes.
 *
 * These are possible argument values for \c mode parameter in NXPlayer::open:. 
 */
typedef NS_ENUM(NSUInteger, NXOpenMode) {
	NXOpenModeAuto				= 0,	///< Select streaming play for "http:", "https:", "rtsp:" and "mms:" addresses, local play for everything else
	NXOpenModeLocal				= 1,	///< Plays a local file, given a local path or a URL starting with "file://"
	NXOpenModeStreaming			= 2,	///< Plays streaming video; if a path (not a URL) is given, it is assumed to be a path to an SDP file for an RTSP stream
	NXOpenModeLocalBundle		= 3,	///< Plays a local file from the current application bundle (a relative path should be passed)
	NXOpenModeLocalDocs			= 4,		///< Plays a local file from the application documents area (the area where files are placed if added via iTunes)
	NXOpenModeStoreStream		= 5		///< New source type value for storing HLS Stream
} _DOC_ENUM(NXOpenMode);


/**
 * \ingroup types
 * \deprecated  This has been deprecated since version 5.16.  Do not use.
 *
 * \since version 5.16
 */
typedef NS_ENUM(NSUInteger, NXOnOffDefault) {
    NXDefault = 0,
    NXOff = 1,
    NXOn = 2
} _DOC_ENUM(NXOnOffDefault);

/**
 * \ingroup types
 * \brief Playback types.
 */
typedef NS_ENUM(NSUInteger, NXPlaybackType) {
	NXPlaybackTypeLocal					= 0, ///< Content is local (local path or "file://" URL)
	NXPlaybackTypeStreaming				= 1  ///< Content is streaming (including on-demand, progressive download or live)
} _DOC_ENUM(NXPlaybackType);

/**
 * \ingroup types
 * \brief Transport layers (TCP and UDP) for RTP and RTCP packets.
 *
 */
typedef NS_ENUM(NSUInteger, NXTransportType) {
	NXTransportTypeTCP					= 0, ///< RTP/RTCP over TCP
	NXTransportTypeUDP					= 1  ///< RTP/RTCP over UDP
} _DOC_ENUM(NXTransportType);

/**
 * \ingroup types
 * \brief Possible states of the player (paused, stopped, etc.).
 *
 * The current player state is available through \c NXPlayer::state.
 */
typedef NS_ENUM(NSUInteger, NXPlayerState) {
	NXPlayerStateNone						= 0,	///< No current valid state (for example API not initialized)
	NXPlayerStateClose						= 1,	///< Content is currently closed
	NXPlayerStateStop                       = 2,	///< Content is open and stopped
	NXPlayerStatePlay                       = 3,	///< Content is open and playing
	NXPlayerStatePause                      = 4		///< Content is open and paused during playback
} _DOC_ENUM(NXPlayerState);

/**
 * \ingroup types
 * \brief RTSP method identifiers.
 *
 * These are used with \c NXPlayer::addRTSPHeaderField:forMethods:
 */
typedef NS_ENUM(NSUInteger, NXRTSPMethod) {

	NXRTSPMethodNone					= 0x00000000,	///< No RTSP method
	NXRTSPMethodDescribe				= 0x00000001,	///< RTSP DESCRIBE method (request presentation description, generally SDP)
	NXRTSPMethodSetup					= 0x00000002,	///< RTSP SETUP method (specify ports, transport, etc.)
	NXRTSPMethodPlay					= 0x00000004,	///< RTSP PLAY method (request playback)
	NXRTSPMethodPause					= 0x00000008,	///< RTSP PAUSE method (pause playback)
	NXRTSPMethodTeardown				= 0x00000010,	///< RTSP TEARDOWN method (stop media streams and terminate session)
	NXRTSPMethodOptions					= 0x00000020,	///< RTSP OPTIONS
	NXRTSPMethodRedirect				= 0x00000040,	///< RTSP REDIRECT
	NXRTSPMethodSetParameter			= 0x00000080,	///< RTSP GET PARAMETER
	NXRTSPMethodGetParameter			= 0x00000100,	///< RTSP SET PARAMETER
	NXRTSPMethodAnnounce				= 0x00000200,	///< RTSP ANNOUNCE
	NXRTSPMethodPlaylist				= 0x00000400,	///< RTSP PLAYLIST
	NXRTSPMethodAll						= 0x0000FFFF	///< Indicates all current and future RTSP method types

} _DOC_ENUM(NXRTSPMethod);

/**
 * \ingroup types
 * \brief Codec type identifiers.
 *
 * These are used with \c NXContentInformation::audioCodec,
 * \c NXContentInformation::videoCodec and
 * \c NXContentInformation::captionType.
 */
typedef NS_ENUM(NSUInteger, NXCodecID) {
	NXCodecID_UNKNOWN	= 0x00000000,
	/************************************
	 Video Codecs
	 ************************************/
	NXCodecID_MPEG4V	= 0x10020100,
	NXCodecID_HEVC		= 0x10010400,
	NXCodecID_H264		= 0x10010300,
	NXCodecID_H263		= 0x10010200,
	NXCodecID_WMV		= 0x10060000,
	NXCodecID_WMV1		= 0x10060100,
	NXCodecID_WMV2		= 0x10060200,
	NXCodecID_WMV3		= 0x10060300,
	NXCodecID_DIVX		= 0x10040000,
	NXCodecID_WVC1		= 0x10060400,

	/************************************
	 Audio Codecs
	 ************************************/
	NXCodecID_AAC		= 0x20020000,
	NXCodecID_AACPlus	= 0x20020100,
	NXCodecID_WMA		= 0x20070000,
	NXCodecID_WMA1		= 0x20070100,
	NXCodecID_WMA2		= 0x20070200,
    NXCodecID_MP3       = 0x20010200,
	NXCodecID_AC3       = 0x20030000,
	NXCodecID_AC4       = 0x20030200,
	NXCodecID_EAC3      = 0x20030100,

	NXCodecID_DTS		= 0x20040000,

	/************************************
	 Text Codecs
	 ************************************/
	NXCodecID_EXTERNAL_SMI		= 0x30030100,
	NXCodecID_EXTERNAL_SRT		= 0x30040100,
	NXCodecID_3GPP_TIMEDTEXT	= 0x30010100,
	NXCodecID_TEXT_WEBVTT		= 0x300C0100,
	NXCodecID_TEXT_CC_CEA		= 0x300D0100,
	NXCodecID_TEXT_TTML			= 0x300B0100,
	NXCodecID_VOB_SUB			= 0x30060100,
	NXCodecID_MICRODVD_SUB		= 0x30070100,
	NXCodecID_DIVX_XSUB			= 0x300E0000,
	NXCodecID_DIVX_XSUBPLUS		= 0x300E0100,
	
	
	/************************************
	 Speech Codecs
	 ************************************/
	NXCodecID_AMR		= 0x20180000
} _DOC_ENUM(NXCodecID);

/**
 * \ingroup types
 * \brief CEA 608 Colors.
 *
 * These are used to indicate the foreground and background colors
 * associated with CEA 608 closed captions.
 *
 * Note that only the semi-transparent options will be used
 * for background color of captions.
 *
 * \since version 5.8
 */
typedef NS_ENUM(NSUInteger, NXCEA608Color) {
    NXCEA608Color_White                 = 0,  ///< white
    NXCEA608Color_White_Semitrans       = 1,  ///< semi-transparent white
    NXCEA608Color_Green                 = 2,  ///< green
    NXCEA608Color_Green_Semitrans       = 3,  ///< semi-transparent green
    NXCEA608Color_Blue                  = 4,  ///< blue
    NXCEA608Color_Blue_Semitrans        = 5,  ///< semi-transparent blue
    NXCEA608Color_Cyan                  = 6,  ///< cyan
    NXCEA608Color_Cyan_Semitrans        = 7,  ///< semi-transparent cyan
    NXCEA608Color_Red                   = 8,  ///< red
    NXCEA608Color_Red_Semitrans         = 9,  ///< semi-transparent red
    NXCEA608Color_Yellow                = 10, ///< yellow
    NXCEA608Color_Yellow_Semitrans      = 11, ///< semi-transparent yellow
    NXCEA608Color_Magenta               = 12, ///< magenta
    NXCEA608Color_Magenta_Semitrans     = 13, ///< semi-transparent magenta
    NXCEA608Color_Black                 = 14, ///< black
    NXCEA608Color_Black_Semitrans       = 15, ///< semi-transparent black
    NXCEA608Color_Transparent           = 16, ///< transparent (only used for background color)
    NXCEA608Color_Default               = 17,  ///< This value is only used when overriding font attribute.
    NXCEA608Color_Last                  = NXCEA608Color_Default, ///< This value marks the maximum possible color value.
} _DOC_ENUM(NXCEA608Color);

/**
 * \ingroup types
 * \brief CEA 608 Character Set IDs.
 *
 * These are used to choose the character set to
 * display CEA 608 closed caption information.
 *
 * \since version 5.8
 */
typedef NS_ENUM(NSUInteger, NXCEA608Charset) {
    NXCEA608Charset_Unicode         = 0, ///< Unicode character set.
    NXCEA608Charset_Private1        = 1, ///< For use with a private, non-standard character set. May be ignored.
    NXCEA608Charset_Private2        = 2, ///< For use with a private, non-standard character set. May be ignored.
    NXCEA608Charset_KSC_5601_1987   = 3, ///< Korean character set.
    NXCEA608Charset_GB_2312_80      = 4  ///< Chinese character set.
} _DOC_ENUM(NXCEA608Charset);

/**
 * \ingroup types
 * \brief CEA-608 caption cell information.
 *
 * This structure is used by to store CEA 608 closed caption cell information
 * and is passed to \c NXCEA608CaptionView to be displayed.
 *
 * \since version 5.8
 */
typedef struct {
    unsigned short  characterCode;   ///< The character code of the cell.
    NXCEA608Charset characterSet;    ///< The character set to use to encode the cell.
    NXCEA608Color   backgroundColor; ///< The background color of the character.
    NXCEA608Color   foregroundColor; ///< The foreground color of the character.
    BOOL            large;     ///< (ignored by NexPlayer&trade;) Whether or not the cell is to be displayed "large".
    BOOL            italic;    ///< Whether or not the cell is displayed in <i>italics</i>.
    BOOL            underline; ///< Whether or not the cell is underlined.
    BOOL            flash;     ///< Whether or not to display the cell flashing.
} NXCEA608CellInfo;

/**
 * \ingroup types
 * \brief Media types.
 *
 * These are used with \c NXMediaStreamInfo::type to indicate the type of the
 * stream (audio or video) described by \c NXMediaStreamInfo.
 */
typedef NS_ENUM(NSUInteger, NXMediaType) {
	NXMediaTypeUnknown	= 0,  ///< Unknown media type.
	NXMediaTypeAudio	= 1,  ///< Audio only stream.
	NXMediaTypeVideo	= 2,  ///< Video only stream.
	NXMediaTypeText     = 3,  ///< Text stream.
    NXMediaTypeAV       = 4   ///< A/V stream.
} _DOC_ENUM(NXMediaType);

/**
 * \ingroup types
 * \brief CEA 608 Channel IDs.
 *
 * These are possible values for \c NXPlayer::selectedCEA608Channel.
 *
 * They set the channel from which CEA 608 closed captions will be received.  While there are four
 * channels to receive caption information from the NTSC line 21 fields, as channels 1 and 2
 * share field 1 and channels 3 and 4 share field 2, the most common channels used to receive
 * captions are Channels 1 and 3.  These channels can represent the same information in
 * different languages and are often intended to be selected by the user from the application.
 *
 * \since version 5.8
 */
typedef NS_ENUM(NSUInteger, NXCEA608Channel) {
	NXCEA608Channel_None	= 0,    ///< No CEA 608 captions (disable)
	NXCEA608Channel_Ch1     = 1,    ///< NTSC line 21 field 1 closed captions (first channel);  CEA 608 Caption Channel 1
	NXCEA608Channel_Ch2     = 2,    ///< NTSC line 21 field 1 closed captions (second channel); CEA 608 Caption Channel 2
	NXCEA608Channel_Ch3     = 3,    ///< NTSC line 21 field 2 closed captions (first channel);  CEA 608 Caption Channel 3
    NXCEA608Channel_Ch4     = 4     ///< NTSC line 21 field 2 closed captions (second channel); CEA 608 Caption Channel 4
} _DOC_ENUM(NXCEA608Channel);

/**
 * \ingroup types
 * \brief Debugging Messages to include.
 *
 * These are possible values for \c NXPlayerDelegate::nexPlayer:debugMessage:category: and
 * set the debugging messages to be provided.
 */
typedef NS_ENUM(NSUInteger, NXDebugMsgCat) {
	NXDebugMsgCat_RTSP                    = 0x00,	///< Debugging information related to the RTSP connection status
	NXDebugMsgCat_RTP_RECV                = 0x01,	///< Debugging information associated with the start of an RTP packet receipt
	NXDebugMsgCat_RTP_RECV_END            = 0x02,	///< Debugging information associated with the end of an RTP packet receipt
	NXDebugMsgCat_RTCP_RR_SEND            = 0x03,	///< Debugging information associated with the transmission of an RTCP RR (Receiver Report) packet
	NXDebugMsgCat_RTCP_BYE_RECV           = 0x04,	///< This occurs when an RTCP BYE packet is received
	NXDebugMsgCat_CONTENT_INFO            = 0x05,	///< General information about the content that is currently playing
	NXDebugMsgCat_HTTP_RESPONSE           = 0x06,	///< Debugging information of HTTP Response
	NXDebugMsgCat_DOWNLOADED_BUFF         = 0x07,	///< Debugging information of downloaded buffer
	NXDebugMsgCat_DECODING                = 0x08,	///< Debugging information of decoding event
	NXDebugMsgCat_H264_SEI_PICTIMING      = 0x09,	///< Debugging information for handling H.264 SEI picture timing information
	NXDebugMsgCat_EYE_PLEASER_STATE		  = 0x10,	///< Debugging information of Eye-Pleaser State
	NXDebugMsgCat_HTTP_REQUEST            = 0x11,	///< Debugging information of HTTP request
	NXDebugMsgCat_TIMESHIFT_BUFFERFULL	  = 0x12	///< Debugging information of full of buffer for TimeShift
} _DOC_ENUM
(NXDebugMsgCat);

/**
 * \ingroup types
 * \brief Opaque file handle.
 *
 * This is an arbitrary value used to identify files in calls
 * to \c NXRemoteFileIOInterface methods.  The meaning of this is unique to
 * a given implementation of \c NXRemoteFileIOInterface, and return values from
 * different implementations should not be mixed.
 *
 * \see NXRemoteFileIOInterface for more details.
 */
typedef void* NXFileHandle;

/**
 * \ingroup types
 * \brief Mode for opening a file.
 *
 * Identifies different methods for opening or creating a file.  This is is
 * passed to implementations of the \c NXRemoteFileIOInterface protocol to
 * indicate how a file should be opened.
 *
 * \see \c NXRemoteFileIOInterface for more details.
 */
typedef enum NXFileMode_
{
	NXFileModeRead         	= 1,	/**< Read                      */
	NXFileModeWrite        	= 2, 	/**< Write                     */
	NXFileModeReadWrite    	= 3, 	/**< Read and Write			   */
	NXFileModeCreate       	= 4  	/**< Create                    */
} NXFileMode;

/**
 * \ingroup types
 * \brief Origin when seeking within a file.
 *
 * Identifies different origins for seeking within a file.  This is is
 * passed to implementations of the \c NXRemoteFileIOInterface protocol to
 * indicate where to measure the seek offset from.
 *
 * \see \c NXRemoteFileIOInterface for more details.
 */
typedef enum NXFileSeekOrigin_
{
    NXFileSeekOriginBeginning	= 0,  /**< Beginning of file         */
    NXFileSeekOriginCurrent		= 1,  /**< Current position          */
    NXFileSeekOriginEnd       	= 2   /**< End of file               */

} NXFileSeekOrigin;

/**
 * \ingroup types
 * \brief DRM types.
 *
 * These are returned by DRM descramblers to indicate at what stage the
 * descrambling takes place.  Not all DRM descrambling protocols support
 * all types; see the individual descrambler protocol documentation for
 * details.
 */
typedef enum NXDRMType_ {
	NXDRMTypePayload = 0x01,        ///< Descrambling is done at the payload level
	NXDRMTypePacket  = 0x10,        ///< Descrambling is done at the packet level
    NXDRMTypeFrame   = 0x20         ///< Descrambling is done individually for each frame
} NXDRMType;

/**
 * \ingroup types
 * \brief Video image scaling modes.
 *
 * These are various possible automatic video scaling modes that
 * can be set for \c NXPlayerView::autoScaling.
 */
typedef NS_ENUM(NSUInteger, NXScale){
    NXScale_None            = 0,    ///< No automatic scaling
    NXScale_OriginalSize    = 1,    ///< Original video size
    NXScale_FitInView       = 2,    ///< Fit video to container (as large as possible without cropping; maintain aspect ratio)
    NXScale_FillView        = 3,    ///< NexPlayer will fill the parent container  (crop and maintain aspect ratio)
    NXScale_Stretch         = 4     ///< Stretch to container dimensions (does not maintain aspect ratio)
} _DOC_ENUM(NXScale);

/**
 * \ingroup types
 * \brief Keep alive send modes.
 *
 * These are possible values for the \c property ::NXPropertyKeepAliveSendMode
 *
 * See that property for details.
 */
typedef enum NXKeepAliveSendMode_ {
    NXKeepAliveSendMode_None            = 0x00000000, ///< None
    NXKeepAliveSendMode_PauseState      = 0x00000001, ///< Pause only
    NXKeepAliveSendMode_PlayState       = 0x00000002, ///< Play only
    NXKeepAliveSendMode_PausePlayState  = 0x00000003, ///< Pause and play
    NXKeepAliveSendMode_AllState        = 0x000000FF  ///< All
} NXKeepAliveSendMode;

/**
 * \ingroup types
 * \brief File formats.
 *
 * These are possible file format values that can
 * be used for \c NXContentInfo::fileFormat.
 */
typedef enum NXFileFormat_ {
	NXFileFormatMP4		= 0x00000001, ///<  MP4
	NXFileFormatAMRNB	= 0x00000002, ///<  AMR-NB
	NXFileFormatAMRWB	= 0x00000004, ///<  AMR-WB
	NXFileFormatADIFAAC	= 0x00000008, ///<  ADIFAAC
	NXFileFormatMP3		= 0x00000010, ///<  MP3
	NXFileFormatADTSAAC	= 0x00000020, ///<  ADTSAAC
	NXFileFormatAVI		= 0x00000040, ///<  AVI
	NXFileFormatASF		= 0x00000080, ///<  ASF
	NXFileFormatRMFF	= 0x00000100, ///<  RMFF
	NXFileFormatMKV		= 0x00000200, ///<  MKV
	NXFileFormatPDCF	= 0x00000400, ///<  PDCF
	NXFileFormatOGM		= 0x00000800, ///<  OGM
	NXFileFormatOGG		= 0x00001000, ///<  OGG
	NXFileFormatMPEG_PS	= 0x00002000, ///<  MPEG-PS
	NXFileFormatMPEG_TS	= 0x00004000, ///<  MPEG-TS
	NXFileFormatFLV		= 0x00008000, ///<  FLV
	NXFileFormatQCELP	= 0x00010000, ///<  QCELP
	NXFileFormatFLAC	= 0x00020000, ///<  FLAC
	NXFileFormatAPE		= 0x00040000, ///<  APE
	NXFileFormatMOV		= 0x00080000, ///<  MOV
	NXFileFormatWAV		= 0x00100000, ///<  WAV
	NXFileFormatNONE	= 0x7FFFFFFF
} NXFileFormat;

/**
 * \ingroup types
 * \brief RTSP options.
 *
 * These are possible values for the \c ::NXPropertyRTSPOptionsSendMode property.
 */
typedef enum NXRTSPOptions_ {
	NXRTSPOptionsSendModeNone			= 0x00000000,	///< No send-mode options specified
	NXRTSPOptionsDescribe				= 0x00000001,	///< Send RTSP OPTIONS before RTSP DESCRIBE
	NXRTSPOptionsFirstSetup				= 0x00000002,	///< Send RTSP OPTIONS before the first RTSP SETUP Request
	NXRTSPOptionsEverySetup				= 0x00000004,	///< Send RTSP OPTIONS before every RTSP SETUP Request
	NXRTSPOptionsFirstPlay				= 0x00000008,	///< Send RTSP OPTIONS before the first RTSP PLAY Request
	NXRTSPOptionsEveryPlay				= 0x00000010,	///< Send RTSP OPTIONS before every RTSP PLAY Request
	NXRTSPOptionsFirstPause				= 0x00000020,	///< Send RTSP OPTIONS before the first RTSP PAUSE Request
	NXRTSPOptionsEveryPause				= 0x00000040,	///< Send RTSP OPTIONS before every RTSP PAUSE Request
	NXRTSPExtraOptionsWaitResponse		= 0x00010000,	///< Wait for extra OPTIONS response timeout
	NXRTSPExtraOptionsNoWaitResponse	= 0x00020000,	///< Do not wait for extra OPTIONS response timeout
} NXRTSPOptions;

/**
 * \ingroup types
 * \brief SAR (Sample Aspect Ratio) of H.264 contents.
 *
 */
typedef struct {
    NSUInteger width; ///< The width of the content.
    NSUInteger height;///< The height of the content.
} NXSARInfo;

/**
 * \ingroup types
 * \brief These are the available log levels for the NXPlayer::setLogLevel:.
 *
 * The higher the log level, the more logs will be enabled. The following are the log levels in ascending order : 
 * -# NXLogLevelError 			(Lowest level)
 * -# NXLogLevelWarning
 * -# NXLogLevelInformation
 * -# NXLogLevelDebug
 * -# NXLogLevelVerbose
 * -# NXLogLevelAboveVerbose
 * -# NXLogLevelExtraVerbose	(Highest level)
 *
 * \note NXLogLevelDisabled disables the log.
 *
 * \since version 5.28 (updated)
 */
typedef NS_ENUM(NSInteger, NXLogLevel) {
	NXLogLevelError = -3,       ///< Enables error level log only
	NXLogLevelWarning = -2,     ///< Enables warning level log and below
	NXLogLevelDisabled = -1,    ///< Log disabled
	NXLogLevelInformation = 0,  ///< Enables information level log and below (default)
	NXLogLevelDebug = 1,        ///< Enables debug level log and below
	NXLogLevelVerbose = 2,      ///< Enables verbose level log and below
	NXLogLevelAboveVerbose = 3,	///< Enables above verbose level log and below. This will have more logs than the verbose level.
	NXLogLevelExtraVerbose = 4,	///< Enables extra verbose level log and below. This will have more logs than the above verbose level.
} _DOC_ENUM(NXLogLevel);

/**
 * \ingroup types
 * \brief This enumeration defines the possible options for the NXPlayer::setVideoBitrates:len:withOption:.
 */
typedef NS_ENUM(NSUInteger, NexAvailableBitrate) {
	NexAvailableBitrateNone = 0,     ///< No restriction on subtracks other than the bitrates selected in \c bitrates.
	NexAvailableBitrateMatch = 1,    ///< Only use subtracks which have exact same bitrate as the selected bitrates passed in \c bitrates.
	NexAvailableBitrateNearest = 2,  ///< Only use subtracks which have the nearest bitrates to the target bitrates.
	NexAvailableBitrateHigh = 3,     ///< Only use subtracks which have bitrates equal to or higher than the target bitrate.
	NexAvailableBitrateLow = 4,      ///< Only use subtracks which have bitrates equal to or lower than the target bitrate.
	NexAvailableBitrateInsideRange = 5   ///< Only use subtracks which have bitrates inside the range defined by the bitrates.
} _DOC_ENUM(NexAvailableBitrate);


/**
 * \ingroup types
 * \brief This enumeration defines the possible events for NXPlayer::didReceiveInformativeEvent:details:.
 */
typedef NS_ENUM ( NSUInteger, NexInformativeEvent )  {
	NexInformativeEventDownloadBegan	= 0,	///< Download of a URL began. Parameter keys in details: kNexInformativeEventURL
	NexInformativeEventDownloadFinished	= 1		///< Download of a URL finished. Parameter keys in details: kNexInformativeEventURL, and kNexInformativeEventResult.
} _DOC_ENUM(NexInformativeEvent);

/**
 * \ingroup types
 * \brief This enumeration defines the possible options for the NXPlayerABRController:: setTargetBandwidth:withSegmentOption:withTargetOption:.
 * One of the following \c NexBandwidthSegmentOption values, indicating how to handle the buffered content when the track switches:
 */
typedef NS_ENUM(NSUInteger, NexBandwidthSegmentOption) {
    NexBandwidthSegmentOptionDefault = 0,   ///< Default (NexPlayer&trade;&nbsp; will decide between \c NexBandwidthSegmentOptionQuickMix (switching tracks quickly) and \c NexBandwidthSegmentOptionLateMix (playing buffered content and changing tracks more slowly)).
    NexBandwidthSegmentOptionQuickMix = 1,  ///< NexPlayer&trade;&nbsp; will clear the buffer as much as possible and will start to download a new track so the user can switch faster.
    NexBandwidthSegmentOptionLateMix = 2    ///< NexPlayer&trade;&nbsp; will preserve and play the content segments already buffered, and will download a new track.
} _DOC_ENUM(NexBandwidthSegmentOption);

/**
 * \ingroup types
 * \brief This enumeration defines the possible options for the NXPlayerABRController:: setTargetBandwidth:withSegmentOption:withTargetOption:.
 * This can be a guide on how to use the target bandwidth value set.  One of the following \c NexBandwidthTargetOption options:
 */
typedef NS_ENUM(NSUInteger, NexBandwidthTargetOption) {
    NexBandwidthTargetOptionDefault = 0,    ///< Default target option (\c NexBandwidthTargetOptionBelow).
    NexBandwidthTargetOptionBelow = 1,      ///< Select a track with a bandwidth below the target bandwidth.
    NexBandwidthTargetOptionAbove = 2,      ///< Select a track with a bandwidth above the target bandwidth.
    NexBandwidthTargetOptionMatch = 3       ///< Select the track that has a bandwidth that matches the set target; otherwise send an error and no new target bandwidth will be selected.
} _DOC_ENUM(NexBandwidthTargetOption);

//++
/**
 * \ingroup types
 * \brief This enumeration defines IDs for the possible options when handling Dynamic Thumbnail information in HLS & Smooth Streaming content.
 * These are possible values for the \c uId parameter in NxPlayer::setOptionDynamicThumbnailwithOption: andParam1: andParam2: ;
 *
 * \since version 5.27
 */
typedef NS_ENUM(NSUInteger, NexDynamicThumbnailOption) {
	NexDynamicThumbnailOptionNone			= 0,	// None
	NexDynamicThumbnailOptionInterval		= 1		//< Interval time (If this option isn't set as (default), the interval time will be set to 20 sec.)
//	NexDynamicThumbnailOptionSetResolution	= 2,	// Resolution set (NOT supported)
//	NexDynamicThumbnailOptionMaxFrameCount	= 3,	// Max frame count (NOT supported)
} _DOC_ENUM(NexDynamicThumbnailOption);

