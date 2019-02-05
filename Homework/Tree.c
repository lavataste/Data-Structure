//This program is ¿°ÅÂ¹Î's HW#05 with Tree ADTs.
#define node_SIZE 200
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
typedef struct
{
	struct node* child[9];
} HEAD;
typedef struct node
{
	char data[40];
	char text[200];
	struct node* parent;
	HEAD* head;
	int number_c;
} NODE;

//global variable
int number_r, number_n, index_r, index_n; 
NODE* root[9];
NODE* node[node_SIZE];
HEAD* head[node_SIZE];

//function
void PrintCommand();
char CheckCommand(char*, int);
void MakeChild(NODE*);
void PrintRoot();
void AddIndex();
void Traverse(NODE*);
void SelectAct();
void DeleteAll(NODE*);
void InitilaizeNODE(NODE*);
void RunTest(NODE*);
void ChildSort(NODE*);
void RootSort();
NODE* SearchAll(char*);
NODE* SearchChild(NODE*, char*);


int main()
{
	printf("Welcome. It is tool for psycological test. You can create a test.(Maxmium 9)\n");
	char command[20], temp_c;	
	int temp_i, exit, count;
	NODE* traverse, *temp_N;
	while(1)
	{ 
		exit=1;
		RootSort();
		PrintCommand();
		printf("Enter the command\n");
		fflush(stdin); 
		gets(command);
		temp_c=CheckCommand(command, strlen(command));
		if(temp_c=='0')
		{
			printf("Invalid input\n");
			continue;
		}
		switch(temp_c)
		{
			case 'C':	//Create psychologicial test
				if(number_r==9)
				{
					printf("The test slot is full.\n");
					break;
				}
				printf("Enter the name of the test.\n");
				node[number_n]=(NODE*)malloc(sizeof(NODE));
				fflush(stdin);
				gets(node[number_n]->data);
				root[number_r]=node[number_n];
				printf("Write the text\n");
				fflush(stdin);
				gets(node[number_n]->text);
				printf("The test %c%s%c is created\n", 34, node[number_n]->data, 34);
				head[number_n]=(HEAD*)malloc(sizeof(HEAD));
				node[number_n]->head=head[number_n];
				InitilaizeNODE(node[number_n]);
				node[number_n]->parent=0;
				AddIndex();
				break;
			
			case 'T':	//Traverse and modify node of tests.
			
				printf("Select a test\n");
				PrintRoot();
				scanf("%d", &temp_i);
				index_r=temp_i-1;
				if(index_r<0 || index_r>8)
				{
					printf("Invalid input\n");
				}
				else if(index_r>=number_r || root[index_r]==0)
				{
					printf("There is no test.\n");
				}
				else
				{
					traverse=root[index_r];
					while(exit)
					{
						Traverse(traverse);
						SelectAct();
						while(1)
						{
							fflush(stdin);
							gets(command);
							temp_c=CheckCommand(command, strlen(command));
							if(temp_c==0)
							{
								printf("Invalid input\n");
								continue;
							}
							break;
						}
						switch(temp_c)
						{
							case 'M':
								
								printf("Enter the node you want move to. (For example, Parent as 'P', Child1 as 'C1')\n");
								gets(command);
								if(command[0]=='P' || command[0]=='p')
								{
									if(traverse->parent==0)
									{
										printf("Error. Current node is root.\n");
									}
									else
									{
										traverse=traverse->parent;
									}
								}
								else if(command[0]=='C' || command[0]=='c')
								{	
									temp_i=command[1]-49;
									if(traverse->number_c==0)
									{
										printf("Current node doesn't have a child.\n");
									}
									else if(temp_i<0 || temp_i>8 || strlen(command)>2 || traverse->head->child[temp_i]==0)
									{
										printf("Invalid input\n");
									}
									else
									{
										traverse=traverse->head->child[temp_i];
									}
								}
								break;
							
							case 'C':
								
								if(traverse->number_c==9)
								{
									printf("Current node's the number of children is full.\n");
								}
								else
								{
									MakeChild(traverse);
								}
								break;
							
							case 'N':
								
								printf("Enter the new name of current node.\n");
								fflush(stdin);
								gets(traverse->data);
								printf("The name is changed.\n");
								break;
							
							case 'T':
								
								printf("Write the new text.\n");
								fflush(stdin);
								gets(traverse->text);
								printf("The text is changed.\n");
								break;
								
							case 'D':
							
								printf("Do you really want to delete the test %c%s%c? (Y/N)\n", 34, traverse->data, 34);
								printf("*All nodes under current node will be deleted.\n");
								fflush(stdin);
								gets(command);
								temp_c=CheckCommand(command, strlen(command));
								if(temp_c=='Y')
								{
									if(traverse->parent!=0)
									{
										temp_N=traverse;
										traverse=traverse->parent;
										for(count=0;count<traverse->number_c;count++)
										{
											if(traverse->head->child[count]==temp_N)
											{
												traverse->head->child[count]=0;
											}
										}
										DeleteAll(temp_N);
										ChildSort(traverse);
									}
									else
									{
										exit--;
										DeleteAll(traverse);
									}
								}
								break;
							
							case 'E':
							
								exit--;
								break;
						}
					}				
				}
				break;
				
			case 'S':
				printf("Enter the name you want to search.\n");
				fflush(stdin);
				gets(command);
				SearchAll(command);
				break;
				
			case 'D':	//Delete the tests.
				
				PrintRoot();
				printf("Select a test number you want delete\n");
				fflush(stdin);
				scanf("%d", &temp_i);
				printf("Do you really want to delete the test %c%s%c? (Y/N)\n", 34, root[temp_i-1]->data, 34);
				printf("*All nodes under current node will be deleted.\n");
				fflush(stdin);
				gets(command);
				temp_c=CheckCommand(command, strlen(command));
				if(temp_c=='Y')
				{
					printf("%c%s%c is deleted.\n", 34, root[temp_i-1], 34);
					DeleteAll(root[temp_i-1]);
				}
				break;
				
			case 'H':	//Show the command.
				
				PrintCommand();
				break;
				
			case 'R':	//Run the test.
				
				PrintRoot();
				printf("Select a test number you want to do.\n");
				fflush(stdin);
				scanf("%d", &temp_i);
				traverse=root[temp_i-1];
				while(1)
				{
					RunTest(traverse);
					if(traverse->number_c==0)
					{
						printf("\nThe test is over.\n");
						break;
					}
					printf("Select a answer.\n");
					while(1)
					{
						fflush(stdin);
						scanf("%d", &temp_i);
						if(temp_i>traverse->number_c || temp_i<1)
						{
							printf("Invalid input.\n");
						}
						else
						{
							traverse=traverse->head->child[temp_i-1];
							break;
						}
					}	
				}
				break;
				
			case 'Q':	//Quit the program.
			
				printf("Do you really want to quit the program? (Y/N)\n");
				gets(command);
				if(strcmp(command, "Y")==0)
				{
					for(count=0;count<index_r;count++)
					{
						DeleteAll(root[count]);
					}
					return 0;
				}
				break;
				
			default:
				printf("Invalid input\n");
		}
	}
	
	
	return 0;
}

