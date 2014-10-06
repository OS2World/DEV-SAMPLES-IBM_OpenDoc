/*====START_GENERATED_PROLOG======================================*/
/*
 *   COMPONENT_NAME: odtextpart
 *
 *   CLASSES: none
 *
 *   ORIGINS: 27
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
/*====END_GENERATED_PROLOG========================================*/
// @(#) 1.21 com/src/samples/text/iodtext.h, odtextpart, od96os2, odos29712d 2/12/97 18:05:46 [3/21/97 17:45:34]
#ifndef _IODTEXT_H_
#define _IODTEXT_H_

// OpenDoc utility functions
#include <itext.h>
#include <odutils.h>
#include <stdtypio.h>
#include <storutil.h>
#include <tempobj.h>

// IBM VAC++ Compiler utility functions
#include <locale.h>
#include <wchar.h>

// TextPart helper functions and classes
#include "textmgr.hpp"
#include "textplat.h"

// NLS Catalog support
#include "iodtextm.h"
#define TX_NLS_CATALOG "iodtextm.cat"  // TextPart Messages are stored in iodtextm.msg

// Local constants and defines
// Constants used for ChangeNotification
const ODULong TP_TEXTCHANGED = 256;

// Constants used for Part Registration
const ODType   kODKindTextPart          = "TextPart";
const ODType   kTextPartKindDisplayName = "TextPart Kind";
const ODType   kTextPartHandlerName     = "TextPart";
const ODType   kTextPartHandlerDisplayName  = "Text Import/Export Part";
const ODType   kTextPartCategory        = "OpenDoc:Category:Sample";
const ODType   kTextPartIconFileName    = "iodtext.ico";

// Property names
#define kODPropTextContents  "TextPart:Property:TextContents"
static const ODPropertyName kTypeAscii = "TextPart:Value:AsciiText";
static char* kTextPartPropertyName  =  "Text";

// allow shorthand specification of menu commands
#define CMD(X)    kODCommand##X

#define kODCommandImport           (CMD_Offset_Subclass)
#define kODCommandExport           (CMD_Offset_Subclass+1)

// NLS Catalog name
#define TX_NLS_CATALOG "iodtextm.cat"  // TextPart Messages are stored in iodtextm.msg
#endif // _IODTEXT_H_

// end of file
