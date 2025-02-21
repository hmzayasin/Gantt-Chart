#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"


//function that prints underscores
void print_topline(void)
{
	for(int i = 0; i < 152; i++)
	{
		printf("_");
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
//function that prints lines
void print_line(void)
{
	for(int i = 0; i < 152; i++)
	{
		printf("-");
		fflush(stdout);
	}
	printf("\n");
	fflush(stdout);
}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/

//function that prints the months on top of the gannt chart
void print_months(enum month i)
{
    switch (i)
    {
    case january:
        printf("|January  ");
        fflush(stdout);
        break;
    case february:
        printf("|February ");
        fflush(stdout);
        break;
    case march:
        printf("|March    ");
        fflush(stdout);
        break;
    case april:
        printf("|April    ");
        fflush(stdout);
        break;
    case may:
        printf("|May      ");
        fflush(stdout);
        break;
    case june:
        printf("|June     ");
        fflush(stdout);
        break;
    case july:
        printf("|July     ");
        fflush(stdout);
        break;
    case august:
        printf("|August   ");
        fflush(stdout);
        break;
    case september:
        printf("|September");
        fflush(stdout);
        break;
    case october:
        printf("|October  ");
        fflush(stdout);
        break;
    case november:
        printf("|November ");
        fflush(stdout);
        break;
    case december:
        printf("|December ");
        fflush(stdout);
        break;
    }
}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/

//function that prints the rest of the gannt chart
void printTask(Task tasks[], int index)
{
    printf("%s", tasks[index].taskname);
    fflush(stdout);
    int length = 18 - strlen(tasks[index].taskname);

    for(int j = 0; j < length; j++)
    {
        printf(" ");
        fflush(stdout);
    }
    printf("|");
    fflush(stdout);

    for (int months = 1; months < 13; months++)
    {
        if (months >= tasks[index].start_month && months <= tasks[index].end_month)
        {
            printf("XXX      |");
            fflush(stdout);
        } else {
            printf("         |");
            fflush(stdout);
        }
    }

    if (tasks[index].num_dependent_tasks == 0)
    {
        printf(" ");
        fflush(stdout);
    }
    else
    {
        for (int j = 0; j < tasks[index].num_dependent_tasks; j++)
        {
            printf("%d ", tasks[index].dependencies[j]);
            fflush(stdout);
        }
    }
    printf("\n");
    fflush(stdout);
}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
//function that allows user to edit the gannt chart
void user_edit(Task tasks[], int num_of_tasks)
{
		int num_edits;
		printf("How many tasks do you want to edit?\n");
		fflush(stdout);
		scanf("%d", &num_edits);

		for(int a = 0; a < num_edits; a++)
		{
			char task_edit[19];
			printf("Please enter the task name you want to change exactly:\n");
			fflush(stdout);
			scanf("%s", task_edit);

			//checks which task to edit
			for (int i = 0; i < num_of_tasks; i++)
			{
				if (strcmp(task_edit, tasks[i].taskname) == 0)
				{
					printf("Please enter the new task name:\n");
					fflush(stdout);
					scanf("%s", tasks[i].taskname);

					printf("Please enter the new start month:\n");
					fflush(stdout);
					scanf("%d", &tasks[i].start_month);

					printf("Please enter the new end month:\n");
					fflush(stdout);
					scanf("%d", &tasks[i].end_month);

					printf("Please enter how many dependencies this task has:\n");
					fflush(stdout);
					scanf("%d", &tasks[i].num_dependent_tasks);

					if (tasks[i].num_dependent_tasks > 0)
					{
						for (int h = 0; h < tasks[i].num_dependent_tasks; h++)
						{
							printf("Enter dependent task: \n");
							fflush(stdout);
							scanf("%d", &tasks[i].dependencies[h]);

						}
					}
				}
			}
		}

}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
//function that checks dependencies of tasks
void printDependentTasks(Task taskList[], int taskId, int visitedTasks[])
{
	int Circular_check = 0;

	printf("%d -> ", taskId + 1);
	fflush(stdout);
	//mark the current task as visited
	visitedTasks[taskId] = 1;

	//loop through the dependency for current task
	for (int i = 0; i < taskList[taskId].num_dependent_tasks; i++)
	{
		int dependentTaskId = taskList[taskId].dependencies[i];

		//if it hasn't been visited do the recursive call
		if (visitedTasks[dependentTaskId - 1] == 0)
		{
			printDependentTasks(taskList, dependentTaskId - 1, visitedTasks);

		}

		else
		{

			printf("(!!!!! warning potential circular dependency !!!!!) \n");
			fflush(stdout);
			//calls the function for circular dependencies and assigns the value to circular check
			Circular_check = checkIfCircular(taskList, dependentTaskId - 1, visitedTasks);

			// if statement for Circular_check which tells us if circular dependency found or not
			if (Circular_check == 1)
			{
				printf("!!! CIRCULAR DEPENDENCIES FOUND !!!\n");
				fflush(stdout);
				break;
			}
			// if value of Circular_check is anything other than 0 then circular dependency is not found
			else
			{
				printf("no circular dependencies found \n");
				fflush(stdout);
				break;
			}
		}
	}

}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
//function that checks circular dependency
int checkIfCircular(Task taskList[], int dependentTaskId, int visitedTasks[])
{
	int Circular_check = 0;
	//if no dependencies then return 0 since no circular dependencies found
	if (taskList[dependentTaskId].num_dependent_tasks == 0)
	{
		return 0;
	}
	 // if more than 0 dependencies
	else
	{

		// loop to go through all of dependentTaskId's dependencies
		for (int i = 0; i < taskList[dependentTaskId].num_dependent_tasks; i++)
		{
			//if dependency has not been visited
			if (visitedTasks[dependentTaskId] == 0)
			{
				// call recursion with the first dependency of dependentTaskId
				Circular_check = checkIfCircular(taskList, taskList[dependentTaskId].dependencies[i], visitedTasks);
			}

			// if it has been visited then circular dependency is found so therefore we assign 1 to Circular_check and break the loop
			else
			{
				Circular_check = 1;
				break;
			}
		}
		// return the value of Circular_check wether that be 1 or 0
		return Circular_check;
	}
}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
//function to reset the visited tasks
void resetVisitedTasks(int visitedTask[])
{
	for (int i = 0; i < 10; i++)
	{
		visitedTask[i]= 0;
	}
}

/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
//function to print ASCII Art
void PrintASCII()
{
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣶⣶⣦⣄⡀⢀⣀⣤⣤⣄\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣆⠀⠀⠀⠀⠀⠀⢀⣄⠙⢿⣿⣟⣿⣿⣿⣿⣿⠇\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⢸⣿⣿⣿⡀⠀⠀⠀⠀⢀⣿⣿⡇⠀⠈⢹⡏⠉⠉⠁⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠸⣿⣿⣿⡇⠀⠀⠀⠀⢸⣿⣿⡇⠀⠀⢸⡇⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⠀⢿⣿⣿⣷⣶⣶⣶⣷⣾⣿⣿⡀⠀⠀⢸⠃⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⠀⠀⠀⣠⣾⡿⠋⢉⠙⣿⣿⣿⣿⣿⠟⠛⢦⡀⣼⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠈⠐⢒⣾⣿⣿⣷⡀⠛⢀⣿⣿⣿⣭⣿⣈⠛⣸⣧⣿⠤⠤⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠠⠤⠒⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠤⠤⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⠀⣼⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⢰⣿⣿⣿⣿⣿⣿⣿⣿⡿⠛⠉⠀⠀⠈⠙⠻⣆⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⠀⣾⣿⣿⣿⣿⣿⣿⡿⠋⢀⣠⣄⠀⠀⠶⠿⠦⠀⠰⠶⠹⣧⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⡇⠀⠚⠉⠉⠀⠀⠀⠀⠀⣀⡀⠀⢀⣇⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣷⠀⠀⠀⠠⠾⠛⠂⠀⠘⠉⠉⠀⠉⢹⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀\n");
    printf("⠀⠀⠀⢸⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡎⠀⠀⠀⠀\n");
    printf("⠀⠀⣠⣾⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠃⠀⠀⠀⠀⠀\n");
    printf("⢠⣾⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣶⣄⣀⠀⠀⠀⢀⣠⣴⣿⠏⠀⠀⠀⠀⠀⠀\n");
    printf("⠸⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠏⠀⠀⠀⠀⠀⠀⠀\n");
    printf("⠀⠀⠉⠉⠉⠉⠉⠉⠙⠛⠿⠿⠿⠿⠟⠛⠿⠿⠿⠿⠿⠇⠀⠀⠀⠀⠀⠀⠀⠀\n");


}
