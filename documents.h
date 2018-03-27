#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef documents_h
#define documents_h
#include "provider.h"
#include "cluster.h"
#include "machine.h"
#include "project.h"
#include "experiment.h"
#include "activity.h"
#include "agent.h"

typedef struct oid{
	char oid[N];
	bool posto;
	char file[N];
	struct oid *next;

}oid;

oid *add_oid(oid *o, char new[N]);
void freedomOid();
int Convert(char name[N], mongoc_collection_t  *collection, mongoc_database_t    *database);
void GetDocuments(mongoc_database_t *database, mongoc_collection_t *collection);
bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal);
bson_t   *PROJECT_DOC(project *proOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal);
bson_t   *DATA_DOC(dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection);

#endif