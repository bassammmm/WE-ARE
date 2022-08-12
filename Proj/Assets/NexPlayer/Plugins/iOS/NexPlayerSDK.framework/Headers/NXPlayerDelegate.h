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


#import <UIKit/UIKit.h>
#import "NXCEA608Caption.h"
#import "NXSEITimingInfo.h"
#import "NXClosedCaption.h"
#import "NXSessionData.h"

@class NXPlayer;

/**
 * \brief Delegate protocol for NXPlayer.
 * 
 * Any class that will receive events from a NXPlayer instance as a
 * delegate should implement this protocol.
 *
 * All methods are optional; implement the methods for events which
 * you wish the delegate to handle.
 *
 * NXPlayerDelegate::nexPlayer:willBeSentEvent:withArgs: is a special
 * method that can be used to trap all events, and which can filter events
 * before they are passed to other event handling methods.
 *
 * Use specific event handling methods if you need to respond to a specific
 * event.  For example, if you wish to issue a \c play command when the
 * content has been successfully opened, you might implement
 * NXPlayerDelegate::nexPlayer:completedAsyncCmdOpenWithResult:playbackType:
 * as follows:
 * \code
	- (void) nexPlayer:(NXPlayer *)nxplayer completedAsyncCmdOpenWithResult:(NXError)result playbackType:(NXPlaybackType)type {
		[m_playerView.player start];
	}
 * \endcode
 *
 * Use the general event handling method if you need to respond to a large
 * group of events (or all events) in an identical way.  For example,
 * if you wish to note every event that occurs in the log, you might
 * implement NXPlayerDelegate::nexPlayer:willBeSentEvent:withArgs:.
 * \code
	- (BOOL) nexPlayer:(NXPlayer *)nxplayer willBeSentEvent:(NSString *)selectorName withArgs:(NSArray *)args {
		NSArray *el = [selectorName componentsSeparatedByString:@":"];
		NSMutableString* output = [NSMutableString string];
		for( int i=0; i<[el count]; i++ ) {
			if( [[el objectAtIndex:i] length] < 1 )
				continue;
			if( i>=[args count] )
				[output appendFormat:@"%@:? ", [el objectAtIndex:i], nil ];
			else
				[output appendFormat:@"%@:%@ ", [el objectAtIndex:i], [args objectAtIndex:i], nil ];
		}
		NSLog(@"NEXPLAYER EVENT: %@\n", output);
		return YES;
	}
 * \endcode
 */


@protocol NXPlayerDelegate <NSObject>

@optional

#pragma mark -
#pragma mark Common Events


/**
 * \brief General event handling method that is called before any specific method.
 *
 * This can be used to filter events (return \c NO to prevent further processing
 * of an event), to handle all events (for example, to log debugging information
 * about events as they occur), or to handle a large group of events (in cases
 * where it might be inconvenient to implement event-specific functions).
 * 
 *
 * @deprecated  This API will be removed from the next SDK version.(5.30.x)
 *	Please implement the methods for events which you wish the delegate to handle
 *	since all the methods are optional in NXPlayerDelegate.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] selectorName	The Objective-C selector for the event-specific 
 *							method for this event (this is specified as a string 
 *                          rather than an actual selector; you can use
 *							NSSelectorFromString(selectorName).
 *
 * \param[in] args			An array of the arguments that would be passed
 *							to the event-specific method, in the same order as
 *							they appear in the selector.  These are in the same
 *							format as the method arguments, except that numeric
 *							values such as integers have been replaced with
 *							NSNumber instances.
 *
 * \returns                 \c YES to continue processing normally (event will be
 *							sent to the event-specific method of the delegate)
 *                          or \c NO to stop processing this event (event-specific
 *							method will not be called).
 */
//- (BOOL)nexPlayer:(NXPlayer*)nxplayer
//  willBeSentEvent:(NSString*)selectorName
//		 withArgs:(NSArray*)args;

/**
 * \brief General method called in addition to (and before) other event-specific
 *			methods if the state of the player (play, pause, stop) has changed.
 *
 * This can be used to update the user interface to reflect the new state, such as
 * by enabling or disabling pause and play buttons.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] oldState		The previous player state (see \ref NXPlayerState for details).
 * \param[in] newState		The new player state (see \ref NXPlayerState for details).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer didChangeFromState:(NXPlayerState)oldState toState:(NXPlayerState)newState;

/**
 * \name Common Events
 * \{
 */

/**
 * \brief The player is now ready to accept control commands (pause and seek)
 *          if appropriate for the open content.
 *
 * There are several stages that the player must go through (opening the
 * content, starting the content, waiting for initial buffering to complete)
 * before it is legal to issue seek and pause commands to the player.  Once
 * these stages have completed, this event is sent.  Note that just because
 * the player is ready to accept commands doesn't mean that all commands
 * are valid (for example, live content may still not be seekable).
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \since version 5.8
 */
- (void)nexPlayerReadyForControl:(NXPlayer*)nxplayer;

