#ifndef GSYY_TEST_H
#define GSYY_TEST_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
#include <string.h>
#include <list>
#include <vector>

#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>


/* Number of cores */
//#define m 4
/* Number of tasks */
#define num_task 1000

/* Define task parameters:
 *      period: Task period Ti
 *      WCET: Task worst-case execution time Ci
 *      priority: Task priority Pi
 *      response: Task response time Ri
 *      deadline: Task deadline Di
 *      value: Task value
 */
typedef struct{
    int period; 
    int WCET;
    int priority;
    int response;
    int deadline;
    float value;
} Task;

/* Read task set from files */
std::vector<Task> readTaskFile(std::string fileName);

/* Construct set of all higher-priority tasks */
std::vector<Task> construct_hp_task_set(std::vector<Task> task_set, Task task_k);

/* Functions for calculating workload/interference */
int calculateWorkload_Wk_NC( int x, Task task_i );
int calculateWorkload_Wk_CI( int x, Task task_i );
int calculateInterfer_Ik_NC( int x, Task task_k, Task task_i );
int calculateInterfer_Ik_CI( int x, Task task_k, Task task_i );
int calculateInterfer_Ik_DIFF( int x, Task task_k, Task task_i );
int calculateInterfer_omega_k_x(int x, int m, std::vector<Task> task_set, Task task_k);

/* Functions related to ZLL */
int calculate_MIN_i_x( int x, std::list<Task> task_set, Task task_k );
int calculate_MAX_i_x( int x, std::list<Task> task_set, Task task_k );

/* Functions for performing schedulability test */
int calculate_response_time(int m, std::vector<Task> task_set, Task * task_k);
bool GSYY_sched_test(int m, std::vector<Task> task_set);

std::vector<Task> GSYY_unit_test(int m, std::vector<Task> task_set);

/* Function for performance evaluation */
float acceptance_ratio_test(std::vector<Task> task_set);

#endif
