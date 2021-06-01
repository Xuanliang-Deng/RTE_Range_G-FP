/*
 * Author:    Xuanliang Deng
 * Descr:     Main function for heuristic priority assignment policies, write files to corresponding folder
 * Date:      May 25 2021
 * Version:   1.0
 * History:   
 *            None
 */
#include "heuristics.h"
#include <gtest/gtest.h>

int num_of_set = 0;

int main()
{
    /* Number of characters in fileName */
    int n_char;
    int M = 10;
    int N = 1000;

    for(int num_of_set =0; num_of_set<= N; num_of_set++)
    {   
        std::vector<Task> task_set;
        char fileName[30];
        
        printf("num of set is: %d", num_of_set);
        n_char = sprintf(fileName, "data_U4_constant/task_set_%d.txt", num_of_set);

        if(n_char >= 0)
        {
            task_set = readTaskFile(fileName);
            n_char = sprintf(fileName, "data_U4_constant_DkC/task_set_%d.txt", num_of_set);
        
            std::vector<Task> updated_task_set;
            
            
            updated_task_set = calculate_prio_DkC(M, task_set);
            saveTask2File(updated_task_set, fileName);
            
            /*
            updated_task_set = calculate_prio_DMPO(task_set);
            saveTask2File(updated_task_set, fileName);
            */
            
            /*
            updated_task_set = calculate_prio_DCMPO(task_set);
            saveTask2File(updated_task_set, fileName);
            */
            
            
        }
    }
        
    return 0;
}