/**
 * \brief Playback has completed successfully up to the end of content
 *
 * If playback was started with \c autoPlay:YES, the player will automatically
 * be stopped when this event occurs.  Otherwise, it is necessary to stop
 * playback by calling \code [nxplayer stop]; \endcode in response to this
 * event.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidReachEndOfContent:(NXPlayer*)nxplayer;

/**
 * \brief The player's video task has been activated.
 *
 * Generally, applications can ignore this event except for debugging purposes.
 *
 * It is not reliable to use this to detect which content has video, because
 * the video task may be reused for playing other content, or there may temporarily
 * be no video due to bandwidth limitations during streaming.  Instead, to determine
 * if the content includes video, check NXContentInfo::hasVideo.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidStartVideoTask:(NXPlayer*)nxplayer;

/**
 * \brief The player's audio task has been activated.
 *
 * Generally, applications can ignore this event except for debugging purposes.
 *
 * It is not reliable to use this to detect which content has audio, because
 * the audio task may be reused for playing other content, or there may temporarily
 * be no audio due to bandwidth limitations during streaming.  Instead, to determine
 * if the content includes audio, check NXContentInfo::hasAudio.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */	
- (void)nexPlayerDidStartAudioTask:(NXPlayer*)nxplayer;

/**
 * \brief Playback has progressed to a certain position. 
 *
 * This event occurs every second during playback, and can be used to update
 * the user interface to reflex the current play position.
 * 
 * The current playback position is also available through
 * NXPlayer::currentTimeStamp, and that can be polled on a timer if more
 * frequent updates are necessary.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] newPosition   The new playback position (in milliseconds from start of content)
 */
- (void)nexPlayer:(NXPlayer*)nxplayer playheadAdvancedTo:(NXDuration)newPosition;

/**
 * \brief An error has occurred during playback.
 *
 * If the delegate implements this method, it should respond to the error by
 * stopping and closing the currently playing content (it can do this by simply
 * calling NXPlayer::close, which will automatically stop the content first).
 *
 * An error message should also be displayed to the user.
 *
 * If this method is not implemented by the delegate, the default behavior is to
 * display a pop-up message with the error (using UIAlertView) and stop and close
 * the current content.
 *
 * \note	The pop-up error provided by default is very simple and is not
 *			localized. It is strongly recommended that you override this
 *			function and provide your own error display that is suited to
 *			your application.	
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] errorCode		The error that has occurred.  (See \ref NXError for details).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer encounteredError:(NXError)errorCode;

/**
 * \brief Provides debugging and diagnostic information during playback.  
 *
 * The information provided here is for debugging purposes only; the contents 
 * of the strings provided may change in future versions, so do not attempt 
 * to parse them or make programmatic decisions based on their contents.
 * Also, do not make assumptions about line length or number of lines.
 *
 * At present, the debugging messages generated relate to the RTSP/RTCP
 * connection. Additional categories may be added in the future.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] message		Debugging message
 * \param[in] category		Message category; currently, one of:
 *							- NXDebugMsgCat_RTSP
 *							- NXDebugMsgCat_RTCP_RR_SEND
 *							- NXDebugMsgCat_RTCP_BYE_RECV
 *							- NXDebugMsgCat_ContentInfo
 *
 */	
- (void)nexPlayer:(NXPlayer*)nxplayer
	 debugMessage:(NSString*)message
		 category:(NXDebugMsgCat)category;

