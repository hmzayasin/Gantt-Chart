#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"

int main(void)
{
	char original_gantt[4];
	printf("Welcome to the Gantt Generator\n");
	fflush(stdout);
	printf("Would you like to use the test example or create your own Gantt from scratch? (Enter \"Yes\" or \"No\"):\n");
	fflush(stdout);
	scanf("%s", original_gantt);

	//prints the sample gannt chart provided
	if(strcmp(original_gantt, "Yes") == 0)
	{
		//initalises an array of struct
		Task sample_tasks[10];
		//initalises the sample task names
		strcpy(sample_tasks[0].taskname, "Planning");
		strcpy(sample_tasks[1].taskname, "Researching");
		strcpy(sample_tasks[2].taskname, "Writing_Code");
		strcpy(sample_tasks[3].taskname, "Pseudo_Code");
		strcpy(sample_tasks[4].taskname, "Code_Review");
		strcpy(sample_tasks[5].taskname, "Testing");
		strcpy(sample_tasks[6].taskname, "Feed_Back");
		strcpy(sample_tasks[7].taskname, "Bug_Fixing");
		strcpy(sample_tasks[8].taskname, "Optomization");
		strcpy(sample_tasks[9].taskname, "Presentation");

		//initialises start month for each sample task
		sample_tasks[0].start_month = 1;
		sample_tasks[1].start_month = 2;
		sample_tasks[2].start_month = 4;
		sample_tasks[3].start_month = 3;
		sample_tasks[4].start_month = 4;
		sample_tasks[5].start_month = 5;
		sample_tasks[6].start_month = 7;
		sample_tasks[7].start_month = 8;
		sample_tasks[8].start_month = 9;
		sample_tasks[9].start_month = 11;

		//intialises end month for each sample task
		sample_tasks[0].end_month = 2;
		sample_tasks[1].end_month = 2;
		sample_tasks[2].end_month = 6;
		sample_tasks[3].end_month = 4;
		sample_tasks[4].end_month = 5;
		sample_tasks[5].end_month = 6;
		sample_tasks[6].end_month = 8;
		sample_tasks[7].end_month = 9;
		sample_tasks[8].end_month = 10;
		sample_tasks[9].end_month = 12;

		//intialises dependencies for each sample task
		sample_tasks[1].dependencies[0] = 1;
		sample_tasks[2].dependencies[0] = 1;
		sample_tasks[3].dependencies[0] = 2;
		sample_tasks[5].dependencies[0] = 2;
		sample_tasks[5].dependencies[1] = 5;
		sample_tasks[6].dependencies[0] = 6;
		sample_tasks[7].dependencies[0] = 7;
		sample_tasks[8].dependencies[0] = 5;
		sample_tasks[9].dependencies[0] = 8;
		sample_tasks[9].dependencies[1] = 9;

        //records how many dependecies of each sample task
        sample_tasks[0].num_dependent_tasks = 0;
        sample_tasks[1].num_dependent_tasks = 1;
        sample_tasks[2].num_dependent_tasks = 1;
        sample_tasks[3].num_dependent_tasks = 1;
        sample_tasks[4].num_dependent_tasks = 0;
        sample_tasks[5].num_dependent_tasks = 2;
        sample_tasks[6].num_dependent_tasks = 1;
        sample_tasks[7].num_dependent_tasks = 1;
        sample_tasks[8].num_dependent_tasks = 1;
        sample_tasks[9].num_dependent_tasks = 2;

        // initalises the number of tasks in gantt chart
        int num_of_tasks = 10;

		print_topline();
		printf("                  ");
		fflush(stdout);
		for(enum month i = january; i <= december; i++)
		    {
				//function that prints the months on top of gannt chart
		        print_months(i);
		    }
		printf("|Dependencies\n");
		fflush(stdout);
		print_line();


		//prints the rest of gannt chart
		for(int i = 0; i < 10; i++)
		{
			printTask(sample_tasks, i);
			print_line();
		}



		//asks user to edit tasks, test tasks or quit.
		char user_input[5];
		printf("If you wish to edit the Gantt type 'edit'/ If you wish to run a test, type 'test' or to exit, type 'quit' and then press enter.\n");
		fflush(stdout);
		scanf("%s", user_input);

		while (! strcmp(user_input, "quit") == 0)
		{
			if(strcmp(user_input, "edit") == 0)
			{
				user_edit(sample_tasks, 10);

		 	 	 //reprints the edited gannt chart
		 	 	 print_topline();
		 	 	 printf("                  ");
		 	 	 fflush(stdout);
		 	 	 for(enum month i = january; i <= december; i++)
		 	 	 {
			 	 	 print_months(i);
		 	 	 }
		 	 	 printf("|Dependencies\n");
		 	 	 fflush(stdout);
		 	 	 print_line();

		 	 	 for (int j = 0; j < 10; j++)
		 	 	 {
			 	 	 printTask(sample_tasks, j);
			 	 	 print_line();
		 	 	 }
			}


			if(strcmp(user_input, "test") == 0)
			{


				int visitedTask[10];
				char name_array[19];

				printf("Please Enter the Task Name to test \n");
				fflush(stdout);
				scanf("%s", name_array);
				printf("check circular\n");
				fflush(stdout);

				resetVisitedTasks(visitedTask);
				for (int i = 0; i < num_of_tasks;i++)
				{
					if (strcmp(name_array, sample_tasks[i].taskname)== 0)
					{
						printDependentTasks(sample_tasks, i, visitedTask);
						break;
					}
				}

			}
			printf("\nIf you wish to edit the Gantt type 'edit' / If you wish to run a test, type 'test' or to exit, type 'quit' and then press enter.\n");
			fflush(stdout);
			scanf("%s", user_input);
		}


	}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
	//code for user input gannt chart
	else if(strcmp(original_gantt, "No") == 0)
	{
		int num_of_tasks = 0;
		Task original_tasks[10];

		//asks user how many tasks they would like
		printf("How many tasks would you like to add ? (1-10)\n");
		fflush(stdout);
		scanf("%d", &num_of_tasks);

		//loop to get all the info for the gannt chart
		for(int i = 0; i < num_of_tasks; i++)
		{	//user input task name
			printf("Please enter the task name:\n");
			fflush(stdout);
			scanf(" %s", original_tasks[i].taskname);

			//user input start month
			printf("Start month (1-12):\n");
			fflush(stdout);
			scanf("%d", &original_tasks[i].start_month);
			//user input end month
			printf("End month (1-12):\n");
			fflush(stdout);
			scanf("%d", &original_tasks[i].end_month);
			//user input number of dependencies
			printf("Enter how many dependencies this task has: \n");
			fflush(stdout);
			scanf("%d", &original_tasks[i].num_dependent_tasks);

			//gets input for dependencies
			if (original_tasks[i].num_dependent_tasks > 0)
			{
				for (int h = 0; h < original_tasks[i].num_dependent_tasks; h++)
				{
					printf("Enter dependent task: \n");
					fflush(stdout);
					scanf("%d", &original_tasks[i].dependencies[h]);

				}
			}

		}

        //block of code that prints the gannt chart
		print_topline();
		printf("                  ");
		fflush(stdout);
		for(enum month i = january; i <= december; i++)
		{
			//prints the months on top of the gannt chart
			print_months(i);
		}
		printf("|Dependencies\n");
		fflush(stdout);
		print_line();

		//prints the rest of the gannt chart
		for(int i = 0; i < num_of_tasks; i++)
		{
			printTask(original_tasks, i);
			print_line();
		}

		//asks user to edit tasks, test tasks or quit.
		char user_input[5];
		printf("If you wish to edit the Gantt type 'edit' / If you wish to run a test, type 'test' or to exit, type 'quit' and then press enter\n");
		fflush(stdout);
		scanf("%s", user_input);

		while (! strcmp(user_input, "quit") == 0) // sets a while loop that keeps going until quit is typed
		{

			if(strcmp(user_input, "edit") == 0)
			{
				user_edit(original_tasks, num_of_tasks);

		 	 	 //reprints the edited gannt chart
		 	 	 print_topline();
		 	 	 printf("                  ");
		 	 	 fflush(stdout);
		 	 	 for(enum month i = january; i <= december; i++)
		 	 	 {
			 	 	 print_months(i);
		 	 	 }
		 	 	 printf("|Dependencies\n");
		 	 	 fflush(stdout);
		 	 	 print_line();

		 	 	 for (int j = 0; j < num_of_tasks; j++)
		 	 	 {
			 	 	 printTask(original_tasks, j);
			 	 	 print_line();
		 	 	 }
			}

			if(strcmp(user_input, "test") == 0)
			{


				int visitedTask[10];
				char name_array[19];

				printf("Please Enter the Task Name to test \n");
				fflush(stdout);
				scanf("%s", name_array);
				printf("check circular\n");
				fflush(stdout);

				resetVisitedTasks(visitedTask);
				for (int i = 0; i < num_of_tasks;i++)
				{
					if (strcmp(name_array, original_tasks[i].taskname)== 0)
					{
						printDependentTasks(original_tasks, i, visitedTask);
						break;
					}
				}

			}

			printf("\nIf you wish to edit the Gantt type 'edit' / If you wish to run a test, type 'test' or to exit, type 'quit' and then press enter\n");
			fflush(stdout);
			scanf("%s", user_input);
			// calls the statement once again at the end of the loop to see if user wants to continue testing or editing.
		}


	}
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
	else
	{
		printf("Invalid input!!! (Please type \"Yes\" or \"No\" exactly)");
	}
	PrintASCII(); //Prints the ASCII art at the end of the code
	return 0;

}










