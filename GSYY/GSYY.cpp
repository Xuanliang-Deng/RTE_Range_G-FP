/*
 * Author:    Xuanliang Deng
 * Descr:     Header file for GSYY schedulability test
 * Date:      May 18 2021
 * Version:   1.0
 * History:   
 *            May 25,2021: Update GSYY
*/
#include "GSYY.h"

/* 
 * Func: Read task parameters from files
 * Args:
 *      fileName: path of the task txt file
 * Return:
 *      task_set: list consists of all tasks
 */
std::vector<Task> readTaskFile(std::string fileName)
{
    Task task;
    std::vector<Task> task_set;
    std::string line;
    std::ifstream taskFile (fileName);
    if (taskFile.is_open())
    {
        while( getline(taskFile, line) )
        {
            
            const char * str = line.c_str();
            sscanf(str, "%d %d %d %d %d %f", &task.period, &task.WCET, &task.priority, &task.deadline, &task.response, &task.value);

            task_set.push_back(task);
        }
        taskFile.close();
    }
    return task_set;
}

/* 
 * Func: Construct set of tasks with higher priorities than analyzed task_k
 * Args:
 *      task_set:  complete task set consists of all tasks
 *      task_k :   current analyzed task tau_k
 * Return:
 *      hp_task_set: set of all tasks with higher priorities than current analyzed task
 */
std::vector<Task> construct_hp_task_set(std::vector<Task> task_set, Task task_k)
{
    std::vector<Task> hp_task_set;

    /* Iterate over all tasks to find the ones with higher priorities */
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        if( it->priority > task_k.priority )
        {
            hp_task_set.push_back(*it);
        }
    }
    return hp_task_set;
}

/* 
 * Func: Calculate max workload Wk^NC(tau_i, x) (without carry-in)
 * Args:
 *      x: length of busy period (i.e., response time)
 *      task_i: task tau_i
 * Return:
 *      Wk_NC: max workload of tau_i in the busy period
 */
int calculateWorkload_Wk_NC( int x, Task task_i )
{
    int Wk_NC;

    /* Eq.(1) */
    Wk_NC = floor( double(x)/task_i.period ) * task_i.WCET + std::min( x%task_i.period, task_i.WCET);

    // Make sure workload is non-negative
    if(Wk_NC >= 0)
    {
        return Wk_NC;
    }
    else
    {
        return 0;
    }
}

/* 
 * Func: Calculate max workload Wk^CI (with carry-in)
 * Args:
 *      x: length of busy period
 *      task_i: struct of task tau_i
 *      alpha: workload of the carry-in job
 * Return:
 *      Wk_CI: max workload of tau_i in the busy period
 */
int calculateWorkload_Wk_CI( int x, Task task_i )
{
    int alpha, Wk_CI;

    alpha =  std::min( std::max( (std::max( x - task_i.WCET , 0 ))%task_i.period - (task_i.period - task_i.response), 0), task_i.WCET-1);

    /* Eq.(2) FIXED THE ISSUE, TYPO IN MY EQUATION 2*/
    Wk_CI = floor( double(std::max( x - task_i.WCET, 0 ))/ task_i.period )*task_i.WCET + task_i.WCET + alpha;

    // Make sure the workload is non-negative
    if(Wk_CI >= 0)
    {
        return Wk_CI;
    }
    else
    {
        return 0;
    }
}

/* 
 * Func: Calculate max interference of task tau_i (without carry-in)
 * Args:
 *      x: length of busy period
 *      task_k: analyzed task
 *      task_i: task with higher priority tahn analyzed task
 * Return:
 *      Ik_NC: max interference of tau_i in the busy period (resp. time of tau_k)
 */
int calculateInterfer_Ik_NC( int x, Task task_k, Task task_i )
{
    int Wk_NC, Ik_NC;

    Wk_NC = calculateWorkload_Wk_NC( x, task_i );

    /* Eq.(3) */
    Ik_NC = std::min( Wk_NC, x - task_k.WCET + 1);
    /* ****************** Debugging: Print out Wk_NC, Ik_NC ************************** */
    
    printf("Wk_NC =  %d  ", Wk_NC);
    printf("Ik_NC =  %d\n", Ik_NC);
    
    /* *************************** End of debugging ************************************** */
    return Ik_NC;
}

/* 
 * Func: Calculate max interference of task tau_i (with carry-in)
 * Args:
 *      x: length of busy period
 *      task_k: analyzed task
 *      task_i: task with higher priority tahn analyzed task
 * Return:
 *      Ik_CI: max interference of tau_i in the busy period (resp. time of tau_k)
 */
int calculateInterfer_Ik_CI( int x, Task task_k, Task task_i )
{
    int Wk_CI, Ik_CI;

    Wk_CI = calculateWorkload_Wk_CI( x, task_i );
    /* Eq.(4) */
    Ik_CI = std::min( Wk_CI, x - task_k.WCET + 1);
    /* ****************** Debugging: Print out Wk_NC, Ik_NC ************************** */
    /*
    printf("Wk_CI =  %d  ", Wk_CI);
    printf("Ik_CI =  %d\n", Ik_CI);
    */
    /* *************************** End of debugging ************************************** */
    return Ik_CI;
}

/* 
 * Func: Calculate interference difference of task tau_i 
 * Args:
 *      x: length of busy period
 *      task_k: analyzed task
 *      task_i: task with higher priority tahn analyzed task
 * Return:
 *      Ik_DIFF: interference difference of Ik_CI and Ik_NC
 */
