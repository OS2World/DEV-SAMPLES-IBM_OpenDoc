#====START_GENERATED_PROLOG======================================
#
#
#   COMPONENT_NAME: odsamples
#
#   CLASSES: none
#
#   ORIGINS: 27
#
#
#   (C) COPYRIGHT International Business Machines Corp. 1995,1996
#   All Rights Reserved
#   Licensed Materials - Property of IBM
#   US Government Users Restricted Rights - Use, duplication or
#   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
#
#
#   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
#   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
#   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
#   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
#   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
#   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
#   OR PERFORMANCE OF THIS SOFTWARE.
#
#====END_GENERATED_PROLOG========================================
#
# @(#) 1.1 os2/src/samples/iodduals.mak, odsamples, od96os2, odos29712d 11/1/96 13:25:17 [ 3/21/97 17:49:26 ]

# on Windows NT and Windows 95, if compiling with the Microsoft VisualC++
# compiler, use a different name for the iodutils lib and dll.  This
# means all VisualAge compiler parts use the iodutils name, and all
# Microsoft VisualC++ compiler parts use the iodmvutl name.
#
!IFDEF CPPMAIN
iodutils = iodutils
!ELSE
!IFDEF MSDEVDIR
iodutils = iodmvutl
!ENDIF
!ENDIF
