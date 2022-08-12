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


/**
 * \brief A singleton class containing version information
 *        about the NexPlayer&trade;&nbsp;SDK.
 *
 * There is only one object of this class, and it is accessed using:
 * \code
	NXSDKVersion *version = [NXSDKVersion sharedInstance];
 * \endcode
 * 
 * Attempts to call \c alloc on this class or \c init on instances of it
 * will fail.
 *
 * The NXSDKVersion instance has properties describing the current
 * version.  The recommended method of displaying the current version
 * at build time is as follows:
 *
 * \code
 NXSDKVersion *version = [NXSDKVersion sharedInstance];
 NSString *buildTimeAndVersion =
	[NSString stringWithFormat: @"%@ %@ %@ %@", 
		version.versionString,
		version.buildDate,
		version.buildTime,
		version.buildTimeZone];
 NSLog( @"Version: %@", buildTimeAndVersion );
 * \endcode
 */
@interface NXSDKVersion : NSObject {
}

@property (nonatomic,readonly) int major;					///< The major version number; this is incremented when major changes are made to the API that may affect compatibility or when significant new functionality is introduced.
@property (nonatomic,readonly) int minor;					///< The minor version number; this is incremented when minor functional changes are made in the API.
@property (nonatomic,readonly) int patch;					///< The patch version number; this is incremented when changes are made that do not affect the basic feature set or API (for example, bug fixes).
@property (nonatomic,readonly) int build;					///< The build number; this is used internally to distinguish different builds with the same version number
@property (weak, nonatomic,readonly) NSString *buildDate;			///< The date when this version was built.  This is a string in the form, "YYYY-MM-DD"
@property (weak, nonatomic,readonly) NSString *buildTime;			///< The time when this version was built.  This is a string in the form, "HH:MM:SS" in 24-hour notation.
@property (weak, nonatomic,readonly) NSString *buildTimeZone;		///< The time zone used to generate BuildDate and BuildTime. Currently, this is always the string "UTC", but it may be changed in the future
@property (weak, nonatomic,readonly) NSString *versionString;		///< The version as a string in the format major.minor.patch.build (does not include date)
@property (weak, nonatomic,readonly) NSString *SDKName;           ///< The name of the current SDK.  This is a string the same as NXPlayer::SDKName. \since version 5.8


/**
 * \brief Returns the single shared instance of this class.
 *
 * This can be used to access the current SDK version information.
 * 
 * \returns The shared singleton instance of this class.
 *
 * \see \ref NXSDKVersion for more information.
 */
+ (NXSDKVersion*) sharedInstance;

@end
