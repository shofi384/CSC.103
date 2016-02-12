/****************************************************
implementation file for linked list class.
*****************************************************/

#include "list.h"
#include <stdlib.h> //for rand()

namespace csc212
{
	/* listNode stuff: */
	listNode::listNode()
	{
		this->next = 0; //set the next pointer to be null
	}

	listNode::listNode(val_type x, listNode *pNext)
	{
		this->data = x;
		this->next = pNext;
	}


	/* linked list implementation: */
	list::list()
	{
		this->root = 0; //initialize the list to be empty
		//remember 0 == NULL, which is never memory you own.
	}

	list::list(const list &L)
	{
		/* TODO: write this. */
		this->root = 0;
	}

	list::~list()
	{
		this->clear(); //delete all nodes, deallocating memory
	}

	list& list::operator=(const list& L)
	{
		/* TODO: write this. */
		return *this;
	}

	bool operator==(const list& L1, const list& L2)
	{
		/* TODO: write this. */
		return false;  //just so it compiles.  you of course need to do something different.
	}
	bool operator !=(const list& L1, const list& L2)
	{
		return !(L1==L2);
	}

	void list::insert(val_type x)
	{
		/* TODO: write this. */
	}

	void list::remove(val_type x)
	{
		/* TODO: write this. */
	}

	bool list::isEmpty()
	{
		return (this->root == 0);
	}

	void list::clear()
	{
		//idea: repeatedly delete the root node...
		listNode* p;
		while((p = root)) //yes, I do mean "=", not "=="
		{
			root = p->next;
			delete p;
		}
	}

	ostream& operator<<(ostream& o, const list& L)
	{
		listNode* p;
		p = L.root;
		while(p)
		{
			o << p->data << " ";
			p = p->next;
		}
		return o;
	}

	bool list::search(val_type x) const
	{
		listNode* p;
		p = root;
		while(p && p->data != x) //again, short circuit evaluation is important...
			p = p->next;
		if(p) 
			return true;
		else 
			return false;
	}

	unsigned long list::length() const
	{
		/* TODO: write this. */
		return 0; //just so it compiles.  you of course need to do something different.
	}

	void list::merge(const list& L1, const list& L2)
	{
		/* TODO: write this. */
		//this algorithm should run in LINEAR TIME and set *this
		//to be the union of L1 and L2, and furthermore the list should remain sorted.
	}

	void list::randomFill(unsigned long n, unsigned long k)
	{
		//we want to fill the list with n random integers from 0..k-1
		this->clear(); //reset to the empty list
		unsigned long i;
		for(i=0; i<n; i++)
		{
			this->insert((val_type)(rand()%k));
		}
	}

	void list::intersection(const list &L1, const list& L2)
	{
		/* TODO: write this. */
		//this algorithm should run in LINEAR TIME, setting *this
		//to be the intersection (ordered) of L1 and L2.
	}
}
