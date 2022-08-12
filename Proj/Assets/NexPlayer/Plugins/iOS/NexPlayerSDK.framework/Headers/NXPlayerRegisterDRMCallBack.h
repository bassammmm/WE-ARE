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


#ifndef NXPlayerRegisterDRMCallBack_h
#define NXPlayerRegisterDRMCallBack_h


#define CB_RET_SUCCESS (0)
#define CB_RET_ERROR  (-1)

//#ifdef __cplusplus
//extern "C"
//{
//#endif

typedef void* NEXPLAYERENGINE_handle;

	
//========================================================================================================
#pragma mark - function interface

	/** \defgroup cbtypes Callback Types
	 * \defgroup apifunc C-level API Functions
	 * \ingroup cbtypes
	 * \brief   Callback function for descrambling HLS-TS encrypted content (HTTP
	 *          Live Streaming content encrypted at the segment level).
	 *
	 * This callback is called every time an HLS segment is received.  The segment
	 * may be either a TS file or an audio file.  The player does not attempt to
	 * detect whether or not a segment is encrypted, but rather passes all segments
	 * directly to the callback, if one is registered.
	 *
	 * \param[in]  pInputBuffer         The segment (TS file or audio file) that
	 *                                  has been received.
	 *
	 * \param[in]  uiInputBufferSize    The size of the data at pInputBuffer, in \c bytes.
	 *
	 * \param[out] pOutputBuffer        The location at which to place the descrambled
	 *                                  output data.  This may point to the same
	 *                                  location as the input buffer, or it may point
	 *                                  to a separate location. The size available for
	 *                                  the output buffer is the same as the size of
	 *                                  the input buffer.  That is, the decrypted data
	 *                                  may be smaller than the encrypted data, but
	 *                                  not larger.
	 *
	 * \param[out] puiOutputBufferSize  The size of the decrypted data.  The callback
	 *                                  must set this value.  This may be equal to or
	 *                                  smaller than \c uiInputBufferSize, but not larger.
	 *
	 * \param[in]  pMediaFileURL        The URL of the segment media file (TS file or
	 *                                  audio file).
	 *
	 * \param[in]  pPlaylistURL         The URL of the immediate parent playlist (the
	 *                                  playlist directly referecing the media file).
	 *
	 * \param[in]  pUserData            The user data passed when the callback was
	 *                                  originally registered.
	 *
	 * \returns                         The callback should return zero if the data
	 *                                  was successfully descrambled.  In the case of
	 *                                  an error, it should return -1.
	 */
	typedef unsigned int  ( *NEXPLAYERHLSTSDescrambleCallbackFunc ) (unsigned char* pInputBuffer,
																	 unsigned int   uiInputBufferSize,
																	 unsigned char* pOutputBuffer,
																	 unsigned int*  puiOutputBufferSize,
																	 void*          pMediaFileURL,
																	 void*          pPlaylistURL,
																	 void*          pUserData);

/**
 * \ingroup cbtypes
 * \brief   Callback function for receiving updates to the HLS playlist data.
 *
 *
 * This is called every time that the player receives an HLS playlist.  This
 * can happen in several cases:
 *
 * - When the initial (master) playlist is received
 * - When the player switches to a new track and loads the playlist for that track
 * - While playing live content, if the server updates the playlist
 *
 * Whenever ::NEXPLAYERHLSTSDescrambleCallbackFunc is called with a TS or audio
 * file to be descrambled, that TS or audio file will always be from the
 * playlist most recently received by this callback.
 *
 * \param[in]  pUrl                 The URL of the playlist.
 *
 * \param[in]  pPlaylist            The contents of the playlist, as \c text.
 *
 * \param[in]  uiPlaylistSize       The size of pPlayList, in \c bytes, not including any terminating \c NULL.
 *
 * \param[in]  pUserData            The user data passed when the callback was
 *                                  originally registered.
 *
 * \returns                         The callback should return zero for success
 *                                  and -1 in case of an error.
 */
typedef unsigned int (*NEXPLAYERGetPlaylistInfoCallbackFunc)(char* pUrl,
															 char* pPlaylist,
															 unsigned int uiPlaylistSize,
															 void* pUserData);

/**
 * \ingroup cbtypes
 * \brief  Callback function to handle content with an encrypted playlist or manifest.
 *
 * NexPlayer&trade;&nbsp;calls this function whenever it receives the manifest or top level of a playlist so
 * that the playlist or manifest can be decrypted (in the case it happens to be encrypted).
 *
 * \param[in]	pMpdUrl			The original URL of the top-level MPD.  In the case of
 *								redirection, this will be the URL <em>before</em>
 *								redirection.
 * \param[in]	dwMpdUrlLen		The length of the manifest or playlist URL, in \c bytes.
 * \param[in,out] pMpd			The top level playlist or manifest.
 * \param[in]	dwMpdLen		The size of the manifest or playlist, in \c bytes.
 * \param[out] pdwNewMpdLen	The size of the decrypted manifest or playlist.
 * \param[in] pUserData		The user data passed when the callback was registered.
 *
 * \returns                         The callback should return zero for success
 *                                  and -1 in case of an error.
 *
 */
