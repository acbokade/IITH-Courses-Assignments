//Ajinkya Bokade
//CS17BTECH11001
#include <stdio.h>
#include <stdlib.h>

struct node{
  int digit;
  struct node* next;
  struct node* previous;
};

struct node* insert(struct node *head,int value) //inserting node
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

void printrll(struct node *head)//printing input 
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
  }
  else
  {
      printf("\n");
  }
  
  printf("\n");
}

void add(struct node* head1,struct node* head2,struct node* head3) //to add numbers
{
  sanitizell(head1);
  sanitizell(head2);
  struct node*temp1=head1;
  struct node*temp2=head2;
  int digit1,digit2,carry=0,digit3,temp,flag=0;
  while(head1!=NULL||head2!=NULL)
  {
    if(head1!=NULL)
      digit1=head1->digit;
    else
      digit1=0;
    if(head2!=NULL)
      digit2=head2->digit;
    else
      digit2=0;
    temp=digit1+digit2+carry;
    digit3=temp%10;
    carry=temp/10;
    if(carry)
      flag=1;
    else
      flag=0;
    head3 = insert(head3,digit3);
    if(head1!=NULL)
      head1=head1->next;
    if(head2!=NULL)
      head2=head2->next;
  }
  if(flag)
    head3=insert(head3,carry);
  /*printf("NUMBER 1: ");
  printrll(temp1);
  printf("NUMBER 2: ");
  printrll(temp2);
  printf("RESULT: ");*/ //printing the inputs
  printll(head3);
  deletell(temp1);
  deletell(temp2);
  deletell(head3);
}

int main(){
  int digit;
  struct node* head1=NULL;
  struct node* head2=NULL;
  struct node* head3=NULL;
  int flag=0;//0 means inserting at head1 else head2
   while((digit=fgetc(stdin))!=EOF){
    if(digit=='\n'){
      add(head1,head2,head3);
      head1=NULL;
      head2=NULL;
      head3=NULL;
      flag=0;
    }
    else if(digit==' '){
      flag=1;
    }
    else{
      if(flag==0)
      {
        head1=insert(head1,digit-48);
      }
      else
      {
        head2=insert(head2,digit-48);
      }
    }
  }
  add(head1,head2,head3);
  return(0);
}