#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "experiment.h"
#ifndef grid_h
#define grid_h
#define N 300

void getGridID();


int Convert(char fileName[N], char db_name[N], mongoc_client_t *client);


#endif
