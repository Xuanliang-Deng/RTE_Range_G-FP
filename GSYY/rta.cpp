#include "GSYY.h"

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


/* Verision 3:  RTA-LC + estimation-inferred response time, use priority-descending task_set */
void calculateResponseTimes(Process * task_set)
{
    int RTE[3] = {5, 10, 40};
    // Number of processors 
    int M = 2;
    for( int index = 0; index <3; index++ )
    {
        // Variables: 
        // - prev: previous response time solution from last computation
        // - curr: current response time solution

        int prev = -1; 
        int curr =  0;  

        // For task with highest priority, set R = WCET 
        if( index == 0 )
        {
            task_set[index].r_time = task_set[index].c_time;
        }
        else
        {
            while(curr != prev)
            {
                prev = curr;
                curr = 0;

                if( index == 1 )
                {
                    int tau_CI[1] = {0};
                    curr += ceil( calculateInterference_CI_RTE(prev, task_set, 0, index, RTE)/M ) + task_set[index].c_time ;
                }
                else if( index == 2)
                {
                    int tau_NC[1] = {1};
                    int tau_CI[1] = {0};
                    curr += ceil( calculateTotalInterference_RTE(tau_NC, tau_CI, index, prev, task_set, RTE)/M ) + task_set[index].c_time ;
                }
            }
            task_set[index].r_time = curr;
        }
    }
}

/*  Equations for RTA-LC, from Guan et al. RTSS 2009 paper */

int calculateInterference_NC( int x, Process * task_set, int index_i, int index_k )
{
    int W_k_NC, I_k_NC;

    /* Calculate W_k^NC(\tau_i, x)  Eq. (5) */
    W_k_NC = floor(x/task_set[index_i].period) * task_set[index_i].c_time + min( (x % task_set[index_i].period), task_set[index_i].c_time );

    /* Calculate I_k^NC(\tau_i, x)  Eq. (7) */
    I_k_NC = min( max( W_k_NC, 0 ), x - task_set[index_k].c_time+1 );

    /* Return the calculated Interference (No carry-in jobs) */
    return I_k_NC;
}

int calculateInterference_CI( int x, Process * task_set, int index_i, int index_k )
{
    int W_k_CI, I_k_CI, alpha;

    /* Definition of alpha below Eq. (6) */
    alpha = min( max((max( (x - task_set[index_i].c_time), 0 ))%task_set[index_i].period - (task_set[index_i].period - task_set[index_i].r_time), 0), task_set[index_i].c_time-1);

    /* Calculate W_k^CI(\tau_i, x)  Eq. (6) */
    W_k_CI = floor( max( x - task_set[index_i].c_time, 0 )/task_set[index_i].period )*task_set[index_i].c_time + task_set[index_i].c_time + alpha;

    /* Calculate I_k^CI(\tau_i, x)  Eq. (8) */
    I_k_CI = min( max(W_k_CI, 0) , x - task_set[index_k].c_time+1);

    return I_k_CI;
}

/* Eq. (11) from Yecheng's paper, Eq.(6) from Nan Guan's paper */
int calculateInterference_CI_RTE( int x, Process * task_set, int index_i, int index_k, int * RTE)
{
    int W_k_CI, I_k_CI, alpha;

    /* Definition of alpha below Eq. (6) */
    alpha = min( max((max( (x - task_set[index_i].c_time), 0 ))%task_set[index_i].period - (task_set[index_i].period - RTE[index_i]), 0), task_set[index_i].c_time-1);

    /* Calculate W_k^CI(\tau_i, x)  Eq. (6) */
    W_k_CI = floor( max( x - task_set[index_i].c_time, 0 )/task_set[index_i].period )*task_set[index_i].c_time + task_set[index_i].c_time + alpha;

    /* Calculate I_k^CI(\tau_i, x)  Eq. (8) */
    I_k_CI = min( max(W_k_CI, 0) , x - task_set[index_k].c_time+1);

    return I_k_CI;
}






int calculateTotalInterference(int * tau_NC, int * tau_CI, int k, int x, Process * task_set)
{
    /* Two input arrays store the index of task, 
     * k is the index of the analyzed task
     * x is the current calculated response time 
     * Get number of higher-priority tasks in two sub task sets 
     */
    //int num_of_tau_NC = sizeof(tau_NC) / sizeof(tau_NC[0]);
    int num_of_tau_NC = 1;
    int num_of_tau_CI = 1;

    /* Calculate total interference omega_k_x  Eq. (9) */
    int omega_k_x = 0;

    for( int xIterator_NC = 0; xIterator_NC < num_of_tau_NC; xIterator_NC++ )
    {
        omega_k_x += calculateInterference_NC(x, task_set, tau_NC[xIterator_NC], k );
    }

    for( int xIterator_CI = 0; xIterator_CI < num_of_tau_CI; xIterator_CI++ )
    {
         omega_k_x += calculateInterference_CI(x, task_set, tau_CI[xIterator_CI], k );
    }

    return omega_k_x;
}


int calculateTotalInterference_RTE(int * tau_NC, int * tau_CI, int k, int x, Process * task_set, int * RTE)
{
    /* Two input arrays store the index of task, 
     * k is the index of the analyzed task
     * x is the current calculated response time 
     * Get number of higher-priority tasks in two sub task sets 
     */
    //int num_of_tau_NC = sizeof(tau_NC) / sizeof(tau_NC[0]);
    int num_of_tau_NC = 1;
    int num_of_tau_CI = 1;

    /* Calculate total interference omega_k_x  Eq. (9) */
    int omega_k_x = 0;

    for( int xIterator_NC = 0; xIterator_NC < num_of_tau_NC; xIterator_NC++ )
    {
        omega_k_x += calculateInterference_NC(x, task_set, tau_NC[xIterator_NC], k );
    }

    for( int xIterator_CI = 0; xIterator_CI < num_of_tau_CI; xIterator_CI++ )
    {
         omega_k_x += calculateInterference_CI_RTE(x, task_set, tau_CI[xIterator_CI], k, RTE );
    }

    return omega_k_x;
}






