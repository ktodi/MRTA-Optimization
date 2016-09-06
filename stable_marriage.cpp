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

bool isfree(int j)
{
    set<int>::iterator it;
    it=free_task.find(j);
    if(it!=free_task.end())
        return true;
    return false;
}

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
bool rankgreater(int engaged_robot,int task,int test_robot)
{
    if(get_rank_pos(task,engaged_robot)<get_rank_pos(task,test_robot))
        return true;
    else
        return false;
}

void stable_marriage()
{
    while(!prospect_robot.empty())
    {
        int test_robot=prospect_robot.top();
        prospect_robot.pop();
      //  cout<<test_robot<<" has got the chance"<<endl;
        int dum_counter;
        int proposed_task=robot_rank[test_robot][count_rank[test_robot]];
      //  cout<<test_robot<<" proposed to "<<proposed_task<<endl;
        count_rank[test_robot]++;
        if(isfree(proposed_task))
        {
      //  	cout<<"is free"<<endl;
            engaged[arr_counter].rob_id=test_robot;
            engaged[arr_counter].task_id=proposed_task;
            free_task.erase(proposed_task);
            arr_counter++;
        }
        else{
            
            dum_counter=get_counter(proposed_task);
       //     cout<<"dum_counter is "<<dum_counter<<endl;
            int robot_dash=engaged[dum_counter].rob_id;
        //    cout<<"compared to robot "<<robot_dash<<endl;
            if(rankgreater(robot_dash,proposed_task,test_robot))
            {
        //    	cout<<"is free and rank greater"<<endl;
                prospect_robot.push(test_robot);
            }
            else{
         //   	cout<<"is free and rank not greater"<<endl;
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
    // robot_rank[0][0]=0;
    // robot_rank[0][1]=2;
    // robot_rank[0][2]=1;
    // robot_rank[1][0]=2;
    // robot_rank[1][1]=0;
    // robot_rank[1][2]=1;
    // robot_rank[2][0]=2;
    // robot_rank[2][1]=1;
    // robot_rank[2][2]=0;
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
    // task_rank[0][0]=1;
    // task_rank[0][1]=2;
    // task_rank[0][2]=0;
    // task_rank[1][0]=1;
    // task_rank[1][1]=0;
    // task_rank[1][2]=2;
    // task_rank[2][0]=2;
    // task_rank[2][1]=1;
    // task_rank[2][2]=0;
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
