#include<iostream>
#include"SkipList.h"
#include<string>
using namespace std;
bool cmp(const int, const int)
{
	return false;
}
string start = "-> Input command: |create| |insert| |search| |delete| |empty| |display| |exit|";
string notfound = "ERROR! Item not found";

void create(SkipList &n)
{
	n.empty();
	cout << "Input total number of elements:" << endl;
	int o,j;
	cin >> o;
	cout << "Input elements: distinct by spacebar (1 - 999)" << endl;
	for (int i = 0; i < o; i++)
	{
		cin >> j;
		n.insert(j);
	}
	cout << "New skip list created" << endl;
	n.display();
	cout<< endl;
}

void insert(SkipList &N)
{
	cout << "Input the element you want to insert: (1 - 999)" << endl;
	int k;
	cin >> k;
	N.insert(k);
	cout << "Element insert successful" << endl;
	N.display();
	cout << endl;
}

void deletel(SkipList &N)
{
	cout << "Input the element you want to delete: (1 - 999)" << endl;
	int k;
	cin >> k;
	if (N.deleten(k))
	{
		cout << "Delete element successful" << endl;
		N.display();
		cout << endl;
	}
	else
	{
		cout << notfound << endl;
	}
}

void search(SkipList &n)
{
	cout << "Input the integer you want to search:" << endl;
	int t;
	cin >> t;
	Node *k = n.search(t);
	if (k)
	{
		cout << "Item found" << endl << endl;
	}
	else
	{
		cout << notfound << endl;
	}
}

void empty(SkipList& n)
{
	n.empty();
	cout << "Skip list emptied" << endl;
}
/*
int main()
{
	cout << "test" << endl;

	system("pause");
}
*/

int main()
{
	cout << "C++ SkipList manage: data type INT    By TomatoVampire 2019" << endl;
	cout << start << endl;
	string command;
	SkipList N;
	while (cin >> command)
	{
		if (command == "create")
		{
			create(N);
		}
		else if (command == "insert")
		{
			insert(N);
		}
		else if (command == "delete")
		{
			deletel(N);
		}
		else if (command == "search")
		{
			search(N);
		}
		else if (command == "destroy")
		{

		}
		else if (command == "empty")
		{
			empty(N);
		}
		else if (command == "display")
		{
			N.display();
			cout << endl;
		}
		else if (command == "exit")
		{
			break;
		}
		else
		{
			cout << "Command not found" << endl;
		}
		cout << endl;
		cout << start << endl;
	}
	system("pause");
}
