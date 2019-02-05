//This program is ¿°ÅÂ¹Î's Inlab#7 excercise with Binary Search Tree ADT.
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct node
{
	int key;
	struct node* lchild;
	struct node* rchild;
	struct node* parent;
} NODE;

char command[40];
int index_node, count_command, one, one_count;
NODE** node;
NODE* root;

void BSTADT();
void PrintCommand();
void Blank(char*);
void CommandPlus();
void CommandL();
void CommandI();
void CommandR();
void CommandS();
void CommandT();
void CommandE();
void CommandMinus();
void CommandD();
void CommandH();
void CommandB();
void CommandC();
void Insert(int);
void PrintChild(NODE*);
void InitializeNode(NODE*);
NODE* Place(NODE*, int);
void Inorder(NODE*);
void RNLorder(NODE*);
NODE* FindTV(NODE*, int, int*, int*);
void InExternal(NODE*, int);
void InDecrement(NODE*, int);
void GetHeight(NODE*, int, int*);
void StartBalanceFactor(NODE*, int*);
void GetBalanceFactor(NODE*, int*);
void CalBalanceFactor(NODE*, int, int*);
void Free(NODE*);

int main()
{
	printf("Hello, This is Binary Search Tree ADT Program.\n");
	PrintCommand();
	BSTADT();
	return 0;
}

void BSTADT()
{
	int count;
	while (1)
	{
		printf("Enter the command\n");
		fflush(stdin);
		gets(command);
		Blank(command);
		for (count_command = 0; count_command<strlen(command); count_command++)
		{
			switch (command[count_command])
			{
			case '+':
				CommandPlus();
				break;

			case 'L':
				CommandL();
				break;

			case 'I':
				CommandI();
				break;

			case 'R':
				CommandR();
				break;

			case 'S':
				CommandS();
				break;

			case 'T':
				CommandT();
				break;

			case 'E':
				CommandE();
				break;

			case '-':
				CommandMinus();
				break;

			case 'D':
				CommandD();
				break;

			case 'H':
				CommandH();
				break;

			case 'B':
				CommandB();
				break;

			case 'C':
				CommandC();
				break;

			case 'Q':
				CommandC();
				return;
				
			case 'O':
				PrintCommand();
				break;

			default:
				printf("Invalid input.\n");
				break;
			}
		}


	}


}

void PrintCommand()
{
	printf(
		"==========================================================================\n"
		"+N : Create N node. (0¡ÂN¡Â999)\n"
		"-N : Delete N node.\n"
		"L : Print the Tree.\n"
		"IOT : Traverse with inorder.\n"
		"RNFT : Traverse with the sequence that right-node-left.\n"
		"SV : Find the smallest value.\n"
		"LV : Find the largest value.\n"
		"TV(N) : Find the N value.\n"
		"IN : Get internal nodes.\n"
		"EN : Get external nodes.\n"
		"IC(N) : All nodes increase N.\n"
		"DC(N) : All nodes decrease N.\n"
		"H? : Get the height of the tree.\n"
		"BF? : Get the balance factor of the tree.\n"
		"C : Clear the tree\n"
		"O : Print the command list\n"
		"Q : Quit the program.\n"
		"==========================================================================\n"
	);
}

void Blank(char* array)
{
	int size, count, count2, k = 1;
	size = strlen(array);
	for (count = 0; count<size; count++)
	{
		if (*(array + count) == ' ')
		{
			for (count2 = 0; count2<size - count - 1; count2++)
			{
				*(array + count + count2) = *(array + count + count2 + 1);
			}
			count--;
			*(array + size - k) = 0;
			k++;
		}
	}
}

void CommandPlus()
{
	int number;
	number = ConvertInt(command + count_command);
	if (number == 1000)
	{
		printf("Invalid input or the number is out of range. (Need smaller than 1000)\n");
		count_command=strlen(command);
	}
	else
	{
		Insert(number);
		if (number<10)
		{
			count_command += 1;
		}
		else if (number >= 10 && number<100)
		{
			count_command += 2;
		}
		else if(number>=100)
		{
			count_command+=3;
		}
	}
}

