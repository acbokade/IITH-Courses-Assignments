#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct Queue{  //struct for queue
	int front;
	int rear;
	int size;
	int *arr;
	int max_length;
};

struct Queue *create_queue(int length) //creating queue with legnth as given max_length
{
	struct Queue *queue =(struct Queue*)malloc(sizeof(struct Queue));
	queue->front=0;
	queue->size=0;
	queue->max_length=length;
	queue->rear=queue->max_length-1;
	queue->arr=(int*)malloc(length*sizeof(int));
	return queue;
}

int isFull(struct Queue *queue) //returns 1 if queue is full else 0
{
	return (queue->size==queue->max_length);
}

int isEmpty(struct Queue *queue) //returns 1 if queue is empty else 0
{
	return (queue->size==0);
}

void enqueue(struct Queue *queue,int value) //enqueuing a value in queue
{
	if(isFull(queue))
		return;
	queue->rear=(queue->rear+1)%queue->max_length;
	queue->arr[queue->rear]=value;
	queue->size++;
}
 
int dequeue(struct Queue *queue) //dequeues element from queue
{
	if(isEmpty(queue))
		return INT_MIN;
	int dequeued_element=queue->arr[queue->front];
	queue->front++;
	queue->size--;
	return dequeued_element;
}

void print_queue(struct Queue *queue) //printing elements of queue
{
	int i;
	if(queue->rear<queue->front)
	{
		for(i=queue->front;i<=queue->max_length;i++)
			printf("%d ",queue->arr[i]);
		for(i=0;i<=queue->rear;i++)
			printf("%d ",queue->arr[i]);
	}
	else
	{
		for(i=queue->front;i<=queue->rear;i++)
			printf("%d ",queue->arr[i]);
	}
	printf("\n");
}

void delete_queue(struct Queue *queue) //deleting queue
{
	if(queue!=NULL)
	{
		free(queue->arr); //freeing array
		free(queue); //freeing queue
	}	
}

struct node{ //struct for node of ll
	int data;
	struct node *next;	
};

struct Graph{ //struct for graph
	int vertices;
	struct node **adj; //pointer to array of adjacency lists
};

struct node* create_node(int value) //creating node of ll
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=value;
	newnode->next=NULL;
	return newnode;
}

struct node* insertll(struct node *head,int value) //inserting value in ll
{
	struct node *newnode=create_node(value);
	struct node *temp=head;
	if(head==NULL)
	{
		head=newnode;
		return head;
	}
	while(temp->next!=NULL)
	{
		temp=temp->next;
	}
	temp->next=newnode;
	return head;
}

void printll(struct node *head) //printing ll
{
	while(head!=NULL)
	{
		printf("%d ",head->data);
		head=head->next;
	}
	printf("\n");
}

void deletell(struct node *head) //deleting ll
{
	struct node *temp=head;
	if(head!=NULL)
	{
		while(temp->next!=NULL)
		{
			temp=head->next;
			free(head);
			head=temp;
		}
		free(head);
	}
}

struct Graph* create_graph(int v) //creating graph 
{
	struct Graph *graph =(struct Graph*)malloc(sizeof(struct Graph));
	graph->adj=(struct node **)malloc((v+1)*sizeof(struct node*)); //dynamically allocating adjacency lists with size of given vertices+1 
	graph->vertices=v;
	int i;
	for(i=1;i<=v;i++)
		graph->adj[i]=NULL;
	return graph;
}

void add_edge(struct Graph *graph,int u,int v) //adding edge in graph
{
	graph->adj[u]=insertll(graph->adj[u],v);
}

void print_graph(struct Graph *graph,int v) //printing graph  
{
	int i;
	for(i=1;i<=v;i++)
	{
		struct node *temp=graph->adj[i];
		while(temp!=NULL)
		{
			printf("%d ",temp->data);
			temp=temp->next;
		}
		printf("\n");
	}
}

void delete_graph(struct Graph *graph) //deleting graph
{
	int i;
	if(graph!=NULL)
	{
		for(i=1;i<=graph->vertices;i++)
			deletell(graph->adj[i]);
	}
	free(graph);
}

int isEdge(struct Graph *graph,int src,int dest) //checking if edge exists between src and dest
{
	struct node *temp=graph->adj[src];
	if(temp==NULL)
		return 0;
	else
	{
		while(temp!=NULL)
		{
			if(temp->data==dest)
				return 1;
			temp=temp->next;
		}
	}
	return 0; 
}

