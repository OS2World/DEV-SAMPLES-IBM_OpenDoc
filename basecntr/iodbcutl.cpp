//====START_GENERATED_PROLOG======================================
//
//
//   COMPONENT_NAME: odbasecntr
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
/* @(#) 1.25 com/src/samples/basecntr/iodbcutl.cpp, odbasepart, od96os2, odos29712d 10/30/96 23:28:15 [3/21/97 17:45:37] */

//#====START_GENERATED_PROLOG======================================
//#
//#
//#
//#   IBM DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE, INCLUDING
//#   ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
//#   PURPOSE. IN NO EVENT SHALL IBM BE LIABLE FOR ANY SPECIAL, INDIRECT OR
//#   CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF
//#   USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR
//#   OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE
//#   OR PERFORMANCE OF THIS SOFTWARE.
//#
//#====END_GENERATED_PROLOG========================================
//#
/*
 *  This file was generated by the SOM Compiler and Emitter Framework.
 *  Generated using:
 *      SOM Emitter emitxtm.dll: Development
 */

#ifndef SOM_Module_iodbcutl_Source
#define SOM_Module_iodbcutl_Source
#endif
#define ALink_Class_Source
#define ALinkedList_Class_Source
#define VARIABLE_MACROS
#define METHOD_MACROS

#include <ODTypes.h>
#include "iodbcutl.xih"


//==================================================================
// ALink
//==================================================================

SOM_Scope ODPtr  SOMLINK ALinkContent(ALink *somSelf,  Environment *ev)
{
    ALinkData *somThis = ALinkGetData(somSelf);
    ALinkMethodDebug("ALink","ALinkContent");

    return _fContent;
}

SOM_Scope ALink*  SOMLINK ALinkNext(ALink *somSelf,  Environment *ev)
{
    ALinkData *somThis = ALinkGetData(somSelf);
    ALinkMethodDebug("ALink","ALinkNext");

    return _fNext;
}

SOM_Scope void  SOMLINK ALinksetContent(ALink *somSelf,  Environment *ev,
                                        ODPtr content)
{
    ALinkData *somThis = ALinkGetData(somSelf);
    ALinkMethodDebug("ALink","ALinksetContent");
    _fContent = content;

}

SOM_Scope void  SOMLINK ALinksetNext(ALink *somSelf,  Environment *ev,
                                     ALink* next)
{
    ALinkData *somThis = ALinkGetData(somSelf);
    ALinkMethodDebug("ALink","ALinksetNext");
    _fNext = next;

}

SOM_Scope void  SOMLINK ALinksomInit(ALink *somSelf)
{
    ALinkData *somThis = ALinkGetData(somSelf);
    ALinkMethodDebug("ALink","ALinksomInit");

    ALink_parent_ODObject_somInit(somSelf);
    _fContent = _fNext = kODNULL;
}

SOM_Scope void  SOMLINK ALinksomUninit(ALink *somSelf)
{
    ALinkData *somThis = ALinkGetData(somSelf);
    ALinkMethodDebug("ALink","ALinksomUninit");

    ALink_parent_ODObject_somUninit(somSelf);
}

//==================================================================
// ALinkList
//==================================================================


SOM_Scope ALink*  SOMLINK ALinkedListFirst(ALinkedList *somSelf,
                                             Environment *ev)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListFirst");
    return _fRoot;

}

SOM_Scope void  SOMLINK ALinkedListAddFirst(ALinkedList *somSelf,
                                             Environment *ev,
                                            ODPtr content)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListAddFirst");

    ALink *node = new ALink;
    node->setContent(ev, content);
    node->setNext(ev, _fRoot);
    _fRoot = node;
}

SOM_Scope void  SOMLINK ALinkedListAddLast(ALinkedList *somSelf,
                                            Environment *ev,
                                           ODPtr content)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListAddLast");

    if (_fRoot->Content(ev) == kODNULL) {
       somSelf->AddFirst (ev, content);
       return;
    }

    ALink *node = _fRoot, *prev = _fRoot;

    while (node->Next(ev) != kODNULL) {
       prev = node;
       node = node->Next(ev);
    }
    ALink *newNode = new ALink;
    newNode->setContent (ev, content);
    newNode->setNext (ev, node);
    prev->setNext (ev, newNode);


}

SOM_Scope void  SOMLINK ALinkedListRemove(ALinkedList *somSelf,
                                           Environment *ev, ODPtr content)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListRemove");

    if (somSelf->Contains(ev, content) == kODFalse)
       return;

    if (_fRoot->Content(ev) == content) {
       ALink *temp = _fRoot;
       _fRoot = _fRoot->Next(ev);
       delete temp;
       return;
    }

    ALink *node = _fRoot, *prev = _fRoot;

    while (node->Content(ev) != content) {
       prev = node;
       node = node->Next(ev);
    }
    prev->setNext (ev, node->Next(ev));
    delete node;

}

SOM_Scope void  SOMLINK ALinkedListRemoveAll(ALinkedList *somSelf,
                                              Environment *ev)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListRemoveAll");

    ALink *node = _fRoot;
    while (node->Next(ev)) {
       ALink *temp = node;
       node = node->Next(ev);
       delete temp;
    }
    _fRoot = node;

}

SOM_Scope ODBoolean  SOMLINK ALinkedListContains(ALinkedList *somSelf,
                                                  Environment *ev,
                                                 ODPtr content)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListContains");

    ALink *node = _fRoot;
    while(node->Next(ev)) {
       if (node->Content(ev) == content)
          return kODTrue;
       node = node->Next(ev);
    }
    return kODFalse;
}

SOM_Scope ODULong  SOMLINK ALinkedListCount(ALinkedList *somSelf,
                                             Environment *ev)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListCount");

    ODULong retVal = 0;
    ALink *node = _fRoot;
    while (node->Next(ev)) {
       retVal++;
       node = node->Next(ev);
    }
    return retVal;

}

SOM_Scope void  SOMLINK ALinkedListsomInit(ALinkedList *somSelf)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListsomInit");

    ALinkedList_parent_ODObject_somInit(somSelf);
    _fRoot = new ALink;

}

SOM_Scope void  SOMLINK ALinkedListsomUninit(ALinkedList *somSelf)
{
    ALinkedListData *somThis = ALinkedListGetData(somSelf);
    ALinkedListMethodDebug("ALinkedList","ALinkedListsomUninit");

    Environment *ev = somGetGlobalEnvironment();
    ALink *node = _fRoot;
    while (node->Next(ev)) {
       ALink *temp = node->Next(ev);
       delete node;
       node = temp;
    }
    delete node;

    ALinkedList_parent_ODObject_somUninit(somSelf);
}