void CommandL()
{
	if (command[count_command + 1] == 'V')
	{
		one = 1;
		RNLorder(root);
		printf("\n");
		one = 0;
		count_command++;
		return;
	}
	if (index_node == 0)
	{
		printf("There is no node\n");
	}
	else if (index_node == 1)
	{
		printf("%d\n", root->key);
	}
	else
	{
		printf("(%d", root->key);
		PrintChild(root);
		printf(")\n");
	}
}

void PrintChild(NODE* root)
{
	if (root->lchild || root->rchild)
	{
		printf("(");
		if (root->lchild)
		{
			printf("%d", root->lchild->key);
			PrintChild(root->lchild);
		}
		printf(",");
		if (root->rchild)
		{
			printf("%d", root->rchild->key);
			PrintChild(root->rchild);
		}
		printf(")");
	}
}

int ConvertInt(char* string)
{
	int count, size = 0, temp = 0;
	for (count = 1; count<strlen(string); count++)
	{
		if (string[count] == '+')
		{
			size = count - 1;
			break;
		}
		else if (count == strlen(string) - 1)
		{
			size = count;
		}
	}
	if (size == 0)
	{
		return 1000;
	}
	else if (size == 1)
	{
		if(string[1]<48 || string[1]>57)
		{
			temp=1000;
		}
		else
		{
			temp = string[1] - 48;
		}
		return temp;
	}
	else if (size == 2)
	{
		if(string[1]<48 || string[1]>57 || string[2]<48 || string[2]>57)
		{
			temp=1000;
		}
		else
		{
			temp = 10 * (string[1] - 48) + string[2] - 48;
		}
		return temp;
	}
	else if (size == 3)
	{
		if(string[1]<48 || string[1]>57 || string[2]<48 || string[2]>57 || string[3]<48 || string[3]>57)
		{
			temp=1000;
		}
		else
		{
			temp = 100 * (string[1] - 48) + 10 * (string[2] - 48) + string[3] - 48;
		}
		return temp;
	}
	else if (size >= 4)
	{
		return 1000;
	}
}

void Insert(int number)
{
	NODE* temp;
	if (index_node == 0)
	{
		node = (NODE**)malloc(sizeof(NODE*));
		node[0] = (NODE*)malloc(sizeof(NODE));
		node[0]->key = number;
		node[0]->parent = 0;
		InitializeNode(node[0]);
		root = node[0];
	}
	else
	{
		node = (NODE**)realloc(node, sizeof(NODE*)*(index_node + 1));
		node[index_node] = (NODE*)malloc(sizeof(NODE));
		node[index_node]->key = number;
		InitializeNode(node[index_node]);
		temp = Place(root, number);
		if (temp->key>number)
		{
			temp->lchild = node[index_node];
			temp->lchild->parent = temp;
		}
		else
		{
			temp->rchild = node[index_node];
			temp->rchild->parent = temp;
		}
	}
	index_node++;
}

void InitializeNode(NODE* node)
{
	node->lchild = 0;
	node->rchild = 0;
}

NODE* Place(NODE* parent, int number)
{
	if (parent->key>number)
	{
		if (parent->lchild)
		{
			Place(parent->lchild, number);
		}
		else
		{
			return parent;
		}
	}
	else
	{
		if (parent->rchild)
		{
			Place(parent->rchild, number);
		}
		else
		{
			return parent;
		}
	}
}

void CommandI()
{
	int number;
	if (command[count_command + 1] == 'O' && command[count_command + 2] == 'T')
	{
		Inorder(root);
		printf("\n");
		count_command += 2;
	}
	else if (command[count_command + 1] == 'N')
	{
		InExternal(root, 1);
		printf("\n");
		count_command++;
	}
	else if (command[count_command + 1] == 'C')
	{
		number = Bracket(command + count_command + 2);
		if (number == 1000)
		{
			printf("Invalid input or the number is out of range. (Need smaller than 1000)\n");
			return;
		}
		InDecrement(root, number);
		if (number<10)
		{
			count_command += 4;
		}
		else if (number >= 10 && number<100)
		{
			count_command += 5;
		}
		else if (number >= 100 && number<1000)
		{
			count_command += 6;
		}
	}
	else
	{
		printf("Invalid input.\n");
		count_command = strlen(command);
	}
}

