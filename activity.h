#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "experiment.h"
#ifndef activity_h
#define activity_h
#include "machine.h"
#include "dataFile.h"
#include "commands.h"

#define N 300

typedef struct files{
  char file_name[N];
  struct files *next;
}files;

/*
typedef struct instruction{
   char command[N];
   char initial_time[N];
   char final_time[N];
   struct files *input_files;
   struct files *output_files;
   struct instruction *next;

}instruction;*/

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
	int execution_status;

  char command_input[2][N];
  char command_output[2][N];

	//dentro de experimento
	int experiment_id;
  int agent_id;
	//int agent_id;

	//aponta para maquina
	int machine_id;
	struct activity *next;
}activity;
dataFile *returnUsedFiles();
activity *define_activity(int *activityNumber, char fileBaseName[N], dataFile *dataFileOrig, bool teste);
activity *create_activity();
activity *insert_activity(activity *origin, int *activityNumber, char fileBaseName[N], dataFile *dataFileOrig);
void freedom_activity(activity *origin);
bool existsExperimentId(int expIdExp, experiment *originExp);
//bool existsAgentId(int expIdAg, agent *originAg);
bool existsMachineIdForActivity(int expIdMac, machine *originMac);

#endif
