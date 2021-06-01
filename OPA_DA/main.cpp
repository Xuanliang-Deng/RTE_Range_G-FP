#include "DA_LC.h"


int num_of_set = 0;

int main()
{
    int   accept_count = 0;
    float accept_ratio = 0.0;
    bool test_result;
    std::vector<Task> task_set;

    // Read num_core = 1000 task files by iteration
    for(int n = 0; n < num_task; n++)
    {
        //int n = 0;
        //std::string fileName = "data/task_set_" + std::to_string(n) + ".txt";
        std::string fileName = "../heuristics/data_U5_constant_DkC/task_set_" + std::to_string(n) + ".txt";
        //std::list<Task> task_set;
        task_set = readTaskFile(fileName);

        // Debugging 1: Print out original task parameters in files 
        /*
        std::cout << "--------------- Original Task Set --------------" << std::endl;
        for(auto it = task_set.begin(); it != task_set.end(); ++it)
        {
            std::cout << " Period: " << it->period ;
            std::cout << " WCET: " << it->WCET ;
            std::cout << " Priority: " << it->priority << std::endl;
        }
        std::cout  << std::endl;
        */
    

        // Debugging 2: DA-LC Schedulability Tests (Independent Version) 
        
        for(auto it = task_set.begin(); it != task_set.end(); it++)
        {
            test_result = DA_LC_is_schedulable(num_core, *it, task_set);
            if(test_result ==false)
            {
                break;
            }
        }
        

        // Debugging 3: OPA + DA (Integrated Version)  */
        //test_result = optimal_priority_assignment(task_set);

        if (test_result == true)
        {
            accept_count+=1;
            //printf("The task set is schedulable under OPA!\n");
        }
        else
        {
            //printf("The task set is unschedulable under OPA!\n");
        }
    }

    accept_ratio = double(accept_count)/num_core;

    printf("The number of tasks deemed schedulable is: %d \n", accept_count);
    printf("The number of tasks deemed schedulable is: %f \n", accept_ratio);
    
    return 0;
}