typedef int(*NEXPLAYERMPDDescrambleCallbackFunc)(char*				pMpdUrl,
												 unsigned int		dwMpdUrlLen,
												 char*				pMpd,
												 unsigned int		dwMpdLen,
												 unsigned int*		pdwNewMpdLen,
												 void*				pUserData);

/**
 * \ingroup cbtypes
 * \brief Callback function for receiving AES128 encrypted HLS content.
 *
 * When registered, this callback function is called every time AES128 encrypted HLS content is received.
 *
 * \param[in] pInBuf			A pointer to the input buffer.
 * \param dwInBufSize			The size of the input buffer, in \c bytes.
 * \param[out] pOutBuf			A pointer to the output buffer where decrypted content is stored.
 * \param[out] pdwOutBufSize	A pointer to the size of the decrypted segment, in \c bytes.
 * \param[in]  pSegmentUrl		A pointer to the URL of the segment of content.
 * \param[in]  pMpdUrl			A pointer to the original URL of the content playlist.
 * \param[in]  pKeyAttr			A pointer to the decryption Key information.
 * \param[in]  dwSegmentSeq		The sequence number of the TS segment file.
 * \param[in]  pKey				A pointer to the decryption Key.  This parameter is only meaningful when \c dwKeySize is greater than 0 (i.e. a key has been downloaded).
 * \param  dwKeySize			The size of the decryption Key.  This parameter will be zero if no key has been downloaded.
 * \param[in]  pUserData		The user data passed when the callback was registered.
 *
 * \returns                     The callback should return zero for success
 *                              and -1 in case of an error.
 *
 */
typedef int (*NEXPLAYERHLSAES128DescrambleCallbackFunc)(unsigned char*				pInBuf,			// [in] Input segment.
														unsigned int				dwInBufSize,	// [in] Input segment size.
														unsigned char*				pOutBuf,		// [out] decrypted segment.
														unsigned int*				pdwOutBufSize,	// [out] The size of decrypted segment.
														char*						pSegmentUrl,	// [in] Segment URL.
														char*						pMpdUrl,		// [in] Original URL of the currently playing MPD.
														char*						pKeyAttr,		// [in] KeyInfo Attribute of the Segment.
														unsigned int				dwSegmentSeq,	// [in] The sequence number of the TS segment file.
														unsigned char*				pKey,			// [in] Key. (Has meaning only when dwKeySize is bigger than 0)
														unsigned int				dwKeySize,		// [in] Key size. (0 if no key is downloaded.)
														void*						pUserData);		// [in] UserData

/**
 *
 *  \ingroup cbtypes
 * \brief Callback function for receiving AES128 encrypted HLS content with byte range.
 *
 * When registered, this callback function is called every time AES128 encrypted HLS content is received.
 *
 * \param[in] pInBuf            A pointer to the input buffer.
 * \param dwInBufSize           The size of the input buffer, in \c bytes.
 * \param[out] pOutBuf          A pointer to the output buffer where decrypted content is stored.
 * \param[out] pdwOutBufSize    A pointer to the size of the decrypted segment, in \c bytes.
 * \param[in]  pSegmentUrl      A pointer to the URL of the content segment.
 * \param[in]  qByteRangeOffset The offset of the byte range.
 * \param[in]  qByteRangeLength The length of the byte range.
 * \param[in]  pMpdUrl          A pointer to the original URL of the content playlist.
 * \param[in]  pKeyAttr         A pointer to the decryption Key information.
 * \param[in]  dwSegmentSeq     The sequence number of the TS segment file.
 * \param[in]  pKey             A pointer to the decryption Key.  This parameter is only meaningful when \c dwKeySize is greater than 0 (i.e. a key has been downloaded).
 * \param  dwKeySize            The size of the decryption Key.  This parameter will be zero if no key has been downloaded.
 * \param[in]  pUserData        The passed user data when the callback was registered.
 *
 * \returns                     The callback should return zero for success
 *                              and -1 in case of an error.
 *
 * \since version 5.29
 */
