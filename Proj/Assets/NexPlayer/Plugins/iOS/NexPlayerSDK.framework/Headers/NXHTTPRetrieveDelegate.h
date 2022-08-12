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


#ifndef NexPlayerSDK_NXHTTPRetrieveDelegate_h
#define NexPlayerSDK_NXHTTPRetrieveDelegate_h

#import <UIKit/UIKit.h>

/**
 * \brief This protocol defines a delegate protocol for the retrieval and offline playback of HLS content stored with NexPlayer&trade;.
 * 
 * Any application that will handle retrieval of HLS content stored for offline playback must implement this protocol.
 * Refer to the \c NXHTTPStoreDelegate protocol for details on how HLS content can be stored so that it can be retrieved with 
 * this delegate protocol.
 * 
 * Once HLS content has been stored by NexPlayer&trade;, to retrieve and play that content offline:
 *      -# Set the bitrate using \c setVideoBitrates:len:withOption: to the <em>same</em> bitrate used to store the HLS content.
 *      -# Implement the \c NXHTTPRetrieveDelegate protocol and call the \c HTTPRetrieve:url:retrieveOffset:receivedLength:outputBuffer:retrievedSize:
 *         function to retrieve offline content.
 *      -# Open, start, and stop the player normally as with any HLS content (except that the previously stored content will be played). 
 * 
 * \see NXHTTPStoreDelegate
 * 
 * \since version 5.24
 */
@protocol NXHTTPRetrieveDelegate

/**
 * \brief  This function retrieves HLS content previously stored so that it can be played when a device is offline.
 * 
 * Once stored content is retrieved by calling this function, the offline content can be opened, started, and stopped
 * normally with the player.
 * 
 * \param player    The NXPlayer instance that this delegate has been assigned to.
 * \param[in] pURL  The pointer to the URL of the HLS content stored.
 * \param dwOffset  The stored offset from the beginning of the content to be played offline.
 * \param dwLength  The length of the content to be played offline.
 * \param[out] ppOutputBuffer  A pointer to the output buffer for the HLS content previously stored.
 * \param pdwSize   The size of the stored content retrieved to be played offline.
 * 
 * \since version 5.24
 */
- (int) HTTPRetrieve:(NXPlayer*)player
				 url:(char*)pURL
	  retrieveOffset:(unsigned long long)dwOffset
	  receivedLength:(unsigned long long)dwLength
		outputBuffer:(char**)ppOutputBuffer
	   retrievedSize:(unsigned long long*)pdwSize;


@end

#endif
