#include "GSYY.h"

int main()
{
    int m = 10;
    int accept_count = 0;
    float accept_ratio = 0.0;

    std::vector<Task> task_set;
    char fileName[60];

    for(int n=0; n<num_task; n++)
    
    {   
        //int n = 4;
        /* Number of characters in fileName */
        int n_char;
        n_char = sprintf(fileName, "../heuristics/data_U10_constant_DkC/task_set_%d.txt", n);
        //n_char = sprintf(fileName, "/data/task_set_%d.txt", n);

        if(n_char >= 0)
        {
            task_set = readTaskFile(fileName);
            /* Debugging 2: GSYY test  */
            if( GSYY_sched_test(m,task_set) ==  true )
            {
                accept_count += 1;
            }
        }
    }
    accept_ratio = double(accept_count)/num_task;
    printf("Acceptance ratio is: %f\n", accept_ratio);
    printf("The number of tasks deemed schedulable is: %d\n", accept_count);

        
    return 0;
}