void Inorder(NODE* parent)
{
	one_count = 0;
	if (parent->lchild)
	{
		Inorder(parent->lchild);
	}
	if (one_count == 0 && one == 1)
	{
		printf("%d ", parent->key);
		one_count++;
		return;
	}
	else if (one_count == 1)
	{
		return;
	}
	else
	{
		printf("%d ", parent->key);
	}
	if (parent->rchild)
	{
		Inorder(parent->rchild);
	}
}

void InDecrement(NODE* parent, int number)
{
	if (!parent)
	{
		printf("There is no node.\n");
	}
	else
	{
		parent->key += number;
		if (parent->lchild)
		{
			InDecrement(parent->lchild, number);
		}
		if (parent->rchild)
		{
			InDecrement(parent->rchild, number);
		}
	}
}

void CommandR()
{
	if (command[count_command + 1] == 'N' && command[count_command + 2] == 'F' && command[count_command + 3] == 'T')
	{
		RNLorder(root);
		printf("\n");
		count_command += 3;
	}
}

void RNLorder(NODE* parent)
{
	one_count = 0;
	if (parent->rchild)
	{
		RNLorder(parent->rchild);
	}
	if (one_count == 0 && one == 1)
	{
		printf("%d ", parent->key);
		one_count++;
		return;
	}
	else if (one_count == 1)
	{
		return;
	}
	else
	{
		printf("%d ", parent->key);
	}
	if (parent->lchild)
	{
		RNLorder(parent->lchild);
	}
}

void CommandS()
{
	if (command[count_command + 1] == 'V')
	{
		one = 1;
		Inorder(root);
		printf("\n");
		one = 0;
		count_command++;
	}
}

void CommandT()
{
	NODE* temp;
	int number, count;
	int* path, index_path = 0;
	path = (int*)malloc(sizeof(int) * 200);
	if (command[count_command + 1] == 'V' && command[count_command + 2] == '(')
	{
		if (!root)
		{
			printf("There is no node.\n");
			return;
		}
		number = Bracket(command + count_command + 2);
		if (number >= 1000)
		{
			printf("Invalid input\n");
			count_command = strlen(command);
			return;
		}
		temp = FindTV(root, number, path, &index_path);
		if (temp)
		{
			printf("Root");
			for (count = 0; count<index_path; count++)
			{
				if (path[count] == 1)
				{
					printf("-Left");
				}
				else if (path[count] == 2)
				{
					printf("-Right");
				}
			}
			printf("\n");
		}
		else
		{
			printf("Not exist!\n");
		}
		if (number<10)
		{
			count_command += 4;
		}
		else if (number >= 10 && number<100)
		{
			count_command += 5;
		}
		else if (number >= 100 && number<1000)
		{
			count_command += 6;
		}
	}
	else
	{
		printf("Invalid input\n");
		count_command = strlen(command);
	}
	free(path);
}

int Bracket(char* string)
{
	int count, number;
	for (count = 0; count<strlen(string); count++)
	{
		if (string[count] == ')')
		{
			break;
		}
		if (count == strlen(string) - 1)
		{
			count = 5;
			break;
		}
	}
	if (count == 2)
	{
		number = string[1] - 48;
	}
	else if (count == 3)
	{
		number = 10 * (string[1] - 48) + string[2] - 48;
	}
	else if (count == 4)
	{
		number = 100 * (string[1] - 48) + 10 * (string[2] - 48) + string[3] - 48;
	}
	else
	{
		number = 1000;
	}
	return number;
}

