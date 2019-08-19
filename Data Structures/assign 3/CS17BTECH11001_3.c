
//Handling numbers of arbitrary size
#include <stdio.h>
#include <stdlib.h>

//node of doubly linked list
struct node{ 
  int digit;
  struct node* next;
  struct node* previous;
};

//node of binary search tree
struct bstnode{
  struct node *key;
  struct bstnode *left;
  struct bstnode *right;
  struct bstnode *parent;
};

struct bstnode* succ=NULL;//successor

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
  //flag=2 if they are equal, flag=1 if number in head1>head2,else flag=0
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

void bstsearch(struct bstnode* root,struct node *search,struct node *bitstring) 
{
  if(root==NULL)
  {
    printf("-1\n");
    return;
  }
  if (comparison(root->key,search)==2) // present
  {
    printrll(bitstring);
    return;
  }
  else if (comparison(root->key,search)==1)//root>head
  {
    bitstring=insert(bitstring,0);
    return bstsearch(root->left,search,bitstring);
  }
  else if (comparison(root->key,search)==0)
  {
    bitstring=insert(bitstring,1);
    return bstsearch(root->right,search,bitstring);
  }
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

void successor(struct bstnode *root,struct node *temp) //finding successor 
{
  if(root==NULL)
    return;
  else
  {
    if(comparison(root->key,temp)==2)//equal
    {
      //case1 bstnode has a right child
      if(root->right!=NULL)
      {
        root=root->right;
        while(root->left!=NULL)
        {
          root=root->left;
        }
        succ = root;
      }
      //case2 bstnode has no right child
      else
      {
        struct bstnode *p=root->parent;
        while(p!=NULL && p->right==root)
        {
          root=p;
          p=p->parent;
        }
        if(p!=NULL)
        {
          succ = p;
        }
        else 
          return;
      }
    }
    else if(comparison(root->key,temp)==1)//greater
    {
      succ = root;
      return successor(root->left,temp);
    }
    else if(comparison(root->key,temp)==0)
    {
      return successor(root->right,temp);
    }
  }
} 


//deletebstnode
struct bstnode* deletebstnode(struct bstnode *root,struct node *temp) //using succesor of node in case of node having 2 children
{
  if(root==NULL)
    return root;
  if(comparison(root->key,temp)==1)//greater
  {
    root->left=deletebstnode(root->left,temp);
  }
  else if(comparison(root->key,temp)==0)//less
  {
    root->right=deletebstnode(root->right,temp);
  }
  else if(comparison(root->key,temp)==2)//node to be deleted
  {
    //case1 no child
    if(root->left==NULL && root->right==NULL)
    {
      free(root);
      return NULL;
    }
    //case2 1 child or 2 children
    if(root->left!=NULL||root->right!=NULL)
    {
      if(root->left!=NULL && root->right==NULL)
      {
        struct bstnode* temp=root->left;
        temp->parent=root->parent;
        free(root);
        return temp;
      }
      else if(root->left==NULL && root->right!=NULL)
      {
        struct bstnode* temp=root->right;
        temp->parent=root->parent;
        free(root);
        return temp;
      }
      //2 children
      else if(root->left!=NULL && root->right!=NULL)
      {
        successor(root,temp);
        root->key=succ->key;
        root->right=deletebstnode(root->right,succ->key);
      }
    }
  }
  return root;
}

int main(){
  int digit;
  struct node *temp1=NULL; //for taking input 
  struct bstnode *root=NULL; //root of bst
  struct node* bitstring=NULL;// for printing bitstring in case of S 
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
      bstsearch(root,temp1,bitstring);
      deletell(bitstring);
      bitstring=NULL;
      deletell(temp1);
      temp1=NULL;
    }
    else if(digit=='P')
    { 
      preordertraversal(root);
      printf("\n");
    }
    else if(digit=='>')
    {
      succ=NULL;
      temp1=NULL;
      digit=fgetc(stdin);//for space
      while((digit=fgetc(stdin))>=48)
      {
          temp1=insert(temp1,digit-48);
      }
      sanitizell(temp1);
      successor(root,temp1);
      if(succ==NULL)
      {
        printf("-1\n");
      }
      else
      {
        printrll(succ->key);
      }
      deletell(temp1);
      temp1=NULL;
    }
    else if(digit=='+')
    {
      temp1=NULL;
      digit=fgetc(stdin);//for space
      while((digit=fgetc(stdin))>=48)
      {
          temp1=insert(temp1,digit-48);
      }
      sanitizell(temp1);
      root=bstinsert(root,temp1);
      temp1=NULL;
    }
    else if(digit=='-') //using succesor of node in case of node having 2 children
    {
      temp1=NULL;
      digit=fgetc(stdin);//for space
      while((digit=fgetc(stdin))>=48)
      {
          temp1=insert(temp1,digit-48);
      }
      sanitizell(temp1);
      root=deletebstnode(root,temp1);
      deletell(temp1);
      temp1=NULL;
    }
  }
  deletetree(root);
  return(0);
}