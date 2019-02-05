#include<stdio.h>
#include<string.h>
void Blank(char*, int);
void Insert(char*, char*, int*, int, int*, int);
void Push(char*, int* , int);
int Travel_b(char*, int);
int Travel_e(char*, int);
void Delete(char*, int*, int);
void Remove_L(char*, int*, int);
void Display(char*, int*);
void Replace(char*, char*, int*);
void Clear(char*, int*, int*, int);
void Movefirst(char*, char*, int*);
void Movebackone(char*, int*);
void Moveforwardone(char*, int*, int);
void Move(char*, char*, int*, int);

int main()
{
	char my_array[30]={}, command[20]={};
	int index=0, j, size_a, size_c, first=0;
	int* p=&index;
	int* f=&first;
	printf(
	"+a : add a (If you write like +aa, it ignores second a.)\n"
	"=a : Replace the element of current cursor to a (If you write like =aa, it ignored second a.)\n"
	"- : delete the element of current cursor\n"
	"< : move cursor to first element\n"
	"> : move cursor to last element\n"
	"N : move cursor to next element\n"
	"P : move cursor to previous element\n"
	"@ : display the element of current cursor\n"
	"C : empty the array\n"
	"Mn : move the element of current cursor to nth element (n:the number, If you write the size, it moves to last element.)\n"
	"MP : move the element of current cursor to previous element\n"
	"MN : move the element of current cursor to next element\n"
	"L : list array elements\n");
	while(1)
{
	printf("=====================================================================================================\nEnter the command\n");
	gets(command);
	size_a=strlen(my_array);
	size_c=strlen(command);
	Blank(command, size_c);
	size_c=strlen(command);
	if(size_a==0)
	{
		first=0;
	}
	if(command[0]=='+') 
	{
		Insert(my_array, command, p, size_c, f, size_a);	
	}
	else if(strcmp(command, "<")==0)
	{
		index=0;
	}
	else if(strcmp(command, ">")==0)
	{
		index=size_a-1;
	}
	else if(strcmp(command, "N")==0)
	{
		if(index==size_a-1)
		{
			printf("error. The cursor can't get out range.");
		}
		else	index++;
	}
	else if(strcmp(command, "P")==0)
	{
		if(index==0)
		{
			printf("error. The cursor can't get out index.");
		}
		else	index--;
	}
	else if(command[0]=='<')
	{
		if(command[1]=='N')
		{
			index=Travel_b(command, size_c);
		}
		else if(command[1]=='M')
		{
			Movefirst(my_array, command, p);
		}
	}	
	else if(command[0]=='>')
	{
		if(command[1]=='P') 
		{	
			size_a=strlen(my_array);
			index=size_a-1-Travel_e(command, size_c);
		}
		else if(command[1]=='-')
		{
			size_a=strlen(my_array);
			Remove_L(my_array, p, size_a);
		}
	}

	else if(command[0]=='-')
	{
		size_a=strlen(my_array);
		Delete(my_array, p, size_a);
	}
	else if(command[0]=='@')
	{
		Display(my_array, p);
	}
	else if(command[0]=='=')
	{
		Replace(my_array, command, p);
	}
	else if(command[0]=='C')
	{
		Clear(my_array, p, f, size_a);
	}
	else if(command[0]=='M')
	{
		if(command[1]>=48 && command[1]<=57)
		{
			Move(my_array, command, p, size_a);
		} 	
		else if(command[1]=='P')
		{
				Movebackone(my_array, p);
		}
		else if(command[1]=='N')
		{
				Moveforwardone(my_array, p, size_a);
		}
	}
	else if(command[0]=='L')
	{
		if(size_a==0)
		{
			printf("There are no elements.\n");
		}
		else
		{
			printf("\nmy array=");
			puts(my_array);
			printf("The cursor is on the %c, and the index is %d\n", my_array[index], index);
		}
	}
	else
	{
		printf("The command is invalid.\n");
	}

}	
	return 0;
}



