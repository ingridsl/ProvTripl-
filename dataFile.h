#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "activity.h"
#ifndef dataFile_h
#define dataFile_h

#define N 300

typedef struct dataFile{
	int id;
	char name[N];
	char type[N];
	char insert_date[N];
	char end_date[N];
	FILE *file;
	float size;;
	int activity_id;
	struct dataFile *next;
}dataFile;

dataFile *create_dataFile();
dataFile *insert_dataFile(dataFile *origin, activity *originAct);
void freedom_dataFile(dataFile *origin);
bool existsActivityId(int expIdAct, activity *originAct);

#endif