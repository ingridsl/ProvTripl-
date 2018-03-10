#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "experiment.h"
#ifndef activity_h
#define activity_h
#include "machine.h"

#define N 300

typedef struct activity{
	int id;
	char name[N];
	char program_name[N];
	char program_version[N];
	char command_line[N];
	char start_date[N];
	char start_hour[N];
	char end_date[N];
	char end_hour[N];
	char execution_status[N];

	//dentro de experimento
	int experiment_id;
	//int agent_id;

	//aponta para maquina
	int machine_id;
	struct activity *next;
}activity;

activity *create_activity();
activity *insert_activity(activity *origin, experiment *originExp, machine *originMac);
void freedom_activity(activity *origin);
bool existsExperimentId(int expIdExp, experiment *originExp);
//bool existsAgentId(int expIdAg, agent *originAg);
bool existsMachineIdForActivity(int expIdMac, machine *originMac);

#endif