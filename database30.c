#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "database30.h"
#include "documents.h"
#include "provider.h"
#include "cluster.h"
#include "machine.h"

void CreateDatabase30(bool index, provider *provOriginal, cluster *cluOriginal, machine *macOriginal, project *projOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, dataFile *dataOriginal, FILE *log){
  dataFile *auxdata = dataOriginal;
   const char *uri_str = "mongodb://localhost:27017";
   mongoc_client_t *client;
   mongoc_database_t *model30;
   mongoc_collection_t *project3, * data3, *activity3,*experiment3, *agent3, * provider3, *cluster3, *machine3;
   bson_t *command, reply, *insert;
   bson_error_t error;
   char *str;
   bool retval;

   /*
    * Required to initialize libmongoc's internals
    */
   printf("\n mongoc_init ();\n");
   mongoc_init ();

   /*
    * Create a new client instance
    */
   client = mongoc_client_new (uri_str);

   /*
    * Register the application name so we can track it in the profile logs
    * on the server. This can also be done from the URI (see other examples).
    */
   mongoc_client_set_appname (client, "ProvenanceMongoDB2");

   /*
    * Get a handle on the database "db_name" and collection "coll_name"
    */
   bson_t   *fileDoc;
   printf("database \n");

   char databaseName[N];
   if(index){
     strcpy(databaseName, "model30-I");
   }else{
       strcpy(databaseName, "model30");
   }
   model30 = mongoc_client_get_database (client, databaseName);
   printf("collection \n");
   data3 = mongoc_client_get_collection (client,databaseName, "data3");
   project3 = mongoc_client_get_collection (client, databaseName, "project3");
   agent3 = mongoc_client_get_collection (client, databaseName, "agent3");
   experiment3 = mongoc_client_get_collection (client, databaseName, "experiment3");
   activity3 = mongoc_client_get_collection (client, databaseName, "activity3");
   provider3 = mongoc_client_get_collection (client, databaseName, "provider3");
   cluster3 = mongoc_client_get_collection (client, databaseName, "cluster3");
   machine3 = mongoc_client_get_collection (client, databaseName, "machine3");
   dataFile *auxDatafile = auxdata;
   activity *auxActivity = actOriginal;

    time_t t;
    struct tm tm;
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nDataDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  while(auxDatafile!=NULL){

      fileDoc = DATA_DOC(index, databaseName, auxDatafile, log, client);
      if (!mongoc_collection_insert(data3, MONGOC_INSERT_NONE, fileDoc, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
      }

      auxDatafile=auxDatafile->next;
  }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nDataDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  // PROVIDER
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProviderDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   bson_t   *providerDoc = PROVIDER_DOC_3(index, provOriginal, log);
   if (!mongoc_collection_insert(provider3, MONGOC_INSERT_NONE, providerDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProviderDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  //CLUSTER
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nClusterDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);



   bson_t   *clusterDoc = CLUSTER_DOC_3(index, cluOriginal, log);
   if (!mongoc_collection_insert(cluster3, MONGOC_INSERT_NONE, clusterDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nClusterDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  //MACHINE
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nMachineDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);



   bson_t   *machineDoc = MACHINE_DOC_3(index, macOriginal, log);
   if (!mongoc_collection_insert(machine3, MONGOC_INSERT_NONE, machineDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nMachineDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

     printf("FIM PROJECT");

 bson_t   *projectDoc = PROJECT_DOC_3(index, projOriginal, log);
   if (!mongoc_collection_insert( project3, MONGOC_INSERT_NONE, projectDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);



  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nExperimentDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  bson_t   *experimentDoc = EXPERIMENT_DOC_3(index, expOriginal, log);
   if (!mongoc_collection_insert(experiment3, MONGOC_INSERT_NONE, experimentDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nExperimentDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nActivityDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
printf("ACTIVITY ---");printf("ACTIVITY ---");

 while(auxActivity!=NULL){
   bson_t   *activityDoc = ACTIVITY_DOC_3(index, auxActivity, log);
   if (!mongoc_collection_insert(activity3, MONGOC_INSERT_NONE, activityDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
   auxActivity = auxActivity->next;
 }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nActivityDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nAgentDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   bson_t   *agentDoc = AGENT_DOC_3(index, model30, ageOriginal, log);
   if (!mongoc_collection_insert(agent3, MONGOC_INSERT_NONE, agentDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nAgentDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  /* bson_destroy (providerDoc);
   bson_destroy (projectDoc);
   bson_destroy (fileDoc);
   mongoc_collection_destroy(data3);
   mongoc_collection_destroy(project3);
   mongoc_collection_destroy(provider3);*/
   mongoc_collection_destroy(agent3);
  // mongoc_collection_destroy(experiment3);
   mongoc_collection_destroy(activity3);
   mongoc_client_destroy(client);
   mongoc_cleanup();

}

void CleanDatabase30(mongoc_client_t *client,
                mongoc_database_t *database,
                mongoc_collection_t *collection){
    /*
    * Release our handles and clean up libmongoc
    */
   mongoc_collection_destroy (collection);
   mongoc_database_destroy (database);
   mongoc_client_destroy (client);
   mongoc_cleanup ();

}