void PrintCommand()
{
	printf(
	"==========================================================================\n"
	"C : Create a new psychological test.\n"
	"T : Traverse and modify the nodes of test.\n"
	"S : Search the node.\n"
	"D : Delete a psychological test.\n"
	"R : Run a psychological test.\n"
	"H : Show the commands list.\n"
	"Q : Quit the program.\n"
	"==========================================================================\n"
	);
}
char CheckCommand(char* command, int size)	
{
		if(size>1)	
		{
			return 0;
		}
		else if(command[0]>=97 && command[0]<=122)
		{
			command[0]-=32;
		}
		return command[0];
}
void MakeChild(NODE* parent)
{
	if(number_n==node_SIZE)
	{
		printf("The node is full.\n");
		return;
	}
	node[number_n]=(NODE*)malloc(sizeof(NODE));
	printf("Enter the name of child.\n");
	fflush(stdin);
	gets(node[number_n]->data);
	printf("Write the text.\n");
	fflush(stdin);
	gets(node[number_n]->text);
	parent->head->child[parent->number_c]=node[number_n];
	parent->number_c++;
	node[number_n]->parent=parent;
	node[number_n]->number_c=0;
	head[number_n]=(HEAD*)malloc(sizeof(HEAD));
	node[number_n]->head=head[number_n];
	InitilaizeNODE(node[number_n]);
	index_n++;
	number_n++;
}
void PrintRoot()	//print the names of tests
{
	int count;
	for(count=0;count<9;count++)
	{
		if(root[count]!=0)
		{
			printf("Test%d: %s\n", count+1, root[count]->data);
		}
		else
		{
			printf("Test%d: none\n", count+1);
		}
	}
}
void AddIndex()	//index variable ++
{
	index_r++;
	number_r++;
	index_n++;
	number_n++;
}
void Traverse(NODE* traverse) 	//current node's parent and children be printed
{
	int count;
	printf("==========================================================================\n");
	printf("\n\nCurrent node:%s\n\n", traverse->data);
	printf("Text:%s\n\n\n", traverse->text);
	if(traverse->parent==0)
	{
		printf("Root node.\n");
	}
	else
	{
		printf("Parent: %s\n", traverse->parent->data);
	}
	if(traverse->number_c==0)
	{
		printf("Current node doesn't have children.\n");
	}
	else
	{
		printf("Children list\n");
		for(count=0;count<traverse->number_c;count++)
		{
			if(traverse->head->child[count]==0)
			{
				printf("Child%d: none\n", count+1);
			}
			else
			{
				printf("Child%d: %s\n", count+1, traverse->head->child[count]->data);
			} 
		}
	}
	printf("\n\n");
}
void SelectAct()	//In current node, what will do
{
	printf(
		"C: Make a child.(Maxmium 9)\n"
		"M: Move to other node.\n" 
		"N: Rename the current node.\n"
		"T: Rewrite the text.\n"
		"D: Delete the current node.\n" 
		"E: Exit the menu.\n"
		"Select your act\n");
}
void DeleteAll(NODE* target)	//current node and under nodes deleted
{	
	int count, count2, temp_i;
	NODE* traverse;
	for(count=0;count<target->number_c;count++)
	{
		traverse=target->head->child[count];
		if(traverse->number_c)
		{
			DeleteAll(traverse);
		}
		if(traverse->number_c==0)
		{
			free(traverse->head);	
			free(traverse);
			target->head->child[count]=0;
		}
	}
	for(count=0;count<10;count++)
	{
		if(root[count]==target)
		{
			root[count]=0;
			break;
		}
	}	
	free(target);
}
void InitilaizeNODE(NODE* target)	//initialize variable in structrue node 
{
	int count;
	for(count=0;count<9;count++)
	{
		target->head->child[count]=0;
	}
	target->number_c=0;
}
void RunTest(NODE* test)	//in running test, print the node's name and text.
{
	int count;
	printf("==========================================================================\n");
	printf("\n\n%s\n\n", test->data);
	printf("%s\n\n", test->text);

	if(test->number_c==0)
	{
		return;
	}
	else
	{
		printf("Next select\n");
		for(count=0;count<test->number_c;count++)
		{
			if(test->head->child[count]!=0)
			{
				printf("%d: %s\n", count+1, test->head->child[count]->data);
			}
		}
	}
	printf("\n\n");	
}
void ChildSort(NODE* parent)	//the number of child sort
{
	int count, count2;
	for(count=0;count<parent->number_c;count++)
	{
		if(parent->head->child[count]==0)
		{
			for(count2=count;count2<parent->number_c-1;count2++)
			{
				parent->head->child[count2]=parent->head->child[count2+1];
				if(count2==parent->number_c-2)
				{
					parent->head->child[count2+1]=0;
				}
			}
		}
	}
	for(count=0;count<9;count++)
	{
		if(parent->head->child[count]==0)
		{
			parent->number_c=count;
			break;
		}
	}
}
void RootSort()	//the number of root sort.
{
	int count, count2;
	for(count=0;count<number_r;count++)
	{
		if(root[count]==0)
		{
			for(count2=count;count2<number_r-1;count2++)
			{
				root[count2]=root[count2+1];
				if(count2==number_r-2)
				{
					root[count2+1]=0;
				}
			}
		}
	}
	for(count=0;count<9;count++)
	{
		if(root[count]==0)
		{
			index_r=count;
			number_r=count;
			break;
		}
	}
}

