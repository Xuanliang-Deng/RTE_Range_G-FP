/*
 * Author:    Xuanliang Deng
 * Descr:     Main function for generating task
 * Date:      May 23 2021
 * Version:   1.0
 * History:   
 *            None
 */
#include "taskGeneration.h"

int num_of_set = 0;

int main()
{
    srand((unsigned) time(0));

    std::vector<Task> task_set;
    
    /* Generate N task sets */
    while(num_of_set < N)
    {
        
        //std::cout << rand() << std::endl;
        generateTask();
    }; 

    return 0;
}