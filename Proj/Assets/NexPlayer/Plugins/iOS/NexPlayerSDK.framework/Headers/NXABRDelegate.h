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


#ifndef NXABRDelegate_h
#define NXABRDelegate_h

#import <UIKit/UIKit.h>



/**
 * \brief Bandwidth information for ABRControl.
 *
 * This structure is used by NXABRDelegate protocol to control ABR track switch
 * and it includes bandwidth information.
 *
 * \since version 5.27.x
 */

typedef struct {
	NSUInteger netBW;				///< The current network bandwidth.
	NSUInteger curTrackBW;			///< The current track bandwidth.
	NSUInteger nextTrackBW;			///< The target track bandwidth.
} NXPlayerABRControllerTrackChangeParams;

/**
 * \brief  This protocol defines a delegate protocol for the application to receive
 *  an ABR Track switch event from NexPlayer&trade;&nbsp;.
 *
 * NexPlayer&trade;&nbsp; will call the methods provided in this interface
 * automatically during playback to notify the application when an
 * ABR Track switch event has occurred.
 *
 * In most cases, the handling of this event is optional; NexPlayer&trade;&nbsp;
 * will continue to play content normally without the application doing anything
 * special in response to the event received.
 *
 * \param nxplayer	The NXPlayer instance that this delegate has been assigned to.
 * \param params	The NXPlayerABRControllerTrackChangeParams structure which consists of bandwidth infomation.
 *
 * \return  The exact track bandwidth that the user wants to set to forcibly. 
 *
 * \since version 5.27.x
 */

@protocol NXABRDelegate <NSObject>

- (NSUInteger) nexPlayer:(NXPlayer*)nxplayer
willChangeABRTrackWithParams:(NXPlayerABRControllerTrackChangeParams) params;

@end


#endif /* NXABRDelegate_h */
