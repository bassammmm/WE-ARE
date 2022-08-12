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
#import "NXTypes.h"
#import "NXPlayer.h"

/**
 * \brief   Provides replacements for standard operating system file I/O
 *          functions.
 *
 * If you are playing back local content that is not available via the standard
 * operating system file APIs, you can provide your own replacement functions which
 * NexPlayer&trade;&nbsp;will use for opening and reading your file.
 *
 * To provide your own replacement funtions, create a class that implements this
 * protocol, and assign an instance of that class to NXPlayer::remoteFileIOInterface
 *
 */
@protocol NXRemoteFileIOInterface <NSObject>

/**
 * \brief   Replacement for open()
 *
 * This should open the requested file in the requested mode, and return
 * a handle to the file.  The handle may be any value that this instance of
 * NXRemoteFileIOInterface can use to identify the open file.
 *
 * \param filename  The path and filename of the file to open.
 * \param mode      NXFileModeRead, NXFileModeWrite, NXFileModeReadWrite or
 *                  NXFileModeCreate.
 * \return          The handle to the file.
 */
- (NXFileHandle)remoteFileOpen:(char*)filename
						  mode:(NXFileMode)mode;

/**
 * \brief   Replacement for close()
 *
 * This should close the requested file and invalidate the handle.
 *
 * \param hFile     The handle of the file to be closed (as returned by
 *                  NXRemoteFileIOInterface::remoteFileOpen:mode:)
 * \return          0 for success, -1 if an error occurred.
 */
- (int)remoteFileClose:(NXFileHandle)hFile;

/**
 * \brief   Replacement for read()
 *
 * This should read the specified number of bytes from the file.  Unless
 * the end of the file has been reached, at least one byte must be read (to
 * avoid confusion with an end-of-file condition).
 *
 * \param hFile     The handle of the file to read from (as returned by
 *                  NXRemoteFileIOInterface::remoteFileOpen:mode:)
 * \param buffer    A buffer to receive the bytes read from the file.
 * \param length    The number of bytes to read.
 *
 * \return          The actual number of bytes read; 0 if the end of the 
 *                  file was reached; -1 if an error occurred.
 */
- (ssize_t)remoteFileRead:(NXFileHandle)hFile
				   buffer:(void*)buffer
				   length:(NSUInteger)length;

/**
 * \brief   Replacement for lseek()
 *
 * This should move the current read/write offset to the specified position.
 *
 * \param hFile     The handle of the file for which to adjust the read/write
 *                  offset (as returned by
 *                  NXRemoteFileIOInterface::remoteFileOpen:mode:)
 * \param offset    The offset (from origin) by which to move the current read/write offset.
 * \param origin    The position which the \c offset parameter is measured relative
 *                  to.  May be NXFileSeekOriginBeginning, NXFileSeekOriginCurrent or
 *                  NXFileSeekOriginEnd.
 * \return          The new position within the file.
 */
- (int)remoteFileSeek:(NXFileHandle)hFile
			   offset:(int)offset
			   origin:(NXFileSeekOrigin)origin;

/**
 * \brief   Same as NXRemoteFileIOInterface::remoteFileSeek:offset:origin: except
 *          that 64-bit values are used for the offset and return value, allowing
 *          support of files greater than 2GB in size.
 *
 * This should move the current read/write offset to the specified position.
 *
 * \param hFile     The handle of the file for which to adjust the read/write
 *                  offset (as returned by
 *                  NXRemoteFileIOInterface::remoteFileOpen:mode:)
 * \param offset    The offset (from origin) by which to move the current read/write offset.
 * \param origin    The position which the \c offset parameter is measured relative
 *                  to.  May be NXFileSeekOriginBeginning, NXFileSeekOriginCurrent or
 *                  NXFileSeekOriginEnd.
 * \return          The new position within the file.
 */
- (long long)remoteFileSeek64:(NXFileHandle)hFile
                       offset:(long long)offset
                       origin:(NXFileSeekOrigin)origin;

/**
 * \brief   Replacement for write()
 *
 * This should write the specified number of \c bytes to the file.
 *
 * \param hFile     The handle of the file to write to (as returned by
 *                  NXRemoteFileIOInterface::remoteFileOpen:mode:)
 * \param buffer    A buffer of \c bytes to write to the file.
 * \param length    The number of \c bytes to write to file.
 *
 * \return          The actual number of \c bytes written, or -1 if an error occurred.
 */
- (ssize_t)remoteFileWrite:(NXFileHandle)hFile
					buffer:(void*)buffer
					length:(NSUInteger)length;

/**
 * \brief   Replacement for getting the size of a file.
 *
 * This should return the size of the file <em>without</em> modifying
 * the position to which the file has been seeked (if the seek location must
 * be moved to determine the size, this function should move it back afterwards).
 *
 * \param hFile     The handle of the file (as returned by
 *                  NXRemoteFileIOInterface::remoteFileOpen:mode:)
 * \return          The actual number of \c bytes of file, or -1 if an error occurred. 
 */
- (long long)remoteFileSize:(NXFileHandle)hFile;

@end
