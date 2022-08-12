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


/** \defgroup prop Properties
 *
 * There are a wide array of properties that can be adjusted to control the
 * behavior of various aspects of the player, from buffer time (how many seconds
 * of streaming content are buffered before playback begins) to the behavior
 * of the player under various error conditions (whether or not to allow
 * audio-only playback if an unsupported video codec is detected, for example).
 *
 * Properties can be set and retrieved through:
 *
 * - NXPlayer::setProperty:toValue: 
 * - NXPlayer::getProperty:value:
 * - NXPlayer::getProperty:
 *
 * Properties are identified with an integer identifier from the NXProperty
 * enumeration.
 * 
 * The value of each property is an unsigned integer.  For some properties, 
 * it may be necessary to cast this to a different type.  See the individual 
 * property documentation for details.  If no type is specified, it is safe
 * to treat the property as an unsigned integer.
 * 
 * \note Members of the enumeration that have not been documented, as
 *       well as values that have not yet been used, are subject to change in future
 * versions.  Do not access or change undocumented properties, or your code
 * may behave unpredictably and may break in future versions.
 */

/**
 * \ingroup prop
 * \brief Property identifiers. 
 *
 * These identify properties that can be set and retrieved with:
 *
 * - NXPlayer::setProperty:toValue: 
 * - NXPlayer::getProperty:value:
 * - NXPlayer::getProperty:
 */
