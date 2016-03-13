/********************************************
This is a simple test program for the BST
*********************************************/

#include <stdio.h>
#include <iostream>
#include <cstdlib>
using std::cin;
using std::cout;
using std::endl;
#include "searchTree.h"
using namespace csc212;

/* locations for graphical output: */
const char* tmpdot = "/tmp/csc212bstree.dot";
const char* tmpsvg = "/tmp/csc212bstree.svg";
const char* dotcmd_fmt = "dot -Tsvg -o %s %s";
const size_t cmdLen = 512;
char dotcmd[cmdLen];

void fillRandom(Tree& T, size_t n, size_t k)
{
	T.clear();
	for (unsigned long i = 0; i < n; i++) {
		T.insert(rand()%k);
	}
}

int main()
{
	snprintf(dotcmd,cmdLen,dotcmd_fmt,tmpsvg,tmpdot);
	FILE* dotout;
	cout << "***************Welcome to the Binary Search Tree test program***************\n\n";
	csc212::val_type A[] = {5,2,3,1,4,8,9,6,7,0};

	//dump the array into the tree:
	Tree T(A,10);
	
	//if you want to test assignment:
	/*Tree S(A,10);
	Tree T;
	T.insert(77);
	T.insert(88);
	T = S;*/

	//if you want to test the copy constructor:
	//Tree S(A,10);
	//Tree T(S);

	char c;
	csc212::val_type x;
	while(true)
	{
		cout << "In order, pOst order, Pre order, Add, Remove, Search, miN, maX, siZe, numLeaves, Clear, Height, Exit, Draw, Write dot, Make random\n";
		cin >> c;
		c = tolower(c);
		switch(c)
		{
		case 'i':
			T.inOrder();
			cout << endl;
			break;
		case 'o':
			T.postOrder();
			cout << endl;
			break;
		case 'p':
			T.preOrder();
			cout << endl;
			break;
		case 'a':
			cout << "enter a value to insert: ";
			cin >> x;
			T.insert(x);
			break;
		case 'r':
			cout << "enter a value to remove: ";
			cin >> x;
			T.remove(x);
			break;
		case 's':
			cout << "what do you want to search for? ";
			cin >> x;
			if(T.search(x))
				cout << x << " was found.\n";
			else
				cout << x << " was not found\n";
			break;
		case 'n':
			cout << "the min value in the tree is " << T.min() << endl;
			break;
		case 'x':
			cout << "the max value in the tree is " << T.max() << endl;
			break;
		case 'z':
			cout << "there are " << T.size() << " values in the tree.\n";
			break;
		case 'l':
			cout << "there are " << T.numLeaves() << " leaf nodes in the tree.\n";
			break;
		case 'c':
			T.clear();
			break;
		case 'h':
			cout << "the height of the tree is " << T.height() << endl;
			break;
		case 'd':
			T.drawTree();
			break;
		case 'w':
			T.drawDot(tmpdot);
			/* convert to svg as well: */
			dotout = popen(dotcmd,"r");
			pclose(dotout);
			break;
		case 'm':
			cout << "How many values? ";
			cin >> x;
			fillRandom(T,x,100);
			break;
		case 'e':
			return 0;
		default:
			cout << "please choose an item from the list.";
		}
	}
	return 0;
}
