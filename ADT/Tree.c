//This program is Inlab Excercise with tree ADT of ¿°ÅÂ¹Î. 
#define NODE_SIZE 200
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct node
{
	char name;
	struct node* parent;
	struct node* lchild;
	struct node** rchildren;
	int degree;
} NODE;

char command[20];
int count_command;
int index_node;
int index_root;
int number_delete;
int level, level_max;
int degree_max;
NODE *node[NODE_SIZE];
NODE *root[9];
 
void TreeADT();
void PrintCommand();
void Blank(char*, int);
void CommandPlus();
void CommandT();
void CommandS();
void CommandP();
void CommandC();
void CommandL();
void CommandMinus();
void CommandA();
void CommandD();
void CommandG();
void CommandJ();
void CommandSharp();
void CommandEqual();
void CommandK();
void Merge(NODE*, NODE*);
void MakeRoot(char);
void MakeNode(NODE*, char);
NODE* SearchRoot(char);
NODE* SearchAll(char);
NODE* SearchChild(NODE*, char);
int Bracket(char*);
void PrintNode();
void PrintChild();
void GetLevel();
void GetLevelChild(NODE*);
void LevelUp();
void GetDegree();
void GetDegreeChild(NODE*);
void SortChild(NODE*);
void SortRoot();
void Kill();

int main()
{
	printf("Hello, you can make trees\n");
	TreeADT();
	return 0;
}

void TreeADT()
{
	PrintCommand();
	while(1)
	{
		printf("Enter the command\n");
		fflush(stdin);
		gets(command);
		Blank(command, strlen(command));
		for(count_command=0;count_command<strlen(command);count_command++)
		{
			switch(command[count_command])
			{
				case '+' :
					CommandPlus();
					break;
				
				case 'S' :
					CommandS();
					break;
				
				case 'P' :
					CommandP();
					break;
				
				case 'C' :
					CommandC();
					break;
				
				case 'T' :
					CommandT();
					break;
				
				case 'L' :
					CommandL();
					break;
				
				case '-' :
					CommandMinus();
					break;
				case 'A' :
					CommandA();
					break;
					
				case 'D' :
					CommandD();
					break;
					
				case 'G' :
					CommandG();
					break;
					
				case '#' :
					CommandSharp();
					break;
				
				case '=' :
					CommandEqual();
					break;
				
				case 'K' :
					CommandK();
					break;
				
				case 'Q' :
					CommandK();
					return;
					break;
				
				case 'J' :
					CommandJ();
					break;
					
				default :
					printf("Invalid input default\n");
					break;			
			}
		}
	}	
}

