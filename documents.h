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

//classe obsoleta - era usada para pegar ids dos documentos gerados com a inclusão do arquivo bruto
typedef struct oid{
	char oid[N];
	bool posto;
	char file[N];
	struct oid *next;

}oid;
//método obsoleto - inseria nó na lista de oids
oid *add_oid(oid *o, char new[N]);
//método obsoleto - libera lista
void freedomOid();
//pega o arquivo bruto e insere no mongo db em vários fragmentos
int Convert(char name[N], mongoc_collection_t  *collection, mongoc_database_t    *database);
//método não funcional - recupera ids dos documentos dos arquivos fragmentados
void GetDocuments(mongoc_database_t *database, mongoc_collection_t *collection);
//monta documento do provider
bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log);
//monta documento do project
bson_t   *PROJECT_DOC(project *proOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, FILE *log);
//monta documento do data
bson_t   *DATA_DOC(dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection, FILE *log);

#endif