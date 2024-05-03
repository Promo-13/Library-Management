#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#include<time.h>
struct date
{
int day;
int month;
int year;
};

typedef struct student
{
char department[20];
char name[50];
char id[20];
int sem;
char btitle[50];
int returned;
struct date start;
struct date end;
struct student *next;
struct student *prev;
}Student;

Student *stu,*head;

typedef struct books
{
char dept[20];
int id;
char author[20];
char publication[50];
char title[50];
int copy;
int taken;
struct books *next;
}Book;

Book *p,*q,*temp,*t;
void details();
void calculate_fine();

void add()
{
  temp=(Book *)malloc(sizeof(Book));
  printf(" Provide the following information\n");
  printf(" Department : ");
  scanf("\n");
  scanf("%[^\n]%*c",temp->dept);
  printf(" ID : ");
  scanf("%d",&temp->id);
  printf(" Title : ");
  scanf("\n");
  scanf("%[^\n]%*c",temp->title);
  printf(" Author : ");
  scanf("\n");
  scanf("%[^\n]%*c",temp->author);
  printf(" Publication : ");
  scanf("\n");
  scanf("%[^\n]%*c",temp->publication);
  printf(" Copies : ");
  scanf("%d",&temp->copy);
  temp->taken=0;
  temp->next=NULL;
  if(p==NULL)
  {
    p=temp;
  }
  else
  {
    temp->next=p;
    p=temp;
  }
 
}

void search()
{
q=p;
char d[20],ti[50];
int flag=0;
printf(" Department : ");
 scanf("\n");
 scanf("%[^\n]%*c",d);
printf(" Book title : ");
 scanf("\n");
 scanf("%[^\n]%*c",ti);
while(q!=NULL)
{
  if(!strcmp(q->title,ti)  && !strcmp(q->dept,d))
  {
      flag++;
      break;
  }
  q=q->next;
}
if(flag==0)
  printf(" Book is not available in library \n");
else
{
   printf(" Book found\n");
   details(q); 
}
}

void view()
{
char d[20];
q=p;
printf(" Enter department : ");
 scanf("\n");
 scanf("%[^\n]%*c",d);
printf(" Books available for %s department are...\n",d);
printf("\t ID \t TITLE \t\t\t AUTHOR \t  COPIES   TAKEN BOOKS \n");
printf("........................................................................................\n");
printf("........................................................................................\n");
while(q!=NULL)
{
   if(!strcmp(q->dept,d))
   {
      printf(" \t %d \t  %s \t  %s \t\t %d \t %d\n",q->id,q->title,q->author,q->copy,q->taken);
   }
   q=q->next;
}
}

void details(Book *q)
{
    printf(" Book details are..\n");
    printf(" Id = %d\n",q->id);
    printf(" Department = %s\n",q->dept);
    printf(" Author = %s\n",q->author);
    printf(" Publication = %s\n",q->publication);
    printf(" No. of copies=%d \n",q->copy);
    if(q->taken != q->copy)
    printf(" Currently available books =%d\n",(q->copy - q->taken));
    else
    printf(" Currently not available\n");
}

void edit()
{
  int b_i,flag=0;
  t=p;
  printf(" Enter book id to edit : ");
  scanf("%d",&b_i);
  while(t!=NULL)
  {  
    if(t->id==b_i)
    {
       flag++;
       break;
     }
     t=t->next;
   }
if(flag==0)
  printf(" Book is not available in library \n");
else
{
int edit_ch;
char d[20],ti[50],a[20],pub[50];
int i,tak,c;
char con;
//do{
printf(" What field do you want to edit :\n");
printf(" 1. Department \n");
printf(" 2. Title\n");
printf(" 3. Author\n");
printf(" 4. Publication\n");
printf(" 5. copies \n");
printf(" 6. Taken\n");            
printf("Enter your choice: ");
scanf("%d",&edit_ch);
switch(edit_ch)
{
 case 1:
    printf(" Enter new department : ");
    scanf("\n");
    scanf("%[^\n]%*c",d);
    strcpy(t->dept,d);
    break; 
 case 2:
     printf(" Enter new title: ");
     scanf("\n");
     scanf("%[^\n]%*c",ti);
     strcpy(t->title,ti);
     break;
 case 3:
     printf(" Enter new author: ");  
     scanf("\n");
     scanf("%[^\n]%*c",a);
     strcpy(t->author,a);
     break;
 case 4:
     printf(" Enter new publication: ");  
     scanf("\n");
     scanf("%[^\n]%*c",pub);
     strcpy(t->publication,pub);
     break;
 case 5:
     printf(" Enter new copies: ");
     scanf("%d",&c);
     t->copy=c;
     break;
 case 6:
     printf(" change availability: ");  
     scanf("%d",&tak);
     t->taken+=tak;
     break;
}
/*printf("Do you want to continue{y/n]");
scanf("%c",&con);
}
while(con=='y' || con=='Y');*/
}
}

