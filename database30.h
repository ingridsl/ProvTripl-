#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "documents.h"
#include "provider.h"
#include "cluster.h"
#include "machine.h"
#include "project.h"
#include "experiment.h"
#include "activity.h"
#include "agent.h"
#include "dataFile.h"


#ifndef database30_h
#define database30_h

#define N 300

void CreateDatabase30(bool index, provider *provOriginal, cluster *cluOriginal, machine *macOriginal, project *projOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, dataFile *dataOriginal, FILE *log);

void CleanDatabase30(mongoc_client_t *client,
                mongoc_database_t *database,
                mongoc_collection_t *collection);

#endif
