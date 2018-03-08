#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef environment_h
#define environment_h

#define N 300

typedef struct environment{
	int id;
	char name[N];
	char key[N];
	char url[N];
	char ip[N];
	int num_machines;
	char provider[N];
	char localization[N];
	struct environment *next;
}environment;

environment *create_environment();
environment *insert_environment(environment *origin);
void freedom_environment(environment *origin);

#endif