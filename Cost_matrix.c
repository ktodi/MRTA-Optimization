// This program will generate a random cost function 
// based on coordinates of robots and tasks generated
// randomly.
// The x and y coordinates of both lies between [0,500].
// The cost between a task and a robot Cij=(vector distance between Robot Ri and task Tj). 
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
int n;
//coord is a structure comprising of x and y coordinates of Robot OR Task
typedef struct coord{
	int x;
	int y;
}coord;
//set helps in avoiding same pair of coordinates to be generated.
coord set[1000];
int set_iter=0;

//The cost genrated here is Euclidean distance between coordinate a and coordinate b.
double gen_cost(coord a,coord b)
{
	return sqrt(pow((double)(a.x-b.x),2)+pow((double)(a.y-b.y),2));
}

//Taking the Robot and task array it gives a cost matrix with each robot mapped to each Task
//Cij respresents distance between Robot i and Task j.
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

//Check set returns 0 and 1 if the coordinate does not appear in set or does appear. 
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

//This function will generate coordinates of Robots for all n robots.
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
		//Here check_set is used to avoid same coordinate to be generated.
		//If a new coordinate is generated it is stored in set array for future reference.
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

//This function will generate coordinates of Tasks for all n tasks.
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
		//Here check_set is used to avoid same coordinate to be generated.
		//If a new coordinate is generated it is stored in set array for future reference.
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
	//We take the number of robots and task as input which is n.
	scanf("n=%d",&n);
	//coordinate array of booth robot and task of size n.
	coord robot[n];
	coord task[n];
	//Cost Matrix of size nXn
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
	//Here in future this cost matrix is written to file for future actions 
	//to be performed on this.
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