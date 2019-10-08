#include <iostream>
#include "my_memory.h"

using namespace std;


void CheckDefaultConstr()
{
	my_unique_ptr<int> uptr;

	if (uptr.isNullptr())
		cout << "default constructor check... OK\n";
	else
		cout << "ERROR: default constructor creates dangling pointer or isNullptr doesn\'t work properly !!!\n";
}


void CheckPointerConstr()
{
	my_unique_ptr<char> uptr{ new char{ 'a' } };

	if (*uptr == 'a')
		cout << "pointer constructor check... OK\n";
	else
		cout << "ERROR: pointer constructor fails !!!\n";
}


void CheckMoveConstr()
{
	my_unique_ptr<int> uptr1{ new int{ 7 } };
	my_unique_ptr<int> uptr2{ move(uptr1) };

	if (*uptr2 == 7)
		cout << "Move constructor... OK\n";
	else
		cout << "ERROR: move constructor fails !!!\n";
}

/*
void CheckCopyConstr()
{
	my_unique_ptr<int> uptr1{ new int{ 7 } };
	my_unique_ptr<int> uptr2{ uptr1 };

	cout << "ERROR: Copy constructor isn\'t disabled !!!\n";
}
*/

void CheckDereferenceOp()
{
	my_unique_ptr<int> uptr{ new int{ 7 } };

	if (*uptr == 7)
		cout << "Dereference operator... OK\n";
	else
		cout << "ERROR: dereference operator fails !!!\n";
}


void CheckMemberOp()
{
	struct S
	{
		int a{ 3 };
		int b{ 8 };
	};

	my_unique_ptr<S> uptr{ new S };

	if (uptr->b == 8)
		cout << "Member dereference operator (->) ... OK\n";
	else
		cout << "ERROR: member dereference operator (->) fails !!!\n";
}


void CheckMoveAssign()
{
	my_unique_ptr<int> uptr1{ new int{ 7 } };
	my_unique_ptr<int> uptr2;

	uptr2 = move(uptr1);

	if (*uptr2 == 7)
		cout << "Move assignment... OK\n";
	else
		cout << "ERROR: move assignment fails !!!\n";

	// Linked list test.
	// if something goes wrong in this test,
	// it will be detected by sanitizer

	struct Node
	{
		int val{ 0 };
		my_unique_ptr<Node> next;
	};

	my_unique_ptr<Node> head{ new Node };			// constructing linked list
	head->next = my_unique_ptr<Node>{ new Node };	// of two nodes

	head->next = move(head->next->next);		// removing the second node
}

/*
void CheckCopyAssign()
{
	my_unique_ptr<int> uptr1{ new int{ 7 } };
	my_unique_ptr<int> uptr2;

	uptr2 = uptr1;

	cout << "ERROR: Copy assignment isn\'t disabled !!!\n";
}
*/


int main()
{
	CheckDefaultConstr();
	CheckPointerConstr();
	CheckMoveConstr();
	//CheckCopyConstr();	// ATTENTION! This function SHOULD BE A CRITICAL ERROR and prevent 
						// the program from compiling. Once you ensure it does so, 
						// COMMENT OUT the function call and the function itself!

	CheckDereferenceOp();
	CheckMemberOp();

	CheckMoveAssign();
	//CheckCopyAssign();	// ATTENTION! This function SHOULD BE A CRITICAL ERROR and prevent 
						// the program from compiling. Once you ensure it does so, 
						// COMMENT OUT the function call and the function itself!

	return 0;
}