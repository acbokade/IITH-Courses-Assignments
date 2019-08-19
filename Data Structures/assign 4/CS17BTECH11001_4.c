
//Handling numbers of arbitrary size
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node of binary search tree
struct bstnode{
  int key;
  struct bstnode *left;
  struct bstnode *right;
  struct bstnode *parent;
};

struct bstnode* succ=NULL;//successor

struct bstnode* bstinsert(struct bstnode *root,int value)//inserting value into a bst
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
  if(value>root->key)
  {
     struct bstnode* rightchild = bstinsert(root->right,value);
     root->right=rightchild;
     rightchild->parent=root;
  }
  else if(value<root->key)
  {
    struct bstnode* leftchild = bstinsert(root->left,value);
    root->left=leftchild;
    leftchild->parent=root;
  }
    return root;
}

void deletetree(struct bstnode *root) //delete all nodes of bst
{
  if(root==NULL)
    return;
  deletetree(root->left);
  deletetree(root->right);
  free(root);
}

void bstsearch(struct bstnode* root,int search,char bitstring[]) //serach if a value exists in bst or not
{
  if(root==NULL)
  {
    printf("-1\n");
    return;
  }
  if (root->key==search) // present
  {
    printf("%s\n",bitstring);
    return;
  }
  else if (root->key>search)//root>head
  {
    strcat(bitstring,"0"); //concatenating 0 to bitsring if search < root->key
    return bstsearch(root->left,search,bitstring);
  }
  else if (root->key<search)
  {
    strcat(bitstring,"1"); //concatenating 1 to bitsring if search > root->key
    return bstsearch(root->right,search,bitstring);
  }
}

void preordertraversal(struct bstnode* root) //recursive preorder traversal of bst
{
  if(root==NULL)
    return;
  else
  {
    printf("%d ",root->key);
    preordertraversal(root->left);
    preordertraversal(root->right);
  }
}

void successor(struct bstnode *root,int temp) //finding successor
{
  if(root==NULL)
    return;
  else
  {
    if(root->key==temp)//equal
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
    else if(root->key>temp)//greater
    {
      succ = root;
      return successor(root->left,temp);
    }
    else if(root->key<temp)
    {
      return successor(root->right,temp);
    }
  }
}

//deletebstnode
struct bstnode* deletebstnode(struct bstnode *root,int value) //using succesor of node in case of node having 2 children
{
  if(root==NULL)
    return root;
  if(root->key>value)//greater
  {
    root->left=deletebstnode(root->left,value);
  }
  else if(root->key<value)//less
  {
    root->right=deletebstnode(root->right,value);
  }
  else if(root->key==value)//node to be deleted
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
        successor(root,value);
        root->key=succ->key;
        root->right=deletebstnode(root->right,succ->key);
      }
    }
  }
  return root;
}

void printChildren(struct bstnode* root,int value)//printing children of nodes
{
  if(root==NULL) //no node with key as value exits
  {
    printf("-1\n");
    return;
  }
  if(value<root->key) //recur to leftsubtree
  {
    return printChildren(root->left,value);
  }
  else if(value>root->key) //recur to rightsubtree
  {
    return printChildren(root->right,value);
  }
  else if(value==root->key) // node with value found
  {
    if(root->left==NULL) //left child is null
      printf("Nil ");
    else 
      printf("%d ",root->left->key); //printing left child key
    if(root->right==NULL) //right child is null
      printf("Nil ");
    else 
      printf("%d ",root->right->key); //printing right child key
  }
}

void printUncle(struct bstnode* root,int value) //printing uncle of bstnode
{
  if(root==NULL) //uncle not found or bstnode with key as value not found
  {
    printf("-1\n");
    return;
  }
  if(value<root->key) //recur to left subtree
  { 
    return printUncle(root->left,value);
  }
  else if(value>root->key) //recur to right subtree
  {
    return printUncle(root->right,value);
  }
  else if(value==root->key) //bstnode with key as value found
  {
    if(root->parent==NULL) //parent of node is null
      printf("-1");
    else
    {
      if(root->parent->parent==NULL) //grandparent of node is null
        printf("-1");
      else
      {
        if(root->parent->parent->left==root->parent) //parent of node is left child of grandparent
        {
          if(root->parent->parent->right==NULL) //right child of grandparent doesnt exist that is uncle is null
            printf("-1");
          else
            printf("%d",root->parent->parent->right->key); //printing uncle's data
        }
        else if(root->parent->parent->right==root->parent) //parent of node is right child of grandparent
        {
          if(root->parent->parent->left==NULL) //left child of grandparent doesnt exist that is uncle is null
            printf("-1");
          else
            printf("%d",root->parent->parent->left->key); //printing uncle's data
        }
      }
    }
  }
}

