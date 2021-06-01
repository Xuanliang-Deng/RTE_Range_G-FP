/*
 * Author:    Xuanliang Deng
 * Descr:     Header file for heuristic priority assignment policies
 * Date:      May 23 2021
 * Version:   1.0
 * History:   
 *            None
 */
#ifndef HEURISTICS_H
#define HEURISTICS_H

#include <stdio.h>
#include <stddef.h>
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

extern int num_of_set;

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

/* Write task parameters into the text file */
void saveTask2File(std::vector<Task> task_set, std::string fileName);

/* Based on DkC policy, assign priorities to all tasks */
std::vector<Task> calculate_prio_DkC(int m, std::vector<Task> task_set);

/* Based on DMPO policy, assign priorities to all tasks */
std::vector<Task> calculate_prio_DMPO(std::vector<Task> task_set);

/* Based on DCMPO policy, assign priorities to all tasks */
std::vector<Task> calculate_prio_DCMPO(std::vector<Task> task_set);

#endif
