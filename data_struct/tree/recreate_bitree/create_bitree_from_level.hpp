#include<iostream>
#include<vector>
struct tree_node
{
	char data;
	tree_node * left;
        tree_node * right;
};
typedef tree_node tree;

struct queue_node
{
	char data;
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

void en_queue(queue& Q, int  x)
{
	queue_node * p=new queue_node;
	p->next=NULL;
	p->data=x;
	Q.rear->next=p;
	Q.rear=p;
	
}


bool de_queue(queue & Q, int& x)
{
	if (is_empty(Q))
		return false;
	queue_node* p=Q.front->next;
	x=p->data;
	Q.front->next=p->next;
	if ( Q.rear== p )
		Q.rear=Q.front;
	delete p;
	return true;
}



tree* create_tree(vector<char> & vec)
{

}