typedef int (*NEXPLAYERHLSAES128DescrambleWithByteRangeCallbackFunc)(unsigned char*			pInBuf,				// [in] Input segment.
																	 unsigned int			dwInBufSize,		// [in] Input segment size.
																	 unsigned char*			pOutBuf,			// [out] decrypted segment.
																	 unsigned int*			pdwOutBufSize,		// [out] The size of decrypted segment.
																	 char*					pSegmentUrl,		// [in] Segment URL.
																	 long long				qByteRangeOffset,	// [in] If qByteRangeOffset is -1, then it means that byte range is not used.
																	 long long				qByteRangeLength,	// [in] If qByteRangeLength is 0, then it means that byte range is not used.
																	 char*					pMpdUrl,			// [in] Original URL of the currently playing MPD.
																	 char*					pKeyAttr,			// [in] KeyInfo Attribute of the Segment.
																	 unsigned int			dwSegmentSeq,		// [in]
																	 unsigned char*			pKey,				// [in] Key. (Has meaning only when dwKeySize is bigger than 0)
																	 unsigned int			dwKeySize,			// [in] Key size. (0 if no key is downloaded.)
																	 void*					pUserData);			// [in]

/**
 *
 * \ingroup cbtypes
 * \brief   Callback function that verifies whether or not a key attribute is supported by the DRM module.
 *
 * This callback is called when NexPlayer&trade;&nbsp; meets #EXT-X-KEY tags while NexPlayer&trade;&nbsp; is parsing
 * playlists. If the callback returns a non-zero value, NexPlayer&trade;&nbsp; will not call DRM functions even if that function is registered.
 *
 * \param[in]  pMpdUrl         The URL of the playlist.
 *
 * \param[in]  pKeyAttr        Key information of the segment that has been received.
 *
 * \param[in]  pUserData       The user data passed when the callback was
 *                             originally registered.
 *
 * \returns                    If the DRM is supporting that key attribute, then it should return <b>zero(0)</b>.
 *                             Then NexPlayer&trade;&nbsp; will call DRM callbacks depending on the encryption method.
 *                             If the DRM does not support the key, then it should return a <b>non-zero value</b>.
 *                             In this case, NexPlayer&trade;&nbsp; will not call the DRM callbacks and it will decrypt using its internal decryption function.
 *
 */
typedef int (*NEXPLAYERHLSIsSupportKeyCallbackFunc) (char*		pMpdUrl,		// [in] Original URL of the currently playing \c MPD.
													 char*		pKeyAttr,		// [in] KeyInfo Attribute of the Segment.
													 void*		pUserData);

/**
 * \ingroup cbtypes
 * \brief   Callback function for descrambling PlayReady encrypted content in a PIFF file.
 *
 * \param[in]  pInputBuffer         The encrypted data to be descrambled.
 *
 * \param[in]  dwInputBufferSize    The size of the encrypted data, in \c bytes.
 *
 * \param[out] pOutputBuffer        The location at which to place the descrambled
 *                                  output data.  This may point to the same
 *                                  location as the input buffer, or it may point
 *                                  to a separate location. The size available for
 *                                  the output buffer is the same as the size of
 *                                  the input buffer.  That is, the decrypted data
 *                                  may be smaller than the encrypted data, but
 *                                  not larger.
 *
 * \param[out] pdwOutputBufferSize  The size of the decrypted data.  The callback
 *                                  must set this value.  This may be equal to or
 *                                  smaller than \c dwInputBufferSize, but not larger.
 *
 * \param[in]  pSampleEncBox        The \c SampleEncryptionBox, as detailed in the
 *                                  <em>[MS-SSTR] Smooth Streaming Protocol Specification</em>.
 *
 * \param[in]  dwSampleEncBoxLen    The length, in \c bytes, of the data at \c pSampleEncBox.
 *
 * \param[in]  dwSampleIDX          The index of the media object (frame or sample, depending
 *                                  on media format) being descrambled.
 *
 * \param[in]  dwTrackID            Media Track ID, from \c TfhdBox, as defined in the
 *                                  <em>[MS-SSTR] Smooth Streaming Protocol Specification</em>.
 *
 * \param[in]  pUserData            The user data passed when the callback was
 *                                  originally registered.
 *
 * \returns                         The callback should return zero if the data
 *                                  was successfully descrambled.  In the case of
 *                                  an error, it should return -1.
 */
typedef int ( *NEXPLAYERPiffPlayReadyDescrambleCallbackFunc ) ( unsigned char*   pInputBuffer,
																unsigned int     dwInputBufferSize,
																unsigned char*   pOutputBuffer,
																unsigned int*    pdwOutputBufferSize,
																unsigned char*   pSampleEncBox,
																unsigned int     dwSampleEncBoxLen,
																unsigned int     dwSampleIDX,
																unsigned int     dwTrackID,
																void*            pUserData);