struct bstnode* rightRotate(struct bstnode* root,int value) //rightrotate at a bstnode
{
  if(root==NULL)
    return root;
  if(value<root->key) //recur to left subtree
  {
    root->left=rightRotate(root->left,value);
  }
  else if(value>root->key) //recur to right subtree
  { 
    root->right=rightRotate(root->right,value);
  }
  else if(value==root->key) 
  {
    struct bstnode* p=root->parent; 
    struct bstnode* child = root->left;
    if(child==NULL) //left child of node is null
      return root;
    else
    {
      root->left=child->right;  //making child's right as left of node 
      if(child->right!=NULL)
        child->right->parent=root; 
      child->right=root; 
      root->parent=child;
      child->parent=p;
      if(p!=NULL)
      {
        if(p->left==root)
        p->left=child;
        else if(p->right==root)
        p->right=child;
      }
      return child;
    }
  }
  return root;
}

struct bstnode* leftRotate(struct bstnode* root,int value) //leftrotate at a bstnode
{
  if(root==NULL)
    return root;
  if(value<root->key)
  {
    root->left=leftRotate(root->left,value); //recur to left subtree
  }
  else if(value>root->key)
  {
    root->right=leftRotate(root->right,value); //recur to right subtree
  }
  else if(value==root->key)
  {
    struct bstnode* p=root->parent;
    struct bstnode* child = root->right;
    if(child==NULL) //right child of node is NULL
      return root;
    else
    {
      root->right=child->left; //making child's left as right of node 
      if(child->left!=NULL)
        child->left->parent=root; //parent of left of child is node
      child->left=root;
      root->parent=child;
      child->parent=p;
      if(p!=NULL)
      {
        if(p->left==root)
        p->left=child;
        else if(p->right==root)
        p->right=child;
      }
      return child;
    }
  }
  return root;
}

struct bstnode* buildtree(int preorder[],int inorder[],int begin,int end,int *preindex) //building bst from given preorder and inorder arrays 
{
  if(begin>end)
    return NULL;
  struct bstnode* newnode=(struct bstnode*)malloc(sizeof(struct bstnode));
  newnode->key=preorder[*preindex];
  newnode->left=NULL;
  newnode->right=NULL;
  newnode->parent=NULL;
  *preindex=*preindex+1;

  //no chilren of the node,simply returning node
  if(begin==end)
    return newnode;
  //finding the newnode->key in inorder[]
  int i;
  for(i=0;i<=end;i++)
  {
    if(inorder[i]==newnode->key)
    {
      break;
    }
  }
  //i is index in inorder array
  struct bstnode* leftchild=buildtree(preorder,inorder,begin,i-1,preindex);
  newnode->left=leftchild;
  if(leftchild!=NULL)
  {
    leftchild->parent=newnode;
  }
  struct bstnode* rightchild=buildtree(preorder,inorder,i+1,end,preindex);
  newnode->right=rightchild;
  if(rightchild!=NULL)
  {
    rightchild->parent=newnode;
  }
  return newnode;
}

void bubble_sort(int inorder[],int size) //sorting function
{
  int i,j,temp;
  for(i=0;i<size-1;i++)
  {
    for(j=0;j<size-i-1;j++)
    {
      if(inorder[j]>inorder[j+1])
      {
        temp=inorder[j];
        inorder[j]=inorder[j+1];
        inorder[j+1]=temp;
      }
    }
  }
}

int main(){
  int digit,num;
  struct bstnode *root=NULL; //root of bst
  int preindex=0;
  while((digit=fgetc(stdin))!=EOF)
  {
    if(digit=='N')
    {
      deletetree(root);
      root=NULL;
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
       root=bstinsert(root,num);
      }
    }
    else if(digit=='S')
    {
      char bitstring[10000]="";
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      bstsearch(root,num,bitstring);
    }
    else if(digit=='P')
    {
        preordertraversal(root);
        printf("\n");
    }
    else if(digit=='>')
    {
      succ=NULL;
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      successor(root,num);
      if(succ==NULL)
      {
        printf("-1\n");
      }
      else
      {
        printf("%d\n",succ->key);
      }
    }
    else if(digit=='+')
    {
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      root=bstinsert(root,num);
    }
    else if(digit=='-') //using succesor of node in case of node having 2 children
    {
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      root=deletebstnode(root,num);
    }
    else if(digit=='C')
    {
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      printChildren(root,num);
      printf("\n");
    }
    else if(digit=='U')
    {
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      printUncle(root,num);
      printf("\n");
    }
    else if(digit=='B')
    {
      int i;
      //allocating memory for preorder and inorder arrays
      int *preorder=(int*)malloc(100000*sizeof(int));
      int *inorder=(int*)malloc(100000*sizeof(int));
      preindex=0;
      deletetree(root);
      root=NULL;
      i=0;//i is size of preorder array
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&preorder[i]);
       inorder[i]=preorder[i];
       i++;
      }
      bubble_sort(inorder,i);
      root=buildtree(preorder,inorder,0,i-1,&preindex);
      //freeing preorder and inorder 
      free(preorder);
      free(inorder);
    }
    else if(digit=='L')
    {
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      root=leftRotate(root,num);
    }
    else if(digit=='R')
    {
      while((digit=fgetc(stdin))!='\n' && digit!=EOF)
      {
       scanf("%d",&num);
      }
      root=rightRotate(root,num);
    }
  }
  deletetree(root);
  return(0);
}
