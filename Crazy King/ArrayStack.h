//Copied from lab 6 (stacks and queues)


//	This is an updated version of code originally
//  created by Frank M. Carrano and Timothy M. Henry.
//  Copyright (c) 2017 Pearson Education, Hoboken, New Jersey.

/** ADT stack: Array-based implementation.
 @file ArrayStack.h */

#ifndef ARRAY_STACK_
#define ARRAY_STACK_

#include "StackADT.h"



template<typename ItemType>
class ArrayStack : public StackADT<ItemType>
{

private:
	ItemType* items;		// Array of stack items to be dynamically allocated
	int     top;            // Index to top of stack
	int		MaxSize;		//max stack size.

public:
	ArrayStack(int r_maxSize);
	bool isEmpty() const;
	bool push(const ItemType& newEntry);
	bool pop(ItemType& TopEntry);
	bool peek(ItemType& TopEntry) const;
	const ItemType** toArray(int& size) const;
}; // end ArrayStack



template<typename ItemType>
ArrayStack<ItemType>::ArrayStack(int r_maxSize) : top(-1), MaxSize(r_maxSize)
{
	items = new ItemType[MaxSize];		//dynamically allocate stack items
}  // end constructor

// Copy constructor and destructor are supplied by the compiler

template<typename ItemType>
bool ArrayStack<ItemType>::isEmpty() const
{
	return top < 0;
}  // end isEmpty

template<typename ItemType>
bool ArrayStack<ItemType>::push(const ItemType& newEntry)
{
	if (top == MaxSize - 1) return false;

	top++;
	items[top] = newEntry;
	return true;
}  // end push

template<typename ItemType>
bool ArrayStack<ItemType>::pop(ItemType& TopEntry)
{

	if (isEmpty()) return false;

	TopEntry = items[top];
	top--;
	return true;

}  // end pop

template<typename ItemType>
bool ArrayStack<ItemType>::peek(ItemType& TopEntry) const
{
	if (isEmpty()) return false;

	TopEntry = items[top];
	return true;
}  // end peek


//template<typename ItemType>
//const ItemType** ArrayStack<ItemType>::toArray(int& size) const
//{
//
//	if (isEmpty())
//	{
//		size = 0;
//		return nullptr;
//	}
//
//	size = top + 1;		//no. of items in the stack	
//
//	//allocating array of pointers to const objects with length equal to stack size
//	const ItemType** Res = new const ItemType * [size];
//
//	//Make each pointer in the Res array point to an item in "Items" array
//	//Array should be filled in the same order as the stack items (LIFO)
//	for (int i = top, j = 0; i >= 0; i--, j++)
//		Res[j] = &items[i];
//
//	return Res;
//
//
//
//}

template<typename ItemType>
const ItemType** ArrayStack<ItemType>::toArray(int& size) const
{

	if (isEmpty())
	{
		size = 0;
		return nullptr;
	}

	size = top + 1;		//no. of items in the stack	

	//allocating array of pointers to const objects with length equal to stack size
	const ItemType** Res = new const ItemType * [size];

	//Make each pointer in the Res array point to an item in "Items" array
	//Array should be filled in the same order as the stack items (LIFO)
	for (int i = top, j = 0; i >= 0; i--, j++)
		Res[j] = &items[i];

	return Res;



}


#endif
