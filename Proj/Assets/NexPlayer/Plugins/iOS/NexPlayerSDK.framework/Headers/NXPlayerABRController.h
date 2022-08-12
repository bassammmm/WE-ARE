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


#import <Foundation/Foundation.h>
#import "NXPlayer.h"

/**
* \brief  This interface must be implemented in order for the application to set a minimum 
* or maximum allowable bandwidth, or both, for playing streaming content.
*
* \since version 5.21
*/
@interface NXPlayerABRController : NSObject

- (id) initWithPlayer:(NXPlayer *) player;

    /**
     * \brief  This method sets the minimum bandwidth for streaming content in NexPlayer&trade;, dynamically during playback.
     *
     * \warning To dynamically change the minimum bandwidth in the middle of playback, please use this method. 
     * To take effect, this method should be called after calling \c open. 
     * Note that the minimum bandwith can also be set before play begins
     * by setting the \c NXProperty, \c NXPropertyMinBW, with \link NXPlayerABRController::changeMinBandwidth: changeMinBandwidth\endlink.
     *
     * This applies in
     * cases with content where there are multiple tracks at different bandwidths (such as
     * in the case of HLS).  The player will not consider
     * any track under the minimum bandwidth when determining whether a track
     * change is appropriate, even if it detects less bandwidth available.
     *
     * Note that to remove a minimum that has been set with this method (so that NexPlayer&trade;&nbsp;will again
     * consider all tracks regardless of bandwidth), set \c min to \c 0x00000000.
     *
     * \param min   Minimum bandwidth in kbps (kilobits per second).  To reset to no minimum bandwidth, set \c min = 0x00000000.
     *
     * \return              NXErrorNone if successful, otherwise nil if there was an error.
     *
     * \since version 5.21
     */
- (NXError) changeMinBandwidth:(NSUInteger) min;

    /**
     * \brief  This method sets the maximum bandwidth for streaming content in NexPlayer&trade;, dynamically during playback.
     *
     * \warning To dynamically change the maximum bandwidth in the middle of playback, please use this method.  
     * To take effect, this method should be called after calling \c open. 
     * Note that the maximum bandwith can also be set before play begins
     * by setting the \c NXProperty, \c NXPropertyMaxBW, with \link NXPlayerABRController::changeMaxBandwidth: changeMaxBandwidth\endlink.
     *
     * This applies in
     * cases with content where there are multiple tracks at different bandwidths (such as
     * in the case of HLS).  The player will not consider
     * any track over the maximum bandwidth when determining whether a track
     * change is appropriate, even if it detects more bandwidth available.
     *
     *
     * Note that to remove a maximum that has been set with this method (so that NexPlayer&trade;&nbsp;will again
     * consider all tracks regardless of bandwidth), set \c max to \c 0x00000000.
     *
     * \param max    Maximum bandwidth in kbps (kilobits per second).  To reset to no maximum bandwidth, set \c max = 0x00000000.
     *
     * \return              NXErrorNone for success, or a non-zero NexPlayer&trade;&nbsp;error code in the event of a failure.
     *
     * \since version 5.21
     */
- (NXError) changeMaxBandwidth:(NSUInteger) max;
   /**
     * \brief  This method sets the minimum and maximum bandwidth for streaming content in NexPlayer&trade;, dynamically during playback.
     *
     * \warning To dynamically change the minimum and maximum bandwidth in the middle of playback, please use this method.
     * To take effect, this method should be called after calling \c open. 
     * Note that the minimum, and maximum bandwith can also be set before play begins
     * by setting the properties, \c NXPropertyMinBW, with \link NXPlayerABRController::changeMinBandwidth: changeMinBandwidth\endlink.
     *  and \c NXPropertyMaxBW, with \link NXPlayerABRController::changeMaxBandwidth: changeMaxBandwidth\endlink.
     *
     * This applies in
     * cases where there are multiple tracks at different bandwidths (such as
     * in the case of HLS).  The player will not consider
     * any track under the minimum, and over the maximum bandwidth when determining whether a track
     * change is appropriate, even if it detects less, and more bandwidth available.
     *
     *
     * Note that to remove a minimum and maximum that has been set with this method (so that NexPlayer&trade;&nbsp;will again
     * consider all tracks regardless of bandwidth), set both of \c min, and \c max to \c 0x00000000.
     *
     * \param min    Minimum bandwidth in kbps (kilobits per second).  To reset to no minimum bandwidth, \c min = 0x00000000.
     * \param max    Maximum bandwidth in kbps (kilobits per second).  To reset to no maximum bandwidth, \c max = 0x00000000.
     *
     * \return              NXErrorNone for success, or a non-zero NexPlayer&trade;&nbsp;error code in the event of a failure.
     *
     * \since version 5.21
     */