/**
 * \brief	Subtitle (caption) text has changed, and the application should 
 *			update the display with the new text.
 *
 * NexPlayer&trade;&nbsp;handles the parsing, decoding and timing of subtitle text,
 * but not the display of that text. When subtitle text is ready for display,
 * this method is called, and the delegate must display the text in an
 * appropriate manner.  Often, this is simply done by setting the text attribute
 * of a UITextView that is positioned on top of the video.
 *
 * For local subtitles, the subtitle text from multiple tracks may be combined
 * in a single string in the \c subtitleText and \c subtitleBytes parameters,
 * depending on the setting of NXPlayer::captionLanguages.
 *
 * There are multiple sources for subtitles.  For example, subtitles may come
 * from a local subtitle file (such as SMI, SUB, or SRT file) specified when
 * the content was opened, or they may be included as part of the data streamed
 * from the server.  When the delegate is called, the \c source parameter 
 * identifies the source of the subtitle text.  This text replaces any previous
 * text from the same source.  Most applications only play subtitles from a
 * single source, so this parameter can usually be ignored.  The source may be
 * any string, but in the current version of the SDK it will always be one of:
 *  - LOCAL
 *  - STREAM
 *
 * To handle subtitles from an arbitrary number of sources simultaneously,
 * use the \c source value as a dictionary key and keep a dictionary of the
 * current subtitles for each source.  Then concatenate these when updating
 * the display.
 *
 * \par     <b>A note about Encoding</b>
 *          Many subtitle formats do not actually specify an encoding
 *          for the subtitle text.  NexPlayer&trade;&nbsp;uses a heuristic
 *			algorithm to attempt to determine the encoding.  
 * \par
 *          Since it is not possible to make an absolutely certain determination about the
 *			encoding in use automatically, alternative algorithms may be better
 *			suited to some applications, or there may be applications where it
 *			is desirable to let the user select the encoding.
 * \par
 *			For these reasons, in addition to a text string (decoded using the
 *          detected encoding), NexPlayer&trade;&nbsp;also provides the raw bytes
 *			prior to decoding, so the application may handle them differently
 *			if necessary.
 * \par
 *          Currently, the following encodings are detected automatically:
 *			- ASCII (low ASCII only)
 *			- UTF-8 (Unicode)
 *			- EUC-KR (Korean)
 *			- EUC-JP (Japanese)
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] subtitleText  The string as decoded using the detected encoding.
 * \param[in] subtitleBytes The original bytes of the string prior to decoding.
 * \param[in] source        The source of the subtitles.  See above.
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
   subTitleChange:(NSString*)subtitleText
	originalBytes:(NSData*)subtitleBytes
   subtitleSource:(NSString*)source;

/**
 * \brief       Subtitle (caption) text has changed, and the application should 
 *              update the display with the new text.
 *
 * \deprecated  This doesn't include subtitle source information, but is retained
 *              for compatibility with existing code. nexPlayer:subTitleChange:originalBytes:subtitleSource:
 *              should be used instead, in new code.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] subtitleText  The string as decoded using the detected encoding.
 * \param[in] subtitleBytes The original bytes of the string prior to decoding.
 *
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
   subTitleChange:(NSString*)subtitleText
	originalBytes:(NSData*)subtitleBytes;

- (void)nexPlayer:(NXPlayer*)nxplayer
   subTitleChange:(NSString*)subtitleText
            start:(NSUInteger)startTime
              end:(NSUInteger)endTime;

/**
 * \brief       CEA 608 closed caption text has changed.
 *
 * Whenever new CEA 608 closed caption data is updated, this event will be sent.
 *
 * NexPlayer&trade;&nbsp;can handle and display CEA 608 closed captions fully
 * but an application may also choose to handle the display of these captions differently
 * in another independent view.
 *
 * \param[in]   nxplayer	The NXPlayer instance that generated the event.
 * \param[in]   caption     The caption to display (see NXCEA608Caption for 
 *                          details). This should replace ALL existing 
 *                          displayed caption text.
 * \param[in]   channel     The channel that closed caption data relates to (may be
 *                          0 if captions were just turned off, and this event
 *                          is to erase the caption display).
 *
 * \since version 5.8
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
   updatedCaption:(NXCEA608Caption*)caption
 forCEA608Channel:(NXCEA608Channel)channel;

/**
 * \brief       The metadata associated with the current content has changed.
 *
 * Whenever any metadata changes for the current content, this method will be
 * called and will provide only the updated fields of the metadata.  These can
 * be used to update the UI view for the relevant fields if desired, without
 * calling the entire NXContentInfo::metaData object.
 *
 * \param[in]   nxplayer	The NXPlayer instance that generated the event.
 * \param[in]   metaData    A dictionary containing only the updated metadata
 *                          fields.  Field names are the same as NXContentInfo::metaData
 *
 * \since version 5.8
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
   updatedMetaData:(NSDictionary*)metaData;

/**
 * \brief  This method provides SEI picture timing information about video frames of H.264 content when it is available and changes.
 *  
 * While SEI may include a variety of attributes, this method specifically receives SEI picture timing information when available.
 * 
 * \param[in] nxplayer    The NXPlayer instance that generated the event.
 * \param[in] timing      The NXPicTimingInfo object that includes the new SEI picture timing information for the content.
 * 
 * \since version 5.16
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
updatedSEIPicTiming:(NXPicTimingInfo*)timing;

/**
 * \brief This method receives updated closed captions for contents such as WebVTT or TTML.
 *
 * \param[in] nxplayer	    The NXPlayer instance that generated the event.
 * \param[in] caption       New captions to be displayed on the contents. (see NXClosedCaption for more details).
 *
 * \since version 5.16.1
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
   updatedCaption:(NXClosedCaption *)caption;


/**
 * \brief This method allows NexPlayer&trade;&nbsp;to pass HTTP request messages to an application.
 *
 * While NexPlayer&trade;&nbsp; normally handles HTTP requests and responses internally, in cases where additional information is required 
 * from the server (for example user cookies), this method can be used in conjunction with onHTTPResponse to allow an application 
 * to handle that information directly.
 *
 * \Note This should be called before a request is sent to an HTTP server.
 * To handle the response received, call \c onHTTPResponse.
 *
 * \param[in] nxplayer	    The NXPlayer instance that generated the event.
 * \param[in] strRequest	The HTTP request to be sent to the server, as a String.
 *
 * \see \c nexPlayer:onHTTPResponse:statusCode:
 *      
 *
 * \since version 5.19
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
	onHTTPRequest:(NSString*)strRequest;

/**
 * \brief This method allows responses from an HTTP server to be received and handled in a more customized way.
 *
 * While NexPlayer&trade;&nbsp; normally handles HTTP requests and responses internally, in cases where additional information is required from the server
 * (for example user cookies), this method can be used in conjunction with onHTTPRequest to handle that information directly.
 * 
 * \Note This should be called after a response has been received from the server. 
 *
 * \param[in] nxplayer	    The NXPlayer instance that generated the event.
 * \param[in] strResponse	The response from the HTTP server, as a String.
 * \param[in] statusCode	The status code from the HTTP server, as an Integer.
 *
 * \see \c nexPlayer:onHTTPRequest:
 * 
 * \since version 5.19
 */

