//This program is ¿°ÅÂ¹Î's inlab excercise#04 with Queue ADTs. 
#define SIZE 500
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
	char element[SIZE];
	int front;
	int rear;
} QUEUE; 

void QueueNumber(int);
void PrintCommand();
void Blank(char*, int);
void Enqueue(QUEUE*, char);
char Dequeue(QUEUE*);
int GetNumberQueue(QUEUE*);
char GetElement(QUEUE*, int);
void ClearQueue(QUEUE*);
void List(QUEUE*);
void Merge(QUEUE*, QUEUE*);


int main()
{
	char command[20], temp_c;
	int count, count2, number_q, index_q=0, temp_i, temp_i2;
	QUEUE* qp[5], *qp_save;
	number_q=5;
	for(count=0;count<number_q;count++)
	{
		qp[count]=(QUEUE*)malloc(sizeof(QUEUE));
		qp[count]->front=0;
		qp[count]->rear=-1;	
	}
	PrintCommand();
	while(1)
	{
		printf("\nEnter the command. You are in %d queue.\n", index_q+1);
		fflush(stdin);
		gets(command);
		Blank(command, strlen(command));
		for(count=0;count<strlen(command);count++)
		{
			if(command[count]>=97 && command[count]<=122)
			{
				command[count]-=32;
			}
			switch(command[count])
			{
				case 'T':	if(command[count+1]>=49 && command[count+1]<=57)
							{
								index_q=command[count+1]-49;
								if(index_q>4)
								{
									printf("You can use only 5 queues.");
								}
								else
								{
									QueueNumber(index_q+1);
								}
							}
							else
							{
								printf("Invalid input.\n");
							}
							count++;
							break;
			
				case '+':	Enqueue(qp[index_q], command[count+1]);
							count++;
							break;
								
				case 'L': 	List(qp[index_q]);
							break;
								
				case '<':	switch(command[count+1])
								{
									case '@':	temp_c=GetElement(qp[index_q], 1);
												printf("%c\n", temp_c);
												count++;
												break;
												
									default	:	if(command[count+2]=='@')
												{
													if(command[count+1]>=49 && command[count+1]<=57)
													{
														temp_i=command[count+1]-48;
														temp_c=GetElement(qp[index_q], temp_i); 
														printf("%c\n", temp_c);
														count=count+2;
													}
												}
												else if(command[count+3]=='@')
												{
													if((command[count+1]>=49 && command[count+1]<=57) && (command[count+2]>=49 && command[count+2]<=57))
													{
														temp_i=(command[count+1]-48)*10+command[count+2]-48;
														temp_c=GetElement(qp[index_q], temp_i);
														printf("%c\n", temp_c);
														count=count+3;
													}
												}
								}
							break;
								
				case '>':	switch(command[count+1])
								{
									case '@':	temp_c=GetElement(qp[index_q], GetNumberQueue(qp[index_q]));
												printf("%c\n", temp_c);
												count++;
												break;
												
									default	:	if(command[count+2]=='@')
												{
													if(command[count+1]>=49 && command[count+1]<=57)
													{
														temp_i=GetNumberQueue(qp[index_q])-(command[count+1]-48)+1;
														temp_c=GetElement(qp[index_q], temp_i);
														printf("%c\n", temp_c);
														count=count+2;
													}
												}
												else if(command[count+3]=='@')
												{
													if((command[count+1]>=49 && command[count+1]<=57) && (command[count+2]>=49 && command[count+2]<=57))
													{
														temp_i=GetNumberQueue(qp[index_q])-((command[count+1]-48)*10+command[count+2]-48)+1;
														temp_c=GetElement(qp[index_q], temp_i);
														printf("%c\n", temp_c);
														count=count+3;
													}
												}
								}
							break;
								
				case '?': 	temp_c=GetElement(qp[index_q], 1);
							if(temp_c==command[count+1])
							{
								printf("True\n");
							}
							else
							{
								printf("False\n");
							}
							count++;
							break;
				
				case 'P':	if(command[count+1]>=47 && command[count+1]<=57)
							{
								if(command[count+2]>=47 && command[count+2]<=57)
								{
									temp_i=(command[count+1]-48)*10+command[count+2]-48;
									printf("%c\n", GetElement(qp[index_q], temp_i));
									count=count+2;
								}
								else
								{
									temp_i=command[count+1]-48;
									printf("%c\n", GetElement(qp[index_q], temp_i));
									count++;
								}
							}
							else
							{
								temp_c=GetElement(qp[index_q], 1);
								printf("%c\n", temp_c);
							}
							break;
				
				case '-':	if(qp[index_q]->front==qp[index_q]->rear+1)
							{
								printf("Error. There is no element.\n");
								break;
							}
							temp_c=Dequeue(qp[index_q]);
							printf("'%c' is deleted.\n", temp_c);
							
							break;
							
				case '#':	temp_i=GetNumberQueue(qp[index_q]);
							printf("%d\n", temp_i);
							break;
							
				case 'E':	temp_i=GetNumberQueue(qp[index_q]);
							if(temp_i)
							{
								printf("False\n");
							}
							else
							{
								printf("True\n");
							}
							break;
							
				case 'M':	temp_i=GetNumberQueue(qp[index_q]);
							for(count2=0;count2<temp_i-1;count2++)
							{
								Enqueue(qp[index_q], Dequeue(qp[index_q]));
							}
							temp_c=Dequeue(qp[index_q]);
							Enqueue(qp[index_q], command[count+1]);
							printf("'%c' is modified as '%c'.\n", temp_c, command[count+1]);
							count++;
							break;
							
				case 'F':	if(qp[index_q]->rear==SIZE-1)
							{
								printf("True\n");
							}
							else
							{
								printf("False\n");
							}
							break;
							
				case 'C':	ClearQueue(qp[index_q]);
							break;
							
				case 'S':	if(command[count]==strlen(command)-1)
							{	
								PrintCommand();
							}
							break;
					
				case 'J':	if(command[count+1]>=49 && command[count+1]<=53 && command[count+2]>=49 && command[count+2]<=53)
							{	
								temp_i=command[count+1]-49;
								temp_i2=command[count+2]-49;
								if(temp_i==temp_i2)
								{
									printf("You can't merge themselves.\n");
								}
								else if(temp_i>4 || temp_i2>4)
								{
									printf("There are only fifth queues.\n");
								}
								else
								{
									Merge(qp[temp_i], qp[temp_i2]);
									printf("%d queues and %d queues are merged.\n", temp_i+1, temp_i2+1);
								}
								count=count+2;
							}
							break;					
							
				case 'Q':	printf("Do you want to really quit the program? (Y/N)\n");
							gets(command);
							if(strcmp(command, "Y")==0)
							{
								for(count2=0;count2<5;count2++)
								{
									free(qp[count2]); 
								}
								return 0;
							}
							break;
				default:	if(count==strlen(command)-1)
							printf("Invalid command.\n");
			}
						
			
		}
	}
	return 0;
}
				