- (NXError) changeBandwidthMin:(NSUInteger) min Max:(NSUInteger) max;

    /**
     * \brief  This method sets the target bandwidth for streaming playback dynamically during playback.
     *
     * This applies in cases with content where there are multiple tracks at different bandwidths (such as
     * in the case of HLS).  The player will not consider
     * any track under the target bandwidth and over the target bandwidth when determining whether a track
     * change is appropriate, even if it detects less and more bandwidth available.
     *
     * \param targetBwBps
     *					Target bandwidth in bps (bits per second).
     * \param segOption One of the following \c NexBandwidthSegmentOption values, indicating how to handle buffered content when the track changes:
     * 					  - <b>\c NexBandwidthSegmentOptionDefault  = 0 </b>:  Default (NexPlayer&trade;&nbsp;will decide between \c NexBandwidthSegmentOptionQuickMix (changing tracks quickly) and \c NexBandwidthSegmentOptionLateMix (playing buffered content and changing tracks more slowly)).
     * 					  - <b>\c NexBandwidthSegmentOptionQuickMix = 1 </b>:  NexPlayer&trade;&nbsp;will clear the buffer as much as possible and will start to download new track so user can see a new track faster.
     * 					  - <b>\c NexBandwidthSegmentOptionLateMix  = 2 </b>:  NexPlayer&trade;&nbsp;will preserve and play the content segments already buffered and will download a new track.
     *
     * \param targetOption  How to use the target bandwidth value set.  One of the following \c NexBandwidthTargetOption options:
     * 						  - <b>\c NexBandwidthTargetOptionDefault = 0 </b>: Default target option (\c NexBandwidthTargetOptionBelow).
     * 						  - <b>\c NexBandwidthTargetOptionBelow   = 1 </b>: Select a track with a bandwidth below the target bandwidth.
     * 						  - <b>\c NexBandwidthTargetOptionAbove   = 2 </b>: Select a track with a bandwidth above the target bandwidth.
     * 						  - <b>\c NexBandwidthTargetOptionMatch   = 3 </b>: Select the track that has a bandwidth that matches the target set; otherwise send an error and no new target bandwidth is selected.
     * \warning This method should be called after NXPlayer::open:.
     *
     * \return              NXErrorNone if successful, otherwise non-zero if there was an error.
     *
     * \see NXPlayerABRController::setABREnabled:
     *
     * \since version 5.26
     */
-(NXError) setTargetBandwidth:(NSUInteger) targetBwBps segmentOption:(NexBandwidthSegmentOption) segOption targetOption:(NexBandwidthTargetOption) targetOption;

    /**
     * \brief  This method sets whether or not ABR methods should be used.
     *
     * In general, NexPlayer&trade;&nbsp;plays streaming content, including content with multiple tracks at different bandwidths such as HLS,
     * by choosing the optimal track according to network conditions and device performance.  This is the default behavior of NexPlayer&trade;&nbsp;and
     * this occurs when ABR is enabled (or calling \c NXPlayerABRController::setABREnabled with the parameter \c enabled set to \c YES).
     *
     * However, there may be instances when an application may want to set limits on which tracks should be selected and played by NexPlayer&trade;&nbsp;in
     * order to provide a specific user experience, and to force NexPlayer&trade;&nsbp;to stay on a particular bandwidth track, regardless of network conditions.
     * In cases like this, in order to keep playing a track at a target bandwidth (set with \c NXPlayerABRController::setTargetBandWidth:withSegmentOption:withTargetOption:) this method must be called
     * to disable NexPlayer&trade;'s ABR behavior (with the parameter \c enabled set to \c NO).
     *
     * \warning This method <em>must</em> be called with \c enabled set to \c NO <b>before</b> calling \c NXPlayerABRController::setTargetBandWidth:withSegmentOption:withTargetOption: if the application should
     *          continue playing the target bandwidth <em>regardless</em> of network conditions.
     *
     * \param enabled
     *			- <b> \c YES</b>: ABR enabled.  NexPlayer&trade;&nbsp;will handle track changes automatically.
     *			- <b> \c NO</b>: ABR disabled.  NexPlayer&trade;&nbsp;will continue playing the target bandwidth track set, regardless of network conditions.
     *
     * \return              NXErrorNone if successful, otherwise non-zero if there was an error.
     *
     * \see NXPlayerABRController::setTargetBandWidth:withSegmentOption:withTargetOption:
     *
     * \since version 5.26
     */
-(NXError) setABREnabled:(BOOL) enabled;

@end
