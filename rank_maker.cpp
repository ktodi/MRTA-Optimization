// on other branch

#include <iostream>
#include <map>
#include <cstdlib>
using namespace std;
double** input;
int n;
int** rob_rank;
int** task_rank;

map<double,int> sorted;
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
			//cout<<it->second<<" ";
			z++;

		}
		sorted.clear();
		//cout<<endl;
	}
}
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
