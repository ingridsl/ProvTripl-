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
//inicializa valores dos agentes
agent *create_agent();
//insere nó na lista
agent *insert_agent(agent *origin);
//libera memoria
void freedom_agent(agent *origin);
//não usado
bool existsActivityId(int expIdAct, activity *originAct);

#endif