- (void)nexPlayer:(NXPlayer*)nxplayer
   onHTTPResponse:(NSString*)strResponse
       statusCode:(NSUInteger) statusCode;


/**
 * \brief       The seekable state of the content has changed.
 *
 * Any time the seekable state of the content changes, this event will be sent.
 * This event should be used to update the seek bar and is used to support
 * server-side timeshifting in live content.
 *
 * If the content is not seekable, \c seekBase and \c seekableLen will both be
 * zero and \c isSeekable will be \c NO.
 *
 * If the content is seekable, \c isSeekable will be \c YES and \c seekableLen
 * will be greater than zero.
 *
 * For most content, \c seekBase will be zero.  However, in the case of seekable
 * live content, there is a sliding window within which seeking is possible.
 * In this case, \c seekBase will be non-zero and indicates the beginning of that
 * window. The end of the seekable window can be determined using \c seekableLen.
 *
 * The actual values that can appear in \c seekBase for live content are 
 * arbitrary and depend on the server.
 *
 * \param[in]   nxplayer	The NXPlayer instance that generated the event.
 * \param[in]   isSeekable  \c YES if the current contents support seeking, otherwise \c NO.
 * \param[in]   seekBase    The earliest possible time that the player can seek to.
 * \param[in]   seekableLen The length of the seekable region starting at \c seekBase.
 *
 * \since version 5.8
 */
- (void)nexPlayer:(NXPlayer*)nxplayer 
seekableStateChangedTo:(BOOL)isSeekable
         seekBase:(uint64_t)seekBase
   seekableLength:(NSUInteger)seekableLen;

/**
 * \brief An asynchronous \em open operation has completed.
 *
 * This method is called when an open operation started by
 * NXPlayer::open:mode:subtitles:transport:autoPlay:
 * (or one of the related convenience functions) has completed.
 *
 * If \c autoPlay was set to \c YES when the open command was issued,
 * the player will automatically call NXPlayer::start to begin playback;
 * otherwise, the delegate will need to start playback explicitly by
 * calling that same method.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 *
 * \param[in] type			The type of content; one of:
 *							- NXPlaybackTypeLocal
 *							- NXPlaybackTypeStreaming
 *
 * \see NXPlayer::open:mode:subtitles:transport:autoPlay:, the method starting the open
 *      operations that calls this method when they complete.
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdOpenWithResult:(NXError)result playbackType:(NXPlaybackType)type;

/**
 * \brief An asynchronous \em start operation has completed.
 *
 * This method is called when playback has started (or failed irrecoverably)
 * after a call to NXPlayer::start.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 *
 * \param[in] type			The type of content; one of:
 *							- NXPlaybackTypeLocal
 *							- NXPlaybackTypeStreaming
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdStartWithResult:(NXError)result playbackType:(NXPlaybackType)type;

/**
 * \brief An asynchronous \em stop operation has completed.
 *
 * This method is called when the stop operation initiated by NXPlayer::stop
 * has completed.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdStopWithResult:(NXError)result;

/**
 * \brief An asynchronous \em pause operation has completed.
 *
 * This method is called when the pause operation initiated by NXPlayer::pause
 * has completed.
 *
 * \note If you call NXPlayer::pause during a seek operation, no pause command is
 *          actually issued.  Rather, the seek operation that is in progress is
 *          modified to leave the player in a paused state upon completion.  In
 *          this case, because the pause command is not actually issued, no
 *          completion event will occur.  You can detect this case by checking
 *          the value of NXPlayer::seeking just before calling NXPlayer::pause.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdPauseWithResult:(NXError)result;

/**
 * \brief An asynchronous \em resume operation has completed.
 *
 * This method is called when the resume operation initiated by NXPlayer::resume
 * has completed.
 *
 * \note If you call NXPlayer::resume during a seek operation, no resume command
 *          actually issued.  Rather, the seek operation that is in progress is
 *          modified to leave the player in a playing state upon completion.  In
 *          this case, because the resume command is not actually issued, no
 *          completion event will occur.  You can detect this case by
 *          checking the value of NXPlayer::seeking just before calling
 *          NXPlayer::resume.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdResumeWithResult:(NXError)result;

/**
 * \brief An asynchronous \em seek operation has completed.
 *
 * This method is called when the seek operation initiated by NXPlayer::seek
 * has completed.
 *
 * \note    If you call NXPlayer::seekTo: while a seek operation is already in
 *          progress, it just modifies the target of the current seek operation.
 *          No new seek operation is started, and therefore, only one single
 *          completion event will be generated.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdSeekWithResult:(NXError)result;

/**
 * \brief An asynchronous \em forward operation has completed.
 *
 * \deprecated              There is currently no API in the NexPlayer&trade;&nbsp;iOS SDK
 *							that implements the \em forward command, and this event
 *							can therefore never occur.  It may be supported in future
 *							versions, so you should not write code that processes
 *							this event at present (otherwise that code may break
 *							in the future).
 *					
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 */
//- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdForwardWithResult:(NXError)result;

