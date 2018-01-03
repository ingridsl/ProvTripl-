#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define N 300

void CleanDatabase(mongoc_client_t *client,
                mongoc_database_t *database,
                mongoc_collection_t *collection);

void CreateDatabase(workflow *wf/*char fileNames[N]*/);
