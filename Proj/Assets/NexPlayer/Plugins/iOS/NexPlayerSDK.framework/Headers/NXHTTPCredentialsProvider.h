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
 * \brief   Classes that will handle requests for HTTP credentials during
 *          streaming playback should implement this protocol.
 *
 * See NXPlayer::HTTPCredentialsProvider for details.
 */
@protocol NXHTTPCredentialsProvider <NSObject>

@optional

/**
 * \brief   Called whenever NexPlayer&trade;&nbsp;receives an authentication
 *          failure response (HTTP 401 or HTTP 407) during streaming play.
 *
 * If this is implemented, it takes precedence over the older NXHTTPCredentialsProvider::HTTPCredentialHeaders
 * method (and NXHTTPCredentialsProvider::HTTPCredentialHeaders will not be called);
 *
 * \param   statusCode      The status code received from the HTTP server (401 or 407)
 *
 * \param   responseData    The actual response sent by the server. This is
 *                          backed by a buffer internal to the SDK, so it should not
 *                          be retained and must not be accessed after this
 *                          function returns.  If it is necessary to access this
 *                          data later, make a copy in a new \c NSData object.
 *
 * \return                  A dictionary containing the HTTP headers to add
 *                          when retrying the request (the header field names
 *                          are in the dictionary keys; the header field values
 *                          are the dictionary values).
 *
 * See NXPlayer::HTTPCredentialsProvider for more information.
 */
- (NSDictionary*)HTTPCredentialHeadersForHTTPStatusCode:(unsigned int)statusCode
                                           responseData:(NSData*)responseData ;

/**
 * \brief   Called whenever NexPlayer&trade;&nbsp;receives an HTTP 401 response
 *          during streaming play.
 *
 * \deprecated  This only handled the HTTP 401 case; please use HTTPCredentialHeadersForHTTPStatusCode:responseData: instead.
 *
 * See NXPlayer::HTTPCredentialsProvider for more information.
 */
- (NSDictionary*)HTTPCredentialHeaders;

@end