/**
 * \ingroup cbtypes
 *
 * \brief Callback function to open DASH DRM Session.
 *
 * \param[out] pSH          DRM session handle. The initial value is -1 which indicates that DRM Session is not opened, therefore \c NEXPLAYERDashDrmSessionCloseCallbackFunc will not be called.
 * \param[in] pDrmInfo      Contains all the ContentProtection tags in MPD.
 * \param[in] dwDrmInfoSize The \c byte length of \c pDrmInfo.
 * \param[in] pUserData   The user data passed when the callback was registered.
 *
 */
typedef int (*NEXPLAYERDashDrmSessionOpenCallbackFunc) (long long*		pSH,
														char*			pDrmInfo,
														unsigned int	dwDrmInfoSize,
														void*			pUserData);

/**
 * \ingroup cbtypes
 *
 * \brief Callback function to close DASH DRM Session.
 * This function will only be called when the parameter \c pSH of \c NEXPLAYERDashDrmSessionOpenCallbackFunc is not -1.
 *
 * \param[in] hSH         DRM session handle.
 * \param[in] pUserData The user data passed when the callback was registered.
 *
 */
typedef int (*NEXPLAYERDashDrmSessionCloseCallbackFunc)	(long long	hSH,
														 void*		pUserData);

/**
 * \ingroup cbtypes
 *
 * \brief Callback function to transfer CencBox.
 *
 * \param[in] hSH            DRM session handle.
 * \param[in] pBoxName       The box name as a NULL-terminated string : \c seig, \c tenc or \c pssh.
 * \param[in] pBoxData       The payload information of the box.
 * \param[in] dwBoxDataSize  \c Byte length of \c pBoxData.
 * \param[in] pUserData      The user data passed when the callback was registered.
 *
 */
typedef int (*NEXPLAYERDashDrmSessionSetCencBoxCallbackFunc) (long long			hSH,
															  char*				pBoxName,
															  char*				pBoxData,
															  unsigned int		dwBoxDataSize,
															  void*				pUserData);

/**
 * \ingroup cbtypes
 *
 * \brief Callback function to decrypt an encrypted frame.
 *
 * \param[in] hSH               DRM Session handle.
 * \param[in] pIV               Initial vector.
 * \param[in] dwIVLen           \c Byte length of initial vector.
 * \param[in] pEncFrame         Encrypted frame.
 * \param[in] dwEncFrameLen     \c Byte length of encrypted frame.
 * \param[out] pDecFrame        Decrypted frame.
 * \param[out] pdwDecFrameLen   \c Byte length of decrypted frame.
 * \param[in] pUserData         The user data passed when the callback was registered.
 *
 *
 */
typedef int (*NEXPLAYERDashDrmSessionDecryptIsobmffFrameCallbackFunc) (long long			hSH,
																		char*				pIV,
																		unsigned int		dwIVLen,
																		char*				pEncFrame,
																		unsigned int		dwEncFrameLen,
																		char*				pDecFrame,
																		unsigned int*		pdwDecFrameLen,
																		void*				pUserData);

/**
 *
 *  \ingroup cbtypes
 *  \brief Callback function for receiving blocks of Progressive Download(PD) content.
 *
 *  This is called each time NexPlayer&trade;&nbsp; receives a block of Progressive Download(PD) content.
 *  NexPlayer&trade;&nbsp; sends the received block and the block's size with this callback.
 *
 *  \param[in,out]  pBlockBuf   The array containing the data from the PD block.
 *  \param[in]  ulOffset        The offset of the block's starting position from the beginning of the content.
 *  \param[in]  uiBlockSize     The size of the PD block received.
 *  \param[in]  pUserData       The user data passed when the callback was registered.
 *
 *  \returns    Zero, but has no meaning and should be ignored.
 *
 **/
typedef int (*NEXPLAYERGetPDBlockCallbackFunc)( char* pBlockBuf,
												long long ulOffset,
												int uiBlockSize,
												void* pUserData);

/**
 *  \ingroup cbtypes
 *  \brief Callback function for parsing headers of Progressive Download(PD) content.
 *
 *  This is called when NexPlayer&trade;&nbsp; receives a header of Progressive Download(PD) content.
 *  NexPlayer&trade;&nbsp; sends the received header and its size with this callback.
 *
 *  \param[in]  pData			The array containing the data of the PD header.
 *  \param[in]  qOffset		    The offset of the header's starting position.
 *  \param[in]  iDataSize       The size of the PD header received.
 *  \param[in,out] puContentOffset The offset of content.
 *  \param[in]	pUserData       The user data passed when the callback was registered.
 *
 *  \returns    Success : 0 <br>
 * Need More Data : -1 <br>
 * DRM error code :  < -1 <br>
 * Remark : When it is not DRM content, return 0 with puContentOffset=0;
 **/
