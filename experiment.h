#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project.h"
#ifndef experiment_h
#define experiment_h

#define N 300

typedef struct experiment{
	int id;
	char name[N];
	char description[N];
	char start_date[N];
	char end_date[N];
	char version[N];
	char version_date[N];
	char note[N];
	int project_id;
	float execution_cost;
	float configuration_cost;
	float total_cost;
	struct experiment *next;
}experiment;

experiment *create_experiment();
experiment *insert_experiment(experiment *origin, project *originPro);
void freedom_experiment(experiment *origin);
bool existsProjectId(int expIdPro, project *originPro);

#endif