/**
 * \brief An asynchronous \em backwards operation has completed.
 *
 * \deprecated              There is currently no API in the NexPlayer&trade;&nbsp;iOS SDK
 *							that implements the \em backwards command, and this event
 *							can therefore never occur.  It may be supported in future
 *							versions, so you should not write code that processes
 *							this event at present (otherwise that code may break
 *							in the future).
 *					
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] result        The result of the asynchronous operation (zero
 *							if the operation succeeded, or a non-zero NXError
 *							code if the operation failed due to an error).
 */
//- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdBackwardsWithResult:(NXError)result;

/**
 * \brief An asynchronous \c setExternalSubtitle operation has completed.
 *
 * This method is called when the pause operation initiated by NXPlayer::setExternalSubtitle
 * has completed.
 *
 *
 * \param[in] result        The result of the asynchronous operation (NXErrorNone for success,
 *                          or a non-zero NXError code in the event of a failure).
 *
 * \since version 5.26
 */

- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdSetExternalSubtitleWithResult:(NXError)result;

/**
 * \brief An asynchronous <tt>media stream</tt> switching operation has completed.
 *
 * This method is called when the media stream switching operation initiated by NXPlayer::setVideoStream:audioStream:textStream:trackAttributes:
 * or NXPlayer::setVideoStream:audioStream:trackAttributes: has completed.
 *
 *
 * \param[in] result        The result of the asynchronous operation (NXErrorNone for success,
 *                          or a non-zero NXError code in the event of a failure).
 * \param[in] stream		The new stream of NXContentInfo.
 *
 * \since version 5.28
 */

- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdSetMediaStreamWithResult:(NXError)result streamInfo:(NXMediaStreamInfo*)stream;

/**
 * \brief An asynchronous media on/off operation has completed.
 *
 * This method is called when the media on/off operation initiated by NXPlayer::setMediaOnOff:mediaType: has completed.
 *
 *
 * \param[in] result The result of the asynchronous operation (NXErrorNone for success,
 * or a non-zero NXError code in the event of a failure).
 * \param[in] mediaType	The mediaType to disable or enable.
 * The method uses NXMediaType and values below only are valid.
 * NXMediaTypeAudio
 * NXMediaTypeVideo
 * NXMediaTypeText
 * \param[in] bOnOff if you want to disable the media, set to NO.
 * if you want to enable the media, set to \c YES.
 *
 *
 * \see NXPlayer::setMediaOnOff:mediaType:
 *
 * \since version 5.29
 */
- (void)nexPlayer:(NXPlayer*)nxplayer completedAsyncCmdMediaOnOffWithResult:(NXError)result mediaType:(NXMediaType)mediaType bOnOff:(BOOL)bOnOff;



/**
 * \brief This method allows the HTTP request that will be used by
 *        NexPlayer&trade;&nbsp; to be switched when an HTTP request should be modified.
 *
 * This method will be called if \c NXPropertyEnableModifyHTTPRequest is set to \c TRUE or enabled.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] requestString		The HTTP Request data.
 *
 * \returns  A \c String with the modified HTTP request.  This value will be used by
 *           NexPlayer&trade;&nbsp; instead of the previous HTTP request.
 *
 * \see NXProperty::NXPropertyEnableModifyHTTPRequest
 * \since version 5.23
 */
- (NSString *) nexPlayer:(NXPlayer *)nxplayer onModifyHttpRequest:(NSString *)requestString;


/**
 * \brief This method is called when an HTTP error response was received from the server.
 *
 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] statusCode	contains the error code (this is a normal HTTP response code, such as 404, 500, etc.)
 *
 * \since version 5.28
 */

- (void)nexPlayer:(NXPlayer*)nxplayer onStatusHTTPInvalidResponse:(NSUInteger)statusCode;



/** \} */ // Common Events

#pragma mark -
#pragma mark Streaming Events

/**
 * \name Streaming Events
 * \{
 */