void PrintCommand()
{
	printf(
	"==========================================================================\n"
	"+^A : Create A root.\n"
	"+A(B,C,D) : Insert children B, C, D nodes under A node.\n"
	"S?B : Get the sibling of B node.\n"
	"P?B : Get the parent of B node.\n"
	"C?A : Get the children of A node.\n"
	"T : Print the tree.\n"
	"L?A : Get the level of A node.\n"
	"L? : Get the level of the tree.\n"
	"-B : Delete the B node. You can't delete a parent node.\n"
	"A?B : Get the ancestors of B node.\n"
	"D?A : Get the descendants of A node.\n"
	"G?A : Get the degree of the A node.\n"
	"G : Get the degree of the tree.\n"
	"# : Get the number of nodes.\n"
	"JAB^Z : Merge Root A and B Root under Z Root. A and B should be root. \n"
	"=+B(E,D) : Inser children E, D nodes as sibling of B node.\n"
	"K : Clear the tree.\n"
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

void CommandPlus()
{
	int temp_i=0, count;
	NODE* temp;
	if(command[count_command+1]=='^')
	{
		if(command[count_command+2])
		{
			if(SearchAll(command[count_command+2]))
			{
				printf("%c Already exists!\n", command[count_command+2]);
				count_command=count_command+2;
				return;
			}
			else
			{
				MakeRoot(command[count_command+2]);
				count_command=count_command+2;
			}
		}
	}
	else if(command[count_command+2]=='(')
	{
		temp_i=Bracket(command+2);
		if(temp_i==1)
		{
			printf("Invalid input\n");
			count_command=strlen(command);
			return;
		}
		temp=SearchAll(command[count_command+1]);
		if(temp)
		{
			for(count=0;count<(temp_i-1)/2;count++)
			{
				MakeNode(temp, command[count_command+2*count+3]);
			}
		}
		else
		{
			printf("No %c node in the tree!\n", command[count_command+1]);
		}
		count_command=count_command+temp_i+1;
	}	
}

void CommandT()
{
	int count;
	if(index_root==0)
	{
		printf("There is no node.\n");
	}
	else 
	{
		for(count=0;count<index_root;count++)
		{
			printf("(%c", root[count]->name);
			PrintNode(root[count]);
			printf(")\n");
		}
	}
}

void CommandS()
{
	int count;
	NODE* temp, *parent;
	if(command[count_command+1]=='?')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp==0)
		{
			printf("No %c node in the tree!\n", command[count_command+2]);	
		}
		else
		{
			parent=temp->parent;
			for(count=0;count<parent->degree;count++)
			{
				if(count==0)
				{
					if(parent->lchild!=temp)
					{
						printf("%c ", parent->lchild->name);
					}
				}
				else
				{
					if(parent->rchildren[count-1]!=temp)
					{
						printf("%c ", parent->rchildren[count-1]->name);	
					}
				}
			}
			printf("\n");
		}
		count_command=count_command+2;
	}
	else
	{
		printf("Invalid input S\n");
		count_command=strlen(command);	
	}
	
}

void CommandP()
{
	NODE* temp;
	if(command[count_command+1]=='?')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp==0)
		{
			printf("No %c node in the tree!\n", command[count_command+2]);
		}
		else
		{
			if(temp->parent==0)
			{
				printf("%c node is root.\n", temp->name);
			}
			else
			{
				printf("%c\n", temp->parent->name);	
			}
		}
		count_command=count_command+2;
	}
	else
	{
		printf("Invalid input\n");
		count_command=strlen(command);		
	}
}

void CommandC()
{
	int count;
	NODE* temp;
	if(command[count_command+1]=='?')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp==0)
		{
			printf("No %c node in the tree!\n", command[count_command+2]);
		}
		else
		{
			if(temp->degree)
			{
				for(count=0;count<temp->degree;count++)
				{
					if(count==0)
					{
						printf("%c ", temp->lchild->name);
					}
					else
					{
						printf("%c ", temp->rchildren[count-1]->name);	
					}
				}
				printf("\n");
			}
			else
			{
				printf("%c node doesn't have a child.\n", temp->name);	
			}
		}
		count_command=count_command+2;
	}
	else
	{
		printf("Invalid input.\n");
		count_command=strlen(command);	
	}
}

void CommandL()
{
	int level=1, count;
	NODE* temp;
	if(command[count_command+1]=='?')
	{
	 	if(command[count_command+2])
	 	{
	 		temp=SearchAll(command[count_command+2]);
			if(temp==0)
			{
				printf("No %c node in the tree!\n", command[count_command+2]);
			}
			else
			{
				while(temp->parent!=0)
				{
					level++;
					temp=temp->parent;
				}	
				printf("%d\n", level);
			}
			count_command=count_command+2;
	 	}
	 	else
	 	{
	 		GetLevel();
	 		printf("%d\n", level_max);
	 		count_command++;
	 	}
	}
	else
	{
	 	printf("Invalid input.\n");
		count_command=strlen(command);
	}
	
}

