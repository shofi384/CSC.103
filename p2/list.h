/******************************************************************
This is the header file for our SORTED linked list class.  We will
implement a singly-linked list that stores its data items in order,
so that walking through the list from the root node to the end will
access data items in increasing order.  We can state things a bit more
formally with a class invariant:

Class invariant: 
1. the root pointer points to the first node in the list, and for 
every other node in the list, the next field of that node points 
to the next node in the list.

2. A node in the list is the last node if and only if it has a null 
next pointer.  Similarly, the list is empty if and only if the root 
pointer is null.

3. Finally, we also require that the list elements are stored in increasing
order, i.e., for any node in the list (call it "Node"), we have that
if Node.next is not null, then (Node.next)->data > Node.data
*********************************************************************/

#pragma once

#include <iostream>
using std::ostream; /* for our operator<< declaration */

namespace csc212
{
	typedef unsigned long val_type;
	/* this typedef statement makes our code a bit more re-usable for other
	 * situations, but it still requires changing the code, re-compiling the
	 * new version, etc...  later on we'll see a better way to do this
	 * (template classes). */

	struct listNode
	{
		/* constructors: */
		listNode();
		listNode(val_type x, listNode* pNext = 0);

		/* data members: */
		val_type data; //the data for the node
		listNode* next; //pointer to the next node in the list
	};

	class list
	{
	public:
		/* constructors: */
		list();
		list(const list& L);

		/* destructor: */
		~list();

		/* operators: */
		list& operator=(const list& L);
		friend bool operator==(const list& L1, const list& L2);
		friend bool operator!=(const list& L1, const list& L2);
		friend ostream& operator<<(ostream& o, const list& L);

		/* member functions to manipulate list: */

		/* pre: none/suff. memory
		 * post: x is inserted (in order) into the list */
		void insert(val_type x);

		/* pre: none
		 * post: x is removed from the list if present */
		void remove(val_type x);

		/* pre: none
		 * post: all items are removed from the list */
		void clear();

		/* pre: none
		 * post: list is unaffected
		 * return: true iff list is empty */
		bool isEmpty();

		/* pre: none
		 * post: list is unaffected
		 * return: boolean that is true iff x was found */
		bool search(val_type x) const;

		/* pre: none
		 * post: list is unaffected
		 * return: length of the list */
		unsigned long length() const;

		/* pre: none, really.  But note that L1 and L2 are assumed to adhere to
		 * part 3 of our class invariant: they should already be sorted.
		 * post: *this is the result of merging L1 and L2, so that it contains
		 * the union of the elements of L1 and L2, in order. */
		void merge(const list& L1, const list& L2);

		/* pre: none
		 * post: the list contains up to n randomly chosen elements in the
		 * range 0..k-1
		 * NOTE: this will only work when val_type is an integer type... */
		void randomFill(unsigned long n, unsigned long k);

		/* pre: none (other than the class invariants)
		 * post: *this will be set to the intersection of L1 and L2 */
		void intersection(const list& L1, const list& L2);

	private:
		listNode* root; /* points to the root.
						   Empty list is described by root == 0 */
	};
}