/**
 * \brief NexPlayer&trade;&nbsp;made an RTSP request, but has not received a
 *		response from the streaming server within the period specified 
 *		by \ref NXPropertyRTSPCommandTimeout.
 *
 * The value of NXPropertyRTSPCommandTimeout can be set by calling
 * NXPlayer::setProperty:toValue: and controls the maximum time that the
 * player will wait for a response before generating this event.
 *
 * If the delegate implements this method, it should respond  by
 * stopping and closing the currently playing content (it can do this by simply
 * calling NXPlayer::close, which will automatically stop the content first).
 *
 * A message should also be displayed to the user.
 *
 * If this method is not implemented by the delegate, the default behavior is to
 * forward this to NXPlayerDelegate::nexPlayer:encounteredError: with the
 * error code \ref NXErrorRTSPCommandTimeout (which, in most cases, will
 * display a message to the user, stop playback, and close the content).
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerRTSPCommandTimeout:(NXPlayer*)nxplayer;

/**
 * \brief NexPlayer&trade;&nbsp;has been in the \ref NXPlayerStatePause state for
 *			the period specified by \ref NXPropertyPauseSupervisionTimeout.
 *
 * The value of NXPropertyPauseSupervisionTimeout can be set by calling
 * NXPlayer::setProperty:toValue: for \c NXPropertyPauseSupervision, and it indicates that the maximum time in
 * the paused state has passed.
 * 
 * The delegate may ignore this event (in which case, nothing will happen) or it
 * may take an appropriate action in response to this event,
 * such as to resume playback or to stop streaming altogether.
 *
 * If this method is not implemented by the delegate, the default behavior is to
 * forward this to NXPlayerDelegate::nexPlayer:encounteredError: with the
 * error code \ref NXErrorPauseSupervisionTimeout (which, in most cases, will
 * display a message to the user, stop playback, and close the content).
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerPauseSupervisionTimeout:(NXPlayer*)nxplayer;

/**
 * \brief NexPlayer&trade;&nbsp;hasn't received any data from the streaming server
 *		for the period specified by NXPropertyDataInactivityTimeout.
 *
 * The value of NXPropertyDataInactivityTimeout can be set by calling
 * NXPlayer::setProperty:toValue:, and it indicates the maximum time to wait
 * for packets from the server before timing out and generating this event.
 *
 * The delegate should take appropriate action in response to this event.
 * In most cases, the correct response is to notify the user and to stop 
 * playback and close the content.
 *
 * If this method is not implemented by the delegate, the default behavior is to
 * forward this to NXPlayerDelegate::nexPlayer:encounteredError: with the
 * error code \ref NXErrorDataInactivityTimeout (which, in most cases, will
 * display a message to the user, stop playback, and close the content).
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDataInactivityTimeout:(NXPlayer*)nxplayer;

/**
 * \brief Failed to determine the audio codec.
 * 
 * This notification can happen at the beginning of playback, or during 
 * playback if there is an audio codec change. This can happen because of a 
 * switch to a new codec that NexPlayer&trade;&nbsp;does not support, or can be due to an error
 * in the format of the content or corrupted data in the content.
 *
 * The player doesn't take any special automatic action when this event
 * occurs.  Playback is allowed to continue because the track may change
 * again in future to one that contains a supported codec.  However, it may
 * be desirable for the application to indicate the state temporarily in the
 * user interface.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidFailToGetAudioCodec:(NXPlayer*)nxplayer;

/**
 * \brief Failed to determine the video codec. 
 *
 * This notification can happen at the beginning of playback, or during 
 * playback if there is a video codec change. This can happen because of a 
 * switch to a new codec that NexPlayer&trade;&nbsp;does not support, or due to an error
 * in the format of the content or corrupted data in the content.
 *
 * The player doesn't take any special automatic action when this event
 * occurs.  Playback is allowed to continue because the track may change
 * again in future to one that contains a supported codec.  However, it may
 * be desirable for the application to indicate the state temporarily in the
 * user interface.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidFailToGetVideoCodec:(NXPlayer*)nxplayer;

/**
 * \brief The audio codec failed to initialize. 
 *
 * This can happen for several reasons. The container may indicate the wrong 
 * audio codec, or the audio stream may be incorrect or corrupted, or the audio
 * stream may use a codec version or features that NexPlayer&trade;&nbsp;doesn't support.
 *
 * The player doesn't take any special automatic action when this event
 * occurs.  Playback is allowed to continue because the track may change
 * again in future to one that contains a supported codec.  However, it may
 * be desirable for the application to indicate the state temporarily in the
 * user interface.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidFailToInitAudioCodec:(NXPlayer*)nxplayer;

/**
 * \brief The video codec failed to initialize. 
 *
 * This can happen for several reasons. The container may indicate the wrong 
 * video codec, or the video stream may be incorrect or corrupted, or the video 
 * stream may use a codec version or features that NexPlayer&trade;&nbsp;doesn't support.
 *
 * The player doesn't take any special automatic action when this event
 * occurs.  Playback is allowed to continue because the track may change
 * again in future to one that contains a supported codec.  However, it may
 * be desirable for the application to indicate the state temporarily in the
 * user interface.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidFailToInitVideoCodec:(NXPlayer*)nxplayer;

/**
 * \brief The track has changed. 
 *
 * This happens for protocols such as HLS that provide the content in multiple 
 * formats or at multiple resolutions or bitrates. The ID of the new track can
 * be found in NXMediaStreamInfo::currentTrack and also as an argument to this
 * method. When this event occurs, a NXPlayerDelegate::nexPlayerDidUpdateContentInfo
 * event will also occur.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] track			The new track. 
 */
