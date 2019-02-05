//This program is ¿°ÅÂ¹Î's Inlab#09 excercise with Heap ADTs. 
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *heap[5], index_heap[5], cursor_heap, count_command;
char command[40];

void HeapADT();
void PrintCommand();
void CommandPlus();
void CountPlus(int);
void Push(int);
int Number(int);
void CommandT();
void CommandE();
void CommandF();
void CommandMinus();
int Pop();
void CommandF();
void CommandP();
void CommandC();
void CommandK();
void CommandS();
void CommandM();
void CommandG();
void CommandH();
void CommandW();
void CommandQ();

int main()
{
	printf("Hello, This is Heap ADT program.\n");
	PrintCommand();
	HeapADT();
	return 0;
}

void HeapADT()
{
	int count;
	for(count=0;count<5;count++)
	{
		index_heap[count]=1;	
	}
	while(1)
	{
		printf("Enter the command. (Current heap cursor : %d )\n", cursor_heap+1);
		fflush(stdin);
		gets(command);
		for(count_command=0;count_command<strlen(command);count_command++)
		{
			switch(command[count_command])
			{
				case '+':
					CommandPlus();
					break;
					
				case '-':
					CommandMinus();
					break;
					
				case 't':
					CommandT();
					break;
					
				case 'e':
					CommandE();
					break;
					
				case 'f':
					CommandF();
					break;
					
				case 'p':
					CommandP();
					break;
					
				case 'c':
					CommandC();
					break;
					
				case 'k':
					CommandK();
					break;
					
				case 's':
					CommandS();
					break;
					
				case 'm':
					CommandM();
					break;
					
				case 'g':
					CommandG();
					break;
					
				case 'h':
					CommandH();
					break;
					
					
				case 'w':
					CommandW();
					break;
					
				case 'Q':
					CommandQ();
					return;
					
				default:
					break; 	
			}
		}
	}	
}

void PrintCommand()
{
	printf(
		"==========================================================================\n"
		"+N : Push N node. (0¡ÂN¡Â999)\n"
		"- : Pop.\n"
		"t : Traverse the heap.\n"
		"e? : Check whether heap is empty.\n"
		"pN : Find the parent of N.\n"
		"cN : Find the children of N.\n"
		"k : Peek the root.\n"
		"sN : Find the N and get index number of the N\n"
		"mN,M : Modify node N to M.\n"
		"hM : Heap cursor to M.\n"
		"gN,M : Merge heap N with heap M. (All nodes of heap M pushed to heap N.)\n"
		"w : Pop all nodes.\n"
		"Q : Quit the program.\n" 
		"==========================================================================\n"
	);
}

void CommandPlus()
{
	int temp;
	temp=Number(count_command);
	if(temp==-1)
	{
		printf("Invalid input. The range is 1 to 999\n");
	}
	else
	{
		Push(temp);
	}
	CountPlus(temp);
}

void CountPlus(int temp)
{
	if(temp==-1)
	{
		count_command=strlen(command);	
	}
	else if(temp<10)
	{
		count_command++;	
	}
	else if(temp<100)
	{
		count_command+=2;	
	}
	else
	{
		count_command+=3;	
	}
}

void Push(int number)
{
	int place=index_heap[cursor_heap];
	if(index_heap[cursor_heap]==1)
	{
		heap[cursor_heap]=(int*)malloc(sizeof(int)*2);
		heap[cursor_heap][1]=number;
	}
	else
	{
		heap[cursor_heap]=(int*)realloc(heap[cursor_heap], sizeof(int)*(index_heap[cursor_heap]+1));
		while(1)
		{
			if(place==1)
			{
				heap[cursor_heap][1]=number;
				break;
			}
			else if(number>heap[cursor_heap][place/2])
			{
				heap[cursor_heap][place]=heap[cursor_heap][place/2];
				place=place/2;
			}
			else
			{
				heap[cursor_heap][place]=number;
				break;
			}
		}
	}
	index_heap[cursor_heap]++;
}

