
#ifndef _LINKEDLIST
#define _LINKEDLIST

#include "Node.h"

template <typename T>
class LinkedList
{
private:
	Node<T> *Head;	//Pointer to the head of the list
	//You can add tail pointer too (depending on your problem)
	int count;	//Number of nodes in the list
public:



	LinkedList()
	{
		count = 0;
		Head = nullptr;
	}

	//List is being desturcted ==> delete all items in the list
	~LinkedList()
	{
		DeleteAll(); 
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: PrintList.
	* prints the values of all nodes in a linked list.
	*/
	bool IsEmpty()
	{
		if (count == 0)
			return 1;
		return 0;
	}

	void PrintList()	const
	{
		cout<<"\nList has "<<count<<" nodes";
		cout<<"\nprinting list contents:\n\n";
		Node<T> *p = Head;

		while(p)
		{
			cout << "[ " << p->getItem() << " ]";
			cout << "--->";
			p = p->getNext();
		}
		cout << "*\n";
	}
	////////////////////////////////////////////////////////////////////////
	/*
	* Function: InsertBeg.
	* Creates a new node and adds it to the beginning of a linked list.
	* 
	* Parameters:
	*	- data : The value to be stored in the new node.
	*/
	void InsertBeg(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		R->setNext(Head);
		Head = R;
		count++;

	}
	//////////////////////

	//bool search(T x)
	//{
	//	Node<T> * current = Head; // Initialize current  
	//	while (current != NULL)
	//	{
	//		if (current->getItem().getValue() == x.getValue())
	//			return true;
	//		current = current->getNext();
	//	}
	//	return false;
	//}

	void DeleteIndex(int index)
	{
		// Store head node 
		Node<T>* P = Head;
		count--;

		if (index == 0)
		{
			Head = P->getNext();
			delete P;
			return;
		}

		int k = 0;
		while (k != index-1)
		{
			P = P->getNext();
			k++;
		}
		//k==index-1
		Node<T>* Q = P->getNext();
		P->setNext(P->getNext()->getNext());
		delete Q;
		
		return;
	}

	T ReturnIndex(int index)
	{
		Node<T>* P = Head;
		int k = 0;
		while (k != index)
		{
			P = P->getNext();
			k++;
		}
		return P->getItem();
	}


	////////////////////////////////////////////////////////////////////////
	/*
	* Function: DeleteAll.
	* Deletes all nodes of the list.
	*/
	void DeleteAll()
	{
		Node<T> *P = Head;
		while (Head)
		{
			P = Head->getNext();
			delete Head;
			Head = P;
		}
		count = 0;
	}

	////////////////////////////////////////////////////////////////////////
	//InsertEnd 
	//inserts a new node at end if the list
	void InsertEnd(const T &data)
	{
		Node<T> *R = new Node<T>(data);
		if(!Head)
			Head = R;
		else
		{
			Node<T> *P = Head;
			while(P->getNext())
				P = P->getNext();

			P->setNext(R);
		}

		count++;

	}

	////////////////////////////////////////////////////////////////////////
	//RemoveFirst
	//removes and returns the first node from the list
	Node<T>* RemoveFirst()
	{
		Node<T>* p = Head;
		if(Head)
		{
			Head = Head->getNext();
			count--;
			p->setNext(nullptr);
		}
		return p;

	}

	////////////////////////////////////////////////////////////////////////
	// ==== Function toArray()  =====
	// returns an array of const objects T and fills size with returned array size
	const T * LinkedList<T>::toArray(int &size) const
	{
		T * retArr = new T [count]; 
		Node<T>* curPtr = Head;
		int i = 0;
		while (curPtr) 
		{
			retArr[i++] = curPtr->getItem();
			curPtr = curPtr->getNext();			
		} // end while
		size = count;
		return retArr;
	} 


	////////////////////////////////////////////////////////////////////////
	/*
	* Function: Copy Constructor
	* Copies all nodes of the passed linked list to this list.
	* 
	* Parameters:
	*	- data : The linked list to be copied to the current list (this list).
	*/
	
	LinkedList(const LinkedList<T> & L)
	{
		if(!L.Head)	//L is empty
		{
			Head = nullptr;
			count = 0;
			return;
		}

		Head = new Node<T>(L.Head->getItem());	//allocate head node
		Node<T>* tail = Head;		
			
		Node<T>* p = L.Head->getNext();

		while(p)
		{
			Node<T>* R = new Node<T>(p->getItem());	//create a new node
			tail->setNext(R);
			tail = R;
			p = p->getNext();
		}
		count = L.count;
	}

	////////////////////////////////////////////////////////////////////////
	/*
	* Function: Assignment operator overloading
	* Assigns RHS to this list by copiing all nodes of the passed linked list to this list.
	* 
	* Parameters:
	*	- data : The linked list to be copied to the current list (this list).
	*
	* Return:
	*	a copy of the linked list to enable assignment cascading  L1 = L2 = L3;
	*/
	
	const LinkedList<T>& operator =(const LinkedList<T> & RHS)
	{
		if(Head == RHS.Head) return *this;	//RHS of "=" operator is the same as LHS
		
		if(!RHS.Head)	//L is empty
		{
			Head = nullptr;
			count = 0;
			return *this;
		}

		Head = new Node<T>(RHS.Head->getItem());	//allocate head node
		Node<T>* tail = Head;		
			
		Node<T>* p = RHS.Head->getNext();

		while(p)
		{
			Node<T>* R = new Node<T>(p->getItem());	//create a new node
			tail->setNext(R);
			tail = R;
			p = p->getNext();
		}
		count = RHS.count;
		return *this;
	}



};

#endif	
