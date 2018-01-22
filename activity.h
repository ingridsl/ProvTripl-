#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "agent.h"
#include "experiment.h"
#ifndef activity_h
#define activity_h

#define N 300

typedef struct activity{
	int id;
	char name[N];
	char program[N];
	char version[N];
	char command[N];
	char function[N];
	char start_date[N];
	char end_date[N];
	char status[N];
	char cost[N];
	int experiment_id;
	int agent_id;
	//char machine_id[N]; -- se cloud
	struct activity *next;
}activity;

activity *create_activity();
activity *insert_activity(activity *origin, experiment *originExp, agent *originAg);
void freedom_activity(activity *origin);
bool existsExperimentId(int expIdExp, experiment *originExp);
bool existsAgentId(int expIdAg, agent *originAg);

#endif