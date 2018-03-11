#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef providerDoc_h
#define providerDoc_h
#include "provider.h"
#include "cluster.h"
#include "machine.h"

bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal);

#endif