void update_book(Book *q)
{
    int cb;
    cb=q->taken;
    q->taken=cb+1;
}

int check_end(Student *stu)
{
time_t now=time(NULL);
struct tm *ct=localtime(&now);
if(stu->end.year == ct->tm_year+1900)
{
  if(stu->end.month == ct->tm_mon+1)
  {
   if(stu->end.day < ct->tm_mday)
   {
     printf(" Enter valid end date :\n");
      return 0;
    }
  }
  if(stu->end.month < ct->tm_mon+1)
  {
    printf(" Enter valid end date :\n");
    return 0;
   }
}
else if(stu->end.year < ct->tm_year+1900)
{
  printf(" Enter valid end date :\n");
  return 0;
}
else
 return(1);
}

void borrow()
{
char ti[50];
time_t now=time(NULL);
struct tm *ct=localtime(&now);
    int flag=0;
printf(" Enter book title :");
 scanf("\n");
 scanf("%[^\n]%*c",ti);
q=p;
while(q!=NULL)
{
  if(!strcmp(q->title,ti) && q->copy > q->taken)
  {
     flag++;
     break;
  }
  q=q->next;
}
if(flag==0)
  printf(" Book is not available currently");
else
{
stu=(Student *)malloc(sizeof(Student));
printf(" Enter student details who is borrowing the book\n");
printf(" Department : ");
 scanf("\n");
 scanf("%[^\n]%*c",stu->department);
printf(" Name : ");
 scanf("\n");
 scanf("%[^\n]%*c",stu->name);
printf(" Id : ");
 scanf("\n");
 scanf("%[^\n]%*c",stu->id);
printf(" Semester : ");
scanf("%d",&stu->sem);  
strcpy(stu->btitle,ti);
stu->start.day=ct->tm_mday;
stu->start.month=ct->tm_mon+1;
stu->start.year=ct->tm_year+1900;
printf(" Enter ending Date \n");
printf(" Day : ");
scanf("%d",&stu->end.day);
printf(" Month : ");
scanf("%d",&stu->end.month);
int vm;
while(stu->end.month >12)
{
printf(" Enter the valid month : ");
scanf("%d",&vm);
stu->end.month=vm;
}
printf(" Year : ");
scanf("%d",&stu->end.year);
while(check_end(stu) == 0)
{
printf(" Enter ending Date \n");
printf(" Day : ");
scanf("%d",&stu->end.day);
printf(" Month : ");
scanf("%d",&stu->end.month);
printf(" Year : ");
scanf("%d",&stu->end.year);
}
stu->returned=0;
stu->next=NULL;
stu->prev=NULL;
if(head==NULL)
{
  head=stu; 
}
else
{
 stu->next=head;
 head->prev=stu;
 head=stu;
}
update_book(q);
 printf(" Details added\n");
}
}

void sdetails(Student *s)
{
printf("\t NAME \t\t ID \t SEMESTER \t BOOK \t\t START DATE \t END DATE \n");
printf("...........................................................................................................\n");
printf("...........................................................................................................\n");
printf("\t %s \t %s \t %d \t %s \t %d/%d/%d \t %d/%d/%d \n ",s->name,s->id,s->sem,s->btitle,s->start.day,s->start.month,s->start.year,s->end.day,s->end.month,s->end.year);
}

