/* This is the implementation file for the queue, where you will define how the
 * abstract functionality (described in the header file interface) is going to
 * be accomplished in terms of explicit sequences of C++ statements. */

#include "queue.h"
#include <stdio.h>

/*Note that we will use the following "class invariants" for our data members:
1. frontIndx is the index of the element at the front of the queue, if any.
2. nextBackIndx is the index that is one after the back of the queue.
3. the elements data[frontIndx...nextBackIndx-1] are the valid elements
	of the queue, where each index in the range [frontIndx...nextBackIndx-1]
	is reduced modulo qArraySize ("modulo" === remainder === %-operator in C)
4. the empty queue will be represented by frontIndx == nextBackIndx
As a result of invariant 4, we must have that the queue is full when
nextBackIndx is one away from frontIndx: otherwise an insertion will make
the queue appear to be empty.  Note that "away from" in the preceding sentence
doesn't necessarily mean "one less" due to the circular way we use the array.*/

namespace csc212
{
	queue::queue()
	{
		/* initialize the queue to be empty. */
		this->nextBackIndx = 0;
		this->frontIndx = 0;
	}

	queue::~queue()
	{
		/* since we did not dynamically allocate any memory,
		 * there is nothing for us to release here.  */
	}

	unsigned long queue::getBack()
	{
		/* TODO: write this function */
		//note: if the precondition is not met, then this function's
		//return value will not have the desired meaning, if it has any at all.
		return 0; //just so it compiles...
	}
	unsigned long queue::getFront()
	{
		return this->data[this->frontIndx];
		//see the remarks for getBack
	}
	unsigned long queue::getCapacity()
	{
		return csc212::qArraySize - 1;
	}

	unsigned long queue::getSize()
	{
		/* TODO: write this function */
		return 0; //just so it compiles...
	}

	bool queue::isEmpty()
	{
		return (this->nextBackIndx == this->frontIndx);
	}

	bool queue::isFull()
	{
		/* TODO: write this function */
		return false; //just so it compiles...
	}

	bool queue::push(unsigned long v)
	{
		/* TODO: write this function */
		return true; //just so it compiles...
	}

	unsigned long queue::pop()
	{
		/* TODO: write this function */
		return 0; //just so it compiles...
	}

	void queue::erase()
	{
		/* TODO: write this function */
	}

	ostream& operator<<(ostream& o, const queue& q)
	{
		unsigned long i;
		for(i=q.frontIndx; i!=q.nextBackIndx; i=(i+1) % csc212::qArraySize)
			o << q.data[i] << "  ";
		return o;
	}
	void queue::print(FILE* f)
	{
		for(unsigned long i=this->frontIndx; i!=this->nextBackIndx;
				i=(i+1) % csc212::qArraySize)
			fprintf(f, "%lu ",this->data[i]);
		fprintf(f, "\n");
	}
}
