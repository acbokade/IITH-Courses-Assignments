
//Handling numbers of arbitrary size

#include <stdio.h>
#include <stdlib.h>

struct node{
  int digit;
  struct node* next;
  struct node* previous;
};

struct node *bitstring=NULL;//bistring for printing path of node to searched from root

struct bstnode{
  struct node *key;
  struct bstnode *left;
  struct bstnode *right;
  struct bstnode *parent;
};

void deletell(struct node* head) //deleting linked list
{
  struct node* temp;
  if(head!=NULL)
  {
     while(head->next!=NULL)
     {
      temp=head->next;
      free(head);
      head=temp;
     }
     free(head);  
  }
}

void sanitizell(struct node* head) //removing initial zeros from input
{
  struct node *temp;
  if(head!=NULL)
  {
    while(head->next!=NULL)
    {
      head=head->next;
    }
    while(head->digit==0)
    {
      temp=head->previous;
      temp->next=NULL;
      free(head);
      head=temp;
    }
  }
}

struct node* insert(struct node *head,int value) //inserting node in ll
{
  struct node* newnode=(struct node*)malloc(sizeof(struct node));
  newnode->digit=value;
  newnode->previous=NULL;
  newnode->next=head;
  if(head!=NULL)
  {
      head->previous=newnode;
  }
  head=newnode;
  return head;
}

int comparison(struct node* head1,struct node* head2)//comparison between 2 ll
{
  sanitizell(head1);
  sanitizell(head2);
  int length1=1,length2=1;
  int flag=-1;
  struct node *temp1=head1;
  struct node *temp2=head2;
  if(head1!=NULL)
  {
    while(head1->next!=NULL)
    {
      length1+=1;
      head1=head1->next;
    }
  }
  if(head2!=NULL)
  {
    while(head2->next!=NULL)
    {
      length2+=1;
      head2=head2->next;
    }
  }
  while(temp1->next!=NULL)
  {
    temp1=temp1->next;
  }
  while(temp2->next!=NULL)
  {
    temp2=temp2->next;
  }
  if(length1>length2)
    return 1;
  else if(length2>length1)
    return 0;
  else 
  {
    flag=2;//equal
    while(temp1!=NULL && temp2!=NULL)
    {
      if(temp1->digit>temp2->digit)
      {
          flag=1;
          return flag;
      }
      else if(temp1->digit<temp2->digit)
      {
        flag=0;
        return flag;
      }
      temp1=temp1->previous;
      temp2=temp2->previous;
    }
    return flag;
  }
}

struct bstnode* bstinsert(struct bstnode *root,struct node *value)//inserting ll into a bst 
{
  if(root==NULL)
  {
    struct bstnode *newnode=(struct bstnode*)malloc(sizeof(struct bstnode));
    newnode->key=value;
    newnode->left=NULL;
    newnode->right=NULL;
    newnode->parent=NULL;
    return newnode;
  }
  if(comparison(root->key,value)==0)
  {
     struct bstnode* rightchild = bstinsert(root->right,value);
     root->right=rightchild;
     rightchild->parent=root;
  }      
  else if(comparison(root->key,value)==1)
  {
    struct bstnode* leftchild = bstinsert(root->left,value);
    root->left=leftchild;
    leftchild->parent=root;
  }
    return root;
}

int bstsearch(struct bstnode* root,struct node *search)//temp for bitstring 
{
  if(root==NULL)
  {
    return 0;
  }
  if (comparison(root->key,search)==2) // present
  {
    return 1;
  }
  else if (comparison(root->key,search)==1)//root>head
  {
    bitstring=insert(bitstring,0);
    return bstsearch(root->left,search);
  }
  else if (comparison(root->key,search)==0)
  {
    bitstring=insert(bitstring,1);
    return bstsearch(root->right,search);
  }
}

void printll(struct node* head3) //printing output
{
  if(head3!=NULL)
  {
     while(head3!=NULL)
      {
        printf("%d",head3->digit);
        head3=head3->next;
      }
      printf("\n") ; 
  }
  else
  {
    printf("\n");
  }
}

void printrll(struct node *head)//printing ll in reverse order 
{
  if(head!=NULL)
  {
    while(head->next!=NULL)
    {
      head=head->next;
    }
    while(head!=NULL)
    {
      printf("%d",head->digit);
      head=head->previous;
    }
    printf("\n");
  }
  else
  {
      printf("\n");
  }
}

void printrllwithspace(struct node *head)//printing ll with space between 2 consecutive nodes value 
{
  if(head!=NULL)
  {
    while(head->next!=NULL)
    {
      head=head->next;
    }
    while(head!=NULL)
    {
      printf("%d",head->digit);
      head=head->previous;
    }
    printf(" ");
  }
  else
  {
    printf("\n");
  }
}

void deletetree(struct bstnode *root) //delete all nodes of bst
{
  if(root==NULL)
    return;

  deletetree(root->left);
  deletetree(root->right);
  free(root);
}

void preordertraversal(struct bstnode* root) //recursive preorder traversal of bst
{
  if(root==NULL)
    return;
  else
  {
    printrllwithspace(root->key);
    preordertraversal(root->left);
    preordertraversal(root->right);
  }
}

int main(){
  int digit;
  struct node *temp1=NULL; //for taking input 
  struct bstnode *root=NULL; //root of bst
  while((digit=fgetc(stdin))!=EOF)
  {
    if(digit=='N')
    {
      deletetree(root);
      root=NULL;
      while((digit=fgetc(stdin))!='\n')
      {
        if(digit==' ')
        {
          if(temp1!=NULL)
          {
            sanitizell(temp1);
            root=bstinsert(root,temp1);
            temp1=NULL;
          }
        }
        else
        {
          temp1=insert(temp1,digit-48);
        }
      }
      if(temp1!=NULL)
      {
        sanitizell(temp1);
        root=bstinsert(root,temp1);
        temp1=NULL;
      }
    }
    else if(digit=='S')
    {
      digit=fgetc(stdin);//spacebar
      temp1=NULL;
      while((digit=fgetc(stdin))>=48)
      {
          temp1=insert(temp1,digit-48);
      }
      sanitizell(temp1);
      if(bstsearch(root,temp1)==1)
      {
          printrll(bitstring);
      }
      else if(bstsearch(root,temp1)==0)
      {
        printf("-1\n");
      }
      deletell(temp1);
      deletell(bitstring);
      temp1=NULL;
      bitstring=NULL;
    }
    else if(digit=='P')
    { 
      preordertraversal(root);
      printf("\n");
    }
  }
  return(0);
}