- (void)nexPlayer:(NXPlayer*)nxplayer trackChangedTo:(NXTrackInfo*)track;

/**
 * \brief The stream has changed.
 *
 * This happens for protocols such as Smooth Streaming that support multiple
 * streams.  A stream change is usually the result of an API call, such as
 * NXPlayer::setVideoStream:audioStream:trackAttributes:.  When this event occurs,
 * a NXPlayerDelegate::nexPlayerDidUpdateContentInfo event will also occur.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] stream		The new stream of NXContentInfo.
 */
- (void)nexPlayer:(NXPlayer*)nxplayer streamChangedTo:(NXMediaStreamInfo*)stream;

/**
 * \brief	An attribute relating to the video or audio format (such as the 
 *          resolution, bitrate, etc.) has changed.
 *
 * See NXPlayer::contentInfo for the updated information.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidChangeDSI:(NXPlayer*)nxplayer;

/**
 * \brief	The stream being played back has changed and the new stream
 *			has a different media type.
 *
 * This event happens whenever the state changes between video-only, audio-only
 * and audio-video.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] newType		The new media type (see \ref NXMediaType).
 */
- (void)nexPlayer:(NXPlayer*)nxplayer mediaTypeChangedTo:(NXMediaType)newType;

/**
 * \brief One or more of the codecs in use has changed.
 *
 * There was a change in the audio codec in use, the video codec in use, or
 * both.  The new codecs are in NXContentInfo::audioCodec and
 * NXContentInfo::videoCodec.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidChangeCodec:(NXPlayer*)nxplayer;

/**
 * \brief	The content information has changed.  
 *
 * There are many reasons why a content information change can happen.  One
 * example is changing streams or tracks when playing streaming content.
 *
 * There are several more specific events that can occur in addition to this one,
 * such as NXPlayerDelegate::nexPlayerDidChangeCodec:.  If there is a more
 * specific event suitable to your need, you should consider using that instead.
 *
 * The new content information can be found in NXPlayer::contentInfo.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidUpdateContentInfo:(NXPlayer*)nxplayer;

/**
 * \brief	The player has begun buffering.
 * 
 * This happens when the player doesn't have enough data to ensure seamless
 * playback, and is waiting for more data before continuing playback.
 *
 * Buffering happens in two cases:
 *
 * -# When beginning playback, the player
 * buffers enough data to play back several seconds of content.  The exact
 * amount of initial buffering can be adjusting by changing the property
 * \ref NXPropertyInitialBufferingDuration.  
 *
 * -# If the player runs out of data during playback (if there is not enough
 * data to decode and play back any additional frames), playback will
 * temporarily stop until the player buffers enough data to play back several
 * seconds of content.  The exact amount of this additional buffering
 * can be adjusted by changing the property \ref NXPropertyReBufferingDuration.
 *
 * In any case, when buffering begins, this event is sent.  Throughout the
 * buffering process, NXPlayerDelegate::nexPlayer:bufferingProgress: events
 * will be sent to indicate the percentage of required data that has been
 * buffered so far.  When enough data has been buffered to resume playback,
 * the NXPlayerDelegate::nexPlayerDidFinishBuffering: event will be sent.
 *
 * In general, the application should handle these events as follows:
 * - \c nexPlayerDidBeginBuffering:  <em>Display a "buffering..." message</em>
 * - \c nexPlayer:bufferingProgress: <em>Update the message to reflect the current buffering percentage.</em>
 * - \c nexPlayerDidFinishBuffering: <em>Remove the buffering message</em>
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidBeginBuffering:(NXPlayer*)nxplayer;

/**
 * \brief The player has finished buffering.
 *
 * This happens when the player has buffered the requested amount of data
 * and is about to resume playback.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \see NXPlayerDelegate::nexPlayerDidBeginBuffering: for more information
 */
- (void)nexPlayerDidFinishBuffering:(NXPlayer*)nxplayer;

/**
 * \brief Buffering has progressed and the percentage complete has changed.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] percent		The percentage (an integer from 0 to 100) of the
 *							required amount of data that has been buffered.
 *
 * \see NXPlayerDelegate::nexPlayerDidBeginBuffering: for more information
 */
- (void)nexPlayer:(NXPlayer*)nxplayer bufferingProgress:(NSInteger)percent;

