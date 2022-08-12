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


#ifndef NexPlayerSDK_NXPlayerCallbackDelegate_h
#define NexPlayerSDK_NXPlayerCallbackDelegate_h


@protocol NXPlayerCallbackDelegate <NSObject>
@end

/**
 * \brief Delegate interface that defines the methods that will be called when 
 * an encryption key retrieval is required from a HLS playlist to be passed to NexPlayer&trade;&nbsp;for descrambling.
 *
 * \since version 5.24
 */
@protocol NXPlayerGetKeyExtDelegate <NXPlayerCallbackDelegate>

/**
 * \brief This method is called for encryption key retrieval from the NexPlayer&trade;&nbsp;for descrambling.
 *
 * \param nxplayer  The \c NXPlayer instance that generated the event.
 * \param URLString The URL of the encryption key.
 * \param pResult [out] YES if encryption key was successful. NO, otherwise.
 * \return NSData object that contains encryption key information if successful. \c nil otherwise.
 *
 * \since version 5.24
 */
- (NSData *) nexPlayer:(NXPlayer *) nxplayer getKeyExtForURLString:(NSString *) URLString result:(BOOL *) pResult;

@end

#endif
