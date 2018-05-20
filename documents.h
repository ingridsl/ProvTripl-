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
int Convert(char fileName[N], char db_name[N], mongoc_client_t *client);
//método não funcional - recupera ids dos documentos dos arquivos fragmentados
void GetDocuments(mongoc_database_t *database, mongoc_collection_t *collection);

//collections individuais

//monta documento do provider
bson_t   *PROVIDER_DOC(bool index, provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log);
//monta documento do project
bson_t   *PROJECT_DOC(bool index, project *proOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, FILE *log);
//monta documento do data
bson_t   *DATA_DOC(bool index, dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection, FILE *log,mongoc_client_t *client);

//embedded

//monta documento do provider
bson_t   *PROVIDER_DOC_S(bool index, provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log);
//monta documento do project
bson_t   *PROJECT_DOC_S(bool index, project *proOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, FILE *log);
//monta documento do data
bson_t   *DATA_DOC_S(bool index, dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection, FILE *log, mongoc_client_t *client);

bson_t   *SINGLE_DOC_2(bool index, project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, dataFile *dataOriginal, FILE *log);




//referenciando
bson_t   *PROJECT_DOC_3(bool index, project *proOriginal, FILE *log);
bson_t   *EXPERIMENT_DOC_3(bool index, experiment *expOriginal, FILE *log);
bson_t   *ACTIVITY_DOC_3(bool index, activity *activitys, FILE *log);
bson_t   *AGENT_DOC_3(bool index, mongoc_database_t *db, agent *ageOriginal, FILE *log);

//indexing
void indexingDocument (char *collection_name, mongoc_database_t *db, char *label);
#endif