int Number(int index)
{
	int count=0, temp;
	while(1)
	{
		if(command[index+count+1]<48 || command[index+count+1]>57)
		{
			break;
		}
		count++;
	}
	if(!count)
	{
		temp=-1;
	}
	else if(count==1)
	{
		temp=command[index+1]-48;
	}
	else if(count==2)
	{
		temp=(command[index+1]-48)*10+command[index+2]-48;
	}
	else if(count==3)
	{
		temp=(command[index+1]-48)*100+(command[index+2]-48)*10+command[index+3]-48;
	}
	else
	{
		temp=-1;
	}
	return temp;	
}

void CommandT()
{
	int count1, count2;
	for(count1=0;count1<5;count1++)
	{
		printf("Heap %d : ", count1+1);
		if(index_heap[count1]==1)
		{
			printf("Not exist.\n");
		}
		else
		{
			for(count2=1;count2<index_heap[count1];count2++)
			{
				printf("%d ", heap[count1][count2]);
			}
			printf("\n");
		}
	}
	
	/*
	int count;
	if(index_heap[cursor_heap]==1)
	{
		printf("There is no node.\n");
		return;	
	}
	for(count=1;count<index_heap[cursor_heap];count++)
	{
		printf("%d ", heap[cursor_heap][count]);
	}
	printf("\n");
	*/
}

void CommandE()
{
	if(command[count_command+1]=='?')
	{		
		if(index_heap[cursor_heap]==1)
		{
			printf("True\n");
		}
		else
		{
			printf("False\n");
		}
		count_command++;
	}
}

void CommandF()
{
	if(command[count_command+1]=='?')
	{		
		printf("False\n"); //µ¿ÀûÀ¸·Î ÇÒ´çÇÏ¹Ç·Î ²ËÂû ¼ö°¡ ¾øÀ½.
		count_command++; 
	}
}

void CommandMinus()
{
	Pop();
}

int Pop()
{
	int temp1, temp2, place=1;
	if(index_heap[cursor_heap]==1)
	{
		printf("There is no node.\n");
		return;	
	}
	temp1=heap[cursor_heap][1];
	heap[cursor_heap][1]=heap[cursor_heap][index_heap[cursor_heap]-1];
	heap[cursor_heap][index_heap[cursor_heap]]=0;
	while(place*2<index_heap[cursor_heap])
	{
		if(heap[cursor_heap][place]>=heap[cursor_heap][place*2] && heap[cursor_heap][place]>=heap[cursor_heap][place*2+1])
		{
			break;	
		}
		else
		{
			if(heap[cursor_heap][place*2]>heap[cursor_heap][place*2+1])
			{
				temp2=heap[cursor_heap][place];
				heap[cursor_heap][place]=heap[cursor_heap][place*2];
				heap[cursor_heap][place*2]=temp2;
				place=place*2;
			}
			else
			{
				temp2=heap[cursor_heap][place];
				heap[cursor_heap][place]=heap[cursor_heap][place*2+1];
				heap[cursor_heap][place*2+1]=temp2;
				place=place*2+1;
			}
		}
	}
	index_heap[cursor_heap]--;
	return temp1;
}

void CommandP()
{
	int temp1, temp2;
	temp1=Number(count_command);
	temp2=Find(temp1);
	if(temp2==-1)
	{
		printf("There is no %d.\n", temp1);
	}
	else if(temp2==1)
	{
		printf("%d is root.\n", heap[cursor_heap][1]);	
	}
	else
	{
		printf("%d\n", 	heap[cursor_heap][temp2/2]);
	}
	CountPlus(temp1);
}

int Find(int number)
{
	int count;
	for(count=0;count<index_heap[cursor_heap];count++)
	{
		if(heap[cursor_heap][count]==number)
		{
			return count;
		}
	}
	if(count==index_heap[cursor_heap])
	{
		return -1;
	}
}

void CommandC()
{
	int temp1, temp2;
	temp1=Number(count_command);
	temp2=Find(temp1);
	if(temp2==-1)
	{
		printf("There is no %d.\n", temp1);
	}
	else if(2*temp2>=index_heap[cursor_heap])
	{
		printf("%d doesn't have a child.\n", temp1);	
	}
	else if(2*temp2==index_heap[cursor_heap]-1)
	{
		printf("%d\n", heap[cursor_heap][index_heap[cursor_heap]-1]);
	}
	else
	{
		printf("%d %d\n", heap[cursor_heap][2*temp2], heap[cursor_heap][2*temp2+1]);	
	}
	CountPlus(temp1);
}

