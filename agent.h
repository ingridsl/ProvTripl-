#include <stdio.h>
#include <string.h>
#include <stdlib.h>
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
	char group[N];
	char note[N];
	struct agent *next;
}agent;

agent *create_agent();
agent *insert_agent(agent *origin);
void freedom_agent(agent *origin);

#endif