NODE* FindTV(NODE* parent, int number, int* path, int* index_path)
{
	NODE* temp = 0;
	if (parent->key == number)
	{
		return parent;
	}
	else
	{
		if (parent->lchild)
		{
			*(path + (*index_path)) = 1;
			*(index_path) = *(index_path)+1;
			temp = FindTV(parent->lchild, number, path, index_path);
			if (temp)
			{
				return temp;
			}
		}
		if (parent->rchild)
		{
			*(path + *index_path) = 2;
			*(index_path) = *(index_path)+1;
			temp = FindTV(parent->rchild, number, path, index_path);
			if (temp)
			{
				return temp;
			}
		}
	}
	if (!temp)
	{
		*(path + *index_path) = 0;
		*(index_path) = *(index_path)-1;
	}
	return temp;
}

void CommandE()
{
	if (command[count_command + 1] == 'N')
	{
		InExternal(root, 2);
		printf("\n");
		count_command++;
	}
	else
	{
		printf("Invalid input.\n");
		count_command = strlen(command);
	}

}

void InExternal(NODE* parent, int judge)
{
	if (parent->lchild || parent->rchild)
	{
		if (judge == 1)
		{
			printf("%d ", parent->key);
		}
		if (parent->lchild)
		{
			InExternal(parent->lchild, judge);
		}
		if (parent->rchild)
		{
			InExternal(parent->rchild, judge);
		}
	}
	else
	{
		if (judge == 2)
		{
			printf("%d ", parent->key);
		}
	}
}

void CommandMinus()
{
	int number, garbage;
	NODE* temp, *parent, *traverse;
	number = ConvertInt(command + count_command);
	if (number == 1000)
	{
		printf("Invalid input or the number is out of range. (Need smaller than 1000)\n");
	}
	else
	{
		temp = FindTV(root, number, &garbage, &garbage);
		if (temp->lchild)
		{
			traverse = temp->lchild;
			while (1)
			{
				if (traverse->rchild)
				{
					traverse = traverse->rchild;
				}
				else
				{
					break;
				}
			}
			parent = traverse->parent;
			if (parent == temp)
			{
				traverse->rchild = parent->rchild;
				traverse->parent = parent->parent;
			}
			else
			{
				parent->rchild = traverse->lchild;
				traverse->lchild = temp->lchild;
				if (traverse->lchild)
				{
					traverse->lchild->parent = traverse;
				}
				traverse->rchild = temp->rchild;
				if (traverse->rchild)
				{
					traverse->rchild->parent = traverse;
				}
				traverse->parent = temp->parent;
				if (parent->rchild)
				{
					parent->rchild->parent = parent;
				}
			}
			if (temp == root)
			{
				root = traverse;
			}
			else
			{
				if (temp->parent->lchild == temp)
				{
					temp->parent->lchild = traverse;
				}
				else if (temp->parent->rchild == temp)
				{
					temp->parent->rchild = traverse;
				}
			}
			free(temp);
		}
		else if (temp->rchild)
		{
			traverse = temp->rchild;
			while (1)
			{
				if (traverse->lchild)
				{
					traverse = traverse->lchild;
				}
				else
				{
					break;
				}
			}
			parent = traverse->parent;
			if (parent == temp)
			{
				traverse->lchild = parent->lchild;
				traverse->parent = parent->parent;
			}
			else
			{
				parent->lchild = traverse->rchild;
				traverse->lchild = temp->lchild;
				if (traverse->lchild)
				{
					traverse->lchild->parent = traverse;
				}
				traverse->rchild = temp->rchild;
				if (traverse->rchild)
				{
					traverse->rchild->parent = traverse;
				}
				traverse->parent = temp->parent;
				if (parent->lchild)
				{
					parent->lchild->parent = parent;
				}
			}
			if (temp == root)
			{
				root = traverse;
			}
			else
			{
				if (temp->parent->lchild == temp)
				{
					temp->parent->lchild = traverse;
				}
				else if (temp->parent->rchild == temp)
				{
					temp->parent->rchild = traverse;
				}
			}
			free(temp);
		}
		else
		{
			parent = temp->parent;
			if (parent->lchild == temp)
			{
				parent->lchild = 0;
			}
			else if (parent->rchild == temp)
			{
				parent->rchild = 0;
			}
			free(temp);
		}

		if (number<10)
		{
			count_command += 1;
		}
		else if (number >= 10)
		{
			count_command += 2;
		}
	}
}

