#include<iostream>

struct tree_node
{
	int data;
	tree_node * left;
        tree_node * right;
};
typedef tree_node tree;

struct queue_node
{
	tree_node* p;
	queue_node* next;
};

struct queue
{
	queue_node * front;
	queue_node * rear;
};


void init_queue(queue & Q)
{
	Q.front = Q.rear = new queue_node;
	Q.front ->next = NULL;
}


bool is_empty(queue & Q)
{
	return Q.front == Q.rear;
}

void en_queue(queue& Q, tree_node x)
{
	queue_node * p=new queue_node;
	
}
