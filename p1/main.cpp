/* simple test program that allows you to manipulate a single queue. */

#include <iostream>
using std::cin;
using std::cout;
using std::endl;

#include "queue.h"
using namespace csc212;

int main(void)
{
	cout << "****************Welcome to the queue test program*****************\n\n\n";

	char input;
	unsigned long elt;
	csc212::queue Q1; //this will call the constructor and init to the empty queue.

	while(true)
	{
		cout << "\nWhat would you like to do?\n(P) Push an element\n";
		cout << "(O) Pop an element\n(F) Get the front\n(B) Get the back\n";
		cout << "(E) Determine if the queue is empty\n(U) Determine if the queue is full\n";
		cout << "(S) Determine the size of the queue\n(C) Determine the capacity of the queue\n";
		cout << "(R) Print the queue\n(D) Delete all elements of the queue\n";
		cout << "(Q) Quit the program\n";

		cin >> input;

		input = ::tolower(input);
		switch(input)
		{
		case 'p':
			cout << "Enter an item to push: ";
			cin >> elt;
			if(Q1.push(elt))
				cout << "Push successful.\n";
			else
				cout << "Queue is already full.\n";
			break;
		case 'o':
			if(Q1.isEmpty())
				cout << "Queue is already empty.\n";
			else
			{
				elt = Q1.pop();
				cout << elt << " was removed from the front of the queue.\n";
			}
			break;
		case 'f':
			if(Q1.isEmpty())
				cout << "Queue is empty.\n";
			else
			{
				elt = Q1.getFront();
				cout << elt << " is at the front of the queue.\n";
			}
			break;
		case 'b':
			if(Q1.isEmpty())
				cout << "Queue is empty.\n";
			else
			{
				elt = Q1.getBack();
				cout << elt << " is at the back of the queue.\n";
			}
			break;
		case 'e':
			if(Q1.isEmpty())
				cout << "Queue is empty.\n";
			else
				cout << "Queue is non-empty.\n";
			break;
		case 'u':
			if(Q1.isFull())
				cout << "Queue is full.\n";
			else
				cout << "Queue is not full.\n";
			break;
		case 's':
			cout << "The size is " << Q1.getSize() << endl;
			break;
		case 'c':
			cout << "The capacity is " << Q1.getCapacity() << endl;
			break;
		case 'r':
			cout << "From front to back, the queue contains\n" << Q1 << endl;
			break;
		case 'd':
			Q1.erase();
			cout << "Queue has been cleared.\n";
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