int calculateInterfer_Ik_DIFF( int x, Task task_k, Task task_i )
{
    int Ik_CI, Ik_NC, Ik_DIFF;

    Ik_NC = calculateInterfer_Ik_NC( x, task_k, task_i) ;
    Ik_CI = calculateInterfer_Ik_CI( x, task_k, task_i );

    Ik_DIFF = Ik_CI - Ik_NC;
    /* ****************** Debugging: Print out Wk_NC, Ik_NC ************************** */
    /*
    printf("Ik_CI =  %d ", Ik_CI);
    printf("Ik_NC =  %d  \n", Ik_NC);
    printf("Ik_DIFF =  %d  \n", Ik_DIFF);
    */
    /* *************************** End of debugging ************************************** */
    return Ik_DIFF;
}

/* Updated here -----------------------------------------------------------------------------------
 * Func: Calculate total interference omega on the analyzed task tau_k
 * Args:
 *      x: length of busy period
 *      hp_task_set:  task set consists of all tasks with higher priorities
 *      task_k : current analyzed task tau_k
 * Return:
 *      omega_k_x: the total interference on analyzed task tau_k
 */
int calculateInterfer_omega_k_x(int x, int m, std::vector<Task> task_set, Task task_k)
{   

    int sum_Ik_NC = 0;
    int sum_Ik_DIFF = 0;
    int omega_k_x = 0;

    // Store Ik_DIFF value and prepare for sorting
    std::list<int> Ik_DIFF_list;

    // Construct hp task sets
    std::vector<Task> hp_task_set;
    hp_task_set = construct_hp_task_set(task_set, task_k);

    for(auto it = hp_task_set.begin(); it != hp_task_set.end(); ++it)
    {

        int Ik_NC, Ik_DIFF;
        Ik_NC = calculateInterfer_Ik_NC(x, task_k, *it);
        Ik_DIFF = calculateInterfer_Ik_DIFF(x, task_k, *it);
        Ik_DIFF_list.push_back(Ik_DIFF);
        sum_Ik_NC += Ik_NC;
    }

    /* Sort Ik_DIFF_list to find the (m-1) largest elements (descending order) */
    Ik_DIFF_list.sort(std::greater<int>());

    // Debugging
    for(auto it = Ik_DIFF_list.begin(); it != Ik_DIFF_list.end(); ++it)
    {/*
        printf("The Ik_DIFF list is: ");
        printf("%d ,", *it);
        */
    }
    std::cout << std::endl;

    if (Ik_DIFF_list.size() <= m)
    {
        /* If the list size is smaller than num of cores, sum up all Ik_DIFF */
        for(auto it = Ik_DIFF_list.begin(); it != Ik_DIFF_list.end(); ++it)
        {
            sum_Ik_DIFF += *it;
        }
    }
    else 
    {
        /* If the list size is greater than num of cores, only sum up (m-1) largest elements  */
        auto start = Ik_DIFF_list.begin();
        for(int i = 0; i < m-1; i++)
        {
            sum_Ik_DIFF += *start;
            start++;
        }
    };

    /* Eq.(5) */
    omega_k_x = sum_Ik_NC + sum_Ik_DIFF;
    return omega_k_x;
}


/* 
 * Func: Calculate response time of the analyzed task tau_k
 * Args:
 *      hp_task_set:  task set consists of all tasks with higher priorities
 *      task_k : current analyzed task tau_k
 * Return:
 *      x: return updated response time as x
 */
int calculate_response_time(int m, std::vector<Task> task_set, Task * task_k)
{
    int omega_k_x = 0;

    /* Set init resp time as WCET, iterate until resp time doesn't change or exceeds deadline */
    int prev_resp_time = task_k->WCET;
    int curr_resp_time = prev_resp_time;
    
    do
    {
        prev_resp_time = curr_resp_time;

        /* Eq.(6) */
        curr_resp_time = floor( double(calculateInterfer_omega_k_x(task_k->response, m, task_set, *task_k))/m ) + task_k->WCET;

        //printf("Curr_response time is: %d\n\n", curr_resp_time);

        if(curr_resp_time <= task_k->deadline)
        {
            task_k->response = curr_resp_time;
        }
        else
        {
            task_k->response = curr_resp_time;
            //printf("The response time exceeds deadline!");
            return curr_resp_time;
        }
        // --------------------------- Add here ---------------------------


    } while ( curr_resp_time != prev_resp_time );

    return curr_resp_time;
}

/* 
 * Func: Perform the GSYY schedulability test
 * Args:
 *      task_set: complete task set of all tasks
 * Return:
 *      No outputs. Print the schedulability test result in terminal, schedulable/unschedulable.
 */
bool GSYY_sched_test(int m, std::vector<Task> task_set)
{
    int sched_test_res;
    int resp_time;
    /* Iterate over all the tasks in the set, check for each task whether it is schedulable under ZLL */
    for( auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        
        resp_time = calculate_response_time( m, task_set, &(*it));
        if(resp_time <= it->deadline)
        {
            sched_test_res = true;
        }
        else
        {
            sched_test_res = false;
        }

        if (sched_test_res == false)
        {
            printf("This task is unschedulable under GSYY schedulability test!\n");
            break;
        }
    }
    if(sched_test_res == true)
    {
        printf("This task is schedulable under GSYY!\n");
    }

    return sched_test_res;
}

std::vector<Task> GSYY_unit_test(int m, std::vector<Task> task_set)
{
    std::vector<Task> updated_task_set;
    int resp_time;
    /* Iterate over all the tasks in the set, check for each task whether it is schedulable under ZLL */
    for( auto it = task_set.begin(); it != task_set.end(); ++it)
    {   
        resp_time = calculate_response_time( m, task_set, &(*it));
        it->response = resp_time;

        updated_task_set.push_back(*it);

    }
    return updated_task_set;
}