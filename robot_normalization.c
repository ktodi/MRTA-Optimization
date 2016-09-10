//This program will genrate a normalized cost matrix
//where the normalization is done based on robots.
//the normalized value of any Cij is calculated by calculating
//MEAN of cost incurred by all robots for particular Task Tj
//The cost Cij for each Robot i corresponding to Task j is subtracted with this MEAN.
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int n;
//The normalize function does performs the naive approach with time complexity O(sq(n)).
//for each Task[column] the mean is calculated by iterating through every robot for that task.
//The normalized cost is calculated by iterating over each robot and subtracting the mean from each cost.
//This action is performed for all the n tasks.

void normalize_matrix(double** cost_matrix,double** new_matrix)
{
	int i,j,k;
	double sum;
	for(i=0;i<n;++i)
	{ 
		sum=0;
		for(k=0;k<n;++k)
		{
			sum+=cost_matrix[k][i];
		}
		for(j=0;j<n;++j)
		{
			new_matrix[j][i]=cost_matrix[j][i]-sum/n;

		}
	}
}

int main()
{
	scanf("%d\n",&n);
	//The cost_matrix is the original matrix read from 
	//previously generated program
	double** cost_matrix;
	cost_matrix=(double**)malloc(n*sizeof(double*)); 	
	int i;
	for(i=0;i<n;++i)
	{
		cost_matrix[i]=(double*)malloc(n*sizeof(double));
	}
	//The new_matrix is the matrix genrated after performing required algorithm.
	double** new_matrix;
	new_matrix=(double**)malloc(n*sizeof(double*)); 	
	for(i=0;i<n;++i)
	{
		new_matrix[i]=(double*)malloc(n*sizeof(double));
	}
	printf("n=%d\n",n);
	//First the cost_matix is read.
	int row,col;
	double cost;
	for(row=0;row<n;++row)
	{
		for(col=0;col<n;++col)
		{
			scanf("%lf ",&cost);
			cost_matrix[row][col]=cost;
			printf("%lf ",cost);
		}
		printf("\n");
	}

	normalize_matrix(cost_matrix,new_matrix);
	
	printf("\n");
	for(row=0;row<n;++row)
	{
		for(col=0;col<n;++col)
		{
			printf("% lf ",new_matrix[row][col]);
		}
		printf("\n");
	}
	
	return 0;
}