/*
 * Author:    Xuanliang Deng
 * Descr:     Header file for DA-LC schedulability test & OPA
 * Date:      May 31 2021
 * Version:   2.0
 * History:   
 *            May 31,2021: Change from list to vector, update all functions
 * Ref:       Improved Priority Assignment for Global Fixed Priority Preemptive Scheduling in Multiprocessor Real-Time Systems
 */

#ifndef DA_LC_H
#define DA_LC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <list>
#include <iostream>
#include <fstream>
#include <algorithm>
#include <vector>
#include <string>
#include <sstream>

#define num_core 10
#define num_task 1000

extern int num_of_set;

// Define the structure of each task generated 
typedef struct{
    int period; 
    int WCET;
    int priority;
    int response;
    int deadline;
    float value;
} Task;

// Read task set from files 
std::vector<Task> readTaskFile(std::string fileName);

// Construct higher-priority task set
std::vector<Task> construct_hp_task_set(std::vector<Task> task_set, Task task_k);

// Eq.(1) and (2) 
int calculateWorkload_Wi_D( int L, Task task_k, Task task_i );

// Eq.(10) and (11) 
int calculateWorkload_Wi_NC(int L, Task task_k, Task task_i);

// Eq.(3) 
int calculateInterfer_Ii_D( Task task_k, Task task_i );

// Eq.(9) 
int calculateInterfer_Ii_NC( Task task_k, Task task_i );

// Eq.(15)
int calculateInterfer_DIFF( Task task_k, Task task_i );

// Eq.(14) 
// Independent ver of DA-LC sched test
bool DA_LC_is_schedulable(int m, Task task_k, std::vector<Task> task_set);

// DA-LC with OPA version
bool DA_LC_is_schedulable(Task task_k, std::vector<Task> hp_task_set);

// DA-LC unit test
std::vector<Task> DA_LC_unitTest(int m, std::vector<Task> task_set);

// OPA
bool optimal_priority_assignment(std::vector<Task> task_set);

#endif