void BFS(struct Graph *graph,int src,struct node **path,char **color,int *parent) //BFS on given graph 
{
	//00 stands for white, 01 stands for gray and 10 stands for black
	int i,v;
	v=graph->vertices;
	for(i=1;i<=v;i++)
	{
		color[i][0]=0;color[i][1]=0; //initially all vertices are colored white 
		parent[i]=-1; //-1 stands for NILL
	}
	struct Queue *queue=create_queue(v+1);
	enqueue(queue,src);
	*path=insertll(*path,src); //linked list containing vertices in order which are colored black during BFS 
	while(!isEmpty(queue)) ///running till queue is not empty
	{	
		int popped=dequeue(queue); //dequeing element from queue
		struct node *temp=graph->adj[popped];
		while(temp!=NULL) //checking all adjacent nodes of dequeued element 
		{
			if(color[temp->data][0]==0 && color[temp->data][1]==0)//enqueing those vertices which are colored white
			{
				color[temp->data][0]=1;color[temp->data][1]=0;//coloring them gray
				parent[temp->data]=popped; //assigning parent of these vertices
				enqueue(queue,temp->data); //enqeuing in queue
				*path=insertll(*path,temp->data); //inserting them in path 
			}
			temp=temp->next;
		}
		color[popped][0]=0;color[popped][1]=1;//coloring them black
	}
	delete_queue(queue); //deleting queue
}

int main()
{
	int digit,num,src,dest,i;
	struct Graph *graph=NULL;
	struct node *path=NULL;
	char **color=NULL;
	int *parent=NULL;
	while((digit=fgetc(stdin))!=EOF)
	{
		if(digit=='N')
		{
			delete_graph(graph); //delete previous graph 
			if(parent!=NULL)
				free(parent); //freeing parent array
			if(color!=NULL)
				free(color); //freeing color matrix
			deletell(path);
			path=NULL;
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&num);
			graph=create_graph(num); //num is number of vertices here
			color=(char**)malloc((num+1)*sizeof(char*)); //dynamically allocating memory for color and parent 
			for(i=1;i<=num;i++) 
				color[i]=(char*)malloc(2*sizeof(char));

			parent=(int*)malloc((num+1)*sizeof(int)); 
		}
		else if(digit=='E')
		{
			digit=fgetc(stdin);//gets space
			scanf("%d",&src);
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
			{
				scanf("%d",&dest);
				add_edge(graph,src,dest); //adding edge
			}
		}
		else if(digit=='?')
		{
			digit=fgetc(stdin);//gets space
			scanf("%d",&src);
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&dest);
			printf("%d\n",isEdge(graph,src,dest)); //printing 1 if edge exits else 0
		}
		else if(digit=='B')
		{
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&src);
			if(path!=NULL && path->data==src) //if BFS has already run previously then no need to run it again on same source vertex
				printll(path);
			else
			{
				deletell(path);
				path=NULL;
				BFS(graph,src,&path,color,parent); //running BFS from src vertex 
				printll(path); //priting the vertices in order of run of BFS
			}
		}
		else if(digit=='P')
		{
			digit=fgetc(stdin);//gets space
			scanf("%d",&src);
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&dest);
			if((path !=NULL && path->data!=src) || path ==NULL) //if the new src is not already in path's head then running BFS on new src
			{
				deletell(path);
				path=NULL;
				BFS(graph,src,&path,color,parent);
			}
			//else the BFS has already run on given src, hence no need to run it again
			if(color[dest][0]==0 && color[dest][1]==0) // if destination is white meaning it is not visited during run of BFS on src vertex
				printf("-1\n"); //meaning the destination cant be reached from given src
			else
			{
				int *shortest_path=(int*)malloc((graph->vertices+1)*sizeof(int)); //array for shortest path
				int count=0;
				while(parent[dest]!=src) //storing parents of dest recursively in shortest path array
				{
					shortest_path[count]=dest;
					dest=parent[dest];
					count++;
				}
				shortest_path[count]=dest;
				count++;
				shortest_path[count]=parent[dest];
				for(i=count;i>=0;i--) //printing shortest path
				{
					printf("%d ",shortest_path[i]);
				}
				printf("\n");
				free(shortest_path); //freeing shortest path
			}
		}
	}
	//print_graph(graph,graph->vertices);
	return 0;
}