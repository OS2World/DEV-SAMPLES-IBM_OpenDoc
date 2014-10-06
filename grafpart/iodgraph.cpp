// @(#) 1.48 com/src/samples/grafpart/iodgraph.cpp, odgrafpart, od96os2, odos29712d 1/23/97 17:34:17 [3/21/97 17:45:35]
/*====START_GENERATED_PROLOG======================================
*/
/*
 *   COMPONENT_NAME: odgrafpart
 *
 *   CLASSES: GrafPart
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

// ************************************************************************
//  Contains:  Class implementation for a 2D-Drawing Container Part
// ************************************************************************

// this file gets its source from graph_cm.cpp which contains the implementation
// for the class in a form that can either be included here to generate the
// implementation for class GraphPart, or included under scrgraph to produce
// implementaion for ScriptableGraphPart.

#undef _Scriptable_GP_

// note we bring in the GrafPart implementation header (xih) here rather than
// in the common code file so that there is no conflict (parent methods) for
// the other class including that common source

#define GrafPart_Class_Source
#ifndef SOM_GrafPart_xih
    #include "iodgraph.xih"
#endif // SOM_GrafPart_xih


#include <graph_cm.cpp>

#define M_GrafPart_Class_Source


// =========================================================================
//
//     Metaclass overrides: GrafPart
//
// =========================================================================

// -------------------------------------------------------------------------
// SOMInitModule
//
//     Used at registration time
// -------------------------------------------------------------------------
SOMEXTERN   void    SOMLINK SOMInitModule ( long    majorversion,
                                            long    minorversion,
                                            string  className )
{
    SQUAWK("> Invoked GrafPart::SOMInitModule()\n");

    SOM_IgnoreWarning (majorversion);
    SOM_IgnoreWarning (minorversion);
    SOM_IgnoreWarning (className);
    GrafPartNewClass(majorversion,minorversion);

    SQUAWK("< Leaving GrafPart::SOMInitModule()\n");
}   // SOMInitModule()


// -------------------------------------------------------------------------
// GrafPart --> clsGetODPartHandlerName
//
//     Define and report the part handler name.
//
//     -> public metaclass override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   ISOString   SOMLINK M_GrafPartclsGetODPartHandlerName(  M_GrafPart  *somSelf,
                                                                    Environment *ev )
{
    SQUAWK("> Invoked M_GrafPart::clsGetODPartHandlerName()\n");

    /* M_GrafPartData *somThis = M_GrafPartGetData(somSelf); */
    M_GrafPartMethodDebug("M_GrafPart","M_GrafPartclsGetODPartHandlerName");

    string handlerName = (string)SOMMalloc(strlen(kGrafPartHandlerName)+1);
    strcpy(handlerName,kGrafPartHandlerName);

    SQUAWK("< Leaving M_GrafPart::clsGetODPartHandlerName()\n");
    return (ISOString) handlerName;

}   // clsGetODPartHandlerName()


// -------------------------------------------------------------------------
// GrafPart --> clsGetODPartHandlerDisplayName
//
//     Define and report the part handler human-readable name.
//
//     -> public metaclass override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   string  SOMLINK M_GrafPartclsGetODPartHandlerDisplayName(   M_GrafPart  *somSelf,
                                                                        Environment *ev )
{
    SQUAWK("> Invoked M_GrafPart::clsGetODPartHandlerDisplayName()\n");

    /* M_GrafPartData *somThis = M_GrafPartGetData(somSelf); */
    M_GrafPartMethodDebug("M_GrafPart","M_GrafPartclsGetODPartHandlerDisplayName");

    string displayName = (string)SOMMalloc(strlen(kGrafPartHandlerDisplayName)+1);
    strcpy(displayName,kGrafPartHandlerDisplayName);

    SQUAWK("< Leaving M_GrafPart::clsGetODPartHandlerDisplayName()\n");
    return displayName;

} // clsGetODPartHandlerDisplayName()


