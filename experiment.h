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
	int execution_time;
	float execution_cost;

	//dentro de projeto
	int project_id;

	struct experiment *next;
}experiment;

//define valores da estrutura do experimento
experiment *create_experiment();
//insere nós na lista
experiment *insert_experiment(experiment *origin, project *originPro);
//libera memória
void freedom_experiment(experiment *origin);

//método obsoleto - não usado
bool existsProjectId(int expIdPro, project *originPro);

#endif