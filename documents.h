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

bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal);
bson_t   *PROJECT_DOC(project *proOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal);

#endif