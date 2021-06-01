/*
 * Author:    Xuanliang Deng
 * Descr:     CPP file for DA-LC schedulability test & OPA
 * Date:      May 31 2021
 * Version:   2.0
 * History:   
 *            May 31,2021: Change from list to vector, update all functions
 */
#include "DA_LC.h"

// Read task set from files 
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

// Construct higher-priority task set
std::vector<Task> construct_hp_task_set(std::vector<Task> task_set, Task task_k)
{
    std::vector<Task> hp_task_set;

    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        if( it->priority > task_k.priority )
        {
            hp_task_set.push_back(*it);
        }
    }
    return hp_task_set;
}

int calculateWorkload_Wi_D( int L, Task task_i )
{
    int Ni_D, Wi_D;

    // Eq.(2) Implicit deadline Di = Ti 
    Ni_D = floor( double( L + task_i.period - task_i.WCET ) / task_i.period );
    // Eq.(1) 
    Wi_D = Ni_D * task_i.WCET + std::min( task_i.WCET, L + task_i.period - task_i.WCET - Ni_D * task_i.period );

    return Wi_D;
}

int calculateWorkload_Wi_NC( int L, Task task_i )
{
    int Ni_NC, Wi_NC;

    // Eq.(11) 
    Ni_NC = floor( double(L) / task_i.period );
    // Eq.(10) 
    Wi_NC = Ni_NC * task_i.WCET + std::min( task_i.WCET, L - Ni_NC * task_i.period );

    return Wi_NC;
}

int calculateInterfer_Ii_D( Task task_k, Task task_i )
{
    int Ii_D, Wi_D;

    // Eq.(3) 
    Wi_D = calculateWorkload_Wi_D( task_k.period, task_i );
    Ii_D = std::min( Wi_D, task_k.period - task_k.WCET + 1 );

    return Ii_D;
}

int calculateInterfer_Ii_NC( Task task_k, Task task_i )
{
    int Ii_NC, Wi_NC;

    // Eq. (9) 
    Wi_NC = calculateWorkload_Wi_NC( task_k.period, task_i);
    Ii_NC = std::min( Wi_NC, task_k.period - task_k.WCET + 1);

    return Ii_NC;
}

int calculateInterfer_DIFF( Task task_k, Task task_i )
{
    int Ii_D, Ii_NC, Ii_DIFF_D;
    Ii_D = calculateInterfer_Ii_D( task_k, task_i );
    Ii_NC = calculateInterfer_Ii_NC( task_k, task_i );

    // Eq.(15) 
    Ii_DIFF_D = Ii_D - Ii_NC;

    return Ii_DIFF_D;
}

// Eq.(14) Independent ver of DA-LC sched test
bool DA_LC_is_schedulable(int m, Task task_k, std::vector<Task> task_set)
{
   std::vector<Task> hp_task_set;
   hp_task_set = construct_hp_task_set(task_set, task_k);

   // Calculate sum of Ii_NC 
   int sum_Ii_NC = 0;
   std::list<int> interference_list;

   for(auto it = hp_task_set.begin(); it != hp_task_set.end(); ++it)
   {
       int Ii_D, Ii_NC;

       Ii_D  = calculateInterfer_Ii_D( task_k, *it);
       Ii_NC = calculateInterfer_Ii_NC( task_k, *it);

       // Eq.(15)
       interference_list.push_back( Ii_D - Ii_NC ); 

       sum_Ii_NC += Ii_NC;
   }
   // Sort I^DIFF in descending order
   interference_list.sort(std::greater<int>()); 

   // Term 2 in Eq.(14) 
   int sum_Ii_DIFF_D = 0;
   if(interference_list.size() < num_core-1)
    {
       for(auto it = interference_list.begin(); it != interference_list.end(); ++it)
       {
           sum_Ii_DIFF_D += *it;
        }
    }
    else
    {
        auto it = interference_list.begin();
        for(int i = 0; i< num_core-1; i++)
        {
            sum_Ii_DIFF_D += *it;
            ++it;
        }
    };
   
   // Determine schedulability Eq.(14) 
   int schedulability_test;

   schedulability_test = task_k.period - task_k.WCET - floor( (sum_Ii_NC + sum_Ii_DIFF_D) / m );
   if(schedulability_test >= 0)
   {
       return true;
   }
   else
   {
       return false;
   }
}

// DA-LC unit test
std::vector<Task> DA_LC_unitTest(int m, std::vector<Task> task_set)
{

    for( auto iterator = task_set.begin(); iterator != task_set.end(); ++iterator)
    {
        // Form hp task set
        std::vector<Task> hp_task_set;
        hp_task_set = construct_hp_task_set(task_set, *iterator);

        // Calculate sum of Ii_NC
        int sum_Ii_NC = 0;
        std::list<int> interference_list;

        for(auto it = hp_task_set.begin(); it != hp_task_set.end(); ++it)
        {
            int Ii_D, Ii_NC;
            Ii_D  = calculateInterfer_Ii_D( *iterator, *it );
            Ii_NC = calculateInterfer_Ii_NC( *iterator, *it );
            interference_list.push_back( Ii_D - Ii_NC );
            sum_Ii_NC += Ii_NC;
        }
   
        // Sort in descending order
        interference_list.sort(std::greater<int>()); 

        // Calculate sum of Ii_DIFF
        int sum_Ii_DIFF_D = 0;
        if(interference_list.size() < m-1)
        {    
            for(auto it = interference_list.begin(); it != interference_list.end(); ++it)
            {
                sum_Ii_DIFF_D += *it;
            }
        }
        else
        {
            auto it = interference_list.begin();
            for(int i = 0; i< m-1; i++)
            {
                sum_Ii_DIFF_D += *it;
                ++it;
            }
        }
        iterator->value =  iterator->WCET + floor( (sum_Ii_NC + sum_Ii_DIFF_D) / m );
    }

    return task_set;
}

