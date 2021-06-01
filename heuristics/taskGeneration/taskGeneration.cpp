/*
 * Author:    Xuanliang Deng
 * Descr:     CPP file for generating tasks
 * Date:      May 25 2021
 * Version:   2.0
 * History:   
 *            None
 */
#include "taskGeneration.h"

/*
 * Func: save generated task parameters to file
 * Param: 
 *      task_set: generated task set
 * Return:
 *      No return value. All task sets will be written under data folder
 */
void saveTask2File(std::vector<Task> task_set)
{
    char fileName[50];
    int n;

    n = sprintf(fileName, "../data/task_set_%d.txt", num_of_set);

    std::ofstream outfile;
    outfile.open(fileName, std::ios::out);

    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        outfile << it->period << " " << it->WCET << " " << it->priority << " " << it->deadline << " " << it->response << " " << it->value <<std::endl;
    }
    outfile.close();
}


/*
 * Func: generate task set with parameters
 * Param: 
 *      None
 * Return:
 *      None. Generated task will be written to files insdie function
 */
void generateTask()
{
    int period, WCET, deadline, response;

    std::vector<Task> task_set;

    double utilization = 0, total_utilization = 0;

    /* Period is uniformly distributed in [10,30], NanGuan_RTSS09 */
    
    const int range_from = 10;
    const int range_to   = 30;

    /* Initialize M+1 task sets */
    do
    {
        Task cur_task;

        period = rand()%( range_to - range_from + 1 ) + range_from;
        cur_task.period = period;

        /* Generate task set with small utilization */
        WCET = 1 + rand()%( period/2 + 1);
        cur_task.WCET = WCET;

        /* For implicit tasks, Di = Ti, set Ri = Ci */
        deadline = period;
        response = WCET;

        cur_task.deadline = deadline;
        cur_task.response = response;

        utilization = double(cur_task.WCET) / cur_task.period;
        total_utilization += utilization;
        printf("total utilization is: %f\n", total_utilization);

        task_set.push_back(cur_task);
    }while(total_utilization < 0.5*M);


    saveTask2File(task_set);
    ++num_of_set ;

    
    while(total_utilization < M && num_of_set<=N)
    {
        Task cur_task;

        period = rand()%( range_to - range_from + 1 ) + range_from;
        cur_task.period = period;


        WCET = 1 + rand()%( period/2 + 1);
        cur_task.WCET = WCET;


        deadline = period;
        response = WCET;

        cur_task.deadline = deadline;
        cur_task.response = response;

        utilization = double(cur_task.WCET) / cur_task.period;
        total_utilization += utilization;

        task_set.push_back(cur_task);
        saveTask2File(task_set);
        ++num_of_set;
        
    };
   
    


    printf("The total utilization ABOVE M is: %f", total_utilization);
    std::cout << " " << std::endl;
    total_utilization = 0;

    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        utilization = double(it->WCET) / it->period;
        total_utilization += utilization;
    }
    printf("The total utilization BELOW M is: %f", total_utilization);
    std::cout << " " << std::endl;

    printf("Print out the task periods\n");
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        std::cout << it->period << " ";
    }
    std::cout << " " << std::endl;

    printf("Print out the task WCETs\n");
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        std::cout << it->WCET << " ";
    }
    std::cout << " " << std::endl;

    printf("Print out the task priorities\n");
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        std::cout << it->priority << " ";
    }
    std::cout << " " << std::endl;
    
}

