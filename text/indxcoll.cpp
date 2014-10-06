// @(#) 1.3 com/src/samples/text/indxcoll.cpp, odtextpart, od96os2, odos29712d 2/3/97 16:50:27 [3/21/97 17:49:31]

#include "indxcoll.hpp"
#include <stdlib.h>
#include <string.h>
#ifdef ODDebug
#include <ODDebug.h>
#endif

// Constructor and Destructor
IndexedCollection::IndexedCollection()
{
   maxElements = 20;
   numElements = 0;
   elements = (ElementType*) calloc(maxElements, ElementSize);
}

IndexedCollection::~IndexedCollection()
{
   free(elements);
}

// Retrieval Methods
int IndexedCollection::Count() const
{
   return numElements;
}

ElementType  IndexedCollection::First()
{
   if (numElements > 0)
     return elements[0];
   else
     return NULL;
}

ElementType  IndexedCollection::FromIndex(int index)
{
   if (index < numElements) {
      return elements[index];
   } else {
      return NULL;
   } /* endif */
}

ElementType  IndexedCollection::Next(int index)
{
   if (index < (numElements-1)) {
      return elements[index+1];
   } else {
      return NULL;
   } /* endif */
}
ElementType  IndexedCollection::Previous(int index)
{
   if (index < numElements && index != 0) {
     return elements[index-1];
   } else {
      return NULL;
   } /* endif */
}
ElementType  IndexedCollection::Last()
{
   if (numElements > 0) {
     return elements[numElements -1];
   } else {
     return NULL;
   } /* endif */
}

// Addition/Deletion methods

void IndexedCollection::AddLast(int numToAdd, ElementType* elemsToAdd)
{
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: AddLast invoked.\n");
#endif
   if ((numElements + numToAdd) > maxElements) {
      ElementType* tempElements = AllocElements(numToAdd);
      memcpy(tempElements, elements, numElements * ElementSize);
      free(elements);
      elements = tempElements;
   } /* endif */

   memcpy(&elements[numElements], elemsToAdd, numToAdd * ElementSize);
   numElements += numToAdd;
}

void IndexedCollection::AddBefore(int index, int numToAdd, ElementType* elemsToAdd)
{
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: AddBefore invoked.\n");
#endif
   ElementType* tempElements;

   // Ensure the index is valid. Invoke AddLast if the index corresponds
   // to the next free element.
   if (index == numElements) {
      AddLast(numToAdd, elemsToAdd);
   } else if (index < numElements) {
       // Allocate a new buffer to copy the old and new data in the proper sequence
       if ((numElements + numToAdd) > maxElements) {
          tempElements = AllocElements(numToAdd);
       } else {
          tempElements = (ElementType*) calloc(maxElements, ElementSize);
       } /* endif */

       // Copy the data from the old buffer up to the index
       memcpy(tempElements, elements, index * ElementSize);
       // Copy in the new data
       memcpy(&tempElements[index], elemsToAdd, numToAdd * ElementSize);
       // Copy the data from the old buffer from the index beyond
       memcpy(&tempElements[index+numToAdd], &elements[index], (numElements - index) * ElementSize);

       // Replace the old buffer with the new buffer
       free(elements);
       elements = tempElements;
       numElements += numToAdd;
   } else {
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: Index %d is greater than list size %d.\n",index,numElements);
#endif
   } /* endif */

}

ElementType  IndexedCollection::RemoveLast()
{
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: RemoveLast invoked.\n");
#endif
   ElementType returnElement = NULL;

   if (numElements > 0) {
     returnElement = elements[--numElements];
     elements[numElements] = NULL;
   } /* endif */

   return returnElement;
}

ElementType IndexedCollection::RemoveFrom(int index)
{
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: RemoveFrom invoked.\n");
#endif
   ElementType returnElement = NULL;

   if (index < numElements) {
     returnElement = elements[index];
     memcpy(&elements[index], &elements[index+1], (--numElements - index) * ElementSize);
     elements[numElements] = NULL;
   }

   return returnElement;
}

ElementType* IndexedCollection::RemoveFromTo(int lowIndex, int highIndex)
{
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: RemoveFromTo invoked.\n");
#endif
   ElementType* tempElements = NULL;
   int removeElem;

   if (lowIndex < highIndex)
   {
     removeElem = highIndex-lowIndex+1;
     tempElements = (ElementType*) calloc(removeElem, ElementSize);
     memcpy(tempElements, &elements[lowIndex], removeElem * ElementSize);

     if (highIndex == numElements-1) {
        memset(&elements[lowIndex], 0, removeElem * ElementSize);
        numElements = lowIndex;
     } else {
        memcpy(&elements[lowIndex], &elements[highIndex+1], (numElements-1 - highIndex) * ElementSize);
        memset(&elements[numElements - removeElem], 0, removeElem * ElementSize);
        numElements -= removeElem;
     } /* endif */
   }

   return tempElements;
}

// Private Methods
ElementType* IndexedCollection::AllocElements(int numElem)
{
#ifdef ODDebug
       PRINT("INDXCOLL.CPP: AllocElements invoked.\n");
#endif
   // Allocate some new buffer space to accommodate future additions
   if (numElem > 1)
     maxElements += numElem;
   maxElements += 20;
   ElementType* tempElements = (ElementType*) calloc(maxElements, ElementSize);
   return tempElements;
}
