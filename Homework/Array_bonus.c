#include<stdio.h>
#include<string.h>
int main()
{
while(1){
	char palindrome[100];
	int i, j, size, judgement=0;
	printf("Write the string you want judge whether palindrome. (It can judge only English string.)\nIf you don't want do it, press enter.\n\n");
	gets(palindrome);
	size=strlen(palindrome);
	if(size==0)
	{
		return 0;
	}
	for(j=0;j<50;j++)
	{
		for(i=0;i<size;i++)
		{	
			if((palindrome[i]>=65 && palindrome[i]<= 90) || (palindrome[i]>=97 && palindrome[i]<=122))
			{
		
			}
			else
			{
				palindrome[i]=palindrome[i+1];
				palindrome[i+1]=0;
			}
		}
	}
	size=strlen(palindrome);
	for(i=0;i<size;i++)
	{
		if(palindrome[i]==palindrome[size-1-i] || palindrome[i]==palindrome[size-1-i]+32 || palindrome[i]==palindrome[size-1-i]-32)
		{
		}
		else judgement++;
	}
	if(judgement==0)
	{
		printf("\nThe string is a palindrome.\n\n");
	}
	else
	{
		printf("\nThe string is not a palindrome.\n\n");
	}
	
	
}
	return 0;
}
	