void CommandMinus()
{
	int count, number=0;
	NODE* temp, *parent;
	if(command[count_command+1])
	{
		temp=SearchAll(command[count_command+1]);
		if(temp)
		{
			parent=temp->parent;
			if(temp->degree)
			{
				printf("Can not delete a parent!\n");
			}
			else if(temp->parent!=0)
			{
				for(count=0;count<parent->degree;count++)
				{
					if(count==0)
					{
						if(parent->lchild==temp)
						{
							break;	
						}
					}
					else
					{
						if(parent->rchildren[count-1]==temp)
						{
							break;
						}
					}
				}
				free(temp);
				if(count==0)
				{
					parent->lchild=0;
				}
				else
				{
					parent->rchildren[count-1]=0;
				}
				number_delete++;
				SortChild(parent);
			}
			else
			{
				for(count=0;count<index_root;count++)
				{
					if(root[count]==temp)
					{
						root[count]=0;
						break;
					}
				}
				free(temp);
				SortRoot();
			}
		}
		else
		{
			printf("No %c node in the tree!\n", command[count_command+1]);
		}
		count_command++;
	}
	else
	{
		printf("Invalid input\n");
	}
}

void CommandA()
{
	int count;
	NODE* temp, parent;
	if(command[count_command+1]=='?')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp==0)
		{
			printf("No %c node in the tree!\n", command[count_command+2]);
		}
		else
		{
			if(temp->parent==0)
			{
				printf("%c is root node.\n", temp->name);
			}
			while(temp->parent)
			{
				printf("%c ", temp->parent->name);
				temp=temp->parent;
			}
			printf("\n");
		}
		count_command+=2;
	}
	else
	{
		printf("Invalid input\n");
		count_command=strlen(command);
	}

}

void CommandD()
{
	int count;
	NODE* temp;
	if(command[count_command+1]=='?')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp==0)
		{
			printf("No %c node in the tree!\n", command[count_command+2]);
		}
		else
		{
			if(temp->degree)
			{
				PrintChild(temp);	
			}
			else
			{
				printf("%c node doesn't have descendants", temp->name);
			}
			printf("\n");
		}
		count_command+=2;
	
	}
	else
	{
		printf("Invalid input\n");
		count_command=strlen(command);
	}

}

void CommandG()
{
	NODE* temp;
	if(command[count_command+1]=='?')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp)
		{
			printf("%d\n", temp->degree);
		}
		else
		{
			printf("No %c node in the tree!\n", command[count_command+2]);
		}
		count_command+=2;
	}
	else
	{
		GetDegree();
	}
}

void CommandSharp()
{
	printf("%d\n", index_root+index_node-number_delete);
}

void CommandEqual()
{
	int temp_i, count;
	NODE* temp, *parent;
	if(command[count_command+1]=='+')
	{
		temp=SearchAll(command[count_command+2]);
		if(temp)
		{
			if(temp->parent)
			{
				parent=temp->parent;
				temp_i=Bracket(command+3);
				if(temp_i==1)
				{
					printf("Invalid input\n");
					count_command=strlen(command);
					return;
				}
				if(temp)
				{
					for(count=0;count<(temp_i-1)/2;count++)
					{
						MakeNode(parent, command[count_command+2*count+4]);
					}
				}
				else
				{
					printf("No %c node in the tree!\n", command[count_command+1]);
				}
				count_command=count_command+temp_i+2;
			
			}
			else
			{
				printf("%c node is root node.\n", command[count_command+2]);
			}
		}
		else
		{
			printf("No %c node in the tree!\n", command[count_command+2]);
		}
	}
	else
	{
		printf("Invalid input.\n");
		count_command=strlen(command);
	}
}

void CommandK()
{
	int count;
	for(count=0;count<index_root;count++)
	{
		Kill(root[count]);
	}
	index_root=0;
	index_node=0;
}

