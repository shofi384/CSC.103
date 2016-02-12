/***********************************************************
This is a simple test program for the linked list class.
************************************************************/

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "list.h"
using namespace csc212;

int main(void)
{
	cout << "****************Welcome to the list test program*****************\n\n\n";

	char input;
	csc212::val_type elt;
	csc212::list L[2]; //an array of two lists. Question: how and when are they initialized?
	unsigned long curIndx = 0; //the list that is currently being manipulated.
	csc212::list mergeList;

	//if you want to have a different sequence of lists (when you use randomFill()) then
	//un-comment the following line and change the number in the parameter.
	//srand(0);

	while(true)
	{
		cout << "\nWhat would you like to do to list[" << curIndx << "]?\n(I)nsert an element | ";
		cout << "(R)emove an element | Determine if the list is (E)mpty\n";
		cout << "Find the (L)ength of the list | (C)lear the list | (M)erge lists\n";
		cout << "(P)rint lists | (S)witch current list | (T)est for equality\n";
		cout << "(F)ill the list randomly | Searc(H) the list | I(N)tersect the lists\n";
		cout << "(A)ssign current list | (Q) Quit the program\n";

		cin >> input;

		input = ::tolower(input);
		switch(input)
		{
		case 'i':
			cout << "Enter an item to insert: ";
			cin >> elt;
			L[curIndx].insert(elt);
			break;
		case 'r':
			cout << "Enter an item to remove: ";
			cin >> elt;
			L[curIndx].remove(elt);
			break;
		case 'e':
			if(L[curIndx].isEmpty())
				cout << "Current list is empty.\n";
			else
				cout << "Current list is non-empty.\n";
			break;
		case 'l':
			cout << "Current list contains " << L[curIndx].length() << " item(s).\n";
			break;
		case 'c':
			L[curIndx].clear();
			cout << "Current list has been cleared.\n";
			break;
		case 'm':
			mergeList.merge(L[0],L[1]);
			cout << "The merged list contains " << mergeList << endl;
			break;
		case 'n':
			mergeList.intersection(L[0],L[1]);
			cout << "The intersection list contains " << mergeList << endl;
			break;
		case 'p':
			cout << "L[0] = " << L[0] << endl;
			cout << "L[1] = " << L[1] << endl;
			break;
		case 's':
			curIndx = (curIndx+1)%2;
			cout << "Current index has been set to " << curIndx << ".\n";
			break;
		case 't':
			if(L[0] == L[1])
				cout << "Lists are equal.\n";
			else
				cout << "Lists are not equal.\n";
			break;
		case 'f':
			L[curIndx].randomFill(10,10);
			break;
		case 'h':
			cout << "Enter item to search for: ";
			cin >> elt;
			if(L[curIndx].search(elt))
				cout << "item was found.\n";
			else
				cout << "item was not found.\n";
			break;
		case 'a':
			L[(curIndx+1)%2] = L[curIndx];
			cout << "Assigned list L[" << (curIndx+1)%2 << "] = L[" << curIndx << "].\n";
			break;
		case 'q':
			return 0;
			break;
		default:
			cout << "I'm sorry I don't understand that selction. Please choose an item from the list.\n";
		}
	}
	return 0;
}
