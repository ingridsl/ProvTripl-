#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "database.h"
#include "documents.h"
#include "provider.h"
#include "cluster.h"
#include "machine.h"

void CreateDatabase30(provider *provOriginal, cluster *cluOriginal, machine *macOriginal, project *projOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, dataFile *dataOriginal, FILE *log){
  dataFile *auxdata = dataOriginal;
   const char *uri_str = "mongodb://localhost:27017";
   mongoc_client_t *client;
   mongoc_database_t *model30;
   mongoc_collection_t *project3, * provider3, * data3, *activity3,*experiment3, *agent3;
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
   model30 = mongoc_client_get_database (client, "model30");
   printf("collection \n");
   data3 = mongoc_client_get_collection (client, "model30", "data3");
   project3 = mongoc_client_get_collection (client, "model30", "project3");
   provider3 = mongoc_client_get_collection (client, "model30", "provider3");
   agent3 = mongoc_client_get_collection (client, "model30", "agent3");
   experiment3 = mongoc_client_get_collection (client, "model30", "experiment3");
   activity3 = mongoc_client_get_collection (client, "model30", "activity3");
   dataFile *auxDatafile = auxdata;
   activity *auxActivity = actOriginal;

    time_t t;
    struct tm tm;
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nDataDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   while(auxDatafile!=NULL){

      fileDoc = DATA_DOC(auxDatafile, model30, data3, log, client);
      if (!mongoc_collection_insert(data3, MONGOC_INSERT_NONE, fileDoc, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
      }

      auxDatafile=auxDatafile->next;
  }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nDataDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  /* // PROVIDER
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProviderDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);



   bson_t   *providerDoc = PROVIDER_DOC(provOriginal, cluOriginal, macOriginal, log);
   if (!mongoc_collection_insert(provider1, MONGOC_INSERT_NONE, providerDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProviderDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  */

  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   bson_t   *projectDoc = PROJECT_DOC_3(projOriginal, log);
   if (!mongoc_collection_insert(project3, MONGOC_INSERT_NONE, projectDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);



  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   bson_t   *experimentDoc = EXPERIMENT_DOC_3(expOriginal, log);
   if (!mongoc_collection_insert(experiment3, MONGOC_INSERT_NONE, experimentDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

 while(auxActivity!=NULL){
   bson_t   *activityDoc = ACTIVITY_DOC_3(auxActivity, log);
   if (!mongoc_collection_insert(activity3, MONGOC_INSERT_NONE, activityDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
   auxActivity = auxActivity->next;
 }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   bson_t   *agentDoc = AGENT_DOC_3(ageOriginal, log);
   if (!mongoc_collection_insert(agent3, MONGOC_INSERT_NONE, agentDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


  // bson_destroy (providerDoc);
  // bson_destroy (projectDoc);
   //bson_destroy (fileDoc);
   mongoc_collection_destroy(data3);
   mongoc_collection_destroy(project3);
   mongoc_collection_destroy(provider3);
   mongoc_collection_destroy(agent3);
   mongoc_collection_destroy(experiment3);
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
