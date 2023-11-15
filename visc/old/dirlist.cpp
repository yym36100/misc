// dirlist.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "dirent.h"

class Node{
public:
	char data[256];
	Node * next;
	Node(char *n){
		strcpy(data,n);
		next = NULL;
	}
	Node(char *n, Node * y){
		strcpy(data,n);
		next = y;
	}
};


class linkedList{
public:
	Node *head;
	int nritems;
public:
	linkedList(){
		head = NULL;
		nritems = 0;
	}
	void addNode(char *n){
		Node *p;
		nritems++;
		if(head == NULL)
			head = new Node (n, NULL);
		else{
			p=head;
			while(p->next !=NULL)
				p=p->next;
			p->next = new Node (n, NULL);
		}
	}
	void print(){
		char buff[512];
		Node * p;
		printf("nritems = %d\n",nritems);
		p = head;
		while(p != NULL){
			strcpy(buff,"e:/visc/sua/");
			strcat(buff,p->data);
			printf("%s\n",buff);
			p = p->next;
		}
	}
	Node *getNext(Node *c)
	{
		return c->next;
	}
};

int _tmain(int argc, _TCHAR* argv[])
{
	DIR *dir;
	struct dirent *ent;
	int cnt = 0;
	linkedList mylist;
	dir = opendir ("e:/visc/sua");

	if (dir == NULL) {
		fprintf (stderr, "Directory tests/1 not found\n");
		abort ();
	}


	/* Read entries */
	while ((ent = readdir (dir)) != NULL) {

		if(ent->d_type == DT_REG)
		{
			//printf ( "%d: %s %d\n", ++cnt,ent->d_name,ent->d_type);
			mylist.addNode(ent->d_name);
		}
	}
	closedir (dir);

	//mylist.print();

	//get one by one
	{
		Node *i;
		i = mylist.head;
		while(i)
		{
			printf("%s\n",i->data);
			i = mylist.getNext(i);
		}
		
	}

	return 0;
}