typedef enum {

	/**
	 * \ingroup prop
	 * \brief	Number of milliseconds of media to buffer initially before
	 *			beginning streaming playback (HLS, RTSP, etc.).
	 * 
	 * This is the initial amount of audio and video that NexPlayer&trade;&nbsp;buffers
	 * when it begins playback.  If further buffering is required later in
	 * the playback process, the value of the property NXPropertyReBufferingDuration
	 * will be used instead.
	 *
	 * If this is set to zero, NexPlayer&trade;&nbsp;will automatically select the
	 * recommended buffering time based on the content type (longer for HLS,
	 * shorter for other streaming types).
	 *
	 * \type{unsigned int}
	 * \default{0 (automatic)}
	 * \unit{msec}
	 */
	NXPropertyInitialBufferingDuration				= 9,
	
	/**
	 * \ingroup prop
	 * \brief	Number of milliseconds of media to buffer if additional buffering
	 *			is required during streaming playback (HLS, RTSP, etc.).
	 * 
	 * This is the amount of audio and video that NexPlayer&trade;&nbsp;buffers
	 * when the buffer becomes empty during playback (requiring additional
	 * buffering).  For the initial buffering, the value of the property 
	 * NXPropertyInitialBufferingDuration is used instead.
	 * 
	 * If this is set to zero, NexPlayer&trade;&nbsp;will automatically select the
	 * recommended buffering time based on the content type (longer for HLS,
	 * shorter for other streaming types).
     *
	 * \type{unsigned int}
	 * \default{0 (automatic)}
	 * \unit{msec}
	 * 
	 * \since version 5.16
	 */
	NXPropertyReBufferingDuration					= 10,

	/**
	 * \ingroup prop
	 * \brief	The number of milliseconds (as a negative number) that video is allowed 
	 *			to run ahead of audio before the player waits for audio to catch up.
	 * 
	 * For example, -20 means that if the current video time is more than 20msec 
	 * ahead of the audio time, the current video frame will not be displayed until
	 * the audio catches up to the same time stamp.  This is used to adjust video 
	 * and audio synchronization.
	 * 
	 * \type{int <em>(should be negative)</em>}
	 * \default{-20 (20msec)}
	 * \unit{msec}
	 */
	NXPropertyTimestampDifferenceVDispWait			= 13,
	
	/**
	 * \ingroup prop
	 * \brief	The number of milliseconds that video is allowed to run behind audio 
	 *			before the system begins skipping frames to maintain synchronization.
	 * 
	 * For example, 200 means that if the current video time is more than 200msec 
	 * behind the audio time, the current video frame will be skipped.
	 * This is used to adjust video and audio synchronization.
	 * 
	 * \type{unsigned int}
	 * \unit{msec}
	 * \default{200 (0.2 sec)}
	 */
	NXPropertyTimestampDifferenceVDispSkip			= 14,

	/**
	 * \ingroup prop
	 * \brief	The size of the prefetch buffer to prepare for playback.
	 *
	 * If the buffer status satisfies either limit set by MAX_BUFFER_RATE or MAX_BUFFER_DURATION,
	 * the filling of the prefetch buffer will be stopped even though there may be spare space still available
	 * in the prefetch buffer.
	 *
	 * If this value is set to 20MB, 1/4 (5MB) is allocated to the past (content already played) and 3/4(15MB)
	 * is allocated to the future (content yet to be played).
	 *
	 * \warning  Setting too large of a value here may lead to a large consumption of data packets
	 * under 3G or LTE network conditions.
	 *
	 * \type{unsigned int}
	 * \unit{bytes}
	 * \default{50x1024x1024 (50MB)}
	 */
	NXPropertyPrefetchBufferSize					= 16,
	
	/**
	 * \ingroup prop
	 * \brief	Amount of time to wait for a server response before
	 *			generating an error event.
	 * 
	 * If there is no response from the server for longer than
	 * the amount of time specified here, an error event will be
	 * generated and playback will stop.
	 * 
	 * Set this to zero to disable timeout (NexPlayer&trade;&nbsp;will wait
	 * indefinitely for a response).
	 * 
	 * \type{unsigned int}
	 * \default{60,000 (60 seconds)}
	 * \unit{msec}
	 */
	NXPropertyDataInactivityTimeout					= 19,
	
	/**
	 * \ingroup prop
	 * \brief	Amount of time to wait before timing out when establishing
	 *			a connection to the server.
	 * 
	 * If the connection to the server (the socket connection) cannot
	 * be established within the specified time, an error event will
	 * be generated and playback will not start.
	 * 
	 * Set this to zero to disable timeout (NexPlayer&trade;&nbsp;will wait
	 * indefinitely for a connection).
	 * 
	 * \type{unsigned int}
	 * \default{0 (infinite)}
	 * \unit{msec (0 for infinite)}
	 */
	NXPropertySocketConnectionTimeout				= 20,
	
	
	
	/**
	 * \ingroup prop
	 * \brief The minimum port number to be used when receiving RTP data.
	 *
 	 * This sets the minimum possible port number to be used for the RTP port that is created
 	 * when performing RTSP streaming over UDP. \n
	 * 
	 * \default{12000}
	 */
	NXPropertyRTPPortMin							= 22,
	
	/**
	 * \ingroup prop
	 * \brief The maximum port number to be used when receiving RTP data.
	 *
	 * The maximum possible port number to be used for the RTP port that is created
	 * when performing RTSP streaming over UDP. \n
	 *
	 * \default{30000}
	 */
	NXPropertyRTPPortMax							= 23,
	
	/**
	 * \ingroup prop
	 * \brief Prevents the audio track from playing back when set to TRUE (1). \n
	 *
	 * \type{boolean}
	 * \default{0}
	 */
	NXPropertyNotOpenPlayAudio						= 27,
	
	/**
	 * \ingroup prop
	 * \brief Prevents the video track from playing back when set to TRUE (1). \n
	 *
	 * \type{boolean}
	 * \default{0}
	 */
	NXPropertyNotOpenPlayVideo						= 28,
	/**
	 * \ingroup prop
	 * \brief Prevents the text (subtitle) track from playing back when set to TRUE (1). \n
	 *
	 * \type{boolean}
	 * \default{0}
	 */
	NXPropertyNotOpenPlayText						= 29,
	
	/**
	 * \ingroup prop
	 * \brief Sets the proxy address.
	 *
	 * \type:{String}
	 * \default{null}
	 */
	NXPropertyProxyAdress							= 31,
	
	/**
	 * \ingroup prop
	 * \brief Sets the proxy port number.
	 *
	 * \type{integer}
	 * \default{0}
	 */
	NXPropertyProxyPort								=32,
	
	/**
	 * \ingroup prop
	 * \brief Sets the log level.
	 *
	 * <b>Values:</b>
	 * - NXPropertyLogLevel_Debug
	 * - NXPropertyLogLevel_RTP	
	 * - NXPropertyLogLevel_RTCP
	 * - NXPropertyLogLevel_Frame
	 * 
	 */
	NXPropertyLogLevel								= 35,
	
	/**
	 * \ingroup prop
	 * \brief Controls when video initialization happens.
	 *
	 * This can be any of the following values:
	 *
	 * <ul>
	 * <li><b>NXPropertyAVInitOption_Partial (0x00000000)</b><br />
	 *  If there is an audio track, wait for audio initialization to complete
	 *  before initializing video.
	 * <li><b>NXPropertyAVInitOption_All (0x00000001)</b><br />
	 *  Begin video initialization as soon as there is any video data, without
	 *  any relation to the audio track status.
	 * </ul>
	 * <b>Type:</b> unsigned integer \n
	 * <b>Default:</b> NXPropertyAVInitOption_All \n
	 * <b>Values:</b>
	 * - NXPropertyAVInitOption_Partial
	 * - NXPropertyAVInitOption_All
	 */
	NXPropertyAVInitOption							= 46,
	
	/**
	 * \ingroup prop
	 * \brief If set to 1, allows media playback even if the audio codec is not supported.
	 *
     * The default behavior (if this is 0) is to return an error or generate an
     * error event if the audio codec is not supported.
     *
     * \type{unsigned int}
	 * \default{0}
	 */
	NXPropertyPlayableForNotSupportAudioCodec		= 48,
	/**
	 * \ingroup prop
	 * \brief If set to 1, allows media playback even if the video codec is not supported.
	 *
     * The default behavior (if this is 0) is to return an error or generate an
     * error event if the audio codec is not supported.
     *
     * \type{unsigned int}
	 * \default{0}
	 */
	NXPropertyPlayableForNotSupportVideoCodec		= 49,
	/**
	 * \ingroup prop
	 * \brief If more than this number of frames are skipped during rendering, the 
     * remaining frames up to the next keyframe are forcibly discarded and 
     * playback resumes from the next keyframe.
     *
     * \type{unsigned int}
	 * \default{0xFFFFFFFF}
	 */
	NXPropertyUseEyePleaser                         = 50,
	
	/**
	 * \ingroup prop
	 * \brief Live playback option.
     *
	 * This must be one of the following values:
	 *
	 *    - <b>NXPropertyHLSLiveViewRecent (0x00000000)</b>
	 * Start playback from the most recently received media segment (.ts) files of the HLS live playlist.
	 * (The player will begin playback at a media segment that was loaded four(4) segments earlier than the latest media segment file loaded.)
	 * For example, if 5.ts is the latest media segment (.ts) file loaded in a sequence of five media segments, playback will begin at
	 * the beginning of the second media segment, four segments (2.ts, 3.ts, 4.ts, and 5.ts) preceding the latest media segment file loaded.
	 *
	 *    - <b>NXPropertyHLSLiveViewRecentByTargetDuration (0x00000001)</b>
	 * Start playback from the most recently received media segement (.ts) files, based on the value set for the EXT-X-TARGETDURATION tag in the HLS live playlist.
	 * (The player will begin playback at the media segment that is immediately precedes the media segment that is <em>three times (x3) the target duration</em>
	 * before the latest media segment file loaded.)
	 * As a concrete example, if the target duration is set to 12 seconds and the total duration of currently loaded media segments is 48 seconds, playback will
	 * begin at the media file that immediately precedes the media segment with the timestamp at 12 (48-36) seconds.
	 * If this example HLS playlist includes media segment files 1.ts (duration of 10 seconds), 2.ts (9 sec), 3.ts (11 sec), 4.ts (10 sec), and 5.ts (8 sec),
	 * then playback will begin at the first media segment, 1.ts, because it immediate precedes the 2.ts segment (where the timestamp at 12 seconds occurs).
	 *
	 *    - <b>NXPropertyHLSLiveViewFirst (0x00000002)</b>
	 * Unconditionally start HLS playback from the first entry in the HLS playlist.
	 *
	 *    - <b>NXPropertyLiveViewLowLatency (0x00000003)</b>
	 * Playback begins as close to the live edge as possible. The first file to load is the last segment in the playlist. (Do not use this option for normal playback.)
	 *
     * \type{unsigned int}
	 * \default{NXPropertyHLSLiveViewRecent}
	 */
	NXPropertyApplsLiveViewOption					= 53,
	NXPropertyLiveViewOption						= 53,
	/**
	 * \ingroup prop
	 * \brief RTSP/HTTP User Agent value.
	 *
     * \type{String}
	 */
	NXPropertyUserAgentString						= 58,
	/**
	 * \ingroup prop
	 * \brief Controls what is displayed while the player is waiting for audio data.
	 *
	 * If this is set to zero, the player will not display the first video frame until
	 * the audio is ready to play.  Whatever was previously displayed will continue to
	 * be visible (typically a black frame) while it is waiting for audio data.
	 *
	 * If this is set to 1, and video data becomes available prior to audio data,
	 * the first video frame will be displayed as a still image until audio data is
	 * available.
	 *
	 * Once audio has started, the behavior for both settings is the same; this only affects
	 * what is displayed while the player is waiting for audio data.
	 *
	 * Under old versions of the SDK (prior to the addition of this property), the default
	 * behavior was as though this property were set to zero.
	 *
	 * \type{boolean}
	 * \default{1}
	 *
	 *
	 * <b>Values:</b>
	 * - 0: Show nothing.
	 * - 1: Show first video frame.
	 *
	 */
	NXPropertyFirstDisplayVideoFrame				= 60,
	
	/**
	 * \ingroup prop
	 * \brief * Sets the amount of time to wait for an {@link NXPlayer::open: open} request to complete.
	 *
	 * This is used when NexPlayer&trade;&nbsp;tries to open new media.  If there is no response from the server for longer than
	 * the amount of time specified here, the {@link NXPlayer::open: open} request will be stopped
	 * and {@link NXPlayerDelegate::nexPlayer:completedAsyncCmdOpenWithResult:playbackType: nexPlayer:completedAsyncCmdOpenWithResult:playbackType:}
	 * will be called with the result, namely the error code, NXErrorMediaOpenTimeout.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> msec (1/1000 sec) \n
	 * <b>Default:</b> 300000 (300 seconds) \n
     *
     * \since version 5.16
     */
	NXPropertySourceOpenTimeOut						= 63, 

	/**
	 * \ingroup prop
	 * \brief The maximum waiting time till an HTTP request/response message arrives to NexPlayer&trade;.
	 *
	 * If the reply does not arrive within this time after HTTP request message is sent to the streaming server, it will be regarded as an error.
	 *
	 * \type{unsigned int} \n
	 * \default{30,000 (30 seconds)} \n
	 * \unit{msec (0 for infinite)} \n
	 */
	NXPropertySocketOperationTimeout				= 73,
	/**
	 * \ingroup
	 * \brief Set a low latency buffer option.<p>
	 *
	 * This must be one of the following values:
	 *    - <b>NXPropertyLowLaytencyBufferOptionNone (0x00000000)</b>
	 * The latency value is set by INITIAL_BUFFERING_DURATION and RE_BUFFERING_DURATION of NexProperty.
	 * It should set the reliable value depending on the bitrate of content and network environment.
	 *
	 *    - <b>NXPropertyLowLaytencyBufferOptionAutoBuffer (0x00000001)</b>
	 * The latency value is calculated by the player at runtime.
	 * During playback, the latency may increase or decrease because it may change depending on the network environment.
	 *
	 *    - <b>NXPropertyLowLaytencyBufferOptionConstBuffer (0x00000002)</b>
	 * The latency value is calculated by the player at the beginning of playback and maintains the value unchanged during playback.
	 * The latency increases more than when using Auto Buffer Mode, but the rebuffering will be reduced and try to maintain constant latency after rebuffering.
	 *
	 * \type{unsigned int} \n
	 * \default{NXPropertyLowLaytencyBufferOptionNone} \n
	 * \since version 5.40
	 */
	NXPropertyLowLatencyBufferOption				= 75,
	/**
	 * \ingroup
	 * \brief Sets the range where NexPlayer&trade;&nbsp;will seek to a Random Access point rather than
	 * the exact target position provided in the \link NXPlayer::seekToAdjustedTime:exact: seekToAdjustedTime\endlink API.
	 *
	 * \warning  This property is <b>only</b> valid when the second parameter, \c exact, in the \link NXPlayer::seekToAdjustedTime:exact: seekToAdjustedTime\endlink
	 * API is \c true.
	 *
	 * Setting this value is a kind of option for the \link NXPlayer::seekToAdjustedTime:exact: seekToAdjustedTime\endlink API and can be used
	 * to minimize the time required to seek in content by taking advantage of Random Access points in the content.
	 *
	 * A Random Access point is a specific position that the parser is allowed to seek to directly.
	 *
	 * This value sets the range where NexPlayer&trade;&nbsp;will seek from a Random Access point given by the parser
	 * to a target position that equals \c msec (milliseconds), the first parameter in the seek() API.
	 *
	 * If the \c exact parameter, the second parameter in the \link NXPlayer::seekToAdjustedTime:exact: seekToAdjustedTime\endlink API, is \c true and
	 * the difference between a Random Access point and the target position is within this value, \link NXPlayer::seekToAdjustedTime:exact: seekToAdjustedTime\endlink
	 * will find and seek to the exact target position.
	 * If the \c exact parameter is set to \c true and the difference between a Random Access point and the target position
	 * is beyond this range, \c seek will give up the accurate target point and will instead seek to and play from
	 * the Random Access point.
	 *
	 * For example, if NexPlayer&trade;&nbsp;is seeking to 10000 ms exactly (\c exact = \c true) and there is a Random Access
	 * point at 7000 ms, if this property is set to less than 3000 ms, the player will ignore the exact target value and will
	 * instead play from 7000 ms.  On the other hand, if this property is set to more than 3000 ms, then NexPlayer&trade;&nbsp;
	 * will seek exactly to 10000 ms and begin playback.
	 *
	 * \warning  Please remember that in order to seek to a target position, audio or video frames have to be decoded.
	 * If too large of a value is set here, it may cause the seek process to consume an excessive amount
	 * of time especially in high resolution video content.
	 *
	 * \type{unsinged int}
	 * \unit{msec (1/1000 sec)}
	 * \default{10000 (10 seconds)}
	 */
	NXPropertySeekRangeFromRAPoint					= 102,
	
    /**
     * \ingroup prop
	 * \brief If set to \c true, unconditionally skips all B-frames without decoding them.
     * 
     * \type{boolean}
	 * \default{0}
     */
    NXPropertySetToSkipBFrame						= 103,
    /**
     * \ingroup prop
	 * \brief Maximum amount of silence to insert to make up for lost audio frames.
     * 
     * Under normal operation, if audio frames are lost (if there is a time gap
     * in received audio frames), silence will be inserted automatically to make
     * up the gap.
     * 
     * However, if the number of audio frames lost represents a span of time
     * larger than the value set for this property, it is assumed that there is
     * a network problem or some other abnormal condition and silence is not
     * inserted.
     * 
     * This prevents, for example, a corruption in the time stamp in an audio
     * frame from causing the system to insert an exceptionally long period of
     * silence (which could possibly prevent further audio playback or cause
     * other unusual behavior).
     * 
     * \type{unsigned int}
	 * \unit{msec (1/1000 sec)}
	 * \default{20000 (20 seconds)}
     */
	NXPropertyTooMuchLostFrameDuration				= 105,
	
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables local file playback support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 1 \n
	 */
	NXPropertySupportLocal							= 110,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables RTSP streaming support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 0 \n
	 *
	 * \warning This property is not supported in this API version.
	 */
	NXPropertySupportRTSP							= 111,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables progressive download support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 1 \n
	 */
	NXPropertySupportPD								= 112,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables Microsoft Windows Media Streaming support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 0 \n
	 */
	NXPropertySupportWMS							= 113,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables Real Media Streaming support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 0 \n
	 */
	NXPropertySupportRDT							= 114,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables Apple HTTP Live Streaming (HLS) support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 1 \n
	 */
	NXPropertySupportAppleHTTP						= 115,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables HLS Adaptive Bit Rate (ABR) support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 1 \n
	 */
	NXPropertySupportABR							= 116,
	/**
	 * \ingroup prop
	 * \brief If set to 1, enables DASH support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 1 \n
	 */
    NXPropertySupportDash							= 507,	
    
    /**
	 * \ingroup prop
     * \brief When streaming with multiple tracks, this sets the maximum allowable bandwidth.
     *
     * Any track over this bandwidth will not be selected for playback.
     * 
     * Set to zero for no maximum.
     * 
     * \type{unsigned int}
	 * \unit{bps (bits per second)}
	 * \default{0 (no maximum)}
     */
	NXPropertyMaxBW									= 117,
	/**
	 * \ingroup prop
	 * \brief Limits the H.264 profile that can be selected from an HLS playlist.
	 *
	 * Under normal operation, the track with the highest supported H.264 profile
	 * is selected from an HLS playlist.  If this property is set, no track with
	 * a profile higher than this value will be selected.
	 *
	 * This should be set to zero for no limit.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Default:</b> 0 (use any profile) \n
	 */
	NXPropertyH264Profile							= 118,
	
	/**
	 * \ingroup prop
	 * \brief Suppresses automatic silence insertion for lost audio frames.
	 *
	 * During normal RTSP streaming operation, if an audio frame is lost (for 
	 * example, due to a bad connection), the NexPlayer&trade;&nbsp;engine inserts a frame of
	 * silence into the audio stream to maintain synchronization.  Enabling this 
	 * setting suppresses that function.  This may improve performance in some 
	 * cases where the RTSP server doesn't send an audio stream.  This should be 
	 * used with caution as it can cause the audio and video streams to lose 
	 * synchronization.
	 *
	 * \default{0 (disable)}
	 *
	 * <b>Values:</b>
	 * - 0: disable
	 * - 1: enable
	 */
	NXPropertyIgnoreAudioLostFrame					= 119,
	
	/**
	 * \ingroup prop
	 * \brief Controls whether audio buffering is independent of the video state.
	 *
	 * In the case of an empty audio frame, if this property is enabled, buffering
	 * will always start regardless of the state of the video buffer.
	 *
	 * \default{0 (disable)}
	 *
	 * <b>Values:</b>
	 * - 0: disable
	 * - 1: enable
	 * 
	 */
	NXPropertyAlwaysBuffering						= 120,
	
	/**
	 * \ingroup prop
	 * \brief Bypasses AV synchronization.
	 *
	 * When this property is enabled, AV synchronization is bypassed.  As soon as 
	 * data is received, it is immediately presented to the user.  
	 *
	 * \warning
	 *		This will almost certainly cause the audio and video to lose 
	 *		synchronization, and video playback speed will be unpredictable and 
	 *		vary depending on the speed of the connection and the speed by which 
	 *		the local system can decode frames.  This may be useful for playing 
	 *		back a live video feed where frames are sent by the server at the 
	 *		correct intervals for playback.
	 *
	 * \default{0 (disable)}
	 *
	 * <b>Values:</b>
	 * - 0: disable
	 * - 1: enable
	 */
	NXPropertyIgnoreAVSync							= 121,
	
	/**
	 * \ingroup prop
	 * \brief If set to 1, this enables MS Smooth Streaming support. \n
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 1 \n
	 */
	NXPropertySupportMSSmoothStreaming				= 123,
	
	/**
	 * \ingroup prop
	 * \brief Adjusts A/V synchronization by ofsetting video relative to audio.
	 *
	 * Positive values cause the video to play faster than the audio, while
	 * negative values cause the audio to play faster than the video.  Under normal
	 * operation, this can be set to zero, but in some cases where the synchronization
	 * is bad in the original content, this can be used to correct for the error.
	 *
	 * While A/V synchronization is generally optimized internally by NexPlayer&trade;&nbsp;, there may
	 * occasionally be devices which need to be offset in order to improve
	 * overall A/V synchronization.  For examples of how to set AV_SET_OFFSET based on the
	 * device in use, please see the Sample Application code as well as the
	 * introductory section \ref avSync "A/V Synchronization" section.
	 *
	 * Appropriate values for any other problematic devices need to be determined experimentally
	 * by testing manually.
	 *
	 * <b>Type:</b> integer \n
	 * <b>Unit:</b> msec (1/1000 sec) \n
	 * <b>Range:</b> -2000 ~ +2000 \n
	 * <b>Default:</b> 0 \n
	 *
	 */
	NXPropertyAVSyncOffset							= 124,
 	
 	/**
	 * \ingroup prop
 	 * \brief Limits the maximum width (in pixels) of the video tracks that can be
 	 * selected during streaming play.
 	 *
 	 * This is used to prevent NexPlayer&trade;&nbsp;from attempting to play
 	 * tracks that are encoded at too high a resolution for the device to
 	 * handle effectively.  NexPlayer&trade;&nbsp;will instead select a track
 	 * with a lower resolution.
 	 *
 	 * \note On <b>iOS ONLY</b>, if this is zero (the default), NexPlayer&trade;&nbsp;
 	 * will automatically set the value based on the device type and type of play
 	 * (streaming or local).  Note that when this is set to zero, NXPlayer::getProperty:
 	 * will also return zero.  To get the actual value that is in effect during playback,
 	 * call NXPlayer::getEffectiveProperty: instead.
 	 *
	 * \type{integer}
 	 * \unit{pixels}
	 * \default{NXPropertyMaxWidthMaxValue}
 	 */
	NXPropertyMaxWidth								= 125,

	/**
	 * \ingroup prop
	 * \brief Limits the maximum height (in pixels) of the video tracks that can be
	 * selected during streaming play.
	 *
	 * This is used to prevent NexPlayer&trade; from attempting to play
	 * tracks that are encoded at too high a resolution for the device to
	 * handle effectively.  NexPlayer&trade; will instead select a track
	 * with a lower resolution.
	 *
	 * \note On <b>iOS ONLY</b>, if this is zero (the default), NexPlayer&trade;&nbsp;
	 * will automatically set the value based on the device type and type of play
	 * (streaming or local).  Note that when this is set to zero, NXPlayer::getProperty:
	 * will also return zero.  To get the actual value that is in effect during playback,
	 * call NXPlayer::getEffectiveProperty: instead.
	 *
	 * \type{integer}
	 * \unit{pixels}
	 * \default{NXPropertyMaxHeightMaxValue}
	 */
	NXPropertyMaxHeight								= 126,
    
	/**
	 * \ingroup prop
	 * \brief Sets preferred bandwidth when switching tracks during streaming play.
	 *
	 * Under normal operation (when this property is zero), if the available
	 * network bandwidth drops below the minimum needed to play the current 
	 * track without buffering, the player will immediately switch to a lower 
	 * bandwidth track, if one is available, to minimize any time spent buffering.
	 *
	 * If this property is set, the player will attempt to choose only tracks 
	 * above the specified bandwidth, even if that causes some buffering.  
	 * However, if the buffering becomes too severe or lasts for an extended 
	 * time, the player may eventually switch to a lower-bandwidth track anyway.
	 *
	 * \unit{kbps (kilobits/sec)}
	 * \type{unsigned int}
	 * \default{0 (immediate switching)}
	 *
	 * <b>Values:</b>
	 * - 0: No preferred bandwidth (immediate switching)
	 * - >0: Preferred bandwidth in kbps
	 *
	 * \see NXPropertyPreferAV 
	 */
	NXPropertyPreferBandwidth                       = 129,
    
	/**
	 * \ingroup prop
	 * \brief Controls whether NexPlayer&trade;&nbsp;prefers tracks with both
	 *          audio and video content.
	 *
	 * Under normal operation (when this property is set to 0), if the available
	 * network bandwidth drops below the minimum needed to play the current 
	 * track without buffering, the player will immediately switch to a lower 
	 * bandwidth track, if one is available, to minimize any time spent buffering.
	 *
	 * If this property is set to 1, the player will attempt to choose only tracks 
	 * that include both audio and video content, even if that causes some buffering.  
	 * However, if the buffering becomes too severe or lasts for an extended 
	 * time, the player may eventually switch to an audio-only track anyway.
	 *
	 * \type{unsigned int}
	 * \default{0 (immediate switching)}
	 *
	 * <b>Values:</b>
	 * - 0: Normal behavior (immediate switching)
	 * - 1: Prefer tracks with both audio and video
	 *
	 * \see NXPropertyPreferBandwidth 
	 */
	NXPropertyPreferAV                              = 130,
 	
 	/**
	 * \ingroup prop
	 * \brief Allows NexPlayer&trade;&nbsp;to switch to a lower bandwidth track if the
	 * resolution or bitrate of the current track is too high for the
	 * device to play smoothly.
	 * 
	 * Under normal operation, NexPlayer&trade;&nbsp;switches tracks based solely on
	 * current network conditions.  When this property is enabled, NexPlayer&trade;&nbsp;
	 * will also switch to a lower bandwith track if too many frames are skipped
	 * during playback.
	 * 
	 * This is useful for content that is targeted for a variety of
	 * devices, some of which may not be powerful enough to handle the higher
	 * quality streams.
	 * 
	 * The ::NXPropertyTrackdownVideoRatio property
	 * controls the threshold at which the track change will occur, if frames
	 * are being skipped.<p>
	 *
	 * Have to set it before start to play.
	 * 
	 * \type{boolean}
	 * \default{0}
	 * <b>Values:</b>
	 * - 0: Normal behavior (switch based on network conditions only)
	 * - 1: Switch based on network conditions and device performance
	 * 
	 */
    NXPropertyEnableTrackdown                       = 131,
    
    /**
	 * \ingroup prop
     * \brief Controls the ratio of skipped frames that will be tolerated before
     * a track change is forced, if ::NXPropertyEnableTrackdown is enabled.
     * 
     * The formula used to determined if a track switch is necessary is:
     * \code 100 * (RenderedFrames / DecodedFrames) < TrackdownVideoRatio \endcode
     * 
     * In other words, if this property is set to 70, and ::NXPropertyEnableTrackdown
     * is set to 1, NexPlayer&trade;&nbsp;will require that at least 70% of the decoded frames
     * be displayed.  If less than 70% can be displayed (greater than 30% skipped frames),
     * then the next lower bandwidth track will be selected.<p>
     * 
     * A performance-based track switch <b>permanently</b> limits the maximum bandwidth of
     * tracks that are eligible for playback, until the content is closed. For this reason, setting this
     * ratio higher than the default value of 70 is strongly discouraged.
     * (This differs from the bandwidth-based algorithm, which continuously adapts to current
     * network bandwidth).
     *
     * \type{integer}
     * <b>Range:</b> 0 to 100 \n
     * \default{70}
     */
    NXPropertyTrackdownVideoRatio                   = 132,
    
    /**
     * \ingroup prop
     * \brief Controls the alogrithm used for bitrate switching when playing an
     *        HLS stream.
     *
	 * \type{unsigned int}
	 * \default{0}
	 *
	 * <b>Values:</b>
	 * - 0: Uses a more agressive algorithm: Up-switching happens sooner.
	 * - 1: Uses a more conservative algorithm: Up-switching happens only if a
     *      significant amount of extra bandwidth is available beyond that
     *      required to support the given bitrate.  This is similar to
     *      the iPhone algorithm.
     */
	NXPropertyHLSRunmode							= 133,
	 
	/**
	 * \ingroup prop
	 * \brief   Adds additional HTTP headers to use to supply credentials when a 401 response
	 *          is received from the server.
	 *
	 * The string should be in the form of zero or more HTTP headers (header
	 * name and value), and each header (including the last) should be terminated
	 * with a CRLF sequence, for example:
	 *
	 * \code
	 * "id: test1\r\npw: 12345\r\n"
	 * \endcode
	 *
	 * The particulars of the headers depend on the server and the authentication
	 * method being used.
	 *
	 * \type{String}
	 */
	NXPropertyHTTPCredentials                       = 134,
	
	
	/**
	 * \ingroup prop
	 * \brief The minumum ratio of prefetch buffer to resume filling buffer.
	 * If the ratio of filling buffer is less than this value, filling buffer will be resumed
	 *	until buffer status meets the condition of MAX_BUFFER_RATE or MAX_BUFFER_DURATION.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> percent \n
	 * <b>Default:</b> 70 (70%) \n
	 */
	NXPropertyMinBufferRate							= 140,		//Prefetch buffer control(based on buffersize)
	
	
	/**
	 * \ingroup prop
	 * \brief The maximum ratio of prefetch buffer to pause filling buffer.
	 * If the ratio of filling buffer is more than this value, filling buffer will be paused
	 *	until buffer status meets only the condition of MIN_BUFFER_RATE.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> percent \n
	 * <b>Default:</b> 90 (90%) \n
	 */
	
	NXPropertyMaxBufferRate							= 141,		//Prefetch buffer control(based on buffersize)
	
	
	/**
	 * \ingroup prop
	 * \brief The minumum duration of prefetch buffer to resume filling buffer.
	 * If the duration of filling buffer is less than this value, filling buffer will be resumed
	 *	until buffer status meets the condition of MAX_BUFFER_RATE or MAX_BUFFER_DURATION.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> second \n
	 * <b>Default:</b> 30 (30s) \n
	 */
	NXPropertyMinBufferDuration						= 142,		//Prefetch buffer control(based on duration)
	
	
	/**
	 * \ingroup prop
	 * \brief The minumum ratio of prefetch buffer to resume filling buffer.
	 * If filling buffer is less this value, filling buffer will be resumed
	 *	until buffer status meets only the condition of MIN_BUFFER_DURATION.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> second \n
	 * <b>Default:</b> 60 (60s) \n
	 */
	NXPropertyMaxBufferDuration						= 143,		//Prefetch buffer control(based on duration)
	/**
	 * \ingroup prop
	 * \brief Sets whether or not NexPlayer&trade;&nbsp; should use SyncTask feature.
	 *
	 * SyncTask may improve decoding performance.
	 *
	 * \note  This property must be set before initializing NexPlayer&trade;&nbsp;or opening and playing content.
	 *
	 * \type{unsigned int}
	 * \default{0}
	 * <b>Values</b>:\n
	 *    - <b>0:</b> Do not use SyncTask.\n
	 *    - <b>1:</b> Use SyncTask.
	 *
	 * \since version 5.16
	 */
	NXPropertyUseSyncTask							= 187,	
	
	/**
	 * \ingroup prop
	 * \brief Sets the size of the buffer used to receive decoded video frames when the software video codec is used.
	 * 
	 * Setting the buffer size in advance based on device system performance can improve decoding 
	 * performance with the SW codec, as more data can be decoded and saved in the buffer.
	 * 
	 * \note This property must be used with the property \ref NXPropertyUseSyncTask set to 1.
	 * 
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> decoded video frame count \n
	 * <b>Default:</b> 0 \n
	 * 
	 * \since version 5.16
	 */
	//NXPropertySwDecodingBufferCount					= 200,
	 
	/**
	 * \ingroup prop
	 * \brief   Controls whether the player honors cookies sent by the server.
	 *
	 * \type{unsigned int}
	 * \default{1}
	 *
	 * <b>Values:</b>
	 * - <b>0:</b> Ignore HTTP cookie headers sent by the server.
	 * - <b>1:</b> Cookie headers received from a streaming server along
	 *                with the initial manifest or playlist are included
	 *                with further HTTP requests during the session.
	 *
	 */
	NXPropertySetCookie                             = 500,
	
	
	
	/**
	 * \ingroup prop
	 * \brief  Sets the SmoothStreaming \c LiveBackOff property when playing Smooth Streaming content.
	 *
	 * This property sets the duration of content (closest to live) that cannot yet be accessed or downloaded
	 * by the player.  It is like setting how long to wait before asking for the latest fragment in a live
	 * presentation, and thus basically sets the played "live" point back from the actual
	 * live content available on the server.
	 *
	 * The end-to-end latency of the player (what is being played "live" in the player compared to what is
	 * available live on the server) is at least the duration of \c LiveBackOff added to the duration
	 * set for \c LivePlaybackOffset with NXPropertySetLiveBackOffset.
	 *
	 * \type{unsigned int}
	 * \unit{msec}
	 * \default{6000}
	 *
	 * \since version 5.9
	 */
	NXPropertySetLiveBackOff                        = 504,

    /**
	 * \ingroup prop
	 * \brief  Sets the SmoothStreaming \c LivePlaybackOffset property when playing Smooth Streaming content.
	 *
	 * This property sets the duration away from the live position to start playback when joining a
	 * live presentation when the LiveView option is set to "Recent", but excludes the \c LiveBackOff
	 * duration (set by NXPropertySetLiveBackOff).
	 *
	 * As a result, live content will be played behind the actual live position by a duration
	 * determined by BOTH \c LiveBackOff and the value for \c LivePlaybackOffset set here.
	 *
	 * Setting this property enables faster startup because it allows a buffer to be built up
	 * as fast as bandwidth will support (potentially faster than real time), which creates a buffer
	 * against network jitter.  It does however also increase end-to-end latency, which means what
	 * is played "live" in the player is farther behind the actual live playing point of the
	 * content.
	 *
	 * \type{unsigned int}
	 * \unit{msec}
	 * \default{7000}
	 *
	 * \since version 5.9
	 */
	NXPropertySetLiveBackOffset                     = 505,
	/**
	 * \ingroup prop
	 * \brief Starts video together with or separately from audio.
	 *
	 * This property starts to play audio and video together when starting, if the video timestamp
	 * is slower than audio's timestamp.
	 *
	 * If it is 1, it forces the video and audio to start at the same time.
	 * If it is 0, it lets the video and audio to start separately.
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 0 (video and audio will start separately, based on the timestamps) \n
	 */
	NXPropertyStartWithAV							= 506,		// output audio/ video at the same time
	
	/**
	 * \ingroup prop
	 * \brief Ignores abnormal segment timestamps.
	 *
	 * If it is 1 or enabled, NexPlayer&trade;&nbsp;will ignore abnormal segment timestamps.
	 * If it is 0 or disabled, NexPlayer&trade;&nbsp;will not ignore any abnormal segment timestamps.
	 *
	 * <b>Type:</b> boolean \n
	 *
	 * \warning This property is not supported in this API version.
	 */
	NXPropertyIgnoreAbnormalSegmentTimestamp		= 508,
	NXPropertyEnableFileSkip						= 508,

	
	/**
	 * \ingroup prop
	 * \brief Allows the application to modify the content of an HTTP Request that NexPlayer&trade;&nbsp;is about to send to a remote HTTP server.
	 *
	 * When this property is set equal to 1 (enabled), NexPlayer&trade;&nbsp;invokes \c nexPlayer:onModifyHttpRequest: with the HTTP Request
	 * as an argument.  The application can return the modified version of the HTTP Request that will actually be sent.
	 *
	 * <b>Values:</b> \n
	 *   - 0 : Disabled. Don't deliver any HTTP Request.
	 *   - 1 : Enabled. Deliver HTTP Request to modify on the application side.
	 *
	 * \see \link NXPlayerDelegate.h::NXPlayerDelegate:nexPlayer:onModifyHTTPRequest: \endlink for more information.
	 *
	 * \since version 5.23
	 */
	NXPropertyEnableModifyHTTPRequest				= 512,
	/**
	 * \ingroup prop
	 * \brief Allows NexPlayer&trade;&nbsp;to begin downloading content media files from a specified time stamp in the content.
	 *
	 * \warning This property is currently only supported for VOD in HTTP Live Streaming (HLS).
	 *
	 * NexPlayer&trade;&nbsp;allows users to start playback in the middle of a content file with the
	 * \link NXPlayer::start start\endlink api, but typically, before playback can begin, the player
	 * still opens content from the first media file available and then has to receive all of the media files between
	 * the first file and the point where the user would like to start playback.
	 *
	 * When playback is to start in the middle of content, this property allows the player to skip receiving
	 * the unneeded earlier media files based on the time stamp value set by the application, and instead begin
	 * downloading media files from a position closer to the specified time stamp instead.
	 *
	 * This property can thus reduce the time needed to open and start playing a media file in
	 * the middle of VOD content.
	 *
	 * \note This property must be set <b>before</b> NexPlayer.open is called.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> msec (1/1000 s) \n
	 * <b>Default:</b> 0xFFFFFFFF \n
	 */
	NXPropertyOpenMediaFileFromSpecifiedTS			= 513,
	NXPropertyHlsVodLiveEncodingStartCTS			= 513, // MONGTO 20130128 when player start nxprotocol start to receive TS file from the start cts.
	
	/**
	 * \ingroup prop
	 * \brief Allows NexPlayer&trade;&nbsp;to add an explicit request for metadata in internet radio stream content.
	 *
	 * \warning  This is currently only supported in SHOUTcast and IceCast HLS content.
	 *
	 * If an explicit request for metadata is not made, a server may or may not send internet radio stream metadata even if it exists.
	 *
	 * Setting this property to 1 means an explicit request for internet radio stream metadata will be included with every content request sent
	 * to a server.  If this property is set to 2, NexPlayer&trade;&nbsp;will only add an explicit request for metadata <b>after</b> initially receiving content and
	 * identifying it as a SHOUTcast or Icecast stream.
	 *
	 * <b>Values:</b> \n
	 *   - <b> 0 : DEFAULT :</b> Default mode. Does not add an additional explicit request for internet radio stream metadata.
	 *   - <b> 1 : INSERT_HEADER :</b> Always inserts a header with a request for internet radio stream metadata (with every content request).
	 *   - <b> 2 : INSERT_HEADER_AFTER_TRIAL :</b> If NexPlayer&trade;&nbsp;determines content is a SHOUTcast or Icecast stream, a header with
	 *             an explicit request for metadata will be added to subsequent server requests.
	 */
	NXPropertyRequestRadioMetadataMode 				= 515,
	NXPropertyRCSProbeMetaInfoMode					= 515, 	// NXPROTOCOL_PROPERTY_RCS_PROBEMETAINFOMODE // 0 - default, 1 -insertHeader, 2 - Trialhold
	
	/**
	 * \ingroup prop
	 * \brief When using HLS ABR, this is the minimum allowable bandwidth.  Any track
	 * with a bandwidth smaller than this value will not be played back.
	 *
	 *  \note  To dynamically set a minimum bandwidth allowed while content is playing, please call the method \c NexABRController::changeMinBandWidth() instead.
	 * This property should be set to zero for no minimum.
	 *
	 * <b>Type:</b> unsigned integer \n
	 * <b>Unit:</b> bps (bits per second) \n
	 * <b>Default:</b> 0 (no minimum) \n
	 */
	NXPropertyMinBW 								= 516,
	
	/**
	 * \ingroup prop
	 * \brief Enables rendering and display of CEA 708 closed captions in content when available.
	 *
	 * While CEA 608 closed captions are always enabled, it is necessary to set this property
	 * to 1 in order for NexPlayer&trade;&nbsp;to support CEA 708 closed captions.
	 *
	 * In the case where content contains both CEA 608 and CEA 708 closed captions and this property
	 * enables CEA 708 closed captions, the application will have to handle choosing which captions
	 * to render and display to the user.
	 *
	 * <b>Type:</b> boolean
	 * <b>Default:</b> 0
	 * <b>Values:</b>
	 *     - <b>0:</b> CEA 708 closed captions disabled.
	 *     - <b>1:</b> CEA 708 closed captions enabled.
	 */
	NXPropertyEnableCEA708							= 517,
	NXPropertyEnableEIA708							= 517,	// 0: disabled(CEA608), 1: enabled (EIA708)
	
	/**
	 * \ingroup prop
	 * \brief Sets whether or not to display WebVTT text tracks automatically when they are included in content.
	 *
	 * In the case when both CEA 708 closed captions and WebVTT text tracks are included in content, this
	 * property can be used to set whether to display the WebVTT text tracks or the closed captions automatically.
	 *
	 * By default, this property is set to 1 to enable WebVTT text tracks automatically if they exist in content
	 * (as was the behavior of NexPlayer&trade;&nbsp;previously).  If for some reason it would be preferable that
	 * CEA 708 closed captions be displayed instead of the WebVTT text tracks, this property should be set to
	 * 0 with by with \c setProperty:
	 * \code
	 * mNexPlayer.setProperty(NexProperty.ENABLE_WEBVTT, 0);
	 * \endcode
	 * This property should only be called once, immediately after calling \c init but before calling \c open.
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Values:</b> \n
	 *   - 0 :  WebVTT text tracks ignored; CEA 708 closed captions enabled \n
	 *   - 1 :  WebVTT text tracks enabled; CEA 708 closed captions ignored \n
	 * <b>Default:</b> 1 (WebVTT text tracks enabled)
	 */
	NXPropertyEnableWebVTT							= 518,
	
	/**
	 * \ingroup prop
	 * \brief Sets whether or not to begin playback after a part of the TS file is downloaded.
	 *
	 * By default, this property is set to 0 to download the first TS file completely to play content.
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 0 \n
	 * <b>Values:</b>
	 *   - 0 :  Partial prefetch ignored; playback will begin after downloading the first TS file completely.\n
	 *   - 1 :  Partial prefetch enabled; playback will begin after a part of the TS file is downloaded.
	 *
	 * \since version 5.36
	 */
	NXPropertyPartialPrefetch 						= 519,
	
    /**
     * \ingroup prop
	 * \brief Allows custom ID3 tags added to timed metadata in content to be recognized and handled by NexPlayer&trade;.
	 *
	 * When customized ID3 tags with additional information have been added to the timed metadata in content,
	 * this property can be used to help NexPlayer&trade;&nbsp;recognize and pass those ID3 tags and the extra information they
	 * contain to an application.
	 *
         * This property must be set <em>before</em> \c open is called.
	 *
	 * <b>Type:</b> String \n
	 * <b>Values:</b> a list of the customized ID3 tag names separated by semicolons (;)\n
	 * <b>Default:</b> nothing
	 *
	 * \since version 5.17
	 *
	 */
	NXPropertyTimedID3MetaKey						= 521,
	
	/**
	 * \ingroup prop
	 * \brief
	 * Sets whether or not to display TTML text tracks in ID3 tag automatically when they are included in content.
	 *
	 * In the case when both CEA closed captions and TTML text tracks in ID3 tag are included in content, this
	 * property can be used to set whether to display the TTML text tracks in ID3 tag or the closed captions automatically.
	 *
	 * By default, this property is set to 0 to disable TTML text tracks in ID3 tag automatically if they exist in content
	 * (as was the behavior of NexPlayer&trade;&nbsp;previously).  If for some reason it would be preferable that
	 * TTML captions in ID3 tag to be displayed instead of the CEA closed captions text tracks, this property should be set to
	 * 1 using \c setProperty:
	 * \endcode
	 * This property should only be called once, immediately after calling \c init but before calling \c open.
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Values:</b> \n
	 *   - 0 :  TTML text tracks in ID3 tag ignored; CEA closed captions enabled \n
	 *   - 1 :  TTML text tracks in ID3 tag enabled; CEA closed captions ignored \n
	 * <b>Default:</b> 0
	 *
	 * \since version 5.32
	 */
	NXPropertyEnableID3TTML							= 522,
	
	/**
     * \ingroup prop
	 * \brief Sets the language of both audio and text played in multi-stream content.
	 *
	 * It can be used to set the preferred language of audio and text streams to be displayed in content, <em>before</em>
	 * NexPlayer&trade;&nbsp;begins playing content.
	 *
	 * This property should be set by calling NXPlayer::setProperty:toValue: after \c init and before \c open is called, as
	 * demonstrated in the following sample code:
	 * \code
	   [nxPlayer setProperty:NXPropertyPreferLanguage toValue:"eng"];
	   \endcode
	 * \note  Accurate language labels (not the name of a text stream) should be used for the values of this property.
	 *
	 * <b>Type:</b> String \n
	 * <b>Default:</b> \c null \n
	 * <b>Values:</b> Accurate language labels as Strings.  For example, "eng" for English.
	 *
	 * \since version 5.17
	 */
	NXPropertyPreferLanguage 						= 530,
	/**
	 * \ingroup prop
	 * \brief Sets the language to use for audio in multi-stream content, before content is played.
	 *
	 * This property can be used to set the preferred language of audio streams to be used in content, <em> before</em>
	 * NexPlayer&trade;&nbsp;begins playing content.
	 *
	 * \warning  To change any media stream <em>while</em> content is playing, the method
	 * \link NXPlayer::setVideoStream:audioStream:textStream:trackAttributes: setVideoStream:audioStream:textStream:trackAttributes:\endlink
	 * should be called instead.
	 *
	 * \warning To set the preferred language for both audio and text streams to the same language, use the NXPropertyPreferLanguage instead.
	 *
	 * This property should be set by calling \c setProperty: after \c init and before \c NXPlayer::open: is called.
	 *
	 * \note  Accurate language labels (not the name of a text stream) should be used for the values of this property.
	 *
	 * <b>Type:</b> String \n
	 * <b>Default:</b> \c null \n
	 * <b>Values:</b> Accurate language labels as \c Strings.  For example, "eng" for English.
	 */
	NXPropertyPreferLanguageAudio					= 531,
	/**
	 * Sets the language to use for text in multi-stream content, before content is played.
	 *
	 * This property can be used to set the preferred language of text streams to be displayed in content, <em> before</em>
	 * NexPlayer&trade;&nbsp;begins playing content.
	 *
	 * \warning  To change any media stream <em>while</em> content is playing, the method
	 * \link NXPlayer::setVideoStream:audioStream:textStream:trackAttributes: setVideoStream:audioStream:textStream:trackAttributes:\endlink
	 * should be called instead.
	 *
	 * \warning To set the preferred language for both audio and text streams to the same language, use the NXPropertyPreferLanguage instead.
	 *
	 * This property should be set by calling \c setProperty: after \c init and before \c NXPlayer::open: is called.
	 *
	 * \note  Accurate language labels (not the name of a text stream) should be used for the values of this property.
	 *
	 * <b>Type:</b> String \n
	 * <b>Default:</b> \c null \n
	 * <b>Values:</b> Accurate language labels as \c Strings.  For example, "eng" for English.
	 */
	NXPropertyPreferLanguageText					= 532,

	
	/**
     * \ingroup prop
	 * \brief Avoids waiting for the first WebVTT segment to download when starting to play content.
	 *
	 * This property can be used when playing WebVTT content.  By default, NexPlayer&trade;&nbsp;waits until
	 * the first WebVTT segment is downloaded before content begins to play so that no caption text will be missed.
	 *
	 * However, if this property is disabled (set to 0),
	 * the player will start playing content as soon as possible (instead of waiting until the first WebVTT segment is fully downloaded).
	 * This may be preferred if content should start playing as quickly as possible (although initial WebVTT text may be missed).
	 *
	 * This property should be called once, immediately after calling \c init but before calling \c open.
	 *
	 * <b>Type:</b> boolean \n
         * <b>Default:</b> 1    \n
	 * <b>Values:</b>
	 *    - <b>0:</b> Content starts playing before first WebVTT segment is downloaded.
	 *    - <b>1:</b> Content starts playing after first WebVTT segment is downloaded.
	 *
	 * \since version 5.17
	 */
	NXPropertyWebVTTWaitOpen						= 540,
	
	/**
     * \ingroup prop
	 * \brief Sets a target bandwidth (before playing HLS content) when selecting which track to play as playback starts.
	 *
	 * While NexPlayer&trade;&nbsp;automatically chooses an ideal track to play based on several factors including device capability and network conditions,
	 * there may be situations in which starting playback from a track with a bandwidth near a particular bandwidth is desired.
	 *
	 * When this property is set, NexPlayer&trade;&nbsp;selects and starts playing the track in content that has the bandwidth closest to the set bandwidth value,
	 * initially ignoring other factors.
	 *
	 * Note that as playback continues, the track played may change as NexPlayer&trade;&nbsp;judges all factors that influence streaming playback and chooses the best option.
	 *
	 * This property should be called after \c init but before calling \c open.
	 *
	 * <b>Type:</b> int        \n
	 * <b>Unit:</b> bps (bits per second) \n
	 * <b>Default:</b> null    \n
	 * <b>Values:</b>   The target bandwidth value, in bits per second (bps). Note that if \c NXPropertyStartNearestBW is set to 0, NexPlayer&trade;&nbsp;will
	 * 					play normally, as if this property has not been set.
	 *
	 * \since version 5.17
	 */
	NXPropertyStartNearestBW						= 555,
	
	/**
	 * \ingroup prop
	 * \brief Sets whether to enable or disable the Audio Only track in HLS content.
	 *
	 * This property should be called after \c init but before calling \c open.
	 *
	 * <b>Type:</b> int    \n
	 * <b>Default:</b> 1    \n
	 * <b>Values:</b>
	 *    - <b>0:</b> Audio Only track disabled.
	 *    - <b>1:</b> Audio Only track enabled.
	 */
	NXPropertyAudioOnlyTrack						= 556,
	
	/**
	 * \ingroup prop
	 * \brief 	Sets whether or not to continue downloading data in pause state when playing content.
	 *
	 * When this property is set, content data will continue to be downloaded even when NexPlayer;&trade;&nbsp;is paused.
	 *
	 * This property should be called after \c init and before calling \c open.
	 *
	 * <b>Type:</b> NSUInteger   \n
	 * <b>Default:</b> 0   \n
	 * <b>Values:</b>
	 *    - <b>0:</b> Stop downloading in pause state.
	 *    - <b>1:</b> Continue downloading in pause state.
	 *
	 * \since version 5.26
	 */
	NXPropertyContinueDownloadAtPause				= 561,
	
	/**
	 * \ingroup prop
	 * \brief Sets whether or not to trust a content segment's timestamp when playback starts.
	 *
	 * This property should be called after \c init but before calling \c open.
	 *
	 * <b>Type:</b> int   \n
	 * <b>Default:</b> 1   \n
	 * <b>Values:</b>
	 *    - <b>0:</b> Adjust the timestamp during playback.
	 *    - <b>1:</b> Trust the timestamp during playback.
	 */
	NXPropertySegmentTSReliable						= 570,
	
	/**
	* \ingroup prop
	* \brief For DASH, use suggestedPresentationDelay to synchronize end users.
	*
	* For HLS, use the #EXT-X-PROGRAM-DATE-TIME tag to sync end users.
	*
	* This property should be called after \c init but before calling \c open.
	*
	* <b>Type:</b> unsigned integer \n
	* <b>Unit:</b> msec (1/1000 sec) \n
	* <b>Default:</b> 2000 (2 sec) \n
	*
	* \since version 5.40
	*/
	NXPropertySuggestedPresentationDelayTime 				= 590,

	/**
	* \ingroup prop
	* \brief Enables synchronization to UTC time(SPD). \n
	*
	* This property should be called after \c init but before calling \c open.
	*
	* <b>Type:</b> int    \n
	* <b>Default:</b> 0    \n
	* <b>Values:</b>
	*    - <b>0:</b> SPD disabled.
	*    - <b>1:</b> SPD enabled.
	*
	* \since version 5.40
	*/
	NXPropertyEnableSpdSyncToGlobalTime = 591,

	/**
	* \ingroup prop
	* \brief If the current playback is not more synchronized than this value, the player will speed up playback and make sync. \n
	*
	* This property should be called after \c init but before calling \c open.
	*
	* <b>Type:</b> unsigned integer \n
	* <b>Unit:</b> msec (1/1000 sec) \n
	* <b>Default:</b> 300 (300 msec) \n
	*
	* \since version 5.40
	*/
	NXPropertySpdSyncDiffTime = 592,
	
	/**
	* \ingroup prop
	* \brief If playback is out of sync than this value, the player will jump to synchronize the video rather than make it by speeding up. \n
	*
	* This property should be called after \c init but before calling \c open.
	*
	* <b>Type:</b> unsigned integer \n
	* <b>Unit:</b> msec (1/1000 sec) \n
	* <b>Default:</b> 5000 (5 seconds) \n
	*
	* \since version 5.40
	*/
	NXPropertySpdTooMuchDiffTime = 593,
	
	/**
	* \ingroup prop
	* \brief Enables synchronization to device UTC time(SPD). \n
	*
	* This property should be called after \c init but before calling \c open.
	*
	* <b>Type:</b> int    \n
	* <b>Default:</b> 0    \n
	* <b>Values:</b>
	*    - <b>0:</b> Disabled device UTC
	*    - <b>1:</b> Enabled device UTC
	*
	* \since version 5.41
	*/
	NXPropertyEnableSpdSyncToDeviceTime = 594,

	/**
	 * \ingroup prop
	 * \brief Sets iOS HW decoder pixel foramt of output property (kCVPixelBufferPixelFormatTypeKey).
	 *
	 * This property is to set a pixel format for decoded video format.
	 * Have to set it before start to play.
	 * \warning Don't use general play if you use this property for general play.
	 * If you don't use it properly, the video will not display normally.
	 *
	 * <b>Type:</b> int   \n
	 * <b>Default:</b> 0 (kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange)   \n
	 * <b>Values:</b>
	 *    - <b>0:</b> If you want to develop iOS application, you should use this. (kCVPixelFormatType_420YpCbCr8BiPlanarVideoRange)
	 *    - <b>1:</b> If you want to develop Unity application, you should use this. kCVPixelFormatType_32BGRA
	 */
	NXPropertySetHWdecoderPixelFormat				= 801,

	/**
	 * Set it to extend max caption length.
	 * 
	 * This property should be called after \c init but before calling \c open.
	 *
	 * <b>Type:</b> int \n
	 * <b>Default:</b> 8192 \n        
	 * \since version 5.40
	 */
	NXPropertySetMaxCaptionLength 					= 901,

	
	/**
	 * \ingroup prop
	 * \brief   Controls the maximum number of pages the player can allocate for
	 * the remote file cache.
	 *
	 * The remote file cache stores data that has been read from disk or
	 * received over the network (this includes local, streaming, and
	 * progressive content).
	 *
	 * In general, this value should not be changed, as an incorrect
	 * setting can adversely affect performance, particularly when seeking.
	 *
	 * In order to play multiplexed content, at least one audio chunk and
	 * one video chunk must fit inside a single RFC buffer page.  For certain formats
	 * (PIFF, for example) at very high bitrates, the chunks may be too big
	 * to fit in a single page, in which case the RFC buffer page size will need
	 * to be increased.  If the system has limited memory resources, it may be
	 * necessary to decrease the buffer count when increasing the page size.
	 *
	 * Increasing the page size can increase seek times, especially for data
	 * received over the network (progressive download and streaming cases), so
	 * this value should not be changed unless there are issues playing
	 * specific content that cannot be solved in another way.
	 *
	 * \type{unsigned int}
	 * \unit{number of buffers}
	 * \default{20}
	 */
	NXPropertyRFCBufferCount                        = 0x00070001,
	
	/**
	 * \ingroup prop
	 * \brief   Controls the size of each page in the remote file cache.
	 *
	 * Use caution when adjusting this value.  Improper settings may
	 * adversely affect performance, or may cause some content to
	 * fail to play.
	 *
	 * See NXPropertyRFCBufferCount for a detailed description.
	 *
	 * \type{unsigned int}
	 * \unit{kilobytes}
	 * \default{512}
	 */
    NXPropertyRFCBufferPageSize                     = 0x00070002,
    
    NXPropertyColorConvert                          = 0x00071000,
	
	/**
	 * \ingroup prop
	 * \brief  This property sets whether CEA 608 closed captions should be rendered in \c caption mode or \c text mode.
	 *
	 * <b>Type:</b> boolean \n
	 * <b>Default:</b> 0    \n
	 * <b>Values:</b>
	 *    - <b>0:</b> Render CEA 608 closed captions in \c caption mode.
	 *    - <b>1:</b> Render CEA 608 closed captions in \c text mode.
	 *
	 * \since version 5.22
	 */
	NXPropertyCEA608TextMode						= 0x00072000

	
} NXProperty;

