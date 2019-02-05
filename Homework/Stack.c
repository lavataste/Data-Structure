#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<string.h>
struct number
{
	int	top;
	int data[50];
};
typedef struct number NUM;
void expression_conversion();
int check_space_tabs(char);
void push(long int);
int pop();
int priority(char);
int isEmpty();
int DisOper(char); 
void push_2(NUM*, int);
int pop_2(NUM*);
int bracket(char*, int);
 
int top;
long int stack[50];
int number[50];
char infix_expression[50], postfix_expression[50];
 
int main()
{
	printf("Welcome. The program is homework of calculation of Infix expression. The maker is ¿°ÅÂ¹Î.\nYou can insert the expression with +, - *, /, %, ^, (, )");
	int count, count_2, temp, oper1, oper2;
	char oper=0;
	NUM num;
	NUM* nump=&num;
	while(1)
	{
		top = -1;
		num.top=-1;
		printf("\nEnter an Expression in Infix format:\t\n");
		fflush(stdin);
		scanf("%[^\n]s", infix_expression);
		if(DisOper(infix_expression[strlen(infix_expression)-1])==1 || bracket(infix_expression, strlen(infix_expression)))
		{
			printf("Invalid Input\n");
			continue;	
		}
		expression_conversion();
		NUM s;
		s.top=-1;
		for(count=0;count<strlen(postfix_expression);count++)
		{
			if(DisOper(postfix_expression[count])==1)
			{
				oper=postfix_expression[count];
			}
			else if(DisOper(postfix_expression[count])==2)
			{
				if(number[count]!=0)
				{
					push_2(nump, number[count]);
				}
				else
				{
					push_2(nump, postfix_expression[count]-48);
				}	
			}
			if(num.top>=1 && oper!=0)
			{
				if(oper=='+')
				{
					oper2=pop_2(nump);
					oper1=pop_2(nump);
					temp=oper1+oper2;
					push_2(nump, temp);

				}
				else if(oper=='-')
				{
					oper2=pop_2(nump);
					oper1=pop_2(nump);
					temp=oper1-oper2;
					push_2(nump, temp);

				}
				else if(oper=='*')
				{
					oper2=pop_2(nump);
					oper1=pop_2(nump);
					temp=oper1*oper2;
					push_2(nump, temp);

				}
				else if(oper=='/')
				{
					oper2=pop_2(nump);
					oper1=pop_2(nump);
					temp=oper1/oper2;
					push_2(nump, temp);
				}
				else if(oper=='^')
				{
					oper2=pop_2(nump);
					oper1=pop_2(nump);
					temp=1;
					for(count_2=0;count_2<oper2;count_2++)
					{
						temp*=oper1;
					}
					push_2(nump, temp);
				}
				else if(oper=='%')
				{
					oper2=pop_2(nump);
					oper1=pop_2(nump);
					temp=oper1%oper2;
					push_2(nump, temp);
				}
				oper=0;
			}
		}
		if(num.top==0)
		{
			printf("%d\n", num.data[num.top]);
		}
		else
		{
			printf("Input is Invalid\n");
		}
		for(count=0;count<50;count++)
		{
			number[count]=0;
		}
	}
	return 0;
}
 
void expression_conversion()
{
	unsigned int count, temp = 0;
	char next;
	char character;	
	for(count = 0; count < strlen(infix_expression); count++)
	{
		character = infix_expression[count];
		if(!check_space_tabs(character))
		{
			switch(character)
			{
				case '(': push(character);
					  break;
				case ')':
					  while((next = pop()) != '(')
					  {
						postfix_expression[temp++] = next;
					  }
					  break;
				case '+':
				case '-':
				case '*':
				case '/':
				case '%':
				case '^':
					  while(!isEmpty() && priority(stack[top]) >= priority(character))
					  postfix_expression[temp++] = pop();
				          push(character);
					  break;
				default:
						if(infix_expression[count+1]>=48 && infix_expression[count+1]<=57)
						{
							number[temp]=(character-48)*10+infix_expression[count+1]-48;
						}
						else
						{
			     			postfix_expression[temp++] = character;
			     		}	
			}
		}
	}
	while(!isEmpty()) 
	{
		postfix_expression[temp++] = pop();
	}
	postfix_expression[temp] = '\0';
}
 
int priority(char character)
{
	switch(character)
	{
		case '(': return 0;
		case '+':
		case '-':
			  return 1;
		case '*':
		case '/':
		case '%':
			  return 2;
		case '^':
			  return 3;
		default:
			 return 0;
	}
}
 
void push(long int character)
{
	if(top > 50)
	{
		printf("Stack Overflow\n");
		exit(1);
	}
	top = top + 1;
	stack[top] = character;
}
 
int check_space_tabs(char character)
{
	if(character == ' ' || character == '\t')
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
 
int pop()
{
	if(isEmpty())
	{
		printf("Stack is Empty\n");
		exit(1);
	}
	return(stack[top--]);
}
 
int isEmpty()
{
	if(top == -1)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int DisOper(char element)
{
	if(element==37 || element==42 || element==43 || element==45 || element==47 || element==94)
	{
		return 1;
	}
	else if(element>=48 || element<=57)
	{
		return 2;
	}
	else
	{
		return 0;
	}
}
void push_2(NUM* nump, int number)
{
	if(nump->top>49)
	{
		printf("The stack is full.\n");
	}
	else
	{
		nump->top++;
		nump->data[nump->top]=number;
	}	
}
int pop_2(NUM* nump)
{
	if(nump->top==-1)
	{
		printf("The stack is empty.\n");
		return 0;
	}
	else
	{
		return nump->data[nump->top--];
	}
}
int bracket(char* infix, int size)
{
	int count, open=0, close=0;
	for(count=0;count<size;count++)
	{
		if(infix[count]=='(')
		{
			open++;
		}
		else if(infix[count]==')')
		{
			close++;	
		}
	}
	if(open==close)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}
