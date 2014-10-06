//  @(#)Z 1.19 com/src/samples/basecntr/iodbcitr.cpp, odbasepart, od96os2, odos29712d 97/03/21 17:45:38 (96/12/06 16:08:01)
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

#ifndef SOM_Module_iodbcitr_Source
#define SOM_Module_iodbcitr_Source
#endif
#define BCIterator_Class_Source

#define VARIABLE_MACROS
#define SOM_DONT_IMPORT_CLASS_ALink
#define SOM_DONT_IMPORT_CLASS_ALinkedList
#define SOM_DONT_IMPORT_CLASS_BaseContainer
#define SOM_DONT_IMPORT_CLASS_ContentObject
#define SOM_DONT_IMPORT_CLASS_ContentFrame

#ifndef _ALinkedList_
#include <iodbcutl.xh>
#endif

#include "iodbcitr.xih"


#include "iodbasec.xh"



// -------------------------------------------------------------------------
// -----                                                               -----
// -----                  BCIterator  Clase                            -----
// -----                                                               -----
// -----              Overriding Inherited Methods                     -----
// -----                                                               -----
// -------------------------------------------------------------------------



// -------------------------------------------------
// List of Methods
// -------------------------------------------------
// SOMObject --> somInit
// SOMObject --> somUninit
//
// ODEmbeddedFramesIteratort --> InitEmbeddedFramesIterator
// ODEmbeddedFramesIteratort --> First
// ODEmbeddedFramesIteratort --> Next
// ODEmbeddedFramesIteratort --> IsNotComplete
//
// ODEmbeddedFramesIteratort --> CheckValid
// ODEmbeddedFramesIteratort --> isValid
// ODEmbeddedFramesIteratort --> PartRemoved



// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> InitEmbeddedFramesIterator
//
//      Initializes the embedded frames iterator for OpenDoc. OpenDoc
//      doesn't provide an iterator class for your part, but allows you
//      the freedom to create your frame list startegy. However other
//      parts may need access to your list of embedded frames, and so
//      OpenDoc provides an intertface which you must match up to your
//      internal implementation.
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BCIteratorInitEmbeddedFramesIterator
                (
                BCIterator *somSelf,            // in
                Environment *ev,                // in
                ODPart* part                    // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorInitEmbeddedFramesIterator");




    BaseContainer *bcpart = (BaseContainer *)part;

    _fLink = bcpart->GetEmbeddedObjects(ev);
    _fNode= _fLink->First(ev); 



}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> First
//
//      Returns the first frame in the parts embedded frames list.
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       ODFrame*
SOMLINK         BCIteratorFirst
                (
                BCIterator *somSelf,            // in
                Environment *ev                 // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorFirst");



    _fNode = _fLink->First(ev);
    ODFrame *frame = (ODFrame*)_fNode->Content(ev);
    _fNode = _fNode->Next(ev);
    return frame;
}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> Next
//
//      Returns the next frame in the parts embedded frames list.
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       ODFrame*
SOMLINK         BCIteratorNext
                (
                BCIterator *somSelf,            // in
                Environment *ev                 // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorNext");


    ODFrame *frame = (ODFrame*)_fNode->Content(ev);
    _fNode = _fNode->Next(ev);
    return frame;
}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> IsNotComplete
//
//      Returns a Boolean value of False if at the end of the embedded
//      frames list, otherwise this method returns true.
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BCIteratorIsNotComplete
                (
                BCIterator *somSelf,            // in
                Environment *ev                 // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorIsNotComplete");




    return ((_fNode->Content(ev)==0) ? kODFalse : kODTrue);
}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> PartRemoved
//
//      Called by this part to invalidate the embedded frames list prior
//      to closing down.
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BCIteratorPartRemoved
                (
                BCIterator *somSelf,            // in
                Environment *ev                 // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorPartRemoved");





}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> CheckValid
//
//      Checks validity of the embedded frames iterator and throws an
//      exception if not. If implemented it should be called by each
//      method of the subclass(i.e. BCIterator)
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BCIteratorCheckValid
                (
                BCIterator *somSelf,            // in
                Environment *ev                 // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorCheckValid");





}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> IsValid
//
//      Checks validity of the embedded frames iterator and returns a
//      Boolean False if not. If implemented it should be called by each
//      method of the subclass(i.e. BCIterator)
//
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       ODBoolean
SOMLINK         BCIteratorIsValid
                (
                BCIterator *somSelf,            // in
                Environment *ev                 // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorIsValid");




    return kODFalse;
}




// -------------------------------------------------------------------------
// ODEmbeddedFramesIterator --> somUninit
//
//      Disposes of storage for SOMObject of this part.
//
//      -> does not call parent method (called automatically by SOM)
//      -> optional for all parts
//
//      -> somUninit must NOT fail
//
//      ->
// -------------------------------------------------------------------------

SOM_Scope       void
SOMLINK         BCIteratorsomUninit
                (
                BCIterator *somSelf             // in
                )
{
    BCIteratorData *somThis = BCIteratorGetData(somSelf);
    BCIteratorMethodDebug("BCIterator","BCIteratorsomUninit");




}