void PrintCommand()
{
	printf(
	"==========================================================================\n"
	"Tn : Transfer to nth queue. you can use 5 queues. (n is number)\n"
	"+a : add 'a' (If you write like +aa, it ignores second a.)\n"
	"Ma : replace the rear of element as 'a' (If you write like Maa, it ignores second a.)\n"
	"- : delete the element of front.\n"
	"Jnm : Merge nth queue and mth queue.\n"
	"# : display the number of the elements in the stack.\n"
	"E : check whether the stack is empty.\n"
	"F : check whether the stack is full.\n"
	"P : display the top element.\n"
	"?a : check whether the front of element 'a'\n"
	"L : list all elements of the queue.\n"
	"C : empty the stack.\n"
	"S : Show the commands list.\n"
	"Q : Quit the program.\n"
	"==========================================================================\n"
	);
}				
void Blank(char* array, int size)
{
	int count, count2, k=1;
	for(count=0;count<size;count++)
	{
		if(*(array+count)==' ')
		{
			for(count2=0;count2<size-count-1;count2++)
			{
				*(array+count+count2)=*(array+count+count2+1);
			}
			count--;
			*(array+size-k)=0;
			k++;
		}
	}
}				
void Enqueue(QUEUE* qp, char element)
{  
	if(qp->rear==SIZE-1)
	{
		printf("The queue is full.\n");	
	}
	else
	{
		qp->element[++(qp->rear)]=element;
//		printf("%c Enqueue\n", element);
	}
}
char Dequeue(QUEUE* qp)
{
	if(qp->front==qp->rear+1)
	{
		printf("There is no element.\n");
		return 0;
	}
	else
	{
//		printf("%c Dequeue\n", qp->element[qp->front]);
		return qp->element[qp->front++];	
	}
}
int GetNumberQueue(QUEUE* qp)
{
	return qp->rear-qp->front+1;
}
char GetElement(QUEUE* qp, int index)
{
	char temp_c, returning;
	int count, temp_i;
	temp_i=GetNumberQueue(qp);
	if(index>temp_i)
	{
		printf("Error. The number of elements is %d.", temp_i);
		return 0;
	}
	for(count=0;count<temp_i;count++)
	{
		temp_c=Dequeue(qp);
		if(count==index-1)
		{
			returning=temp_c;
		}
		Enqueue(qp, temp_c);	
	}
	return returning;
}
void ClearQueue(QUEUE* qp)
{
	int count, temp_i;
	temp_i=GetNumberQueue(qp);
	for(count=0;count<temp_i;count++)
	{
		Dequeue(qp);
	}
}
void List(QUEUE* qp)
{
	int count;
	int temp_i=GetNumberQueue(qp);
	char temp_c;
	if(temp_i==0)
	{
		printf("There is no element.\n");
	}
	else
	{
		for(count=0;count<temp_i;count++)
		{
			temp_c=Dequeue(qp);
			printf("%c ", temp_c);
			Enqueue(qp, temp_c);
		}
	}
	printf("\n");
}
void QueueNumber(int index)
{
	if(index==1)
	{
		printf("You moved to the 1st queue.\n");
	}
	else if(index==2)
	{
		printf("You moved to the 2nd queue.\n");
	}
	else if(index==3)
	{
		printf("You moved to the 3rd queue.\n");
	}
	else
	{
		printf("You moved to the %dth queue.\n", index);
	}
}
void Merge(QUEUE* q1, QUEUE* q2)
{
	int temp_i, count;
	char temp_c;
	temp_i=GetNumberQueue(q2);
	for(count=0;count<temp_i;count++)
	{
		temp_c=Dequeue(q2);
		Enqueue(q1, temp_c);
		Enqueue(q2, temp_c);
	}
}