void Blank(char* array, int size)
{
	int i, j, k=1;
	for(i=0;i<size;i++)
	{
		if(*(array+i)==' ')
		{
			for(j=0;j<size-i-1;j++)
			{
				*(array+i+j)=*(array+i+j+1);
			}
			i--;
			*(array+size-k)=0;
			k--;
		}
	}
}
void Insert(char* array, char* command, int* index, int size, int* first, int size_a)
{
	int j;
	if(*first!=0)
	{
		(*index)++;
		for(j=0; j<size; j++)
		{
			if(*(command+j)=='+')
			{
				Push(array, index, size_a);
				*(array+*index)=*(command+j+1);
				(*index)++;
				size_a++;
			}		
		}
	}
	else
	{
		for(j=0; j<size; j++)
		{
			if(*(command+j)=='+')
			{
				*(array+*index+1)=*(array+*index);
				*(array+*index)=*(command+j+1);
				(*index)++;
				(*first)++;
			}		
		}
	}
	(*index)--;
} 
void Push(char* array, int* index, int size)
{
	int j;
	for(j=size;j>(*index);j--)
	{
		*(array+j)=*(array+j-1);
	}
	*(array+*index)=' ';
	*(array+size+1)='\0';
}
int Travel_b(char* command, int size)
{
	int j, N=0;
	for(j=0; j<size; j++)
	{
		if(*(command+j)=='N')
		{
			N++;
		}
	}
	return N;
}
int Travel_e(char* command, int size)
{
	int j, P=0;
	for(j=0; j<size; j++)
	{
		if(*(command+j)=='P')
		{
			P++;
		}
	}
	return P;
}
void Delete(char* array, int* index, int size)
{
	
	int i=*index;
	if(size==0)
	{
		printf("There are no elements\n");
	}
	else
	{	
		for(;i<size;i++)
		{
			*(array+i)=*(array+i+1);
		}
		*(array+size)=0;
		if(*index==size-1)
		{
			*index=0;
		}
	}
	
}
void Remove_L(char* array, int* index, int size)
{
	*(array+size-1)=0;
	*index=0;
}
void Display(char* array, int* index)
{
	if(*(array+*index)==0)
	{
		printf("There is no element.\n");
	}
	else
	{
		printf("The element of current cursor is %c\n", *(array+*index));
	}
}
void Replace(char* array, char* command, int* index)
{	
	*(array+*index)=*(command+1);
}
void Clear(char* array, int* index, int* first, int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		*(array+i)=0;
	}
	*index=0;
	printf("The array is cleared\n");
}
void Movefirst(char* array, char* command, int* index)
{
	int j;
	char temp=*array;
	*index=*(command+2)-48;
	for(j=0;j<*index;j++)
		{
			*(array+j)=*(array+j+1);
		}
	*(array+*index)=temp;
}
void Movebackone(char* array, int* index)
{	
	char temp=*(array+*index);
	if(*index==0)
	{
		printf("error. The element can't get out range.\n");
	}
	else
	{
		*(array+*index)=*(array+*index-1);
		*(array+*index-1)=temp;
		(*index)--;
	}
}
void Moveforwardone(char* array, int* index, int size)
{
	char temp=*(array+*index);
	if(*index==size-1)
	{
		printf("error. The element can't get out range.\n");
	}
	else
	{	
		*(array+*index)=*(array+*index+1);
		*(array+*index+1)=temp;
		(*index)++;
	}
}
void Move(char* array, char* command, int* index, int size)
{
	int j, move=*(command+1)-48;
	char temp=*(array+*index);
	if(move>size)
	{
		printf("error. It can't move out of range.");
	}
	else if(*index>move)
	{
		for(j=*index; j>move; j--)
		{	
			*(array+j)=*(array+j-1);
		}
		*(array+move)=temp;
		*index=move;
	}
	else if(*index<move)
	{
		if(move==size) move--;
		for(j=*index; j<move; j++)
		{	
			*(array+j)=*(array+j+1);
		}
		*(array+move)=temp;
		*index=move;
	}
}
