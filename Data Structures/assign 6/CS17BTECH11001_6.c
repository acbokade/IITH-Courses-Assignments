#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

struct node{ //struct for node of ll
	int data;
	int weight; // weight of edge 
	struct node *next;
};

struct Graph{ //struct for graph
	int vertices;
	struct node **adj; //pointer to array of adjacency lists
};

struct node* create_node(int value,int wt) //creating node of ll 
{
	struct node *newnode=(struct node*)malloc(sizeof(struct node));
	newnode->data=value;
	newnode->weight=wt;
	newnode->next=NULL;
	return newnode;
}

struct node* insertll(struct node *head,int value,int wt) //inserting value and weight in ll
{
	struct node *newnode=create_node(value,wt);
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

//min heap
struct heap_node{ //struct for node of a heap 
	int dest;
	int weight; //priority
};

struct Heap{ //struct for heap
	int size;
	int max_size;
	struct heap_node *heapnode;
};

struct Heap *create_Heap(int length) //creating heap with size as given length
{
	struct Heap *minheap=(struct Heap*)malloc(sizeof(struct Heap));
	minheap->size=length;
	minheap->heapnode=(struct heap_node*)malloc((length+1)*sizeof(struct heap_node));
	return minheap;
}

void swap(int *a,int *b) //swapping two integers
{
	int temp;
	temp=*a;
	*a=*b;
	*b=temp;
}
 // 1-based indexing of heap 
int parent(int index) //return parent of index
{
    return index/2;
}

int leftChild(int index) //return left child of index
{
    return (2*index);
}

int rightChild(int index) //return right child of index
{
    return (2*index+1);
}

void minHeapify(struct Heap *minHeap,int index) //minheapify function  
{
	int leftIndex=leftChild(index);
	int rightIndex=rightChild(index);
	int least=index;
	if(leftIndex<=minHeap->size && minHeap->heapnode[leftIndex].weight < minHeap->heapnode[index].weight)
		least=leftIndex;
	if(rightIndex<=minHeap->size && minHeap->heapnode[rightIndex].weight < minHeap->heapnode[least].weight)
		least=rightIndex; //finding least weight among index and left child and right child 
	if(least!=index)
	{
		swap(&minHeap->heapnode[index].dest,&minHeap->heapnode[least].dest); //swapping both entities of node that is dest and weight
		swap(&minHeap->heapnode[index].weight,&minHeap->heapnode[least].weight);
		minHeapify(minHeap,least);
	}
}

void buildHeap(struct Heap *minHeap,int dist[]) //building heap from given dist array
{
	int i;
	for(i=1;i<=minHeap->size;i++)
	{
		minHeap->heapnode[i].dest=i;
		minHeap->heapnode[i].weight=dist[i];
	}
	for(i=(minHeap->size)/2;i>=1;i--)
		minHeapify(minHeap,i);
}

void decreaseKey(struct Heap *minHeap,int destination,int val,int min_dist) //decrease key of destination to given value with condition
{
	int i;
	for(i=1;i<=minHeap->size;i++)
	{
		if(minHeap->heapnode[i].dest==destination)
			break;
	}
	if(val+min_dist<minHeap->heapnode[i].weight)  //d[u]+w(u,v) < d[v], then d[v]=d[u] + w(u,v)
    {        
        minHeap->heapnode[i].weight=val+min_dist; //decrease key
        while(i!=1 && minHeap->heapnode[parent(i)].weight > minHeap->heapnode[i].weight)
        {
            swap(&minHeap->heapnode[parent(i)].dest,&minHeap->heapnode[i].dest);
            swap(&minHeap->heapnode[parent(i)].weight,&minHeap->heapnode[i].weight);
            i=parent(i);
        }
    }
}

struct heap_node extractMin(struct Heap *minHeap) //extract minimum value from heap 
{
	struct heap_node min = minHeap->heapnode[1];
	swap(&minHeap->heapnode[1].dest,&minHeap->heapnode[minHeap->size].dest);
	swap(&minHeap->heapnode[1].weight,&minHeap->heapnode[minHeap->size].weight);
	minHeap->size--;
	minHeapify(minHeap,1);
	return min;
}

int isEmpty(struct Heap *minHeap) //returns 1 if heap is empty else 0
{
    return (minHeap->size==0);
}

void deleteHeap(struct Heap *minHeap)
{
	if(minHeap!=NULL)
	{
		free(minHeap->heapnode); //freeing all heap nodes
		free(minHeap); //freeing the heap 
	}
}

void printHeap(struct Heap *minHeap) //prints index and weight of all heap nodes of heap
{
	int i;
	for(i=1;i<=minHeap->size;i++)
		printf("%d %d\n",minHeap->heapnode[i].dest,minHeap->heapnode[i].weight);
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

void add_edge(struct Graph *graph,int u,int v,int wt) //adding edge in graph
{
	graph->adj[u]=insertll(graph->adj[u],v,wt);
}

int isEdge(struct Graph *graph,int src,int dest) //retuns weight of edge if it exists else -1
{
	struct node *temp=graph->adj[src];
	if(temp==NULL)
		return -1;
	else
	{
		while(temp!=NULL)
		{
			if(temp->data==dest)
				return temp->weight;
			temp=temp->next;
		}
	}
	return -1;
}

void Dijkstra_algo(struct Graph *graph,int src,struct node **path,int *parent) //dijkstra algorithm 
{
    int *dist=(int*)malloc((graph->vertices+1)*sizeof(int));
    int *visited=(int*)malloc((graph->vertices+1)*sizeof(int));
    int i;
    for(i=1;i<=graph->vertices;i++)
    {
        dist[i]=INT_MAX; 
        parent[i]=-1;//NILL
        visited[i]=0;
    }
    dist[src]=0;
    struct Heap *minHeap=(struct Heap*)malloc(sizeof(struct Heap));
    minHeap=create_Heap(graph->vertices);
    buildHeap(minHeap,dist);
    while(!isEmpty(minHeap))
    {
        struct heap_node min=extractMin(minHeap); //minnode extracted
        int min_dist= min.weight;//d[u]
        *path=insertll(*path,min.dest,min.weight); //path
        //min.dest is extracted vertex
        struct node *temp=graph->adj[min.dest];
        if(min_dist!=INT_MAX)
        {
        	while(temp!=NULL) //process all adjacent vertices of extracted vertex
        	{
        		if(visited[temp->data]==0)//not in the set
        		{
            		decreaseKey(minHeap,temp->data,temp->weight,min_dist);
            		parent[temp->data]=min.dest;
           	    }
            	temp=temp->next;
       		}
        }
        visited[min.dest]=1; //marking the vertex which is going to set as visited
    }
    free(dist); //freeing the dist array
    free(visited); //freeing the visited array
    deleteHeap(minHeap); // deleting the heap
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

int main()
{
	int digit,num,src,dest,wt,count,i;
	struct Graph *graph=NULL;
	struct node *path=NULL;
	int *parent;
	while((digit=fgetc(stdin))!=EOF)
	{
		if(digit=='N')
		{
			delete_graph(graph); //delete previous graph
			deletell(path);
			path=NULL;
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&num);
			graph=create_graph(num); //num is number of vertices here
		}
		else if(digit=='E')
		{
			digit=fgetc(stdin);//gets space
			scanf("%d",&src);
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
			{
				scanf("%d %d",&dest,&wt);
				add_edge(graph,src,dest,wt); //adding edge
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
		else if(digit=='P')
        {
        	count=0;
        	digit=fgetc(stdin);//gets space
			scanf("%d",&src);
			while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&dest);
			int *shortest_path=(int*)malloc((graph->vertices+1)*sizeof(int)); //shortest path array having vertices of shortest path between src and dest
			if(path==NULL || path->data!=src) //need to run Dijkstra on src vertex
			{
				free(parent); //freeing parent array
            	deletell(path); //deleting path linked list
            	path=NULL;
				parent=(int*)malloc((graph->vertices+1)*sizeof(int));
				Dijkstra_algo(graph,src,&path,parent); //running dijkstra on src vertex
			}
			if(parent[dest]==-1) // if parent of dest is -1 as initialized then its not reachable
				printf("-1\n");
			else
			{
				struct node *temp=path;
				while(temp->data!=dest)
				{
					temp=temp->next;
				}
				printf("%d ",temp->weight);
				while(parent[dest]!=src)
				{
					shortest_path[count]=dest;
					dest=parent[dest];
					count++;
				}
				shortest_path[count]=dest;
				count++;
				shortest_path[count]=parent[dest];
				for(i=count;i>=0;i--)
					printf("%d ",shortest_path[i]);
				printf("\n");
			}
            free(shortest_path); //freeing shortest path array
        }
        else if(digit=='D')
        {
            while((digit=fgetc(stdin))!='\n' && digit!=EOF)
				scanf("%d",&src);
			if(path==NULL || path->data!=src) //need to run dijkstra on src vertex
            {
               	free(parent);
        		deletell(path);
        		path=NULL;
            	parent=(int*)malloc((graph->vertices+1)*sizeof(int));
                Dijkstra_algo(graph,src,&path,parent);	
            }
            struct node *temp=path;
            while(temp!=NULL)
            {
                printf("%d ",temp->data);
                if(temp->weight==INT_MAX)
                	printf("-1\n");
                else
                	printf("%d\n",temp->weight);
                temp=temp->next;
            }
        }
	}
	deletell(path);
    free(parent);
    delete_graph(graph);
	return 0;
}