// -------------------------------------------------------------------------
// GrafPart --> clsGetODPartKinds
//
//     Define and report the part kinds for this handler.
//
//     -> public metaclass override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   _IDL_SEQUENCE_PartKindInfo  SOMLINK M_GrafPartclsGetODPartKinds(M_GrafPart  *somSelf,
                                                                            Environment *ev )
{
    SQUAWK("> Invoked M_GrafPart::clsGetODPartKinds()\n");

    /* M_GrafPartData *somThis = M_GrafPartGetData(somSelf); */
    M_GrafPartMethodDebug("M_GrafPart","M_GrafPartclsGetODPartKinds");
    _IDL_SEQUENCE_PartKindInfo GrafPartInfo;

    // Create structure PartKindInfo  and allocate memory for variable
    PartKindInfo * info = (PartKindInfo *)SOMMalloc(sizeof(PartKindInfo));

    info->partKindName     = (ISOString)SOMMalloc(strlen(kGrafPartPartKind) + 1);
    info->partKindDisplayName = (string)SOMMalloc(strlen(kGrafPartPartKindDisplayName) + 1);
    info->filenameFilters     = (string)SOMMalloc(strlen(kGrafPartfilenameFilters) + 1);
    info->filenameTypes       = (string)SOMMalloc(strlen(kGrafPartfilenameTypes) + 1);
    info->categories          = (string)SOMMalloc(strlen(kGrafPartCategory) + 1);
    info->categoryDisplayName = (string)SOMMalloc(strlen(kGrafPartCategoryDisplayName) + 1);
    info->objectID            = (string)SOMMalloc(strlen(kGrafPartobjectID) + 1);

    // Copy the information into the structure
    strcpy(info->partKindName,        kGrafPartPartKind);
    strcpy(info->partKindDisplayName, kGrafPartPartKindDisplayName);
    strcpy(info->filenameFilters,     kGrafPartfilenameFilters);
    strcpy(info->filenameTypes,       kGrafPartfilenameTypes);
    strcpy(info->categories,          kGrafPartCategory);
    strcpy(info->categoryDisplayName, kGrafPartCategoryDisplayName);
    strcpy(info->objectID,            kGrafPartobjectID);

    GrafPartInfo._maximum = 1;
    GrafPartInfo._length = 1;
    GrafPartInfo._buffer = info;

    SQUAWK("< Leaving M_GrafPart::clsGetODPartKinds()\n");
    return GrafPartInfo;

}   // clsGetODPartKinds()


// -------------------------------------------------------------------------
// GrafPart --> clsGetOLE2ClassId
//
//     Define and report the OLE2 class ID for this handler.
//
//     -> public metaclass override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   string  SOMLINK M_GrafPartclsGetOLE2ClassId(M_GrafPart  *somSelf,
                                                        Environment *ev )
{
    SQUAWK("> Invoked M_GrafPart::clsGetOLE2ClassId()\n");

    /* M_GrafPartData *somThis = M_GrafPartGetData(somSelf); */
    M_GrafPartMethodDebug("M_GrafPart","M_GrafPartclsGetOLE2ClassId");

    string classID = (string)SOMMalloc(strlen(kGrafPartOLE2ClassId)+1);
    strcpy(classID,kGrafPartOLE2ClassId);

    SQUAWK("< Leaving M_GrafPart::clsGetOLE2ClassId()\n");
    return classID;
}   // clsGetOLE2ClassId()


// -------------------------------------------------------------------------
// GrafPart --> clsGetWindowsIconFileName
//
//     Define and report the icon file name for this handler.
//
//     -> public metaclass override method
//     -> does not call parent
// -------------------------------------------------------------------------
SOM_Scope   string  SOMLINK M_GrafPartclsGetWindowsIconFileName(M_GrafPart  *somSelf,
                                                                Environment *ev )
{
    SQUAWK("> Invoked M_GrafPart::clsGetWindowsIconFileName()\n");

    /* M_GrafPartData *somThis = M_GrafPartGetData(somSelf); */
    M_GrafPartMethodDebug("M_GrafPart","M_GrafPartclsGetWindowsIconFileName");

    string fileName = (string)SOMMalloc(strlen(kGrafPartWindowsIconFileName)+1);
    strcpy(fileName,kGrafPartWindowsIconFileName);

    SQUAWK("< Leaving M_GrafPart::clsGetWindowsIconFileName()\n");
    return fileName;

}   // clsGetWindowsIconFileName()





// =========================================================================
// End of file: iodgraph.cpp
// =========================================================================
