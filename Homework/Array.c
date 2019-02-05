#include<stdio.h>
int main()
{
	int Matrix_A[3][3] = {3, 24, 11, 42, 71, 9, 51, 14, 35};
	int Matrix_B[3][3] = {-7, 33, 3, 82, 21, 41, 32, 56, 123};
	int Matrix_result[3][3] = {0};
	int i, j;
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			Matrix_result[i][j] = Matrix_A[i][j] + Matrix_B[i][j];
		}
	}	
	
	printf("The result of add two matrices\n");
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("%d ", Matrix_result[i][j]);
		}
		printf("\n");
	}
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			Matrix_result[i][j] = Matrix_A[i][j] - Matrix_B[i][j];
		}
	}	
	
	printf("The result of subtract two matrices\n");
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("%d ", Matrix_result[i][j]);
		}
		printf("\n");
	}
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			Matrix_result[i][j] = Matrix_A[i][0]*Matrix_B[0][j] + Matrix_A[i][1]*Matrix_B[1][j] + Matrix_A[i][2]*Matrix_B[2][j];
		}
	}
	
		printf("The result of multiply two matrices\n");
	
	for(i=0; i<3; i++)
	{
		for(j=0; j<3; j++)
		{
			printf("%d ", Matrix_result[i][j]);
		}
		printf("\n");
	}
	
	return 0;
}
		