// ----------------------------------- OPA starts here ---------------------------------------
// DA-LC with OPA version -----
bool DA_LC_is_schedulable(Task task_k, std::vector<Task> hp_task_set)
{
    int m = 8;

   /* Calculate sum of Ii_NC */
   int sum_Ii_NC = 0;
   std::list<int> interference_list;

   for(auto it = hp_task_set.begin(); it != hp_task_set.end(); ++it)
   {
       int Ii_D, Ii_NC;

       Ii_D  = calculateInterfer_Ii_D(  task_k, *it);
       Ii_NC = calculateInterfer_Ii_NC( task_k, *it);
       sum_Ii_NC += Ii_NC;
       std::cout << Ii_D << " " << Ii_NC << std::endl;

       /* Eq.(15) */
       interference_list.push_back( Ii_D - Ii_NC ); 
   }

   /* Sort Ii_D - Ii_NC in descending order */
   interference_list.sort(std::greater<int>()); 

   /* Term 2 in Eq.(14) */
   int sum_Ii_DIFF_D = 0;
   if(interference_list.size() < num_core-1)
    {
       for(auto it = interference_list.begin(); it != interference_list.end(); ++it)
       {
           sum_Ii_DIFF_D += *it;
        }
    }
    else
    {
        auto it = interference_list.begin();
        for(int i = 0; i< num_core-1; i++)
        {
            sum_Ii_DIFF_D += *it;
            ++it;
        }
    };
   

   /* Determine schedulability Eq.(14) */
   int schedulability_test;

   schedulability_test = task_k.period - task_k.WCET - floor( (sum_Ii_NC + sum_Ii_DIFF_D) / m );
   if(schedulability_test >= 0)
   {
       return true;
   }
   else
   {
       return false;
   }
}

/* -------------------------- Audsley's optimal priority assignment ------------------------------------- */
bool optimal_priority_assignment(std::vector<Task> task_set)
{
    bool test_result, is_schedulable;

    std::vector<Task> priority_assigned_task_set;
    std::vector<Task> unassigned_task_set(task_set);


    /* Assume available priority levels = size of the list */
    int max_priority; 
    max_priority = task_set.size();

    
    /* OPA algorithm */
    
    for( int k = 1; k < max_priority+1; k++ )
    {   
        int num_unassigned_task_before, num_unassigned_task_after;
        num_unassigned_task_before = unassigned_task_set.size();
    

        for(auto it = unassigned_task_set.begin(); it != unassigned_task_set.end(); ++it)
        {
            // I can't use erase function here, will cause segmentation fault
            // hp_task_set.erase(it);

            // Manually create the hp_task_set by comparison
            std::vector<Task> hp_task_set;
            for(auto iterator = unassigned_task_set.begin(); iterator != unassigned_task_set.end(); ++iterator)
            {
                if( (iterator->period == it->period)&&(iterator->WCET == it->WCET)&&(iterator->priority == it->priority))
                {
                    continue;
                }
                else
                {
                    hp_task_set.push_back(*iterator);
                }
            }

            /* Debugging: Print the hp_task_set info */
            /*
            for(auto it = hp_task_set.begin(); it != hp_task_set.end(); ++it)
            {
                std::cout << " Period: " << it->period ;
                std::cout << " WCET: " << it->WCET ;
                std::cout << " Priority: " << it->priority << std::endl;
            }
            std::cout << "---------------------------------------" << std::endl;
            */
           
            test_result = DA_LC_is_schedulable(*it, hp_task_set);

            if(test_result == true)
            {
                it->priority = k;
                priority_assigned_task_set.push_back(*it);
                unassigned_task_set = hp_task_set;
                break;
            }
        }
        
        
        num_unassigned_task_after = unassigned_task_set.size();

        if(num_unassigned_task_before != num_unassigned_task_after)
        {
            continue;
        }
        else
        {
            is_schedulable = false;
            return is_schedulable;
        }
    }
    
    /* Debugging: Print the OPA assigned task*/
    std::cout << "--------------- OPA Task Set ---------------------" << std::endl;
    for(auto it = priority_assigned_task_set.begin(); it != priority_assigned_task_set.end(); ++it)
    {
        std::cout << " Period: " << it->period ;
        std::cout << " WCET: " << it->WCET ;
        std::cout << " Priority: " << it->priority << std::endl;
    }
    std::cout << "---------------------------------------" << std::endl;

    is_schedulable = true;
    return is_schedulable;

}
