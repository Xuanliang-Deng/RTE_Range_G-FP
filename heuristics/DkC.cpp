/*
 * Author:    Xuanliang Deng
 * Descr:     DkC priority assignment policy implementation
 * Date:      May 23 2021
 * Version:   1.0
 * History:   
 *            None
 */
#include "heuristics.h"

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

            /*
            std::stringstream ss(line);
            std::string token;

            ss >> token;
            task.period = std::stoi( token, nullptr, 10);
            ss >> token;
            task.WCET = std::stoi( token, nullptr, 10);
            ss >> token;
            task.priority = std::stoi( token, nullptr, 10);
            ss >> token;
            task.deadline = std::stoi( token, nullptr, 10 );
            ss >> token;
            task.response = std::stoi( token, nullptr, 10);
            ss >> token;
            task.value = std::stoi( token, nullptr, 10);
            */


            task_set.push_back(task);
        }
        taskFile.close();
    }
    return task_set;
}

/* 
 * Func: Read task parameters from files
 * Args:
 *      m: number of processors
 *      task_set: vector consists of all tasks
 * Return:
 *      task_set: updated vector consists of all tasks
 */
std::vector<Task> calculate_prio_DkC(int m, std::vector<Task> task_set)
{

    int period, WCET, deadline, response, priority;
    float k;

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

    /* Calculate value = Ti - k * Ci */
    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        k = 0.5 * ( m - 1 + sqrt( 5 * pow(m,2) - 6 * m + 1 ) )/m;

        /* printf("k = %f ", k); */

        period = it->period;
        WCET   = it->WCET;
        
        it->value = period - k * WCET;
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
            return a.value < b.value;
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

/*
 * Func: save generated task parameters to file
 * Param: 
 *      task_set: generated task set
 * Return:
 *      No return value. All task sets will be written under data folder
 */
void saveTask2File(std::vector<Task> task_set, std::string fileName)
{
    std::ofstream outfile;
    outfile.open(fileName, std::ios::out);

    for(auto it = task_set.begin(); it != task_set.end(); ++it)
    {
        outfile << it->period << " " << it->WCET << " " << it->priority << " " << it->deadline << " " << it->response << " " << it->value <<std::endl;
    }
    outfile.close();
}








