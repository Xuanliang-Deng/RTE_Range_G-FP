/*
 * Author:    Xuanliang Deng
 * Descr:     Header file for generating tasks
 * Date:      May 23 2021
 * Version:   1.0
 * History:   
 *            None
 */
#ifndef TASKGENERATION_H
#define TASKGENERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <math.h>
#include <list>
#include <iostream>
#include <fstream>
#include <vector>
#include <time.h>
#include <ctime>



/* M is the number of cores */
#define M 10
/* N is the number of task sets */
#define N 1000

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
    int priority = 0;
    int response;
    int deadline;
    float value = 0;
} Task;

/* Write task parameters into the text file */
void saveTask2File(std::vector<Task> task_set);

/* Generate task wrt number of processors M */
void generateTask();

#endif