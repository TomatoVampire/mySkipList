#include"SkipList.h"
#include<ctime>
#include "stdlib.h"
#include<iostream>
using namespace std;

SkipList::SkipList()
{
	Head = new Node;
	Head->data = 0;
	Head->level = MAXLEVEL;
	num = 0;
	randomSeed = 0;
	for (int i = 0; i < MAXLEVEL; i++)
	{
		Head->forward[i] = NULL;
	}
}

SkipList::~SkipList()
{
	delete[]Head;
}

int SkipList::randL()
{
	/*
	int i, j=0, t;
	for (i = 0; i < MAXLEVEL; i++)
	{
		srand((unsigned int)time(NULL));//use time to create real random number
		t = rand() % 10;
		if (t <= 5)
		{
			j++;
		}
	}*/
	//return j;
	srand(time(NULL)+randomSeed);
	randomSeed++;
	return (int)rand() % 9;
}

void SkipList::insert(int key)
{
	Node* p, * update[MAXLEVEL];
	int i, newlevel;
	newlevel = randL();
	//cout << newlevel << endl;
	for (i = MAXLEVEL-1; i >= 0; i--)
	{
		p = Head;
		while ((p->forward[i] != NULL) && (p->forward[i]->data < key))
		{
			p = p->forward[i];
		}
		update[i] = p;
	}

	p = new Node;
	p->data = key;
	p->level = newlevel;
	for (i = 0; i < MAXLEVEL; i++)
	{
		if (i <= newlevel)
		{
			p->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = p;
		}
		else
		{
			p->forward[i] = NULL;
		}
	}
	Head->data++;
}

Node* SkipList::search(int key)
{
	Node* p = Head;
	for (int i = MAXLEVEL-1; i >= 0; i--)
	{
		while ((p->forward[i] != NULL) && (p->forward[i]->data <= key))
		{
			if (p->forward[i]->data == key) return p->forward[i];
			p = p->forward[i];
			
		}
		
	}
	return nullptr;
}

int SkipList::deleten(int key)
{
	Node* p =search(key);
	
	if( p == NULL ) return NULL;
	else
	{
		//Node* del = p->forward[0];
		Node* update[MAXLEVEL];
		Node* t;
		for (int i = MAXLEVEL-1; i >= 0; i--)
		{
			t = Head;
			while ((t->forward[i] != 0) && (t->forward[i]->data < key))
			{
				t = t->forward[i];
			}
			update[i] = t;
		}
		for (int i = 0; i < MAXLEVEL; i++)
		{
			//if (del->forward[i] == NULL) break;
			update[i]->forward[i] = p->forward[i];
		}
		Head->data--;
		return 1;
	}
}

void SkipList::empty()
{
	Node* p = Head->forward[0];
	Node* m = p;
	Head->data = 0;
	
	while (m)
	{
		m = p->forward[0];
		delete p;
		p = m;
	}
	for (int i = 0; i < MAXLEVEL; i++)
	{
		Head->forward[i] = NULL;
	}
}

void SkipList::display()
{
	Node* p = Head->forward[0];
	cout << Head->data << ": ";
	while (p)
	{
		cout << p->data << " ";
		p = p->forward[0];
	}
}