NODE* SearchAll(char* name)
{
	int count;
	NODE* temp;
	for(count=0;count<number_r;count++)
	{
		temp=SearchChild(root[count], name);
/*		if(root[count]->name==name)
		{
			return root[count];
		}
		if(root[count]->degree!=0)
		{
			temp=SearchChild(root[count], name);
			if(temp)
			{
				return temp;
			}
		}*/
	}
	return 0;
}

NODE* SearchChild(NODE* node, char* name)
{
	int count;
	NODE* temp;
	for(count=0;count<node->number_c;count++)
	{
		if(strcmp(node->head->child[count]->data, name)==0)
		{
			return node->head->child[count];
		}
		if(node->head->child[count]->number_c)
		{
			temp=SearchChild(node->head->child[count], name);
			if(temp)
			{
				return temp;
			}
		}
		
		/*
		if(count==0)
		{
			if(node->lchild->name==name)
			{
				return node->lchild;
			}
			if(node->lchild->degree!=0)
			{
				temp=SearchChild(node->lchild, name);
				if(temp)
				{
					return temp;
				}
			}
		}
		else
		{
			if(node->rchildren[count-1]->name==name)
			{
				return node->rchildren[count-1];
			}
			if(node->rchildren[count-1]->degree!=0)
			{
				temp=SearchChild(node->rchildren[count-1], name);
				if(temp)
				{
					return temp;
				}
			}
		}
		*/
	}
	return 0;
}