/**
 * \brief The RTSP connection has been successfully established with the streaming server.
 *
 * This is a one-time event and applies only to RTSP streaming, not to other
 * forms of streaming.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidConnectToServer:(NXPlayer*)nxplayer;

/**
 * Called whenever a new playlist is received.
 *
 * This is called every time that the player receives an HLS playlist.  This
 * can happen in several cases:
 *
 * - When the initial (master) playlist is received.
 * - When the player switches to a new track and loads the playlist for that track.
 * - Whenever the server updates the playlist while playing live content.
 *
 * Whenever NXPlayer::HLSTSDescrambler is called with a TS or audio
 * file to be descrambled, that TS or audio file will always be from the
 * playlist most recently received by this callback.
 *
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 *
 * \param[in] URL             The URL of the playlist.
 *
 * \param[in] newPlaylist
 *                The playlist that was just received.  Playlists can be very large,
 *                so the memory backing this string is managed by the engine. Do not retain this string.
 *                If you must use it after this method returns, make a copy of the playlist string or relevant portions.
 *
 * \since version 5.9
 */
- (void)nexPlayer:(NXPlayer*)nxplayer playlistReceived:(NSString*)newPlaylist forURL:(NSString*)URL;

/** \} */ // Streaming Events

#pragma mark -
#pragma mark Downloading Events

/**
 * \name Downloading Events
 * \{
 */

/**
 * \brief The player connected to the HTTP server and got the HEAD 
 *			information successfully
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 * \param[in] sizeInBytes   The total size, in bytes, of the file to be downloaded.
 */
- (void)nexPlayerDidConnectForDownload:(NXPlayer*)nxplayer
							 totalSize:(NSInteger)sizeInBytes;

/**
 * \brief The player has begun to download the content.
 * 
 * \param[in] nxplayer		The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidBeginDownloading:(NXPlayer*)nxplayer;

/**
 * \brief The player is downloading content, and the download has progressed.
 *
 * This event provides status updates on the number of bytes downloaded so that
 * applications can display that information in the user interface.
 * 
 * \param[in] nxplayer			The NXPlayer instance that generated the event.
 * \param[in] downloadedBytes   The number of bytes downloaded so far.
 * \param[in] totalSize			The total number of bytes in the file to be downloaded.
 */
- (void)nexPlayer:(NXPlayer*)nxplayer
 didDownloadSoFar:(NSUInteger)downloadedBytes
		totalSize:(NSUInteger)totalSize;

/**
 * \brief The player has finished downloading the content.
 * 
 * \param[in] nxplayer			The NXPlayer instance that generated the event.
 */
- (void)nexPlayerDidFinishDownloading:(NXPlayer*)nxplayer;

/**
 * \brief	The player does not have enough data to play back content.
 *
 * This event occurs during a progressive download when there is not enough
 * data to continue playing.  The download will continue, but playback will
 * be temporarily suspended until additional data is available.  Once enough
 * data is available, the NXPlayerDelegate::nexPlayerFinishedDownloadBuffering:
 * event will occur.
 * 
 * \param[in] nxplayer			The NXPlayer instance that generated the event.
 */
- (void)nexPlayerBeganDownloadBuffering:(NXPlayer*)nxplayer;

/**
 * \brief	This event occurs when there is enough data downloaded to resume
 *			playback.
 *
 * \param[in] nxplayer			The NXPlayer instance that generated the event.
 *
 * \see		NXPlayerDelegate::nexPlayerBeganDownloadBuffering: for details.
 */
- (void)nexPlayerFinishedDownloadBuffering: (NXPlayer*)nxplayer;

/** \} */ // Downloading Events

/**
 * \brief This method provides the download progress for Offline Playback.
 *
 * \param[in] nxplayer		The \c NXPlayer instance that generated the event.
 * \param[in] current		Current file count.
 * \param[in] total			Total File count.
 *
 * \since version 5.24
 */
- (void) nexPlayer:(NXPlayer *)nxplayer didUpdateDownloadProgressWithFileCount:(NSUInteger)current totalFileCount:(NSUInteger)total;


/**
 * \brief This method delivers an informative event such as NexInformativeEventDownloadBegan.
 *
 * \param[in] nxplayer		The \c NXPlayer instance that generated the event.
 * \param[in] event			The informative event.
 * \param[in] details		Dictionary contains parameters for the event, if available. See \c NexInformativeEvent for details.
 *
 * \since version 5.26
 */
- (void) nexPlayer:(NXPlayer *)nxplayer didReceiveInformativeEvent:(NexInformativeEvent)event details:(NSDictionary*)details;


/**
 * \brief  This method reports the arbitrary session data of the HLS master playlist.
 *
 * \param[in] nxplayer			The \c NXPlayer instance that generated the event.
 * \param[in] sessionDataArr	The array of NexSessionData object that includes the arbitrary session data of the HLS master playlist.
 *
 * \since version 5.33
 */
- (void)nexPlayer:(NXPlayer *)nxplayer didReceiveSessionData:(NSMutableArray*)sessionDataArr;


#pragma mark -

@end
