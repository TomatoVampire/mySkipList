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
	利用时间函数生成随机数，决定新元素的层数
	randomseed是为了避免同时生成多个元素时，因为在同一秒处理，生成层数一样
	}*/
	srand(time(NULL)+randomSeed);
	randomSeed++;
	return (int)rand() % 9;
}

void SkipList::insert(int key)
{
	Node* p, * update[MAXLEVEL];
	int i, newlevel;
	newlevel = randL();
	for (i = MAXLEVEL-1; i >= 0; i--)
	{
		p = Head;
		while ((p->forward[i] != NULL) && (p->forward[i]->data < key))
		{
			p = p->forward[i];
		}
		update[i] = p;//找到待插入元素前面全部的待修改forward[i]指针，方法为每一层找到小于新元素的最后一个指针
	}

	p = new Node;
	p->data = key;
	p->level = newlevel;
	for (i = 0; i < MAXLEVEL; i++)
	{
		if (i <= newlevel)
		{
			p->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = p;//在当前层数小于元素层数时，更新forward[i]指针，指向新元素
		}
		else
		{
			p->forward[i] = NULL;//层数往上，forward[i]内容都为NULL
		}
	}
	Head->data++;//增加计数
}

Node* SkipList::search(int key)
{
	/*
	从最高层开始慢慢往前寻找元素，当往前元素大于查找值/往前为空时进入下一层
	*/
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
		Node* update[MAXLEVEL];
		Node* t;
		for (int i = MAXLEVEL-1; i >= 0; i--)
		{
			t = Head;
			while ((t->forward[i] != 0) && (t->forward[i]->data < key))
			{
				t = t->forward[i];//找到待删除元素前面全部的待修改forward[i]指针，方法为每一层找到小于新元素的最后一个指针
			}
			update[i] = t;
		}
		for (int i = 0; i <= p->level; i++)
		{
			update[i]->forward[i] = p->forward[i];//在当前层数小于元素层数时，更新forward[i]指针，指向后一个元素
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
		m = p->forward[0];//m指向后一个，p在m前，删除p。最后一个仍然适用
		delete p;
		p = m;
	}
	for (int i = 0; i < MAXLEVEL; i++)
	{
		Head->forward[i] = NULL;//修正head所有forward指针为空
	}
}

void SkipList::display()
{
	Node* p = Head->forward[0];
	cout << Head->data << ": ";//元素数目
	while (p)
	{
		cout << p->data << " ";//元素
		p = p->forward[0];
	}
}
