/*
 * Author:    Xuanliang Deng
 * Descr:     DCMPO priority assignment policy implementation
 * Date:      May 24 2021
 * Version:   1.0
 * History:   
 *            None
 */
#include "heuristics.h"

/* Read task parameters from files*/
std::vector<Task> readTaskFile(std::string fileName);

/* 
 * Func: Assign priorities according to DMPO
 * Args:
 *      m: number of processors
 *      task_set: vector consists of all tasks
 * Return:
 *      task_set: updated vector consists of all tasks
 */
std::vector<Task> calculate_prio_DCMPO(std::vector<Task> task_set)
{
    /* Debugging */
    /*
    printf("The original task set is: \n");
    std::cout << "--------------- Original task set --------------" << std::endl;
    for(auto it= task_set.begin(); it != task_set.end(); ++it)
    {
        std::cout << " Period: "   << it->period ;
        std::cout << " deadline: " << it->deadline ;
        std::cout << " WCET: "     << it->WCET ;
        std::cout << " response: " << it->response ;
        std::cout << " Priority: " << it->priority ;
        std::cout << " Value: " << it->value << std::endl ;
    }
    std::cout << std::endl;
    */

    /* Calculate value = deadline */
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        it->value = it->deadline - it->WCET;
    }

    /* sort tasks wrt their calculated values (aescending) */
    struct compareTaskValue_aes
    {
        bool operator()(Task const & a, Task const & b)
        {
            if(a.value == b.value)
            {
                if(a.period == b.period)
                {
                    return a.WCET < b.WCET;
                }
                return a.period < b.period;
            }
            else
            {
                return a.value < b.value;
            }
        }
    } value_aes;
    std::sort( task_set.begin(), task_set.end(), value_aes );

    /* set maximum priority as the num of tasks */
    int max_prio;
    max_prio = task_set.size();

    /* the smaller the value, the higher the priority */
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        it->priority = max_prio;
        --max_prio;
    }

    /* Debugging */
    /*
    printf("The updated task set is: \n");
    std::cout << "--------------- Updated task set --------------" << std::endl;
    for(auto it= task_set.begin(); it != task_set.end(); ++it)
    {
        std::cout << " Period: "   << it->period ;
        std::cout << " deadline: " << it->deadline ;
        std::cout << " WCET: "     << it->WCET ;
        std::cout << " response: " << it->response ;
        std::cout << " Priority: " << it->priority ;
        std::cout << " Value: " << it->value << std::endl ;
    }
    std::cout << std::endl;
    */

    return task_set;
}







