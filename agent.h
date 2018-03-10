#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "activity.h"
#ifndef agent_h
#define agent_h

#define N 300

typedef struct agent{
	int id;
	char name[N];
	char login[N];
	char instituition[N];
	char position[N];
	char role[N];
	char annotation[N];

	//dentro de atividade
	int activity_id; //checar se existe
	struct agent *next;
}agent;

agent *create_agent();
agent *insert_agent(agent *origin, activity *originAct);
void freedom_agent(agent *origin);
bool existsActivityId(int expIdAct, activity *originAct);

#endif