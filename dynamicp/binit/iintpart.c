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
/* @(#) 1.4 com/src/samples/dynamicp/binit/iintpart.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:49:45 [3/21/97 17:44:46]
*******************************************************************
** Name: void InitPart
**
** Description:  Initialize a part when it is created dynamically
**               (i.e. via new).  All values should be given
**               default values.
**
*******************************************************************
*/
try {

    if (_fIsInitialized)
      // We have already done this -- don't go through it again.
      return;

    _fIsInitialized = kODTrue;
    // save a self-reference for later use
    _fPartWrapper = partWrapper;

    if(!storageUnit->Exists(ev, kODPropContents, kKindTestDynamicPart, 0))
    {
        storageUnit->AddProperty(ev, kODPropContents)->AddValue(ev, kKindTestDynamicPart);
    }

} catch (...) {
   reportAnyException(ev);
} /* end try */
// end initpart.frg
