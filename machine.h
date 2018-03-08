#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "environment.h"
#ifndef machine_h
#define machine_h

#define N 300


typedef struct machine{
	int id;
	char hostname[N];
	char ip[N];
	char type[N];
	char operational_system[N];
	char cpu[N]; // que dado da cpu é esse?
	float ram_memory; //float ou char?
	int disk;
	char disk_type[N];
	char localization[N];
	float price;
	char billing_type[N];
	char setup_time[N];
	float setup_cost;
	int environment_id;
	struct machine *next;
}machine;

machine *create_machine();
machine *insert_machine(machine *origin, environment *originPro);
void freedom_machine(machine *origin);
bool existsEnvironmentId(int expIdEnv, environment *originEnv);

#endif