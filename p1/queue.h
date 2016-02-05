#pragma once

#include <iostream>
using std::ostream;

namespace csc212
{
	/* declaration of our queue class.  For now, it will just store unsigned
	 * long integers. */
	const unsigned long qArraySize = 6; /* NOTE: max size is qArraySize-1 */
	class queue
	{
	public: //this means that the following delcarations are to be part of the public interface

		/* constructor.  called when a variable of this type is created.
		 * pre-condition: sufficient memory, I guess.
		 * post-condition: a new queue is created and initialized to be empty.
		 * */
		queue();

		/* destructor. this is called when the variable is freed
		 * (i.e., when it goes out of scope, or explicitly deleted).
		 * pre-condition: none
		 * post-condition: all queue resources are released.
		 * */
		~queue();

		/********  other member functions  ********/

		/* push function.
		 * Pre-condition: queue is not full.
		 * Post-condition: the unsigned long parameter is inserted at the back
		 * of the queue.
		 * Return value: true indicates that the insertion took place, false
		 * indicates that the queue was full.
		 * */
		bool push(unsigned long);
		
		/* pop function.
		 * Pre-condition: queue is not empty
		 * Post-condition: element at the front of the queue is removed
		 * Return value: the element at the front of the queue
		 * prior to the function call is returned.
		 * */
		unsigned long pop();

		/* isEmpty function.
		 * Pre-condition: none.
		 * Post-condition: queue is un-affected.
		 * Return value: boolean indicating whether or not the queue is empty.
		 * */
		bool isEmpty();

		/* isFull function.
		 * Pre-condition: none.
		 * Post-condition: queue is un-affected.
		 * Return value: a boolean indicating whether or not the queue is full.
		 * */
		bool isFull();

		/* getBack function.
		 * Pre-condition: queue is not empty.
		 * Post-condition: queue is un-affected.
		 * Return value: the element at the back of the queue is returned.
		 * */
		unsigned long getBack();

		/* getFront function.
		 * Pre-condition: queue is not empty.
		 * Post-condition: queue is un-affected.
		 * Return value: the element at the front of the queue is returned.
		 * */
		unsigned long getFront();

		/* getSize function.
		 * Pre-condition: none.
		 * Post-condition: queue is un-affected.
		 * Return value: the number of elements in the queue.
		 * */
		unsigned long getSize();

		/* getCapacity function.
		 * Pre-condition: none.
		 * Post-condition: queue is un-affected.
		 * Return value: the maximum number of elements that the queue can store.
		 * */
		unsigned long getCapacity();

		/* erase function.
		 * Pre-condition: none.
		 * Post-condition: queue is empty.
		 * */
		void erase();

		/* printing functions */
		friend ostream& operator<<(ostream& o, const queue& q);
		void print(FILE* f); /* f should be open... */

	private:
		unsigned long data[qArraySize]; /* storage for elements of queue */
		unsigned long frontIndx; /* index of the front element */
		unsigned long nextBackIndx; /* index _after_ the back element */
	};
}