void CommandJ()
{
	NODE* temp1, *temp2;
	int count, count2, judge=0;
	for(count=0;count<strlen(command);count++)
	{
		if(command[count]=='^' && command[count+1])
		{
			judge++;
			break;
		}
	}
	if(judge==0)
	{
		printf("Invalid input\n");
		count_command=strlen(command);
	}
	else
	{
		temp1=SearchRoot(command[count+1]);
		if(temp1==0)
		{
			if(SearchAll(command[count+1]))
			{
				printf("%c already exists!\n", command[count+1]);
				return;
			}
			MakeRoot(command[count+1]);
			temp1=SearchRoot(command[count+1]);
		}
		for(count2=count_command+1;count2<strlen(command);count2++)
		{
			if(count2==count || count2==count+1)
			{
				continue;
			}
			temp2=SearchRoot(command[count2]);
			if(temp2==0)
			{
				printf("No %c root in the tree!\n", command[count2]);
				continue;
			}
			Merge(temp1, temp2);
		}
	}
	count_command=strlen(command);
}

void Merge(NODE* parent, NODE* child)
{
	int count;
	if(parent->degree==0)
	{
		parent->lchild=child;
	}
	else
	{
		parent->rchildren=(NODE**)realloc(parent->rchildren, sizeof(NODE*)*parent->degree);
		parent->rchildren[parent->degree-1]=child;
	}
	for(count=0;count<index_root;count++)
	{
		if(root[count]==child)
		{
			root[count]=0;
			break;
		}
	}
	parent->degree++;
	SortRoot();
}

void MakeRoot(char name)
{
	NODE* temp;
	temp=SearchAll(name);
	if(temp!=0)
	{
		printf("%c already exists!\n", name);
		return;
	}
	root[index_root]=(NODE*)malloc(sizeof(NODE));
	root[index_root]->name=name;
	root[index_root]->parent=0;
	root[index_root]->lchild=0;
	root[index_root]->rchildren=0;
	root[index_root]->degree=0;
	index_root++;
}

void MakeNode(NODE* parent, char name)
{
	NODE* temp;
	temp=SearchAll(name);
	if(temp!=0)
	{
		printf("%c already exists!\n", name);
		return;
	}
	node[index_node]=(NODE*)malloc(sizeof(NODE));
	node[index_node]->name=name;
	node[index_node]->parent=parent;
	node[index_node]->lchild=0;
	node[index_node]->rchildren=0;
	node[index_node]->degree=0;
	if(parent->degree==0)
	{
		parent->lchild=node[index_node];	
	}
	else
	{
		parent->rchildren=(NODE**)realloc(parent->rchildren, sizeof(NODE*)*parent->degree);
		parent->rchildren[parent->degree-1]=node[index_node];	
	}
	parent->degree++;
	index_node++;
}

NODE* SearchRoot(char name)
{
	int count;
	NODE* temp=0;
	for(count=0;count<index_root;count++)
	{
		if(root[count]->name==name)
		{
			temp=root[count];
			break;
		}
	}
	return temp;
}

NODE* SearchAll(char name)
{
	int count;
	NODE* temp;
	for(count=0;count<index_root;count++)
	{
		if(root[count]->name==name)
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
		}
	}
	return 0;
}

NODE* SearchChild(NODE* node, char name)
{
	int count;
	NODE* temp;
	for(count=0;count<node->degree;count++)
	{
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
	}
	return 0;
}

int Bracket(char* bracket)
{
	int size=0, close=0, count;
	if(bracket[1]==',')
	{
		return 1;	
	}
	for(count=0;count<strlen(bracket);count++)
	{
		size++;
		if(bracket[count]==')')
		{
			close++;
			break;
		}
	}
	if(close==0 || size<3)
	{
		return 1;
	}
	for(count=1;count<size-2;count++)
	{
		if(bracket[count]==',' && bracket[count+1]==',')
		{
			return 1;
		}
		if(bracket[count]!=',' && bracket[count+1]!=',')
		{
			return 1;
		}
	}
	return size;
}

void PrintNode(NODE* node)
{
	int count;
	if(node->degree)
	{
		printf("(");
		for(count=0;count<node->degree;count++)
		{
			if(count==0)
			{
				printf("%c", node->lchild->name);
				if(node->lchild->degree)
				{
					PrintNode(node->lchild);
				}
			}
			else
			{
				if(node->rchildren[count-1]==0)
				{
					printf("0 count-1 : %d", count-1);
				}
				printf(",%c", node->rchildren[count-1]->name);
				if(node->rchildren[count-1]->degree)
				{
					PrintNode(node->rchildren[count-1]);
				}
			}
		}
		printf(")");
	}
}