#define NXPropertyAVInitOption_Partial			0x00000000
#define NXPropertyAVInitOption_All				0x00000001

#define NXPropertyLogLevel_Debug		0x00000001	// Default log level for debugging. (only logs relating to Start, Stop, and Errors are produced)
#define NXPropertyLogLevel_RTP			0x00000002	// RTP Packet related logs are printed.
#define NXPropertyLogLevel_RTCP			0x00000004	// RTCP Packet related logs are printed.
#define NXPropertyLogLevel_Frame		0x00000008	// Frame related logs are printed.

#define NXPropertyColorConvert_Auto     0
#define NXPropertyColorConvert_CPU      1
#define NXPropertyColorConvert_GPU      2

#define NXPropertyMaxWidthMaxValue	0x7FFFFFFF
#define NXPropertyMaxHeightMaxValue	0x7FFFFFFF

#define NXPropertyHLSLiveViewRecent						0x00000000
#define NXPropertyHLSLiveViewRecentByTargetDuration		0x00000001
#define NXPropertyHLSLiveViewFirst						0x00000002

#define NXPropertyLiveViewRecent						0x00000000
#define NXPropertyLiveViewRecentByTargetDuration		0x00000001
#define NXPropertyLiveViewFirst							0x00000002
#define NXPropertyLiveViewLowLatency					0x00000003

#define NXPropertyLowLaytencyBufferOptionNone			0x00000000
#define NXPropertyLowLaytencyBufferOptionAutoBuffer		0x00000001
#define NXPropertyLowLaytencyBufferOptionConstBuffer	0x00000002
