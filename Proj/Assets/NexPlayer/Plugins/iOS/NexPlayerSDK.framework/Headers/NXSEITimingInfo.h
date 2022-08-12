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


/**
 * \brief  This class allows NXPlayer to handle SEI picture timing information in H.264 content.
 *
 * In summary, this class passes timing information about each video frame in H.264 content if the content provides
 * SEI picture timing information.  NXPlayer passes an instance of this class.
 *
 * In most cases, this information will include \c full_timestamp_flag, \c seconds_value, \c minutes_value, and \c hours_value.
 * But also note that \c seconds_value, \c minutes_value, and \c hours_value are valid <b>only</b> if \c full_timestamp_flag is 1.
 *
 * For more in depth information about SEI picture timing information, please see the H.264 specifications.
 *
 */
#ifndef NexPlayerSDK_Header_h
#define NexPlayerSDK_Header_h

typedef struct
{
	/**
	 * \brief  This is the clock timestamp flag of SEI picture timing information in H.264 content.
	 *
	 *  <b>Values:</b>
	 *    - 1 :  Indicates that several clock timestamp syntax elements are present and follow immediately.
	 *    - 0 :  Indicates that the related clock timestamp elements are <b>present</b>.
	 *
	 */
	unsigned char 	clock_timestamp_flag;
	/**
	 * \brief  This is the scan type of the source material from SEI picture timing information in H.264 content.
	 *
	 * <b>Values:</b>
	 *  - 0 : Original picture scan was progressive.
	 *  - 1 : Original picture scan was interlaced.
	 *  - 2 : Original picture scan is unknown.
	 *  - 3 : Reserved.
	 *
	 */
	unsigned int 	ct_type;
	/**
	 * \brief  This is the \c nuit_field_based_flag in SEI picture timing information in H.264 content.
	 *
	 * This value can be used to calculate the clock timestamp of H.264 video frames.
	 *
	 */
	unsigned char 	nuit_field_based_flag;
	/**
	 * \brief  This is the \c counting_type value in SEI picture timing information in H.264 content.
	 *
	 *  It indicates the method of dropping values of the \c n_frames in SEI picture timing information.
	 *
	 * <b>Values:</b>
	 * 	- 0 : no dropping of \c n_frames count values and no use of \c time_offset
	 * 	- 1 : no dropping of \c n_frames count values
	 *  - 2 : dropping of individual zero values of \c n_frames count
	 *  - 3 : dropping of individual \c MaxFPS - 1 values of \c n_frames count
	 *  - 4 : dropping of the two lowest (value 0 and 1) \c n_frames counts when \c seconds_value is equal to 0 and \c minutes_value is not an integer multiple of 10
	 *  - 5 : dropping of unspecified individual \c n_frames count values
	 *  - 6 : dropping of unspecified numbers of unspecified \c n_frames count values
	 *  - 7..31 : Reserved.
	 *
	 */
	unsigned int 	counting_type;
	/**
	 * \brief  This is the \c full_timestamp_flag value in SEI picture timing information in H.264 content.
	 *
	 * <b>Values:</b>
	 *   - 0 : Indicates that the \c n_frames element is followed only by the \c seconds_flag
	 *   - 1 : Indicates that a full timestamp is included and that the \c n_frames element is followed by \c seconds_value, \c minutes_value, and \c hours_value.
	 *
	 */
	unsigned char 	full_timestamp_flag;
	/**
	 * \brief  This is the discontinuity_flag value in SEI picture timing information in H.264 content.
	 *
	 * Please see the H.264 specifications for details in how to interpret the values here.
	 *
	 * <b>Values:</b>
	 *    - 0 : Continuous clock timestamps.
	 *    - 1 : Discontinuity in clock timestamps.
	 *
	 */
	unsigned char 	discontinuity_flag;
	/**
	 * \brief  This is the \c cnt_dropped_flag value in SEI picture timing information in H.264 content.
	 *
	 *  Based on the counting method set by \c mCountingType, this value specifies that one or more values of \c mNFrames
	 *  should be skipped.
	 *
	 */
	unsigned char 	cnt_dropped_flag;
	/**
	 * \brief  This is the \c seconds_value in SEI picture timing information in H.264 content.
	 *
	 * <b>Values:</b> 0 to 59 (inclusive)
	 *
	 */
	unsigned int 	n_frames;
	/**
	 * \brief  This is the \c minutes_value in SEI picture timing information in H.264 content.
	 *
	 * <b>Values:</b> 0 to 59 (inclusive)
	 *
	 */
	unsigned int 	seconds_value;
	/**
	 * \brief  This is the \c minutes_value in SEI picture timing information in H.264 content.
	 *
	 * <b>Values:</b> 0 to 59 (inclusive)
	 *
	 */
	unsigned int 	minutes_value;
	/**\brief  This is the \c hours_value in SEI picture timing information in H.264 content.
	 *
	 * <b>Values:</b> 0 to 23 (inclusive)
	 *
	 */
	unsigned int 	hours_value;
	/**\brief  This is the \c time_offset value in SEI picture timing information in H.264 content.
	 *
	 * It can be used to determine the clock timestamp.
	 *
	 */
	int 			time_offset;
} NXPicTiming_ClockTSInfo;

typedef struct
{
	/*CPB removal delay in SEI picture timing information for H.264 content, as an unsigned integer*/
	unsigned int cpb_removal_delay;
	/*DPB removal delay in SEI picture timing information for H.264 content, as an unsigned integer*/
	unsigned int dpb_output_delay;
	/*Picture struct in SEI picture timing information for H.264 content, as an unsigned integer
		<b>Values:</b>
		* SEI_PIC_STRUCT_FRAME = 0, // * 0: frame
		* SEI_PIC_STRUCT_TOP_FIELD = 1, // * 1: top field
		* SEI_PIC_STRUCT_BOTTOM_FIELD = 2, // * 2: bottom field
		* SEI_PIC_STRUCT_TOP_BOTTOM = 3, // * 3: top field, bottom field, in that order
		* SEI_PIC_STRUCT_BOTTOM_TOP = 4, // * 4: bottom field, top field, in that order
		* SEI_PIC_STRUCT_TOP_BOTTOM_TOP = 5, // * 5: top field, bottom field, top field repeated, in that order
		* SEI_PIC_STRUCT_BOTTOM_TOP_BOTTOM = 6, // * 6: bottom field, top field, bottom field repeated, in that order
		* SEI_PIC_STRUCT_FRAME_DOUBLING = 7, // * 7: frame doubling
		* SEI_PIC_STRUCT_FRAME_TRIPLING = 8 // * 8: frame tripling
	*/
	unsigned int pic_struct;
	/*The number of clock TS in SEI picture timing information for H.264 content, as an unsigned integer*/
	unsigned int NumClockTS;
	
	NXPicTiming_ClockTSInfo TSInfo[3];
	
	/*Presentation time stamp, as an unsigned integer*/
	unsigned int uiPTS;
	/*Decoding time stamp, as an unsigned integer*/
	unsigned int uiDTS;
	
} NXPicTimingInfo;

#endif