typedef int (*NEXPLAYERPDEnvelopHeaderParsingCallbackFunc)( char* pData,
															long long qOffset,
															int iDataSize,
															unsigned int* puContentOffset,
															void* pUserData);
//--------------------------------------------------------------------------------------------------------
/**
 * \ingroup     types
 * \brief       File handle used in <em>Remote File I/O</em> callbacks.
 *
 * This is the file handle used in calls to the various <em>Remote File I/O</em>
 * callback functions.  This value is returned by the file-open callback, and
 * can be any value that the remote file callbacks can use to uniquely
 * identify the open file instance.
 */
typedef      void*    NEXFileHandle;

/**
 * \ingroup     types
 * \brief       File open mode.
 *
 * This is passed by NexPlayer&trade;&nbsp;in calls to the
 * ::NEXPLAYERRemoteFile_OpenFt callback.
 *
 * This is a bitfield, so the constants can be combined with the bitwise-or
 * operator.
 *
 * \code
 * NEX_FILE_WRITE | NEX_FILE_CREATE // Open file for writing; create if it doesn't exist
 * NEX_FILE_READ | NEX_FILE_WRITE // Same as NEX_FILE_READWRITE
 * \endcode
 */
typedef enum _NEXFileMode
{
	/** Open for reading                                                                           */
	NEX_FILE_READ           = 1,
	/** Open for writing                                                                           */
	NEX_FILE_WRITE          = 2,
	/** Open for reading and writing                                                               */
	NEX_FILE_READWRITE      = 3,
	/** Create the file if it doesn't exist                                                        */
	NEX_FILE_CREATE         = 4
	
} NEXFileMode;

/**
 * \ingroup     types
 * \brief       Origin for Remove File I/O callback seek operations.
 *
 * \see ::NEXPLAYERRemoteFile_SeekFt
 * \see ::NEXPLAYERRemoteFile_Seek64Ft
 */
typedef enum _NEXFileSeekOrigin
{
	/** Beginning of file         */
	NEX_SEEK_BEGIN          = 0,
	/** Current position          */
	NEX_SEEK_CUR            = 1,
	/** End of file               */
	NEX_SEEK_END            = 2
	
} NEXFileSeekOrigin;

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for opening a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * \param[in]  pFileName        Path and filename of the file to be opened.  This is the path
 *                              that the application originally passed to NexPlayer&trade;, so
 *                              the application may treat it in any way appropriate in the callback.
 *
 * \param[in]  iMode            Specifies how the file is to be opened; see ::NEXFileMode for details.
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns                     The handle of the opened file, or -1 if an error occurred.
 */
typedef NEXFileHandle ( *NEXPLAYERRemoteFile_OpenFt ) ( char* pFileName, NEXFileMode iMode, void *pUserData );

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for closing a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * \param[in]  hFile            File handle (as returned by ::NEXPLAYERRemoteFile_OpenFt) of file
 *                              to be closed.
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns                     0 if successful, or -1 if an error occurred.
 */
typedef int ( *NEXPLAYERRemoteFile_CloseFt ) ( NEXFileHandle hFile, void *pUserData );

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for reading a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * The actual number of \c bytes to read is \c (uiSize * \c uiCount).
 *
 * \param[in]  hFile            File handle (as returned by ::NEXPLAYERRemoteFile_OpenFt) of file
 *                              to read from.
 *
 * \param[out] pBuf             Buffer to receive the data.
 *
 * \param[in]  uiSize           Record size, in \c bytes.
 *
 * \param[in]  uiCount          Number of records to read.
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns
 *                              - &gt;0: The number of \c bytes actually read
 *                              - 0: Reached the end of the file.
 *                              - -1: An error occurred.
 */
typedef ssize_t ( *NEXPLAYERRemoteFile_ReadFt ) ( NEXFileHandle hFile, void *pBuf, unsigned int uiSize, size_t uiCount, void *pUserData );

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for seeking a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * This sets the location in the file at which the next <em>read</em> operation
 * will occur.
 *
 * \note    This supports seek offsets of up to 32-bits.  For large offsets,
 *          ::NEXPLAYERRemoteFile_Seek64Ft will be called instead.  If the
 *          64-bit callback is not registered, file with sizes over 2GB will
 *          not be supported.
 *
 * \param[in]  hFile            File handle (as returned by ::NEXPLAYERRemoteFile_OpenFt) of file
 *                              to be seeked.
 *
 * \param[in]  iOffset          Seek destination, as an offset in \c bytes from \c iOrigin
 *
 * \param[in]  iOrigin          Origin for \c iOffset.  See ::NEXFileSeekOrigin for possible values.
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns                     New offset from beginning of file, or -1 if an error occurred.
 */