void calculate_fine(Student *s)
{
int cday,cmonth,cyear;
int days,fine;
time_t now=time(NULL);
struct tm *ct=localtime(&now);
cday=ct->tm_mday;
cmonth=ct->tm_mon+1;
cyear=ct->tm_year+1900;
if(cyear == s->end.year)
{
if(cmonth == s->end.month)
{
if(cday > s->end.day)
{
days=cday - s->end.day;
fine=days*10;
printf(" Fine = Rs. %d /- \n",fine); 
}
else
{
    fine=0;
  printf(" Fine = Rs. %d /- \n",fine); 
}
}
else if(cmonth > s->end.month)
{
  days=(cday+30) - s->end.day;
  fine=days*10;
  printf(" Fine = Rs. %d /- \n",fine); 
}
else
{
  fine=0;
  printf("\n Fine = Rs. %d /- \n",fine); 
}
}
if(cyear > s->end.year)
{
  fine=500;
  printf(" Fine = Rs. %d /- \n",fine); 
}
}

void delrecord(Student *s)
{
   Student *st,*sd;
    st=head;
    while(st->next!=NULL)
    {
    if(!strcmp(st->id,s->id) && !strcmp(st->btitle,s->btitle) && !strcmp(st->name,s->name))
    {
        sd=st->prev;
        sd->next=st->next;
        st->next->prev=sd;
    }
    st=st->next;
    break;
    } 
}

void editbook(char ti[50])
{
  q=p;
  while(q!=NULL)
  {
      if(!strcmp(q->title,ti))
      {
          q->taken=q->taken-1;
          break;
      }
  }
}

void return_books()
{
char i[20],ti[50];
Student *s;
int flag=0;
printf(" Enter student ID : ");
 scanf("\n");
 scanf("%[^\n]%*c",i);
printf(" Enter book title : ");
 scanf("\n");
 scanf("%[^\n]%*c",ti);
s=head;
while(s!=NULL)
{
if(!strcmp(s->id,i) && !strcmp(s->btitle,ti))
{
flag++;
break;
}
s=s->next;
}
if(flag!=0)
{
sdetails(s);
calculate_fine(s);
editbook(ti);
delrecord(s);
}
else
  printf(" No such student exist \n");
}

void main()
{
    printf(" ****************************************\n");
    printf(" *                                      *\n");
    printf(" *                                      *\n");
    printf(" *     ----------------------------     *\n");
    printf(" *      WELCOME TO STUDENT'S LIBRARY    *\n");
    printf(" *     ----------------------------     *\n");
    printf(" *                                      *\n");
    printf(" *                                      *\n");
    printf(" ****************************************\n");
    printf("\n\n");
    printf(" ****************************************\n");
    printf(" *                                      *\n");
    printf(" *       ------------------------       *\n");
    printf(" *           STUDENT'S LIBRARY          *\n");
    printf(" *       ------------------------       *\n");
    printf(" *                                      *\n");
    printf(" *     Chennai,TamilNadu,India          *\n");
    printf(" *     Email: studentlib@gmail.com      *\n");
    printf(" *     Contact:8800991010,8800992020    *\n");
    printf(" *                                      *\n");
    printf(" ****************************************\n");
    int choice;
    while(choice!=7)
    {
    printf(" MainMenu:\n");
    printf(" 1 : Add books\n");
    printf(" 2 : Search books\n");
    printf(" 3 : View books\n");
    printf(" 4 : Edit books \n");
    printf(" 5 : Borrow books \n");
    printf(" 6 : Return books \n");
    printf(" 7 : Exit \n");
    printf("\n Enter your choice : ");
    scanf("%d",&choice);
    switch(choice)
    {
        case 1:
          add();
          break;
        case 2:
          search();
          break;
        case 3:
          view();
          break;
        case 4:
          edit();
          break;
        case 5:
           borrow();
           break;
        case 6:
           return_books();
           break;
        case 7:
           exit(0);
           break;
    }
    }
}



