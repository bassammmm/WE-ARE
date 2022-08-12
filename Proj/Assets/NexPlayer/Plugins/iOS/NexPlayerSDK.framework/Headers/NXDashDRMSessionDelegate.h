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

/** For internal use only.  Please do not use. */
@protocol NXDashDRMSessionDelegate

/** For internal use only.  Please do not use. */
- (int) DashDRMSessionOpen:(NXPlayer*)player
		  drmSessionHandle:(long long*)pSH
				   drmInfo:(char*)pDRMInfo
			   pDRMInfoLen:(unsigned int)dwDrmInfoSize;

/** For internal use only.  Please do not use. */
- (int) DashDRMSessionClose:(NXPlayer*)player
		   drmSessionHandle:(long long)hSH;

/** For internal use only.  Please do not use. */
- (int) DashDRMSessionSetCencBox:(NXPlayer*)player
					drmSessionHandle:(long long)hSH
							 boxName:(char*)pBoxName
							 boxData:(char*)pBoxData
							  boxLen:(unsigned int)dwBoxDataSize;

/** For internal use only.  Please do not use. */
-(int) DashDRMSessionDecryptIsobmffFrame:(NXPlayer*)player
						drmSessionHandle:(long long)hSH
						   initialVector:(char*)pIV
						initialVectorLen:(unsigned int)dwIVLen
								encFrame:(char*)pEncFrame
							 encFrameLen:(unsigned int)dwEncFrameLen
								decFrame:(char*)pDecFrame
							 decFrameLen:(unsigned int*)pdwDecFrameLen;

@end
