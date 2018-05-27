#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#ifndef dataFile_h
#define dataFile_h

#define N 300

typedef struct dataFile{
	int id;
	char name[N];
	char description[N];
	char localization[N];
	char annotation[N];
	int size;
	char insertion_date[N];
	int machine_id;
	char type[N];
	FILE *file;
	struct dataFile *next;
}dataFile;

dataFile *create_dataFile(char file_name[N]);
dataFile *insert_dataFile(dataFile *origin, char file_name[N]);
void freedom_dataFile(dataFile *origin);
bool existsDataFileId(char fileName[N], dataFile *origin);
int retrieveDataFileId(char fileName[N], dataFile *origin);
#endif
