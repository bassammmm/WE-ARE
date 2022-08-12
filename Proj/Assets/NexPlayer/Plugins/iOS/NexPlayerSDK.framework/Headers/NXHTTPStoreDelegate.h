/******************************************************************************
 ______________________________________________________________________________
 |                                                                            |
 |                                                                            |
 |          Copyrightⓒ 2002-2019 NexPlayer Corp. All rights reserved.      |
 |                        http://www.nexplayer.com                         |
 |                                                                            |
 |____________________________________________________________________________|
 
 ******************************************************************************
 *  THIS CODE AND INFORMATION IS PROVIDED "AS IS" WITHOUT WARRANTY OF ANY
 *  KIND, EITHER EXPRESSED OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
 *  IMPLIED WARRANTIES OF MERCHANTABILITY AND/OR FITNESS FOR A PARTICULAR
 *  PURPOSE.
 *****************************************************************************/


#ifndef NexPlayerSDK_NXHTTPStoreDelegate_h
#define NexPlayerSDK_NXHTTPStoreDelegate_h

#import <UIKit/UIKit.h>

/** 
 * \brief  This protocol defines a delegate protocol for the HLS offline storage feature in NexPlayer&trade;.
 * 
 * Any application that will handle HLS offline storage must implement this protocol.
 * 
 * In order to store content for offline playback:
 *     -# NXPlayer should set a desired bitrate using the \c setVideoBitrates:len:withOption.
 *     -# The \c NXHTTPStoreDelegate should be implemented.  The \c HTTPStore:url:storeOffset:receivedLength:storeBuffer:retrievedSize: method 
 *        will be called when HLS contents need to be stored.
 *     -# The player should be opened with a call to \c mode:NXOpenModeStoreStream.
 *     -# Then the player should be started with a call to \c nexPlayer:completedAsyncCmdOpenWithResult:playbackType: from the NXPlayer delegate.
 *     -# After contents are stored, \c stop: should be called once the event \c nexPlayerDidReachEndOFContent is received by \c NXPlayerDelegate.
 * 
 * Once content is stored for offline playback, an application can implement \c NXHTTPRetrieveDelegate to retrieve the stored
 * HLS content and play it back.
 * 
 * \see NXHTTPRetrieveDelegate
 * \since version 5.24
 */
@protocol NXHTTPStoreDelegate

/**
 * \brief  This function stores HLS content for playback offline.
 * 
 * \param player    The NXPlayer instance that this delegate has been assigned to.
 * \param[in] pURL  A pointer to the URL of the HLS content to be stored for offline playback
 * \param dwOffset  The offset from the beginning of content at which the delegate should start storing for offline playback
 * \param dwLength  The received length of the content to be stored.
 * \param pBuffer  A pointer to the buffer where content downloaded for offline playback will be stored.
 * \param dwSize   The size of the stored content to be retrieved for offline playback.
 * 
 * \since version 5.24
 */
- (int) HTTPStore:(NXPlayer*)player
			  url:(char*)pURL
	  storeOffset:(unsigned long long)dwOffset
   receivedLength:(unsigned long long)dwLength
	  storeBuffer:(char*)pBuffer
	retrievedSize:(unsigned long long)dwSize;

@end

#endif
