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
	����ʱ�亯�������������������Ԫ�صĲ���
	randomseed��Ϊ�˱���ͬʱ���ɶ��Ԫ��ʱ����Ϊ��ͬһ�봦�����ɲ���һ��
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
		update[i] = p;//�ҵ�������Ԫ��ǰ��ȫ���Ĵ��޸�forward[i]ָ�룬����Ϊÿһ���ҵ�С����Ԫ�ص����һ��ָ��
	}

	p = new Node;
	p->data = key;
	p->level = newlevel;
	for (i = 0; i < MAXLEVEL; i++)
	{
		if (i <= newlevel)
		{
			p->forward[i] = update[i]->forward[i];
			update[i]->forward[i] = p;//�ڵ�ǰ����С��Ԫ�ز���ʱ������forward[i]ָ�룬ָ����Ԫ��
		}
		else
		{
			p->forward[i] = NULL;//�������ϣ�forward[i]���ݶ�ΪNULL
		}
	}
	Head->data++;//���Ӽ���
}

Node* SkipList::search(int key)
{
	/*
	����߲㿪ʼ������ǰѰ��Ԫ�أ�����ǰԪ�ش��ڲ���ֵ/��ǰΪ��ʱ������һ��
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
				t = t->forward[i];//�ҵ���ɾ��Ԫ��ǰ��ȫ���Ĵ��޸�forward[i]ָ�룬����Ϊÿһ���ҵ�С����Ԫ�ص����һ��ָ��
			}
			update[i] = t;
		}
		for (int i = 0; i <= p->level; i++)
		{
			update[i]->forward[i] = p->forward[i];//�ڵ�ǰ����С��Ԫ�ز���ʱ������forward[i]ָ�룬ָ���һ��Ԫ��
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
		m = p->forward[0];//mָ���һ����p��mǰ��ɾ��p�����һ����Ȼ����
		delete p;
		p = m;
	}
	for (int i = 0; i < MAXLEVEL; i++)
	{
		Head->forward[i] = NULL;//����head����forwardָ��Ϊ��
	}
}

void SkipList::display()
{
	Node* p = Head->forward[0];
	cout << Head->data << ": ";//Ԫ����Ŀ
	while (p)
	{
		cout << p->data << " ";//Ԫ��
		p = p->forward[0];
	}
}
