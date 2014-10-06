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
/* @(#) 1.3 com/src/samples/dynamicp/bregist/rgetole2.c, oddynamicpart, od96os2, odos29712d 97/03/21 17:44:49 (96/11/01 08:50:26)
*******************************************************************
** Name: string clsGetOLE2ClassId
**
** Description:  Override method to get the OLE2 Class id from
**               the metaclass.
**
*******************************************************************
*/
{
  // OLE2 Class ID is determined by running the tool UUIDGEN.EXE
  // or GUIDGEN.EXE found in the IBM VAC++ SDK\BIN directory
  // this tool is gauranteed to generate a unique ID based on your
  // network address and the time of day (DCE Standard)


    string OLE2 = "{9874b1c0-00f8-11d0-b25e-08005a49d940}";
    string OLE2ClassId = (string)SOMMalloc(strlen(OLE2)+1);
    strcpy(OLE2ClassId,OLE2);

    return OLE2ClassId;
}
// end rGetOLE2.c
