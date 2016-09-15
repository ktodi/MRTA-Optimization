//This here implements the famous Stable Marriage algorithm
//For matching of Robots and Tasks in Multi-Robot Task Allocation.
//This algorithm uses the concept of ranking of bbot tasks and robots to each other.
//Each robot chooses its best available option and if there is a conflict 
//task decides which robot gets preference based on ranking.

#include <cstdlib>
#include <iostream>
#include <stack>
#include <set>
using namespace std;

typedef struct node{
    int task_id;
    int rob_id;
}node;

int n;
double **input;
int *count_rank;
int **robot_rank;
int **task_rank;
stack<int> prospect_robot;
node* engaged;
int arr_counter=0;
set<int> free_task;
stack<int> temp;

//This function looks for the task
//if it has been matched till now or not.
//If it is matched it returns false else true.
bool isfree(int j)
{
    set<int>::iterator it;
    it=free_task.find(j);
    if(it!=free_task.end())
        return true;
    return false;
}

//This is helful to get the counter position of
//queried task in the engaged array.
int get_counter(int task)
{
    int i;
        for(i=0;i<arr_counter;i++)
        {
            if(engaged[i].task_id==task)
                break;
        }
        return i;
}

//This gives the rank of robot for that particular task
//as formulated in task_rank matrix.
int get_rank_pos(int task,int robot)
{
    int i;
    for(i=0;i<n;i++)
    {
        if(task_rank[task][i]==robot)
            break;
    }
    return i-1;
}

//This function checks for if the new candidate robot
//has better rank then already assigned robot to that particular task.
//It returns true if previously assigned robot is better than new
//robot else false.
bool rankgreater(int engaged_robot,int task,int test_robot)
{
    if(get_rank_pos(task,engaged_robot)<get_rank_pos(task,test_robot))
        return true;
    else
        return false;
}

//This is the main algorithm which perform the stable marriage
//algorithm as proposed above on the data to give appropriate matching.
void stable_marriage()
{
    while(!prospect_robot.empty())
    {
        int test_robot=prospect_robot.top();
        prospect_robot.pop();
        int proposed_task=robot_rank[test_robot][count_rank[test_robot]];
        count_rank[test_robot]++;
        if(isfree(proposed_task))
        {
            engaged[arr_counter].rob_id=test_robot;
            engaged[arr_counter].task_id=proposed_task;
            free_task.erase(proposed_task);
            arr_counter++;
        }
        else{
            
            int dum_counter=get_counter(proposed_task);
            int robot_dash=engaged[dum_counter].rob_id;
            if(rankgreater(robot_dash,proposed_task,test_robot))
            {
                prospect_robot.push(test_robot);
            }
            else{
                engaged[dum_counter].rob_id=test_robot;
                prospect_robot.push(robot_dash);
            }
        }

    }
}


int main(){
    cin>>n;
    int dummy;
    double double_dummy;
    //The task_rank are rob_rank are rank matrics
    //of both task and robot based on robots and tasks respectively
    //.This is generated before by rank_generator

    //The count rank here stores the counter of each robot at its ranking list.
    //This is helpful to avoid robots to again consider previously operated rank 
    //for new operation.
    count_rank=(int*)malloc(n*sizeof(int));
    robot_rank=(int**)malloc(n*sizeof(int*));
    for(int i=0;i<n;i++)
    {
        robot_rank[i]=(int*)malloc(n*sizeof(int));
    }
     for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
        	cin>>dummy;
        	robot_rank[i][j]=dummy;
        }
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
        	cin>>dummy;
        	task_rank[i][j]=dummy;
        }
    }
   
    input=(double**)malloc(n*sizeof(double*));
    for(int i=0;i<n;i++)
    {
        input[i]=(double*)malloc(n*sizeof(double));
    }
       for(int i=0;i<n;i++)
    {
        for(int j=0;j<n;j++)
        {
        	cin>>double_dummy;
       		input[i][j]=double_dummy;
        }
    }

    for(int i=0;i<n;i++)
    {
        count_rank[i]=0;
    }

    engaged=(node*)malloc(n*sizeof(node));
    for(int i=n-1;i>=0;i--)
    {
        prospect_robot.push(i);
    }
    for(int i=0;i<n;i++)
    {
        free_task.insert(i);
    }
    for(int i=0;i<n;i++)
    {
        engaged[i].task_id=0;
    }
    stable_marriage(); 
    double cost=0;
    for(int i=0;i<n;i++)
    {
        cost=cost+input[engaged[i].rob_id][engaged[i].task_id];
    }
    cout<<"Stable_marriage cost is : "<<cost<<endl;
    for(int i=0;i<n;i++)
    {
    	cout<<"robot "<<engaged[i].rob_id+1<<" matched with task "<<engaged[i].task_id+1<<" with cost "<<input[engaged[i].rob_id][engaged[i].task_id]<<endl;
    }
    
    return 0;
}
