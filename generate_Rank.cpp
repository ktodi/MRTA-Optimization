//Here two rank matrices are generated:-

//1) Rank all robots for each task based on their cost.
//The least cost robot is given 1st rank and next is given 2nd rank and so on.
//The highest cost robot is given last rank.
//This ranking is performed for each task.

//2)  Rank all tasks for each robot based on their cost.
//The least cost task is given 1st rank and next is given 2nd rank and so on.
//The highest cost task is given last rank.
//This ranking is performed for each Robot.

#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;
double** input;
int n;
int** rob_rank;
int** task_rank;
//Here we are using map to sort cost and ranking them.
map<double,int> sorted;
//This function genrates Rob_rank ,ranking of robots for each task
//for each task here the Robot Robot_Id is stored as value with its cost as key.
//The sorted map is then iterated and corresponding Task column stores the ranking i.e. the values stored in map.
void make_robot_rank()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			sorted[input[i][j]]=j;
		}
		int z=0;
		for(map<double,int> :: iterator it=sorted.begin();it!=sorted.end();it++)
		{
			rob_rank[i][z]=it->second;
			z++;
		}
		sorted.clear();
	}
}
//This function genrates Task_rank ,ranking of tasks for each robot
//for each robot here the task's Task_Id is stored as value with its cost as key.
//The sorted map is then iterated and corresponding Robot row stores the ranking i.e. the values stored in map.
void make_task_rank()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			sorted[input[j][i]]=j;
		}
		int z=0;
		for(map<double,int> :: iterator it=sorted.begin();it!=sorted.end();it++)
		{
			task_rank[i][z]=it->second;
			z++;

		}
		sorted.clear();
	}
}

//This will print the Task rank and Robot rank in a file.
//So this output generated here can be used for future reference.
void print_rank()
{
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<rob_rank[i][j]<<" ";
		} 
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<task_rank[i][j]<<" ";
		} 
		cout<<endl;
	}
	cout<<endl;
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cout<<input[i][j]<<" ";
		} 
		cout<<endl;
	}
}

int main()
{
	cin>>n;
	double x;

	//Here we are first reading the original matrix in input.
	//Then 2 rank matrices are genrated viz.
	//Rob_rank stores ranking based on robots where robots are ranked for each task.
	//And, Task_rank stores ranking based on tasks where tasks are ranked for each robot.

	input=(double**)malloc(n*sizeof(double*));
	for(int i=0;i<n;i++)
	{
		input[i]=(double*)malloc(n*sizeof(double));
	}
	rob_rank=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		rob_rank[i]=(int*)malloc(n*sizeof(int));
	}
	task_rank=(int**)malloc(n*sizeof(int*));
	for(int i=0;i<n;i++)
	{
		task_rank[i]=(int*)malloc(n*sizeof(int));
	}
	for(int i=0;i<n;i++)
	{
		for(int j=0;j<n;j++)
		{
			cin>>x;
			input[i][j]=x;
		}
	}
	cout<<n<<endl;
	make_robot_rank();
	make_task_rank();
	print_rank();
	return 0;
}