void CommandK()
{
	int temp;
	temp=Pop();
	printf("%d\n", temp);
	Push(temp);	
}

void CommandS()
{
	int temp;
	temp=Number(count_command);
	printf("%d\n", Find(temp));
	CountPlus(temp);
}

void CommandM()
{
	int temp1, temp2, count, place;
	temp1=Number(count_command);
	place=Find(temp1);
	if(place==-1)
	{
		printf("There is no %d.\n", temp1);
		return;	
	}
	CountPlus(temp1);
	if(command[count_command+1]==',')
	{
		temp2=Number(count_command+1);
		if(temp2==-1)
		{
			printf("Invalid input.\n");
			count_command=strlen(command);
			return;	
		}
		heap[cursor_heap][place]=temp2;
		CountPlus(temp2);
		count_command++;
	}
	else
	{
		printf("Invalid input.\n");	
		count_command=strlen(command);
		return;
	}
	while(place*2<index_heap[cursor_heap])
	{
		if(place*2==index_heap[cursor_heap]-1)
		{
			if(heap[cursor_heap][place]<heap[cursor_heap][index_heap[cursor_heap]-1])
			{
				temp1=heap[cursor_heap][place];
				heap[cursor_heap][place]=heap[cursor_heap][index_heap[cursor_heap]-1];
				heap[cursor_heap][index_heap[cursor_heap]-1]=temp1;
			}
			break;
		}
		else
		{
			if(heap[cursor_heap][place]<heap[cursor_heap][place*2] || heap[cursor_heap][place]<heap[cursor_heap][place*2+1])
			{
				if(heap[cursor_heap][place*2]>heap[cursor_heap][place*2+1])
				{
					temp1=heap[cursor_heap][place];
					heap[cursor_heap][place]=heap[cursor_heap][place*2];
					heap[cursor_heap][place*2]=heap[cursor_heap][temp1];
					place=place*2;
				}
				else
				{
					temp1=heap[cursor_heap][place];
					heap[cursor_heap][place]=heap[cursor_heap][place*2+1];
					heap[cursor_heap][place*2+1]=heap[cursor_heap][temp1];
					place=place*2+1;
				}
			}
			else
			{
				break;	
			}
		}
	}
	while(place>1)
	{
		if(heap[cursor_heap][place]>heap[cursor_heap][place/2])
		{
			temp1=heap[cursor_heap][place];
			heap[cursor_heap][place]=heap[cursor_heap][place/2];
			heap[cursor_heap][place/2]=temp1;
			place=place/2;	
		}
		else
		{
			break;
		}
	}
}

void CommandG()
{
	int index1, index2, count, temp1, temp2;
	index1=command[count_command+1]-49;
	index2=command[count_command+3]-49;
	if(index1>=0 && index1<=4 && index2>=0 && index2<=4 && command[count_command+2]==',')
	{
		if(index1==index2)
		{
			printf("Can not merge same heap.\n");	
		}
		else
		{
			temp1=index_heap[index2];
			for(count=1;count<temp1;count++)
			{
				cursor_heap=index2;
				temp2=Pop();
				cursor_heap=index1;
				Push(temp2);
			}
		}
	}
}

void CommandH()
{
	if(command[count_command+1]<49 || command[count_command+1]>53)
	{
		printf("Invalid input. The range of cursor is 1 to 5.\n");
	}
	else
	{
		cursor_heap=command[count_command+1]-49;
	}
}

void CommandW()
{
	int count;
	for(count=1;count<index_heap[cursor_heap];count++)
	{
		Pop();
	}
	index_heap[cursor_heap]=1;
	printf("All nodes of %d heap are poped.\n", cursor_heap+1);
}

void CommandQ()
{
	int count;
	CommandW();
	for(count=0;count<5;count++)
	{
		free(heap[count]);
	}
}
