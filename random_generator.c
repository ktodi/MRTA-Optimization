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

coord set[1000];
int set_iter=0;

double gen_cost(coord a,coord b)
{
	return sqrt(pow((double)(a.x-b.x),2)+pow((double)(a.y-b.y),2));
}

void gen_matrix(double** cost_matrix,coord* robot,coord* task)
{
	int i,j;
	for(i=0;i<n;++i)
	{
		for(j=0;j<n;++j)
		{
			cost_matrix[i][j]=gen_cost(robot[i],task[j]);

		}
	}
}

int check_set(coord a)
{
	int i=0;
	while(i<set_iter)
	{
		if(set[i].x==a.x && set[i].y==a.y)
			return 1;
		i++;
	}
	return 0;
}

void gen_robot(coord* robot)
{
	int x_coord,y_coord;
	coord a;
	int i;
	srand(time(NULL));

	for(i=0;i<n;++i)
	{
		a.x=rand()%500;
		a.y=rand()%500;
		while(check_set(a))
		{
			a.x=rand()%500;
			a.y=rand()%500;
		}
		robot[i].x=a.x;
		robot[i].y=a.y;
		set[set_iter].x=a.x;
		set[set_iter].y=a.y;
		set_iter++;
	}
}

void gen_task(coord* task)
{
	int x_coord,y_coord;
	coord a;
	int i;
	srand(time(NULL));

	for(i=0;i<n;++i)
	{
		a.x=rand()%500;
		a.y=rand()%500;
		while(check_set(a))
		{
			a.x=rand()%500;
			a.y=rand()%500;
		}
		task[i].x=a.x;
		task[i].y=a.y;
		set[set_iter].x=a.x;
		set[set_iter].y=a.y;
		set_iter++;
	}
}

int main()
{
	scanf("n=%d",&n);
	coord robot[n];
	coord task[n];
	// fclose(fopen("input1.txt", "w"));
	// fclose(fopen("input_hungarian.txt", "w"));
	// fclose(fopen("output_hungarian.txt", "w"));
	// fclose(fopen("output_rob_algo.txt", "w"));
	double** cost_matrix;
	cost_matrix=(double**)malloc(n*sizeof(double*)); 	
	int i;
	for(i=0;i<n;++i)
	{
		cost_matrix[i]=(double*)malloc(n*sizeof(double));
	}

	gen_robot(robot);
	gen_task(task);
	gen_matrix(cost_matrix,robot,task);
	printf("%d\n",n);
	int row,col;
	for(row=0;row<n;++row)
	{
		for(col=0;col<n;++col)
		{
			printf("%f ",cost_matrix[row][col]);
		}
		printf("\n");
	}
	
	return 0;
}