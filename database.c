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

void CreateDatabase(provider *provOriginal, cluster *cluOriginal, machine *macOriginal, project *projOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal, dataFile *dataOriginal, FILE *log){
  dataFile *auxdata = dataOriginal;
   const char *uri_str = "mongodb://localhost:27017";
   mongoc_client_t *client;
   mongoc_database_t *database;
   mongoc_collection_t *collection;
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
   database = mongoc_client_get_database (client, "db_name");
   printf("collection \n");
   collection = mongoc_client_get_collection (client, "db_name", "collection");
   dataFile *aux1 = auxdata;
    time_t t;
    struct tm tm;
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nDataDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
   

   while(aux1!=NULL){

      fileDoc = DATA_DOC(aux1, database, collection, log);
      if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, fileDoc, NULL, &error)) {
        fprintf (stderr, "%s\n", error.message);
      }

      aux1=aux1->next;
  }
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nDataDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProviderDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  


   bson_t   *providerDoc = PROVIDER_DOC(provOriginal, cluOriginal, macOriginal, log);
   if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, providerDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProviderDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc begin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  

   bson_t   *projectDoc = PROJECT_DOC(projOriginal, expOriginal, actOriginal, ageOriginal, log);
   if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, projectDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nProjectDoc end: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
  
   
  // bson_destroy (providerDoc);
  // bson_destroy (projectDoc);
   //bson_destroy (fileDoc);
   mongoc_collection_destroy(collection);
   mongoc_client_destroy(client);
   mongoc_cleanup();

}

void CleanDatabase(mongoc_client_t *client,
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