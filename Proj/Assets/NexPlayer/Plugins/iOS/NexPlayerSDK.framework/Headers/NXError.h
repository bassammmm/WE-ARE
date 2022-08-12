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

/**
 * \ingroup types
 * \brief NexPlayer&trade; error codes.
 *
 * There are many error codes defined in this enum, but only the error codes 
 * documented here are used.
 */
typedef NS_ENUM(NSUInteger, NXError) {
	
	NXErrorNone								= 0x00000000,	///< No error
	NXErrorHasNoEffect,										///< Already in the requested state or non-valid command (Ex: seek for live-streaming).
	NXErrorInvalidParameter,								///< One or more of the parameters passed in is invalid
	NXErrorInvalidInfo,										///< One or more of the information passed in is invalid
	NXErrorInvalidState,									///< The command is not valid at the current state. (Ex. NexPlayerSWPPause function is called when the current state is NEXPLAYERSTATEPAUSE) 
	NXErrorMemoryOperation,									///< The memory operation failed. (Ex. heap memory allocation)
	NXErrorFileOperation,									///< The file operation failed. (Ex. file seek, file open)
	NXErrorFileInvalidSyntax,
	NXErrorNotSupportPVXFile,
	NXErrorNotSupportAudioCodec,							///< The content included unregistered audio codec type
	NXErrorNotSupportVideoCodec,							///< The content included unregistered video codec type
	NXErrorNotSupportVideoResolution,	
	NXErrorNotSupportMedia,
	NXErrorInvalidCodec,									///< The content includes unknown audio or video codec type
	NXErrorCodec,											///< An error occurred at audio or video decoding
	NXErrorPartialSuccess,
	NXErrorAlreadyCreateAsyncProc,
	NXErrorInvalidAsyncCmd,
	NXErrorAsyncOthercmdPrcessing,							///< The command queue for processing invoked Async functions was full
	NXErrorRTCPByeReceived,									///< An error occurred in receiving RTCP BYE message from streaming server
	NXErrorUserTerminated,									///< Terminated by the user
	NXErrorSystemFail,
	NXErrorNoDataInBuffer,
	NXErrorUnknown,
	NXErrorNotSupportToSeek,
	NXErrorNotSupportAVCodec,
	NXErrorMediaOpenTimeout					= 0x00000023,
	NXErrorDataInactivityTimeout			= 0x00000026,	///< An unhandled \c NXPlayerDelegate::nexPlayerDataInactivityTimeout: event occurred.
	NXErrorNetworkProtocol					= 0x00000029,	///< Network or protocol error
	NXErrorMediaNotFound					= 0x0000002A,	///< Media not found at the URL
	NXErrorDrmDecryptFailed					= 0x00000022,	///< DRM decryption failure
	NXErrorDrmInitFailed					= 0x0000002C,	///< DRM init failure
	
	NXErrorNotSupportFeature				= 0x00000FFF,
    
    NXErrorProtocolInvalidURL               = 0x00010001,
    NXErrorProtocolInvalidResponse          = 0x00010002,
    NXErrorProtocolContentInfoParsingFail   = 0x00010003,
    NXErrorProtocolNoProtocol               = 0x00010004,
    NXErrorProtocolNoMedia                  = 0x00010005,
    NXErrorProtocolNetOpenFail              = 0x00010006,
    NXErrorProtocolNetConnectFail           = 0x00010007,
    NXErrorProtocolNetBindFail              = 0x00010008,
    NXErrorProtocolNetDNSFail               = 0x00010009,
    NXErrorProtocolNetConnectionClosed      = 0x0001000A,
    NXErrorProtocolNetSendFail              = 0x0001000B,
    NXErrorProtocolNetRecvFail              = 0x0001000C,
    NXErrorProtocolNetRequestTimeout        = 0x0001000D,
	NXErrorProtocolNotSupportAESEncryption	= 0x0001000E,
	NXErrorProtocolNetSSLCertFail			= 0x0001000F,
	NXErrorProtocolDisabledMedia			= 0x00010010,

    NXErrorHTTPStatusCode                   = 0x00020000,
	
	NXErrorInternalBase						= 0x00030000,
	
	NXErrorExternalBase						= 0x00040000,
	NXErrorExternalDescrambleTimeout        = 0x01000001,
	
	NXErrorDownloaderInvalidParameter		= 0x00050000,
	NXErrorDownloaderInvalidState,
	NXErrorDownloaderMemoryOperation,
	NXErrorDownloaderFileOperation,
	NXErrorDownloaderConnectionFail,
	NXErrorDownloaderConnectionClosed,
	NXErrorDownloaderPVXdownFail,
	NXErrorDownloaderPVXparsingFail,
	NXErrorDownloaderNotMultiparts,
	NXErrorDownloaderHTTPparsingFail,
	
	NXErrorTimeshiftBase					= 0x00060000, 
	NXErrorTimeshiftWrite					= 0x00060001, 
	NXErrorTimeshiftRead					= 0x00060002, 
	NXErrorTimeshiftFindIframe				= 0x00060003, 
	
	//DivXDRM Error
	NXErrorDivXDRMBase						= 0x00070000,
	NXErrorDivXDRMNotAuthorized,
	NXErrorDivXDRMNotRegistered,
	NXErrorDivXDRMRentalExpired,
	NXErrorDivXDRMGeneralError,
	NXErrorDivXDRMNeverRegistered,
	
	//Thumbnail Error
	NXErrorThumbnailBase					= 0x00080000,
	NXErrorThumbnailCreateFail,
	NXErrorThumbnailProcessFail,
	NXErrorThumbnailDRMContents,
	
	// Recording Error
	NXErrorRecordBase						= 0x00090000,
	NXErrorAddframeSizeFull,	
	NXErrorAddframeTimeFull,	
	NXErrorAddframeMemFull,
	NXErrorAddframeError,
	
	// NexPlayer SDK for iOS API-Level Error
	NXErrorAPIBase							= 0x00900000,
	NXErrorAPICannotCreateDownloader,
	NXErrorAPIInvalidInfo,
	NXErrorCommandResult,
	NXErrorCreateRFC,
	NXErrorRTSPCommandTimeout,                      ///< An unhandled NXPlayerDelegate::nexPlayerRTSPCommandTimeout: event occurred
	NXErrorPauseSupervisionTimeout,                 ///< An unhandled NXPlayerDelegate::nexPlayerPauseSupervisionTimeout: event occurred
    NXErrorNoValidFrameFound,
    NXErrorOperationNotValidInCurrentState,
	NXErrorDownloadFailure,
	NXErrorUnsupportedEncryption,
	NXErrorNotSupportedContentInAirPlay,
	
	// NexPlayer Invalid SDK error
	NXErrorInvalidSDKBase							= 0x80000000,
    NXErrorInvalidSDK                               = 0x8000000D,
	NXErrorNotActivatedAppID						= 0x80000012,
	NXErrorTimeLocked								= 0x800000A0,
    NXErrorInvalidLicense                           = 0x800000C0,
} _DOC_ENUM(NXError);
