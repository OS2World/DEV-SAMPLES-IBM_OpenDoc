/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: oddynamicpart
 *
 *   CLASSES: none
 *
 *   ORIGINS: 82,27
 *
 *
 *   (C) COPYRIGHT International Business Machines Corp. 1995,1996
 *   All Rights Reserved
 *   Licensed Materials - Property of IBM
 *   US Government Users Restricted Rights - Use, duplication or
 *   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
 *   	
 *   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
 *   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 *   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
 *   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
 *   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
 *   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
 *   OR PERFORMANCE OF THIS SOFTWARE.
 */
/*====END_GENERATED_PROLOG========================================
 */
/* @(#) 1.3 com/src/samples/dynamicp/binit/isominit.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:49:49 [3/21/97 17:44:46]
*******************************************************************
** Name: void somDefaultInit
**
** Description:  override method to do basic initialization.
**               Equivalent to a c++ default constructor.
**               This method should not perform ANY action that
**               might fail.  Here me merely ensure the part's
**               data area is initialized to NULL.
**
*******************************************************************
*/
try {
   // initialize instance variables used during initialization.
   // Since we initialize them all to NULL, this is not strictly
   // necessary, but might be considered good programming practice.

   memset(somThis, 0, sizeof(DynamicPartData));
   //_fMenuBar         = kODNULL;
   //_fPopup           = kODNULL;
   //_fPartWrapper     = kODNULL;
   //_fIsInitialized   = kODFalse;
   //_fSession         = kODNULL;
   //_fWindowID        = 0;
   //_fDisplayFrames   = 0;
   //_fFrameNegotiated = kODFalse;

} catch (...) {
   reportAnyException(somGetGlobalEnvironment());
} /* end try */
// end sominit.frg
