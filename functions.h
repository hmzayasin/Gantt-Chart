//defining new struct type "Task"
typedef struct {
	char taskname[19];
	int start_month;
	int end_month;
	int dependencies[10];
	int num_dependent_tasks;
}Task;

enum month {january,february,march,april,may,june,july,august,september,october,november,december};
/*
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
 ***********************************************************************************************************************************************
*/
void print_topline(void);

void print_line(void);

void print_months(enum month i);

void printTask(Task tasks[], int index);

void user_edit(Task tasks[], int num_of_tasks);

void printDependentTasks(Task taskList[], int taskId, int visitedTasks[]);

void resetVisitedTasks(int visitedTask[]);

int checkIfCircular(Task taskList[], int dependentTaskId, int visitedTasks[]);

void PrintASCII();