typedef int ( *NEXPLAYERRemoteFile_SeekFt ) ( NEXFileHandle hFile, int iOffset, NEXFileSeekOrigin iOrigin, void *pUserData );

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for seeking a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * This sets the location in the file at which the next <em>read</em> operation
 * will occur.
 *
 * \note    This supports seek offsets of up to 64-bits.  Implement this
 *          callback if you wish to support files over 2GB in size.
 *
 * \param[in]  hFile            File handle (as returned by ::NEXPLAYERRemoteFile_OpenFt) of file
 *                              to be seeked.
 *
 * \param[in]  iOffset          Seek destination, as an offset in \c bytes from \c iOrigin
 *
 * \param[in]  iOrigin          Origin for \c iOffset.  See ::NEXFileSeekOrigin for possible values.
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns                     New offset from beginning of file, or -1 if an error occurred.
 */
typedef long long ( *NEXPLAYERRemoteFile_Seek64Ft ) ( NEXFileHandle hFile, long long iOffset, NEXFileSeekOrigin iOrigin, void *pUserData );

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for writing to a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * \param[in]  hFile            File handle (as returned by ::NEXPLAYERRemoteFile_OpenFt) of file
 *                              to be written to.
 *
 * \param[in]  pBuf             The data to write to file
 *
 * \param[in]  dwSize           The number of \c bytes to write to file
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns                     The actual number of \c bytes written, or -1 if an error occurred.
 */
typedef ssize_t ( *NEXPLAYERRemoteFile_WriteFt ) ( NEXFileHandle hFile, char* pBuf, size_t dwSize, void *pUserData );

/**
 * \ingroup cbtypes
 * \brief   Remote File I/O callback for getting the size of a file.
 *
 * This is one of several callback functions that can be registered using
 * the \ref rfio Interface in order to replace the system
 * calls normally used for opening and accessing files.
 *
 * This callback should return the size of the file <em>without</em> modifying
 * the position to which the file has been seeked (if the seek location must
 * be moved to determine the size, this function should move it back afterwards).
 *
 * \param[in]  hFile            File handle (as returned by ::NEXPLAYERRemoteFile_OpenFt) of the ile
 *                              for which the size should be retrieved.
 *
 * \param[in]  pUserData        The user data passed when the callback was
 *                              originally registered.
 *
 * \returns                     The actual number of \c bytes written, or -1 if an error occurred.
 */
typedef long long ( *NEXPLAYERRemoteFile_SizeFt ) ( NEXFileHandle hFile, void *pUserData );


/**
 * \ingroup     types
 * \brief       A structure holding function pointers to all of the functions that
 *              comprise the Remote File I/O interface.
 *
 * This structure provides replacements for the standard operating system file I/O functions.
 * Basically, to play back local content that is not available via the standard operating system file APIs,
 * all calls to open or read from the file are directed to the function pointers in this structure instead.
 *
 * This structure is passed to the \ref rfio Interface
 * when registering the callbacks.
 *
 * More information about each function pointer can be found in the documentation.
 *
 * \see  ::NEXPLAYERRemoteFile_OpenFt
 * \see  ::NEXPLAYERRemoteFile_CloseFt
 * \see  ::NEXPLAYERRemoteFile_ReadFt
 * \see  ::NEXPLAYERRemoteFile_SeekFt
 * \see  ::NEXPLAYERRemoteFile_Seek64Ft
 * \see  ::NEXPLAYERRemoteFile_WriteFt
 * \see  ::NEXPLAYERRemoteFile_SizeFt
 */
typedef struct NEXPLAYERRemoteFileIOInterface_
{
	/** Open callback (see ::NEXPLAYERRemoteFile_OpenFt) */
	NEXPLAYERRemoteFile_OpenFt      Open;
	/** Close callback (see ::NEXPLAYERRemoteFile_CloseFt) */
	NEXPLAYERRemoteFile_CloseFt     Close;
	/** Read callback (see ::NEXPLAYERRemoteFile_ReadFt) */
	NEXPLAYERRemoteFile_ReadFt      Read;
	/** Seek callback (see ::NEXPLAYERRemoteFile_SeekFt) */
	NEXPLAYERRemoteFile_SeekFt      Seek;
	/** Seek64 callback (see ::NEXPLAYERRemoteFile_Seek64Ft) */
	NEXPLAYERRemoteFile_Seek64Ft    Seek64;
	/** Write callback (see ::NEXPLAYERRemoteFile_WriteFt) */
	NEXPLAYERRemoteFile_WriteFt     Write;
	/** Size callback (see ::NEXPLAYERRemoteFile_SizeFt)  */
	NEXPLAYERRemoteFile_SizeFt      Size;
} NEXPLAYERRemoteFileIOInterface;


