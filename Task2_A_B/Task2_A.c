#include <stdio.h>
#include <time.h>

#define ROW 2
#define COLUMN 2
#define SAME 1

int A[ROW][SAME],B[SAME][COLUMN],result[ROW][COLUMN]; //instance variables

int create_matrix(); //Creation Matrix
void print_result_matrix();
void print_A();
void print_B();

int main(int argc, char const *argv[])
{
	create_matrix();
	//Initial Naive method algorithm for matrix multiplication
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			for (int k = 0; k < SAME; ++k)
			{
				result[i][j] = result[i][j] + A[i][k] * B[k][j];
			}
			
		}
	}
	
	
	print_result_matrix();

	return 0;
}

int create_matrix(){
	//Creating Matrix for B
	for (int i = 0; i < SAME; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{

			B[i][j]= 2;
		}
	}
	
	
	//Creating Matrix for A
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < SAME; ++j)
		{
			A[i][j]= 2;
			
		}
	}
	return 0;
}

void print_result_matrix(){
	for (int i = 0; i < ROW; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			//print
			printf("%3d", result[i][j]);
		}
		printf("\n");
	}
}

void print_A(){
	for (int i = 0; i < SAME; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{		
			printf("%d\n", A[SAME][COLUMN]);
		}
	} 
}

void print_B(){
	for (int i = 0; i < SAME; ++i)
	{
		for (int j = 0; j < COLUMN; ++j)
		{
			
			printf("%d\n", B[ROW][COLUMN]);
		}
	}
}
