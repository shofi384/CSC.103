/******************************************************************
This is the header file for our binary search tree class.  You can
read about binary search trees in our textbook in chapter 10.

To pseudo-formalize our data representation we'll use the following
class invariant:

1. data is stored in nodes, each of which have two pointers (a left
and a right) which point to other nodes in the tree, subject to
the following conditions:

2. for all nodes x in the tree, every node to the left of x has a 
value smaller than that of x, and every node to the right has a value
larger than that of x.  If there are no nodes to the left (or right)
of a given node, this will as usuall be denoted by a null pointer.

3. there is a distinguished node called the root, which has the property
that it is not the left or right of any other node.

4. the empty tree will be represented by a root pointer which is null.

Note: as a result of our phrasing of item 2 above, our tree will store
unique elements (no duplicates).
*********************************************************************/

#pragma once
#include <iostream>
using std::ostream;

namespace csc212
{
	typedef long val_type;

	//we'll keep the details of the treeNode structure hidden from the
	//public interface and define it in the implementation.  For now,
	//all the compiler needs to know is that there exists a treeNode structure...
	struct treeNode;

	//////////////////////simple binary search tree class////////////////////////
	class Tree
	{
	public:
		/////////////////////{con,de}structors//////////////////////
		Tree(); //creates an empty tree
		Tree(val_type* A, unsigned long size); //creates tree from an array
		Tree(const Tree& T); //copy constructor
		~Tree(); //deallocates a tree

		////////////////////other member functions///////////////////////
		void operator=(const Tree& T); //assignment operator.
		bool search(val_type x); //search for x in the tree
		bool insert(val_type x); //returns the opposite of search(x). Does not insert duplicates
		void remove(val_type x); //removes x if x is present
		//note: for remove, use the minimal value of the right subtree for a substitution if needed.
		//It will be easier for the grader if you implement it the same way as I do.
		void preOrder(ostream* o = 0); //prints pre-order traversal of tree.
		void inOrder(ostream* o = 0); //prints in-order traversal of tree.
		void postOrder(ostream* o = 0); //prints post-order traversal of tree.
		val_type min(); //returns min value in tree
		val_type max(); //returns max value in tree
		unsigned long size(); //returns total number of nodes in tree.
		unsigned long numLeaves(); //returns total number of leaves in the tree
		void clear(); //erases a tree.
		unsigned long height(); //returns the height of the tree.
		bool isEmpty(); //tells if tree is empty
		void drawTree(); //displays crapy drawing of tree on the screen
		void drawDot(const char* fname); //slightly less crappy drawing via graphviz
		//this will just print a pre-order traversal to the output stream
		friend ostream& operator<<(ostream& o, Tree& T);

	private:
		treeNode* root;
	};
}
