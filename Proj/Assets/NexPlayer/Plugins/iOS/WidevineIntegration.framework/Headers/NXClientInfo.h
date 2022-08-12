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


#ifdef __cplusplus
extern "C" {
#endif
	
@interface NXClientInfo:NSObject

/** 
 * \ingroup property
 * \brief This property indicates the product name. For example, NexPlayerSample; Default value is \c Unknown.
 * \since version 5.29
 */
@property (nonatomic) NSString* productName;

/** 
 * \ingroup property
 * \brief This property indicates the company name. For example, NexPlayer; Default value is \c Unknown.
 * \since version 5.29
 */
@property (nonatomic) NSString* companyName;

/** 
 * \ingroup property
 * \brief This property indicates the device name. For example, iPhone; Default value is \c Unknown.
 * \since version 5.29
 */
@property (nonatomic) NSString* deviceName;

/** 
 * \ingroup property
 * \brief This property indicates the model name. For example, 6+; Default value is \c Unknown.
 * \since version 5.29
 */
@property (nonatomic) NSString* modelName;

/** 
 * \ingroup property
 * \brief This property indicates the architecture name. For example, ARM64; Default value is \c Unknown.
 * \since version 5.29
 */
@property (nonatomic) NSString* archName;

/** 
 * \ingroup property
 * \brief This property indicates the build information. For example, 1.0; Default value is \c Unknown.
 * \since version 5.29
 */
@property (nonatomic) NSString* buildInfo;

/**
 * \ingroup property
 * \brief This property enables the logging for widevine module; Default value is false
 */
@property (nonatomic) BOOL logging;


/** 
 * \brief This is the designated initializer of \c ClientInfo.
 * 
 * \since version 5.29
 */
- (id) init;

@end
	
#ifdef __cplusplus
}
#endif
