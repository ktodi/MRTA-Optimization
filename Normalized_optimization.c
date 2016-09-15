//This the devised algorithm which works on the principle of normalization and
//sequential matching with interrobot communication.Here sequentially a robot finds its optimum task
//It communicates its choice to all other robots and based on optimum tasks for the rest of the robots
//the reply back.If the optimum task of 2 or more robot matches , they compete between each other and the one
//with least cost gets the task assigned.
//Here we have implemented this feature by implementing 2-D Linked List.

#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>

int n;
int turn;
int final_sol_iter=0;
int contender_iter=0;

//A task node is a node of a linked list 
//with cost as its value and task_id as its id and pointing
//to next node.
typedef struct task_node{
	int task_id;
	double cost;
	struct task_node *next;
}task_node;

//A robot node is a node of a linked list 
//with best task as and min_cost for that robot
//and linked list of task nodes and a pointer pointing
//to next node.
typedef struct robot_node{
	int rob_id;
	int best_task;
	double min_cost;

	task_node* head;
	struct robot_node* next;
}robot_node;

robot_node* initial_head;

//This provides with the optimal matching solution.
typedef struct 
optimal{
	int opt_rob;
	int opt_task;
	double cost;
	
}optimal;

optimal *final_sol;
optimal *contender_arr;

//The below two function initilizes a task node
//and robot nodes and allocates size to them.
task_node* initialize_task_node()
{
	task_node* newtask=(task_node*)malloc(sizeof(task_node));
	newtask->task_id=0;
	newtask->cost=0;
	newtask->next=NULL;
	return newtask;
}

robot_node* initialize_rob_node()
{
	robot_node* newrob=(robot_node*)malloc(sizeof(robot_node));
	newrob->rob_id=0;
	newrob->best_task=0;
	newrob->min_cost=0;
	newrob->head=NULL;
	newrob->next=NULL;

	return newrob;
}

//This initializes and allocates memmory for a new optimal node.
optimal* initial_optimal()
{
	optimal* new_optimal=(optimal*)malloc(sizeof(optimal));
	new_optimal->opt_rob=0;
	new_optimal->opt_task=0;
	new_optimal->cost=0;
	return new_optimal;
}
//The 4 functions below are insert functionf for both robots and tasks in the doubley linked list.
//Robots are in vertical manner and tasks in horizontal manner.
void insertFront_robot(robot_node** curr,robot_node* to_insert)
{
	to_insert->next=*curr;
		*curr=to_insert;
}

void insertFront_task(task_node** curr,task_node* to_insert)
{
	to_insert->next=*curr;
		*curr=to_insert;
}

void insertAfter_robot(robot_node* curr,robot_node* to_insert)
{	
	to_insert->next=(curr)->next;
	(curr)->next=to_insert;
}

void insertAfter_task(task_node* curr,task_node* to_insert)
{
	to_insert->next=(curr)->next;
	(curr)->next=to_insert;

}

//This will design the 2-D Linked list from the read 
//input so that further operations can be performed on it.
robot_node* read_list()
{
	int i,j;
	double cost;
	robot_node* head=NULL;
	robot_node* bef_r;
	task_node* bef_t;
	robot_node* curr_rob;
	task_node*curr_task;
	for(i=0;i<n;i++)
	{
		curr_rob=initialize_rob_node();
			curr_rob->rob_id=i+1;
		if(i==0)
		{
			insertFront_robot(&head,curr_rob);
		}
		else
		{
			insertAfter_robot(bef_r,curr_rob);
		}
		bef_r= curr_rob;
		for(j=0;j<n;j++)
		{
			curr_task=initialize_task_node();
			curr_task->task_id=j+1;
				scanf("%lf ",&cost);
			curr_task->cost=cost;
			if(j==0)
			{
			
				insertFront_task(&(curr_rob->head),curr_task);
				bef_t= curr_task;
			}
			else
			{
				if(j==n-1)
				{
					insertAfter_task(bef_t,curr_task);
				}
				else
				{
					insertAfter_task(bef_t,curr_task);
					bef_t= curr_task;
				}
			}
		}
	}
	return head;
}

//To prevent the anomaly caused by removing front robot in the list.
//This function manages this problem.
void remove_Frontrobot(robot_node** head)
{
	robot_node* temp=*head;
	*head=temp->next;
	free(temp);
}

//This removes the assigned robot and decrease the vertical length by 
//1 for all tasks.
void remove_robot_at(int rob_id)
{
	robot_node* curr;
	curr=initial_head;
	robot_node* y;

	if(curr==NULL)
		return -1;
	else
		
	{if(curr->rob_id==rob_id)
		
		{
			remove_Frontrobot(&initial_head);
		}
		else
		{
		while(curr!=NULL && curr->rob_id!=rob_id )
		{	y=curr;
			curr=curr->next;
		}
		if(curr==NULL)
		{
			y->next=NULL;
			free(curr);
		}
		else
		{
			y->next=curr->next;
			curr->next=NULL;
			
			free(curr);
		}
	}
	}

}

//This will remove a particular task from all the robot's linked list 
//of tasks.This will decrease the length of all horizontal linked list
//by 1.
void remove_task_at(int task_id,robot_node* temp)
{
	task_node* head_task;
	robot_node* curr=temp;
	task_node* y;

	if(curr==NULL)
	return -1;
else
{
	while(curr!=NULL)
	{
		head_task=curr->head;
		if(head_task->task_id==task_id)
		{
			curr->head=head_task->next;
			head_task->next=NULL;
			free(head_task);
		}
		else
		{
		while(head_task!=NULL && head_task->task_id!=task_id)
		{
			y=head_task;
			head_task=head_task->next;
		}
		if(head_task==NULL)
		{
			y->next=NULL;
			free(head_task);
		}
		else
		{
			y->next=head_task->next;
			head_task->next=NULL;
			free(head_task);
		}
	}
		curr=curr->next;
	}
}
}

