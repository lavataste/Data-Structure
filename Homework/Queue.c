//It is ¿°ÅÂ¹Î's data structre HW#04 with Queue. 
#define MAX 100
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
typedef struct	//the definition of struct of employee.
{
	char name[20];
	char* done[20];
	int go;
	int leave;
	int free;
	int idletime;
	int job;
} EMPLOYEE;
typedef struct	//the definition of struct of work.
{
	char name[20];
	char* doneby;
	int become;
	int duration;
	int finish;
} WORK;
typedef struct
{
	EMPLOYEE* item[MAX];
	int front;
	int rear;
} QUEUE_E;
typedef struct
{
	WORK* item[MAX];
	int front;
	int rear;
} QUEUE_W;
typedef struct
{
	char* work;
	char* employee;
	int start;
	int finish;
	int waiting;
} LOG;

int time;
int number_e=0, number_w=0, index_e=0, index_w=0, index_l=0, index_lr=0;
QUEUE_E queue_e;
QUEUE_W queue_w;
LOG* log_d[50], *log_r[50];
EMPLOYEE* employee[MAX];
WORK* work[MAX];

void PrintCommand();
void Enqueue_e(EMPLOYEE*);
EMPLOYEE* Dequeue_e();
void Enqueue_w(WORK*);
WORK* Dequeue_w();
int NumberQueue_e();
int NumberQueue_w();
int CheckWorkPossible();
int TimeConversion(int);
void PrintTime(int);
void QueueIdletime();
void PrintDoWork(char*);
void InitializeQueue_e();
void InitializeQueue_w();
void InitializeRun();
int StringTimeConversion(char*);
int CheckTime(char*);
void EmployeeOrder();

