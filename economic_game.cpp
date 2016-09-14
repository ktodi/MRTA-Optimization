//It is one of the Optimal Assignment Problem named as "ECONOMIC GAME"
//It uses auction game as method to asssign matching and come up with best alternative.
//The algorithm applies and economic market of buyers and sellers.
//where robots are buyers and sellers are selling tasks at a price with zero cost.
//The main aim of robots is to maximize its profit by choosing one task out of all the task.
//and this is achieved by dynamic pricing, as it changes with each assignment.

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

//MAX is the maximum value a cost can attain
//A cost with less value will have a great value.
//So we subtract the cost from this maximmum value.
//EPSILON is a smallest value which acts as an ignoring factor
//while finding maximum profit.

#define MAX sqrt(pow(500,2.0)+pow(500,2.0))
#define epsilon 0.00000001

//This will decide if all robots are happy or not
bool all_happy(vector<bool> &happy)
{
	for(int i=1;i<happy.size();i++)
	{
		if(!happy[i])
			return false;
	}
	return true;
}

//This will switch the tasks for two robots
//when one of them is not happy and it maximizes on task
//alloted to second one.
void switch_task(int ri,int rj,vector<int> &allotment,vector<int> &happy)
{
	int temp=allotment[ri];
	allotment[ri]=allotment[rj];
	allotment[rj]=temp;
	happy[ri]=true;
	happy[rj]=false;
}

//The below 2 functions collectively will determine
//if a robot is happy or not based on the property
//that value[i][ti]-p[ti]>=max{value[i][j]-p[j]} -epsilon
double get_max(vector<vector<double> > &value,vector<double> &price,int robot,int n)
{
	double maximum=0;
	for(int i=1;i<=n;i++)
	{
		maximum=max(maximum,value[robot][i]-price[i]);
	}
	return maximum;
}

bool is_robot_happy(vector<vector<double> > &value,vector<double> &price,int robot,int n,vector<int> &allotment,vector<bool> &happy)
{
	if(value[robot][allotment[robot]]-price[allotment[robot]]>=get_max(value,price,robot,n)-epsilon)
	{
		happy[robot]=true;
		return true;
	}
	else
	{
		return false;
	}
}

//This will find the robot matched with particular task.
//It will be helpful when we want to switch tasks
// between robots.
int find_robot(vector<int> &allotment,int task,int n)
{
	for(int i=1;i<=n;i++)
	{
		if(task==allotment[i])
			return i;
	}
}

//When a robot is not happy , this will provide the task which
//maximizes the profit for that particular robot.
int max_profit_task(vector<vector<double> > &value,vector<double> &price,int robot,int n)
{
	int task=1;
	int maximum=0;
	for(int i=1;i<=n;i++)
	{
		if(maximum<value[robot][i]-price[i])
		{
			maximum=value[robot][i]-price[i];
			task=i;
		}
	}
	return task;
}
//This will generate maximum profit for a robot
//when a task has been assigned to it by switching it with some other task.
//and this newly assigned task is excluded from the maximum consideration.
double profit_without_assignedtask(vector<vector<double> > &value,vector<double> &price,int robot,int n,int task)
{
	double maximum=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=task)
			maximum=max(maximum,value[robot][i]-price[i]);
	}
	return maximum;
}

//This is the main algorithm which does matching based on economic game
void economic_matching(vector<vector<double> > &input,vector<int> &price, vector<int> &allotment,vector<bool> &happy,int n)
{
	int robot,task;
	while(!all_happy(happy))
	{
		for(int rob=1;rob<=n;rob++)
		{
			if(!is_robot_happy(value, price,rob,n,allotment,happy))
			{
				task=max_profit_task(value,price,rob,n);
				robot=find_robot(allotment,task,n);
				switch_task(rob,robot,allotment,happy);
				price[task]=value[rob][task]-profit_without_assignedtask(value,price,robot,n,task)+epsilon;
			}
			if(all_happy(happy))
				break;
		}
	}
}
int main()
{
	cin>>n;
	vector<vector<double> > input(n+1,vector<double> (n+1));
	vector<bool> happy(n+1,false);
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>x;
			input[i][j]=x;
		}
	}
	vector<vector<double> > value(n+1,vector<double> (n+1));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>x;
			value[i][j]=MAX-input[i][j];
		}
	}
	vector<int> allotment(n+1);
	vector<double> price(n+1);
	for(int i=1;i<=n;i++)
	{
		allotment[i]=i;
	}
	economic_matching(value,price,allotment,happy,n);

	//Here the total cost incurred in matching and the 
	//matching is formulated and is presented as output.
	double total_cost=0;
	for(i=1;i<=n;i++)
	{
		total_cost+=input[i][allotment[i]];
	}
	cout<<total_cost<<endl;
	for(i=0;i<n;i++)
	{
		cout<<"<R"i",T"<<allotment[i]<<","<<input[i][allotment[i]]<<">"<<endl;
	}
}