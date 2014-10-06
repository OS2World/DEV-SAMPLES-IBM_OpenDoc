// @(#) 1.3 com/src/samples/grafpart/iodgcomm.cpp, odgrafpart, od96os2, odos29712d 11/7/96 17:00:53 [3/21/97 17:47:54]
/*====START_GENERATED_PROLOG======================================
 */
/*
 *   COMPONENT_NAME: odgrafpart
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
/*====END_GENERATED_PROLOG========================================
 */

// *********************************************************************
//  File:      iodgcomm.cpp
//  Contains:  Common implementation details for a 2D-Drawing Container Part
// ************************************************************************

#ifndef _IODGCOMM_CPP_
#define _IODGCOMM_CPP_

#ifdef __IBMC__
    #pragma linkage (SOMInitModule, system)
#endif

// includes for OD-specific function
#if defined(_PLATFORM_WIN32_) || \
    defined(_PLATFORM_OS2_)
//  #include <Arbitrat.xh>
//  #include <Draft.xh>
//  #include <Info.xh>
    #include <Facet.xh>
//  #include <FacetItr.xh>
//  #include <Foci.xh>
    #include <FocusSet.xh>
//  #include <FocusItr.xh>
    #include <Frame.xh>
    #include <FrFaItr.xh>
    #include <MenuBar.xh>
//  #include <ODSessn.xh>
//  #include <Popup.xh>
    #include <Shape.xh>
    #include <StdTypes.xh>
    #include <StdProps.xh>
    #include <StorageU.xh>
    #include <Trnsform.xh>
    #include <Window.xh>
//  #include <winStat.xh>
    typedef long RGBColor;
#endif // _PLATFORM_WIN32_ || _PLATFORM_OS2_

// support exception handling (DrawContents)
#ifndef _ODEXCEPT_
    #include "ODExcept.h"
#endif

// support defines like ODBoolean, kODNULL, etc
#ifndef _ODTYPES_
    #include <ODTypes.h>
#endif  // _ODTYPES_

// support debugging
#ifdef ODDebug
    #include <ODDebug.h>
#endif // ODDebug

// define debugging message vehicle
#ifdef GPDebug
    #define SQUAWK PRINT
#else
    #define SQUAWK //_SQUAWK
#endif // GPDebug

// support math conversion macros for use of ODPoints
#ifndef _ODMATH_
    #include <ODMath.h>
    // define inverse of ODIntToFixed(), since ODMath.h doesn't
    #define ODFixedToInt(a) ((LONG)(a) >> 16)
#endif   // _ODMATH_


// system-dependant support for NLS
#include <locale.h>
#include <wchar.h>
#include <odnltyps.h>
// Use the NLS catalogs if using the VisualAge compiler or AIX's xlC
#if defined(__IBMCPP__) || defined(_IBMR2)
    #define _NLS_
#else
    #undef  _NLS_
// if this platform/compiler does not support NLS, create dummy definitions for NLS function
    #ifndef NL_CAT_LOCALE
        #define NL_CAT_LOCALE 1
        typedef int nl_catd;
        int     catopen(char *, int) { return 0; }
        char*   catgets(int a, int b, int c, char *defaultMsg) { return defaultMsg; }
        void    catclose(int) { }
    #endif  // NL_CAT_LOCALE
#endif  // VAC++, xLC ?

// subclass from BaseContainer
#ifndef BaseContainer_Header
    #include <BCMain.h>
#endif  // BaseContainer_Header

// make a nickname for kODCommands
#ifndef CMD
    #define CMD(X)    kODCommand##X
#endif // CMD()

// Use resources
#ifndef _ODRESRC_
    #include <ODResrc.h>
#endif  // _ODRESRC_

// define a platform independant menubar separator attribute
#if defined(_PLATFORM_WIN32_)
    #define MB_SEPARATOR    MF_SEPARATOR
#elif defined(_PLATFORM_OS2_)
    #define MB_SEPARATOR    CA_TITLESEPARATOR
#endif

// =========================================================================
//
//  Global helper Functions: GrafPart
//
//  ->  Prototypes only, definitions appear once in iodgraph.cpp
// =========================================================================
ODFacet*    FirstFacet( Environment*    ev,
                        ODFrame*        frame);

ODRect*     FluffRect(  ODRect*         rect);

void        GetPoint(   Environment*    ev,
                        ODFacet*        facet,
                        ODEventData*    event,
                        ODPoint*        point);


#endif  // _IODGCOMM_CPP_

// =========================================================================
// End of file: iodgcomm.cpp
// =========================================================================
