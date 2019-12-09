#pragma once
#define MAXLEVEL 8
struct Node
{
	int data;
	Node* forward[MAXLEVEL];
	int level;
};

class SkipList
{
private:
	int num;
	//int level;
	Node* Head;
	int randomSeed;
public:
	SkipList();
	~SkipList();
	int randL();
	void insert(int key);
	Node* search(int key);
	int deleten(int key);
	void empty();
	void display();
};