void CommandD()
{
	int number;
	number = -Bracket(command + count_command + 2);
	if ((-number) == 1000)
	{
		printf("Invalid input or the number is out of range. (Smaller than 1000)\n");
		return;
	}
	InDecrement(root, number);
	if ((-number)<10)
	{
		count_command += 4;
	}
	else if ((-number) >= 10 && (-number)<100)
	{
		count_command += 5;
	}
	else if ((-number) >= 100 && (-number)<1000)
	{
		count_command += 6;
	}
}

void CommandH()
{
	int height_max = 0;
	if (command[count_command + 1] == '?')
	{
		if (root)
		{
			GetHeight(root, 1, &height_max);
			printf("%d\n", height_max);
		}
		else
		{
			printf("0\n");
		}
		count_command++;
	}
	else
	{
		printf("Invalid input.\n");
		count_command = strlen(command);
	}
}

void GetHeight(NODE* parent, int height, int* height_max)
{
	if (height>*height_max)
	{
		*height_max = height;
	}
	if (parent->lchild)
	{
		height++;
		GetHeight(parent->lchild, height, height_max);
		height--;
	}
	if (parent->rchild)
	{
		height++;
		GetHeight(parent->rchild, height, height_max);
		height--;
	}
}

void CommandB()
{
	int bf_max = 0;
	if (command[count_command + 1] == 'F' && command[count_command + 2] == '?')
	{
		if (!root)
		{
			printf("There is no node.\n");
			return;
		}
		StartBalanceFactor(root, &bf_max);
		printf("%d\n", bf_max);
		count_command += 2;
	}
	else
	{
		printf("Invalid input.\n");
		count_command = strlen(command);
	}
}

void StartBalanceFactor(NODE* parent, int* bf_max)
{
	GetBalanceFactor(parent, bf_max);
	if (parent->lchild)
	{
		StartBalanceFactor(parent->lchild, bf_max);
	}
	if (parent->rchild)
	{
		StartBalanceFactor(parent->rchild, bf_max);
	}
}

void GetBalanceFactor(NODE* parent, int* bf_max)
{
	int left_max = 0, right_max = 0, bf;
	if (parent->lchild)
	{
		CalBalanceFactor(parent->lchild, 1, &left_max);
	}
	if (parent->rchild)
	{
		CalBalanceFactor(parent->rchild, 1, &right_max);
	}
	bf = left_max - right_max;
	if (*bf_max >= 0)
	{
		if (bf >= 0 && bf>*bf_max)
		{
			*bf_max = bf;
		}
		else if (bf<0 && -bf>*bf_max)
		{
			*bf_max = bf;
		}
	}
	else
	{
		if (bf >= 0 && bf>-(*bf_max))
		{
			*bf_max = bf;
		}
		else if (bf<0 && bf<*bf_max)
		{
			*bf_max = bf;
		}
	}
}

void CalBalanceFactor(NODE* root, int bf, int* bf_max)
{
	if (bf >= *bf_max)
	{
		*bf_max = bf;
	}
	if (root->lchild)
	{
		bf++;
		CalBalanceFactor(root->lchild, bf, bf_max);
		bf--;
	}
	if (root->rchild)
	{
		bf++;
		CalBalanceFactor(root->rchild, bf, bf_max);
		bf--;
	}
}

void CommandC()
{
	int count;
	if(root)
	{
		Free(root);
		free(node);
	}
	root=0;
	index_node = 0;
	printf("Clear\n");
}

void Free(NODE* parent)
{
	if(parent->lchild)
	{
		Free(parent->lchild);
	}
	if(parent->rchild)
	{
		Free(parent->rchild);
	}
	free(parent);
}
