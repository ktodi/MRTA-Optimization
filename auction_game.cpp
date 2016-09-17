//It is one of the Optimal Assignment Problem named as "ECONOMIC GAME"
//It uses auction game as method to asssign matching and come up with best alternative.
//The algorithm applies and economic market of buyers and sellers.
//where robots are buyers and sellers are selling tasks at a price with zero cost.
//The main aim of robots is to maximize its profit by choosing one task out of all the task.
//and this is achieved by dynamic pricing, as it changes with each assignment.

#include <iostream>
#include <vector>
#include <cmath>
#include <random>
#include <functional>
#include <set>
using namespace std;

//MAX is the maximum value a cost can attain
//A cost with less value will have a great value.
//So we subtract the cost from this maximmum value.
//EPSILON is a smallest value which acts as an ignoring factor
//while finding maximum profit.

#define MAX sqrt(pow(500,2.0)+pow(500,2.0))
#define epsilon 0.00000001

// These two sets determine which robots are happy
// and which are not.
set<int> happy;
set<int> unhappy;

//The below to functions are used to select random element from the respective sets.
int GetSample() {
  double r = rand() % unhappy.size();
  std::set<int>::iterator it = unhappy.begin();
  for (; r != 0; r--) it++;
  return *it;
}

int Gettemp(const std::set<int>& s) {
  double r = rand() % s.size();
  std::set<int>::iterator it = s.begin();
  for (; r != 0; r--) it++;
  return *it;
}

//This function will generate a random double number.
//It is useful for initialization of price vector.
class Rand_double
{
public:
    Rand_double(double low, double high)
    :r(std::bind(std::uniform_real_distribution<>(low,high),std::default_random_engine())){}

    double operator()(){ return r(); }

private:
    std::function<double()> r;
};

//This will switch the tasks for two robots
//when one of them is not happy and it maximizes on task
//alloted to second one.
void switch_task(int ri,int rj,vector<int> &allotment)
{
	int temp=allotment[ri];
	allotment[ri]=allotment[rj];
	allotment[rj]=temp;
	unhappy.erase(ri);
	happy.insert(ri);
	if(happy.find(rj)!=happy.end())
	{
		happy.erase(rj);
		unhappy.insert(rj);
	}
}

//The below 2 functions collectively will determine
//if a robot is happy or not based on the property
//that value[i][ti]-p[ti]>=max{value[i][j]-p[j]} -epsilon
double get_max(vector<vector<double> > &value,vector<double> &price,int robot,int n,int *max_task)
{

	double maximum=0;

	for(int i=1;i<=n;i++)
	{
		if(maximum<value[robot][i]-price[i])
		{
			maximum=value[robot][i]-price[i];
			*max_task=i;
		}
	}
	return maximum;
}

bool is_robot_happy(vector<vector<double> > &value,vector<double> &price,int robot,int n,vector<int> &allotment,int *max_task)
{
	if(value[robot][allotment[robot]]-price[allotment[robot]]>=get_max(value,price,robot,n,max_task)-epsilon)
	{
		happy.insert(robot);
		unhappy.erase(robot);
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
int find_robot(vector<int> &allotment,int *task,int n)
{
	for(int i=1;i<=n;i++)
	{
		if(*task==allotment[i])
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
double profit_without_assignedtask(vector<vector<double> > &value,vector<double> &price,int robot,int n,int *task)
{
	double maximum=0;
	for(int i=1;i<=n;i++)
	{
		if(i!=*task)
			maximum=max(maximum,value[robot][i]-price[i]);
	}
	return maximum;
}

//This is the main algorithm which does matching based on economic game
void economic_matching(vector<vector<double> > &value,vector<double> &price, vector<int> &allotment,int n)
{
	int robot,task;
	while(!unhappy.empty())
	{
		int rob=GetSample();
		int *task=(int *)malloc(sizeof(int));
			if(!is_robot_happy(value, price,rob,n,allotment,task))
			{
				robot=find_robot(allotment,task,n);
				switch_task(rob,robot,allotment);
				price[*task]=value[rob][*task]-profit_without_assignedtask(value,price,robot,n,task)+epsilon;
			}
	}
}
int main()
{
	int n;
	cin>>n;
	vector<vector<double> > input(n+1,vector<double> (n+1));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			cin>>input[i][j];
		}
	}
	vector<vector<double> > value(n+1,vector<double> (n+1));
	for(int i=1;i<=n;i++)
	{
		for(int j=1;j<=n;j++)
		{
			value[i][j]=MAX-input[i][j];
		}
	}
	vector<int> allotment(n+1);
	vector<double> price(n+1);
	set<int> temp;
	Rand_double rd{1,250};
	for(int i=1;i<=n;i++)
	{
		price[i]=rd();
	}
	for(int i=1;i<=n;i++)
	{
		unhappy.insert(i);
		temp.insert(i);
	}

	//Here random allotment is done at first between robots and tasks.
	for(int i=1;i<=n;i++)
	{
		allotment[i]=Gettemp(temp);
		temp.erase(allotment[i]);
	}
	economic_matching(value,price,allotment,n);

	//Here the total cost incurred in matching and the 
	//matching is formulated and is presented as output.
	double total_cost=0;
	for(int i=1;i<=n;i++)
	{
		total_cost+=input[i][allotment[i]];
	}
	cout<<"Economic Cost is : "<<total_cost<<endl;
	for(int i=1;i<=n;i++)
	{
		cout<<"<R"<<i<<",T"<<allotment[i]<<","<<input[i][allotment[i]]<<">"<<endl;
	}
}