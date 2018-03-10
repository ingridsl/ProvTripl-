#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#ifndef provider_h
#define provider_h

#define N 300

typedef struct provider{
	int id;
	char name[N];
	char url[N];
	char description[N];
	
	//localization
	int localization_id;
	char localization_region[N];
	char localization_zone[N];

	struct provider *next;
}provider;

provider *create_provider();
provider *insert_provider(provider *origin);
void freedom_provider(provider *origin);

#endif