void PrintChild(NODE* parent)
{
	int count;
	for(count=0;count<parent->degree;count++)
	{
		if(count==0)
		{
			printf("%c ", parent->lchild->name);
		}
		else
		{
			printf("%c ", parent->rchildren[count-1]->name);
		}
	}
	for(count=0;count<parent->degree;count++)
	{
		if(count==0)
		{
			if(parent->lchild->degree!=0)
			{
				PrintChild(parent->lchild);
			}
		}
		else
		{
			if(parent->rchildren[count-1]->degree!=0)
			{
				PrintChild(parent->rchildren[count-1]);
			}
		}
	}
}

void GetLevel()
{
	int count;
	level=0;
	level_max=0;
	if(index_root==0)
	{
		return;
	}
	else
	{
		for(count=0;count<index_root;count++)
		{
			LevelUp();
			if(root[count]->degree!=0)
			{
				GetLevelChild(root[count]);
			}
			level=0;
		}
	}
}

void GetLevelChild(NODE* parent)
{
	int count;
	if(parent->degree)
	{
		for(count=0;count<parent->degree;count++)
		{
			if(count==0)
			{
				LevelUp();
				GetLevelChild(parent->lchild);
			}
			else
			{
				LevelUp();
				GetLevelChild(parent->rchildren[count-1]);
			}
		}
	}
	level--;
}

void LevelUp()
{
	level++;
	if(level>level_max)
	{
		level_max=level;
	}
}

void GetDegree()
{
	int count;
	degree_max=0;
	if(index_root)
	{
		for(count=0;count<index_root;count++)
		{
			if(root[count]->degree!=0)
			{
				GetDegreeChild(root[count]);
			}
		}
	}
	printf("%d\n", degree_max);
}

void GetDegreeChild(NODE* parent)
{
	int count;
	if(parent->degree)
	{
		if(parent->degree>degree_max)
		{
			degree_max=parent->degree;			
		}
		for(count=0;count<parent->degree;count++)
		{
			if(count==0)
			{
				GetDegreeChild(parent->lchild);
			}
			else
			{
				GetDegreeChild(parent->rchildren[count-1]);
			}
		}
	}
}

void SortChild(NODE* parent)
{
	int count, count2, number=0;
	for(count=0;count<parent->degree-number;count++)
	{
		if(count==0)
		{
			if(parent->lchild==0)
			{
				parent->lchild=parent->rchildren[0];
				for(count2=0;count2<parent->degree-2;count2++)
				{
					parent->rchildren[count2]=parent->rchildren[count2+1];
				}
				number++;
				parent->rchildren[parent->degree-2]=0;
			}
		}
		else
		{
			if(parent->rchildren[count-1]==0)
			{
				for(count2=count-1;count2<parent->degree-2-number;count2++)
				{
					parent->rchildren[count2]=parent->rchildren[count2+1];
				}
				number++;
				parent->rchildren[parent->degree-1-number]=0;
			}
		}
	}
	parent->degree-=number;
}

void SortRoot()
{
	int count, count2, number=0;
	for(count=0;count<index_root-number;count++)
	{
		if(root[count]==0)
		{
			for(count2=count;count2<index_root-number-1;count2++)
			{
				root[count2]=root[count2+1];
			}
			root[index_root-number-1]=0;
			number++;
		}
	}
	index_root-=number;
}

void Kill(NODE* parent)
{
	int count;
	if(parent->degree)
	{
		for(count=0;count<parent->degree;count++)
		{
			if(count==0)
			{
				Kill(parent->lchild);
			}
			else
			{
				Kill(parent->rchildren[count-1]);
			}
		
		}
	}
	free(parent);
}