//========================================================================================================
#pragma mark - functions for registery

/**
 * \ingroup apifunc
 * \brief Registers an HLS/TS descrambling callback function.
 *
 * \param	hEngine		The handle of the NexPlayer&trade;&nbsp; engine.
 * \param[in]  pDescrambleCallbackFunc  Callback function to register
 *
 * \param[in]  pUserData                Additional data to pass to the callback function when it is called.
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERHLSTSDescrambleCallbackFunc NEXPLAYERHLSTSDescrambleCallbackFunc\endlink
 */
void 	NEXPLAYEREngine_registerHLSTSDescrambleCallBackFunc(NEXPLAYERENGINE_handle hEngine,
															NEXPLAYERHLSTSDescrambleCallbackFunc pDescrambleCallbackFunc,
															void *pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a callback function to receive HLS playlist content every time a new HLS playlist is received.
 *
 * \param		hEngine		The handle of the NexPlayer&trade;&nbsp;engine.
 * \param[in]  	pGetPlaylistInfoCallbackFunc     Callback function to register
 *
 * \param[in]  	pUserData                Additional data to pass to callback function when it is called
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERGetPlaylistInfoCallbackFunc NEXPLAYERGetPlaylistInfoCallbackFunc\endlink
 */
void		NEXPLAYEREngine_registerGetPlaylistInfoFuncCallBackFunc(NEXPLAYERENGINE_handle hEngine,
																	NEXPLAYERGetPlaylistInfoCallbackFunc pGetPlaylistInfoCallbackFunc,
																	void *pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a callback function to handle encrypted manifests or playlists in content.
 *
 * \param 		hEngine					The handle of the NexPlayer&trade;&nbsp; engine.
 * \param[in] 	pDescrambleCallbackFunc	Callback function to register.
 * \param[in]	pUserData				Additional data to pass to callback function when it is called.
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERMPDDescrambleCallbackFunc NEXPLAYERMPDDescrambleCallbackFunc\endlink
 *
 */
void NEXPLAYEREngine_registerMPDDescrambleCallbackFunc(NEXPLAYERENGINE_handle hEngine,
													   NEXPLAYERMPDDescrambleCallbackFunc pDescrambleCallbackFunc,
													   void* pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a callback function to handle AES128 encrypted HLS content.
 *
 * \param		hEngine		The handle of the NexPlayer&trade;&nbsp; engine.
 * \param[in]	pDescrambleCallbackFunc  Callback function to register.
 * \param[in]	pUserData	Additional data to pass to callback function when it is called.
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERHLSAES128DescrambleCallbackFunc NEXPLAYERHLSAES128DescrambleCallbackFunc\endlink
 *
 */
void NEXPLAYEREngine_registerHLSAES128DescrambleCallbackFunc(NEXPLAYERENGINE_handle hEngine,
															 NEXPLAYERHLSAES128DescrambleCallbackFunc pDescrambleCallbackFunc,
															 void* pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a callback function to handle AES128 encrypted HLS content with ByteRange.
 *
 * \param		hEngine		The handle of the NexPlayer&trade;&nbsp; engine.
 * \param[in]	pDescrambleCallbackFunc  Callback function to register.
 * \param[in]	pUserData	Additional data to pass to callback function when it is called.
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERHLSAES128DescrambleWithByteRangeCallbackFunc NEXPLAYERHLSAES128DescrambleWithByteRangeCallbackFunc\endlink
 *
 */
void NEXPLAYEREngine_registerHLSAES128DescrambleWithByteRangeCallbackFunc(NEXPLAYERENGINE_handle hEngine,
																		  NEXPLAYERHLSAES128DescrambleWithByteRangeCallbackFunc pDescrambleCallbackFunc,
																		  void* pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a callback function that verifies whether or not a key attribute is supported by the DRM module.
 *
 * \param		hEngine             The handle of the NexPlayer&trade;&nbsp;engine.
 * \param[in]	pHLSIsSupportKey    Callback function to register.
 * \param[in]	pUserData           Additional data to pass to the callback function when it is called.

 */
void NEXPLAYEREngine_registerHLSIsSupportKeyCallbackFunc(NEXPLAYERENGINE_handle hEngine,
														 NEXPLAYERHLSIsSupportKeyCallbackFunc pHLSIsSupportKeyCallbackFunc,
														 void* pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a PIFF PlayReady descrambling callback function.
 *
 * \param		hEngine		The handle of the NexPlayer&trade;&nbsp;engine.
 * \param[in]   pDescrambleCallbackFunc  Callback function to register
 *
 * \param[in]   pUserData    Additional data to pass to callback function when it is called.
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERPiffPlayReadyDescrambleCallbackFunc NEXPLAYERPiffPlayReadyDescrambleCallbackFunc\endlink
 */
void 	NEXPLAYEREngine_registerPIFFPlayReadyDescrambleCallBackFunc(NEXPLAYERENGINE_handle hEngine,
																	NEXPLAYERPiffPlayReadyDescrambleCallbackFunc pDescrambleCallbackFunc,
																	void *pUserData);

//-----------------------------------------------------------------------------
//DashDRM
void NEXPLAYEREngine_registerDashDRMSessionOpenCallbackFunc(NEXPLAYERENGINE_handle hEngine,
															NEXPLAYERDashDrmSessionOpenCallbackFunc pOpenCallbackFunc,
															void *pUserData);

void NEXPLAYEREngine_registerDashDRMSessionCloseCallbackFunc(NEXPLAYERENGINE_handle hEngine,
															 NEXPLAYERDashDrmSessionCloseCallbackFunc pCloseCallbackFunc,
															 void *pUserData);

void NEXPLAYEREngine_registerDashDRMSessionSetCencBoxCallbackFunc(NEXPLAYERENGINE_handle hEngine,
																  NEXPLAYERDashDrmSessionSetCencBoxCallbackFunc pSetCencBoxCallbackFunc,
																  void* pUserData);

void NEXPLAYEREngine_registerDashDRMSessionDecryptIsobmffFrameCallbackFunc(NEXPLAYERENGINE_handle hEngine,
																		   NEXPLAYERDashDrmSessionDecryptIsobmffFrameCallbackFunc pDecryptIsobmffFrameCallbackFunc,
																		   void *pUserData);
//-----------------------------------------------------------------------------

/**
 * \ingroup apifunc
 * \brief Registers a callback function to receive a pointer for Progressive Download(PD) block and block's size. PD data is decrypted using this information.
 *
 * \param	 	hEngine				The handle of the NexPlayer&trade;&nbsp;engine.
 * \param[in]  	pGetPDBlockCallbackFunc    	Callback function to register.
 *
 * \param[in]  	pUserData          	Additional data to pass to callback function when it is called.
 *
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERGetPDBlockCallbackFunc NEXPLAYERGetPDBlockCallbackFunc\endlink
 */
void		NEXPLAYEREngine_registerGetPDBlockCallBackFunc(NEXPLAYERENGINE_handle hEngine,
														   NEXPLAYERGetPDBlockCallbackFunc pGetPDBlockCallbackFunc,
														   void *pUserData);

/**
 * \ingroup apifunc
 * \brief Registers a callback function to receive a pointer of Progressive Download(PD) Header and header's size. Header data is parsed using this information.
 *
 * \param	 	hEngine				The handle of the NexPlayer&trade;&nbsp;engine.
 * \param[in]  	pPDEnvelopHeaderParsingCallbackFunc    	Callback function to register.
 *
 * \param[in]  	pUserData          	Additional data to pass to the callback function when it is called.
 *
 *
 * \see \link nexplayer_Callback.h#NEXPLAYERPDEnvelopHeaderParsingCallbackFunc NEXPLAYERPDEnvelopHeaderParsingCallbackFunc\endlink
 */
void		NEXPLAYEREngine_registerPDEnvelopHeaderParsingCallBackFunc(NEXPLAYERENGINE_handle hEngine,
																	   NEXPLAYERPDEnvelopHeaderParsingCallbackFunc pPDEnvelopHeaderParsingCallbackFunc,
																	   void *pUserData);

//--------------------------------------------------------------------------------------------------------
/**
 * \ingroup apifunc
 * \brief Registers a set of callback functions for Remote File I/O.
 *
 * See \ref rfio for more information.
 *
 * \param		hEngine		The handle of the NexPlayer&trade;&nbsp;engine.
 * \param[in]  	pRemoteFileIOInterface   Structure containing pointers to functions to register
 *
 * \param[in]  	pUserData                Additional data to pass to callback function when it is called
 *
 * \see  \link nexplayer_Callback.h#NEXPLAYERRemoteFileIOInterface NEXPLAYERRemoteFileIOInterface\endlink
 */
void 	NEXPLAYEREngine_registerRemoteFileIOInterface(
													  NEXPLAYERENGINE_handle hEngine,
													  NEXPLAYERRemoteFileIOInterface * pRemoteFileIOInterface,
													  void *pUserData);


//========================================================================================================
#pragma mark -

//#ifdef __cplusplus
//}
//#endif


#endif /* NXPlayerRegisterDRMCallBack_h */
