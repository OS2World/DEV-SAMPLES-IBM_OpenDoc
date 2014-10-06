/* @(#) 1.3 com/src/samples/dynamicp/ioddyext.cpp, oddynamicpart, od96os2, odos29712d 11/1/96 21:00:35 [3/21/97 17:49:25] */
//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: oddynamicpart
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


// This file implements the ScriptExtension code for a scriptable part which
// inherits from 'SimplePart'.

/*
 *  This file was generated by the SOM Compiler and Emitter Framework.
 *  Generated using:
 *      SOM Emitter emitxtm.dll: Development
 */

#ifndef SOM_Module_ioddyext_Source
#define SOM_Module_ioddyext_Source
#endif
#define ScriptableSimplePartScrExt_Class_Source

#include "ioddyext.xih"
#include "scrcomp.xh"          // to get return value codes


SOM_Scope ODScriptExtension_ODScrRegRet  SOMLINK DYNExt_Register(ScriptableDynamicPartScrExt *somSelf,
                                                                  Environment *ev,
                                                                  ODScriptExtension* RegScope,
                                                                  string Prefix)
{
    ODScrRegRet RetVal = ODScrRegOK ;
    ODObject* basepart ;
    char*     className ;
    char*     nameAssigned ;

    /* ScriptableDynamicPartScrExtData *somThis = ScriptableDynamicPartScrExtGetData(somSelf); */
    ScriptableDynamicPartScrExtMethodDebug("ScriptableDynamicPartScrExt","SSPExt_Register");

    basepart = somSelf->GetBase(ev) ;
    if (basepart == NULL) {return ODScrRegErr;}

    // The class for each scriptable object needs to be registered with the
    // ScriptComponent.

    className = basepart->somGetClassName() ;
    RetVal = RegScope->DoRegisterClass(ev, className) ;
    if (RetVal != ODScrRegOK)
    { return RetVal ; }

    // DoRegisterObject can take care of most normal naming issues.  We
    // call it here with the option option that will append a
    // numeric string to the name supplied here if needed to
    // make the name unique in the set of names assigned for this Part.

    RetVal = RegScope->DoRegisterObject(ev,
                     basepart,          // the object to be scriptable
                     className,         // the class name of that object
                     "Dynamic",           // the default name to be used
                      Prefix,            // prefix that applies in the scope
                                        //  where registration begins
                      &nameAssigned,     // receives name actually assigned
                      somSelf,           // the scope/extension of the object
                     kODTrue);          // digits to be appended to make the
                                        //  name unique if needed.

    if (RetVal == ODScrRegOK)           // if registration was successful, we
    { SOMFree(nameAssigned) ; }         //  need to release the storage
                                        //  that holds the actual name assigned.
                                        //  For this part we don't need to
                                        //  save that information.

    return RetVal ;

}
