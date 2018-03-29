#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "provider.h"

#ifndef cluster_h
#define cluster_h

#define N 300


typedef struct cluster{
	int id;
	char name[N];
	int number_machines;
	char description[N];

	//reference provider
	int provider_id;
	
	struct cluster *next;
}cluster;
//inicializa valores do cluster
cluster *create_cluster();
//insere nó na lista
cluster *insert_cluster(cluster *origin, provider *originPro);
//libera memória
void freedom_cluster(cluster *origin);
//não usado
bool existsProviderId(int expIdPro, provider *originPro);

#endif
