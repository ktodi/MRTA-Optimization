#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int n;

typedef struct coord{
	int x;
	int y;
}
coord;

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
			new_matrix[i][j]=cost_matrix[i][j]-sum/n;

		}
	}
}

int main()
{
	scanf("%d\n",&n);
	double** cost_matrix;
	cost_matrix=(double**)malloc(n*sizeof(double*)); 	
	int i;
	for(i=0;i<n;++i)
	{
		cost_matrix[i]=(double*)malloc(n*sizeof(double));
	}

	double** new_matrix;
	new_matrix=(double**)malloc(n*sizeof(double*)); 	
	for(i=0;i<n;++i)
	{
		new_matrix[i]=(double*)malloc(n*sizeof(double));
	}
	printf("n=%d\n",n);
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