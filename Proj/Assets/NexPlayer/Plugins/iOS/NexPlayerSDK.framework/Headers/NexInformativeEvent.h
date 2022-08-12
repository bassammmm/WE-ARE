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


#ifndef NexInformativeEvent_h
#define NexInformativeEvent_h

/**
 * \defgroup infokeys Informative Event Keys
 */

/**
 * \ingroup infokeys
 * Detailed parameter key for \c NexInformativeEventDownloadBegan and \c NexInformativeEventDownloadFinished events.
 * The value type is NSString.
 *
 * \since version 5.26 
 */
static NSString* kNexInformativeEventURL = @"URL";

/** 
 * \ingroup infokeys
 * Detailed parameter key for NexInformativeEventDownloadFinished events.
 * The value type is NSNumber, which contains a NXError.
 *
 * \since version 5.26 
 */
static NSString* kNexInformativeEventResult = @"Result";


#endif /* NexInformativeEvent_h */