//This function returns the contender which is optimal with respect to the
//task for which they are competing.
optimal* find_min_contender(optimal* curr)
{
	
	int i=0;
	optimal* contest=initial_optimal();
	contest->cost=curr->cost;
	contest->opt_rob=curr->opt_rob;
	contest->opt_task=curr->opt_task;

	while(i<contender_iter)
	{
		if(contest->cost>contender_arr[i].cost)
			{
				contest->opt_task=contender_arr[i].opt_task;
				contest->opt_rob=contender_arr[i].opt_rob;
				contest->cost=contender_arr[i].cost;

			}
			i++;
	}
return contest;
}

//Every time for new iteration/new chance for a robot
//this is initialized to manage the list of contenders.
void clear_contender_arr()
{
	int i;
	
	for(i=0;i<n;i++)
	{
		contender_arr[i].opt_task=0;
		contender_arr[i].opt_rob=0;
		contender_arr[i].cost=0;

	}
	contender_iter=0;
}

optimal* my_best(robot_node* choice)
{
	
	task_node* y;
	optimal* new=initial_optimal();
	task_node* temp_node=choice->head;
	int temp_task=temp_node->task_id;
	double cost=temp_node->cost;
	while(temp_node!=NULL)
	{
		y=temp_node;
		if(cost>temp_node->cost)
			
			{
				temp_task=temp_node->task_id;
				cost=temp_node->cost;
			}
		temp_node=temp_node->next;
	}
	new->opt_rob=choice->rob_id;
	new->opt_task=temp_task;
	new->cost=cost;
	return new;
}

//This will print the final matching and total cost,
//be it a output file or STDOUT.
void print_list(robot_node* head)
{
	robot_node* temp=head;
	task_node* temp_t;
	while(temp !=NULL)
	{
		temp_t=temp->head;
		while(temp_t!=NULL)
		{
			printf("\n%d,%d,%lf\n",temp->rob_id,temp_t->task_id,temp_t->cost);
			temp_t=temp_t->next;
		}
		temp=temp->next;
	}
}

//This is the main function implementing the proposed algorithm.
//It will iterate till all the robots are not assigned a task.
//and it will itearte atleast n times to give n channces to n robots.
void Rob_Algorithm(robot_node* traverse)
{
	robot_node* curr=traverse;
	optimal* temp;
	optimal* temp2;
	optimal* min;

	while(curr!=NULL && curr->rob_id!=turn)
	{
 		curr=curr->next;
	}
	if(curr==NULL)
		return -1;
	temp=my_best(curr);

	// printf("\nRobot %d's best choice is T%d with cost:%f\n",turn,temp->opt_task,temp->cost);
	curr=traverse;

	while(curr!=NULL)
	{
		if(curr->rob_id!=turn)
			{
				temp2=my_best(curr);
				if(temp2->opt_task==temp->opt_task)
				{
					// printf("\nRobot%d replied its best choice as task T%d with cost:%f\n",temp2->opt_rob,temp2->opt_task,temp2->cost);
					contender_arr[contender_iter].opt_rob=curr->rob_id;
					contender_arr[contender_iter].opt_task=temp2->opt_task;
					contender_arr[contender_iter].cost=temp2->cost;
					contender_iter++;
		
				}
			}
			
			curr=curr->next;
	}

	min=find_min_contender(temp);
	// printf("\nRobot wins:%d\n",min->opt_rob);
	// printf("\nThe optimal assignement is <R%d,T%d,%f>\n",min->opt_rob,min->opt_task,min->cost);
	final_sol[final_sol_iter].opt_rob=min->opt_rob;
	final_sol[final_sol_iter].opt_task=min->opt_task;
	final_sol[final_sol_iter].cost=min->cost;
	final_sol_iter++;

	remove_robot_at(min->opt_rob);
	remove_task_at(min->opt_task,traverse);
	clear_contender_arr();

}

int main()
{

	scanf("n=%d\n",&n);

	final_sol=(optimal*)malloc(n*sizeof(optimal));
	contender_arr=(optimal*)malloc(n*sizeof(optimal));
	int i;
	double** cost_matrix;
	cost_matrix=(double**)malloc(n*sizeof(double*)); 	

	for(i=0;i<n;++i)
	{
		cost_matrix[i]=(double*)malloc(n*sizeof(double));
	}
	int row,col;
	double cost;
	for(row=0;row<n;++row)
	{
		for(col=0;col<n;++col)
		{
			scanf("%lf ",&cost);
			cost_matrix[row][col]=cost;
		}
	}
	initial_head=read_list();		

	while(initial_head!=NULL)
	{
		for(turn=1;turn<=n;turn++)
		{
			// printf("\nChanceis:Robot%d\n",turn);
			Rob_Algorithm(initial_head);
			if(initial_head==NULL)
				break;
		}
	}
	double total_cost=0;
	for(i=0;i<n;i++)
	{
		total_cost+=cost_matrix[final_sol[i].opt_rob-1][final_sol[i].opt_task-1];
	}
	printf("Algorithm cost is : %f \n",total_cost);
	for(i=0;i<n;i++)
	{
		printf("<R%d,T%d,%f>\n",final_sol[i].opt_rob,final_sol[i].opt_task,cost_matrix[final_sol[i].opt_rob-1][final_sol[i].opt_task-1]);
	}


	return 0;
}