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
	char local[N];
	char start_date[N];
	char end_date[N];
	char annotation[N];
	int version;
	char version_date[N];
	int execution_time; // é referente a cada comando colocado no terminal?
	float execution_cost;

	//dentro de projeto
	int project_id;

	struct experiment *next;
}experiment;

experiment *create_experiment();
experiment *insert_experiment(experiment *origin, project *originPro);
void freedom_experiment(experiment *origin);
bool existsProjectId(int expIdPro, project *originPro);

#endif