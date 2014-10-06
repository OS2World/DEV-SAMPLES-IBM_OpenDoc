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
/* @(#) 1.3 com/src/samples/dynamicp/bregist/rgetkind.c, oddynamicpart, od96os2, odos29712d 11/1/96 08:50:22 [3/21/97 17:44:49]
*******************************************************************
** Name: _IDL_SEQUENCE_PartKindInfo clsGetODPartKinds
**
** Description:  Override method to determine the part kinds this
**               part handler is capable of handling.
**
*******************************************************************
*/
{
   _IDL_SEQUENCE_PartKindInfo DynamicPartInfo;

   // creating PartKindInfo Structure and allocating memory for variables
   PartKindInfo * info = (PartKindInfo *) SOMMalloc(sizeof(PartKindInfo));
   info->partKindName = (ISOString)SOMMalloc(strlen(kKindTestDynamicPart)+1);
   info->partKindDisplayName = (string)SOMMalloc(strlen(kDynamicPartKindDisplayName)+1);
   info->filenameFilters = (string)SOMMalloc(strlen(kDynamicPartFileNameFilter)+1);
   info->filenameTypes = (string)SOMMalloc(strlen(kDynamicPartFileNameType)+1);
   info->categories = (string)SOMMalloc(strlen(kDynamicPartCategory)+1);
   info->categoryDisplayName = (string)SOMMalloc(strlen(kDynamicPartCategory)+1);
   info->objectID = (string)SOMMalloc(strlen(" ")+1);

   // copy the information into the structure
   strcpy(info->partKindName,kKindTestDynamicPart);
   strcpy(info->partKindDisplayName,kDynamicPartKindDisplayName);
   strcpy(info->filenameFilters,kDynamicPartFileNameFilter);
   strcpy(info->filenameTypes,kDynamicPartFileNameType);
   strcpy(info->categories, kDynamicPartCategory);
   strcpy(info->categoryDisplayName, kDynamicPartCategory);
   strcpy(info->objectID," ");

   DynamicPartInfo._maximum = 1;
   DynamicPartInfo._length = 1;
   DynamicPartInfo._buffer = info;
   return DynamicPartInfo;
}  // end rGetKind.c
