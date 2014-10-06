/* @(#) 1.6 com/src/samples/utils/iodprint.hpp, odpagepart, od96os2, odos29712d 11/8/96 15:22:51 [3/21/97 17:48:15] */

//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odsamples
//
//   CLASSES: none
//
//   ORIGINS: 82,27
//
//
//   (C) COPYRIGHT International Business Machines Corp. 1995,1996
//   All Rights Reserved
//   Licensed Materials - Property of IBM
//   US Government Users Restricted Rights - Use, duplication or
//   disclosure restricted by GSA ADP Schedule Contract with IBM Corp.
//
//   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
//   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
//   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
//   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
//   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
//   OR PERFORMANCE OF THIS SOFTWARE.
//
//====END_GENERATED_PROLOG========================================
//


#ifndef ODPrintExtension_Header
#define ODPrintExtension_Header
#endif

#define kODPrintExtension       "ODPrintExtension"

#define kNoBias                 kODNULL

#define CPL_ERROR               -1
#define CPL_NOPRINTERS          -2
#define CPL_NODEFAULT           -3

#define PRINT_QUEUE_LENGTH      100
#define QUEUENAME_LENGTH        10
#define DRIVERNAME_LENGTH       125
#define LEN_WORKSTRING          256
#define LEN_TITLE               256

#define ERRm                    1
#define WARNm                   2
#define INFOm                   3

#define PrinterListBoxDlgRes    201
#define PrintListBox            202
#define PrinterProperties       203
#define RefreshList             204

#define PrintingPage            206
#define StopPrinting            207
#define PrintQueueName          208
#define PrintPageNum            209

#define PrintRangeDlgRes        210
#define PrinterName             211
#define DocumentName            212
#define PrintAllPages           213
#define PrintSelectivePages     214
#define PrintFrom               215
#define PrintTo                 216
#define PrintCopies             217
#define PrintDoc                218
#define PrintCancel             219

#define PrintingPageXString     884
#define ErrorQueueXString       885

#define ErrorMsgString          890
#define WarningMsgString        891
#define InfoMsgString           892
#define MessageMsgString        893

#define NoPrintQueueMsg         918
#define CantPrintErrorMsg       919
#define CantQueryPrinterMsg     920
#define PrinterFormErrorMsg     921
#define PrintFailureMsg         922
#define NoDefaultQueueMsg       923
#define PrintBufferErrorMsg     924
#define PrintersNotAvailMsg     925
#define NoPrintersWarning       926

#define UntitledDocumentMsg     930
#define InitializingMsg         931
#define PreparingJobMsg         932
#define CompletingJobMsg        933
#define PageNumberMsg           934

//jwa: Following two strings must stay here - do not move to resource file
//     (since they are displayed when we can't get at our string table)
#define ResourceErrorMsg        "Unable to load resources!"
#define StringNotFoundMsg       "Message not found"

// #define kMRIFileName            "IODUtils.dll"; //jwa: using ".dll" extension makes it not search libpath???
#define kMRIFileName            "IODUtils"

#define kHelpFileName           "IODUtils.hlp"
#define PRINTER_SETUP_HELP      33501
#define PRINT_DOCUMENT_HELP     33502
#define AVAILABLE_PRINTERS_HELP 33517


#ifndef IODUTILS_RESOURCES
#ifdef _PLATFORM_OS2_
typedef struct {
   DEVOPENSTRUC    dosPrinter ;
   CHAR            achDevice [256] ;
   CHAR            pszPrinters [256] ;
   PDRIVDATA       pdrv ;
   ODBoolean       selected;
} PRNLISTINFO, *PPRNLISTINFO;


typedef struct
{
   PSZ            pszPrinter ;
   PSZ            pszDocument;
   ODUShort       usCopies;
   ODUShort       usPrintFrom;
   ODUShort       usPrintTo;
   ODBoolean      fPrintAllPages;
   ODBoolean      fAllowChoiceOfPages;
} PRNRANGE, *PPRNRANGE;
#endif //_PLATFORM_OS2_


struct PRNINFO
{
   ODPoint    offset;
   ODRect     bounds;
   HDC        hdc;

#ifdef _PLATFORM_OS2_
   HPS        hps;
   PHCINFO    phcInfo;
   PRINTDEST  printDest;
   PPRNRANGE  pRange;
#endif //_PLATFORM_OS2_

#ifdef _PLATFORM_WIN32_
   PRINTDLG*  printDlg;
#endif //_PLATFORM_WIN32_
};
typedef PRNINFO* PPRNINFO;
#endif //IODUTILS_RESOURCES

