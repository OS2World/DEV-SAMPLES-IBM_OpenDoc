// @(#) 1.1 com/src/samples/text/indxcoll.hpp, odtextpart, od96os2, odos29712d 12/19/96 11:26:25 [3/21/97 17:49:31]
#ifndef _INDXCOLL_HPP_
#define _INDXCOLL_HPP_

typedef void* ElementType;
#define ElementSize sizeof(ElementType)

class IndexedCollection  // An indexable collection of ElementTypes
{

public:

  IndexedCollection();
  virtual ~IndexedCollection();

  // Retrieval Methods
  int Count() const;
  ElementType  First();
  ElementType  FromIndex(int index);
  ElementType  Next(int index);
  ElementType  Previous(int index);
  ElementType  Last();

  // Addition/Deletion methods
  virtual void  AddLast(int numToAdd, ElementType* elemsToAdd);
  virtual void  AddBefore(int index, int numToAdd, ElementType* elemsToAdd);
  virtual ElementType  RemoveLast();
  virtual ElementType  RemoveFrom(int index);
  virtual ElementType* RemoveFromTo(int lowIndex, int highIndex);

  private:
    // data
    ElementType* elements;
    int    numElements;
    int    maxElements;

    // methods
    ElementType* AllocElements(int numElem);
};

#endif // _INDXCOLL_HPP_
