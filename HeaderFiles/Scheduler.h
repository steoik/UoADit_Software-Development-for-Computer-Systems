///////////////////////////////////
// University: UoA DIT
// Course : [K23a] Software Development for Computer Systems
// Semester : Fall 2021-2022
// Professor : Yannis Ioannidis 
// Assistant : Sarantis Paskalis
// --------------------------------
// Students: Stylianos Oikonomou , Anastasios Triantafyllou
// ID : 1115201500243 , 1115201600173 
// --------------------------------
// File : Scheduler.h
///////////////////////////////////

#pragma once

#include "common_types.h"
#include "core.h"

#define MAX_THREADS 16

//////////////////////////////////////////////

int JobScheduler_Initialize(int );
int JobScheduler_SubmitJob(Job );
void *JobScheduler_Run(void *);
int JobScheduler_Destroy();
void JobScheduler_WaitJobs();