int main()
{
//	int time=0;
	int count, count2, judgement=0, time_temp, temp=0; 
	char command;
	char command_s[20], command_time[6];
	EMPLOYEE *temp_e;
	WORK *temp_w; 
	queue_e.front=0;
	queue_e.rear=-1;
	queue_w.front=0;
	queue_w.rear=-1;
	printf("Hello, you can calculate the schedule of employee.\n");
	PrintCommand();
	while(1)	//main repeat statement
	{
		judgement=0;
		printf("Enter the command.\n");
		fflush(stdin);
		scanf("%c", &command);
		if(command=='E' || command=='e')
		{
			employee[index_e]=(EMPLOYEE*)malloc(sizeof(EMPLOYEE));
			printf("Enter the employee's name.\n");
			fflush(stdin);
			gets(employee[index_e]->name);
			printf("Enter the employee's going to work time.(Example : 09:00)\n");
			while(judgement==0)
			{
		 		fflush(stdin);
		 		gets(command_time);
		 		time_temp=StringTimeConversion(command_time);
				if(CheckTime(command_time)==1)
				{
					printf("Invalid time. Enter the valid time.\n");
				}
				else
				{
					employee[index_e]->go=time_temp;
					employee[index_e]->free=employee[index_e]->go;
					judgement++;
				}
			}
			judgement--;
		 	printf("Enter the employee's leaving to home time.(Example : 17:30)\n");
		 	while(judgement==0)
			{
				fflush(stdin);
		 		gets(command_time);
		 		time_temp=StringTimeConversion(command_time);
				if(CheckTime(command_time)==1)
		 		{
		 			printf("Invalid time. Enter the valid time.\n");
		 		}
		 		else
		 		{
		 			employee[index_e]->leave=time_temp;
		 			employee[index_e]->job=0;
		 			employee[index_e]->idletime=employee[index_e]->leave-employee[index_e]->go;
					number_e++;
		 			index_e++;
		 			judgement++;
		 		}
		 	}
		}
		else if(command=='W' || command=='w')
		{
			work[index_w]=(WORK*)malloc(sizeof(WORK));
			printf("Enter the work's name.\n");
			fflush(stdin);
			gets(work[index_w]->name);
			printf("Enter the work's start time.(Example : 09:00)\n");
			while(judgement==0)
			{
		 		fflush(stdin);
				gets(command_time);
		 		time_temp=StringTimeConversion(command_time);
				if(CheckTime(command_time)==1)
				{
					printf("Invalid time. Enter the valid time.\n");
				}
				else
				{
					work[index_w]->become=time_temp;
		 			printf("Enter the work's duration.(The unit is minute.)\n");
			 		fflush(stdin);
			 		scanf("%d", &(work[index_w]->duration));
			 		number_w++;
			 		index_w++;
			 		judgement++;
			 	}
			}
		}
		else if(command=='S' || command=='s')
		{
			printf("What do you want to read the list? Enter employee as 'E' or work as 'W'\n");
			fflush(stdin);
			scanf("%c", &command);
			if(command=='E' || command=='e')
			{
				if(number_e==0)
				{
					printf("There is no employee.\n");
				}
				else
				{
					for(count=0;count<index_e;count++)
					{
						if(employee[count]==0)
						{
							continue;
						}
						else
						{
							puts(employee[count]->name);
							PrintTime(employee[count]->go);
							PrintTime(employee[count]->leave);
							printf("\n");
						}
					}
				}
			}
			else if(command=='W' || command=='w')
			{
				if(number_w==0)
				{
					printf("There is no work.\n");
				}
				else
				{
					for(count=0;count<index_w;count++)
					{
						if(work[count]==0)
						{
							continue;
						}
						else
						{
							printf("%s ", work[count]->name);
							PrintTime(work[count]->become);
							printf("%d\n", work[count]->duration);
						}
					}
				}
			}
			else
			{
				printf("Invalid input.\n");
			}
		}
		else if(command=='D' || command=='d')
		{
			printf("What do you want to delete? Enter employee as 'E' or work as 'W'\n");
			fflush(stdin);
			scanf("%c", &command);
			if(command=='E' || command=='e')
			{
				printf("Enter the name of employee you want to delete.\n");
				fflush(stdin);
				gets(command_s);
				for(count=0;count<index_e;count++)
				{
					if(employee[count]==0)
					{
						continue;
					}
					else if(strcmp(employee[count]->name, command_s)==0)
					{
						printf("deleted\n");
						free(employee[count]);
						employee[count]=0;
						number_e--;
						break;
					}
				}
			}
			else if(command=='W' || command=='w')
			{
				printf("Enter the name of work you want to delete.\n");
				fflush(stdin);
				gets(command_s);
				for(count=0;count<index_w;count++)
				{
					if(work[count]==0)
					{
						continue;
					}
					else if(strcmp(work[count]->name, command_s)==0)
					{
						printf("deleted\n");
						free(work[count]);
						work[count]=0;
						number_w--;
						break;
					}
				}
			}
			else
			{
				printf("Invalid input\n");
			}
		}
		else if(command=='C' || command=='c')
		{
			PrintCommand();
		}
		else if(command=='R' || command=='r')
		{
			if(number_e==0 && number_w==0)
			{
				printf("Before calculaiting, you have to enter the employees and works.\n");	
			}
			else
			{
				while(time<1440) // every minute calculating
				{
					for(count=0;count<index_e;count++)
					{
						if(employee[count]==0)
						{
							continue;
						}
						else if(employee[count]->free==time)
						{
							Enqueue_e(employee[count]);
						}
					}
					for(count=0;count<index_w;count++)
					{
						if(work[count]==0)
						{
							continue;
						}
						else if(work[count]->become==time)
						{
							Enqueue_w(work[count]);
						}	
					}
					while(NumberQueue_e()!=0 && NumberQueue_w()!=0)
					{
						if(CheckWorkPossible()) 
						{
							temp_e=Dequeue_e();
							temp_w=Dequeue_w();
							temp_e->free=time+(temp_w->duration);
							temp_e->done[temp_e->job]=temp_w->name;
							temp_e->job++;
							temp_e->idletime-=temp_w->duration; 
							temp_w->finish=time+temp_w->duration;
							temp_w->doneby=temp_e->name;
							log_d[index_l]=(LOG*)malloc(sizeof(LOG));
							log_d[index_l]->work=temp_w->name;
							log_d[index_l]->employee=temp_e->name;
							log_d[index_l]->start=time;
							log_d[index_l]->finish=time+temp_w->duration;
							log_d[index_l]->waiting=time-temp_w->become;
							index_l++;
						}
						else
						{
							if(NumberQueue_e()==judgement || NumberQueue_e()==1)
							{
								break;
							}
							else
							{
								Enqueue_e(Dequeue_e());
								judgement++;
							}
						}
					}
					time++;
				}
				if(NumberQueue_w()!=0)
				{
					temp=NumberQueue_w();
					for(count=0;count<temp;count++)
					{
						log_r[index_lr]=(LOG*)malloc(sizeof(LOG));
						log_r[index_lr]->work=Dequeue_w()->name;
						index_lr++;
					}
					
				}
				printf("================================================================\nResult\n\n");
				printf("Job order:\n");
				for(count=0;count<index_l;count++)
				{
					printf("%s ", log_d[count]->work);
				}
				printf("\n\nEmployee order:\n");
				EmployeeOrder();
				for(count=0;count<index_e;count++)
				{
					if(employee[count]==0)
					{
						continue;
					}
					else
					{
						printf("%s ", employee[count]->name);
					}
				}
				printf("\n\nJob Schedule\n");
				for(count=0;count<index_l;count++)
				{
					printf("%s done by %s start at ", log_d[count]->work, log_d[count]->employee);
					PrintTime(log_d[count]->start);
					printf(" finish at ");
					PrintTime(log_d[count]->finish);
					printf(" waiting time %d ", log_d[count]->waiting);
					printf("\n");
				}
				for(count=0;count<index_lr;count++)
				{
					printf("%s is not done.\n", log_r[count]->work);
				}
				printf("\nEmployee Schedule\n");
				for(count=0;count<index_e;count++)
				{
					if(employee[count]==0)
					{
						continue;
					}
					else
					{
						printf("%s idle time %d minute do job\n", employee[count]->name, employee[count]->idletime);
						for(count2=0;count2<employee[count]->job;count2++)
						{
							PrintDoWork(employee[count]->done[count2]);
						}
						if(count2==0)
						{
							printf("none.\n");
						}
						printf("\n");
					}
				}
				printf("================================================================\n\n");
			}
			
			InitializeRun();
		}
		else
		{
			printf("Invalid input.\n");
		}
	}
	
return 0;
}
void PrintCommand()
{
	printf(
		"================================================================\n"
		"E : Enter the employees.\n"
		"W : Enter the works.\n"
		"S : Show the works or employees list.\n"
		"D : Delete the works or employees.\n"
		"R : Run calculate the schedule.\n"
		"C : Print the commands list.\n"
		"================================================================\n"
		);
}
void Enqueue_e(EMPLOYEE* item)
{
	queue_e.rear++;
	queue_e.item[queue_e.rear]=item;
}
EMPLOYEE* Dequeue_e()
{
	return queue_e.item[queue_e.front++];
}
void Enqueue_w(WORK* item)
{
	queue_w.rear++;
	queue_w.item[queue_w.rear]=item;
}
WORK* Dequeue_w()
{
	return queue_w.item[queue_w.front++];
}
int NumberQueue_e()
{
	int temp;
	temp=queue_e.rear-queue_e.front+1;
	return temp;
}
int NumberQueue_w()
{
	int temp;
	temp=queue_w.rear-queue_w.front+1;
	return temp;
}
int CheckWorkPossible()
{
	return queue_e.item[queue_e.front]->leave-time>=queue_w.item[queue_w.front]->duration;
}
int TimeConversion(int input)
{
	int hour, minute, temp;
	hour=input/100;
	minute=input-hour*100;
	temp=hour*60+minute;
	return temp;
}
void PrintTime(int input)
{
	int hour=input/60;
	int minute=input-hour*60;
	if(hour/10==0 && minute/10==0)
	{
		printf("0%d:0%d ", hour, minute);
	}
	else if(hour/10==0)
	{
		printf("0%d:%d ", hour, minute);
	}
	else if(minute/10==0)
	{
		printf("%d:0%d ", hour, minute);
	}
	else
	{
		printf("%d:%d ", hour, minute);
	}
}
void QueueIdletime()
{
	int count;
	int temp=NumberQueue_e();
	for(count=0;count<temp;count++)
	{
		queue_e.item[count]->idletime++;
	}
}
void PrintDoWork(char* done)
{
	int count;
	for(count=0;count<index_l;count++)
	{
		if(strcmp(log_d[count]->work, done)==0)
		{
			printf("%s started at ", log_d[count]->work);
			PrintTime(log_d[count]->start);
			printf(" finished at ");
			PrintTime(log_d[count]->finish);
			printf("\n");
		}
	}
}
void InitializeQueue_e()
{
	queue_e.front=0;
	queue_e.rear=-1;
}
void InitializeQueue_w()
{
	queue_w.front=0;
	queue_w.rear=-1;
}
void InitializeRun()
{
	int count;
	InitializeQueue_e();
	InitializeQueue_w();
	time=0;
	index_l=0;
	index_lr=0;
	for(count=0;count<index_e;count++)
	{
		if(employee[count]==0)
		{
			continue;
		}
		else
		{
			employee[count]->free=employee[count]->go;
			employee[count]->idletime=employee[count]->leave-employee[count]->go;
			employee[count]->job=0;
		}
	}
	for(count=0;count<index_w;count++)
	{
		if(work[count]==0)
		{
			continue;
		}
		else
		{
			work[count]->doneby=0;
		}
	
	}
}
int CheckTime(char* input)
{
	int sum, hour, minute;
	hour=(input[0]-48)*10+input[1]-48;
	minute=(input[3]-48)*10+input[4]-48;
	sum=hour*60+minute;
	if(input[2]!=':')
	{
		return 1;
	}
	else if(minute>=60 || hour>24 || sum>2400)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}
int StringTimeConversion(char* input)
{
	int sum, hour, minute;
	hour=(input[0]-48)*10+input[1]-48;
	minute=(input[3]-48)*10+input[4]-48;
	sum=hour*60+minute;
	return sum;
}
void EmployeeOrder()
{
	int count, count2, jump=0;
	EMPLOYEE* temp;
	for(count2=0;count2<index_e;count2++)
	{
		for(count=0;count<index_e-1;count++)
		{
			if(employee[count]==0)
			{
				continue;
			}
			while(employee[count+1+jump]==0 && count+1+jump!=index_e)
			{
				jump++;
			}
			if(employee[count]->go>employee[count+1+jump]->go)
			{
				temp=employee[count];
				employee[count]=employee[count+1+jump];
				employee[count+1+jump]=temp;
			}
			jump=0;
		}	
	}	
}

