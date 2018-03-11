#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "providerDoc.h"
#include "provider.h"
#include "cluster.h"
#include "machine.h"

#define N 300

void CreateDatabase(provider *proOriginal, cluster *cluOriginal, machine *macOriginal);

void CleanDatabase(mongoc_client_t *client,
                mongoc_database_t *database,
                mongoc_collection_t *collection);
