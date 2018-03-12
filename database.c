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

void CreateDatabase(provider *provOriginal, cluster *cluOriginal, machine *macOriginal, project *projOriginal, experiment *expOriginal, activity *actOriginal, agent *ageOriginal){
  
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
   printf("database \n");
   database = mongoc_client_get_database (client, "db_name");
   printf("collection \n");
   collection = mongoc_client_get_collection (client, "db_name", "collection");


   bson_t   *providerDoc = PROVIDER_DOC(provOriginal, cluOriginal, macOriginal);
   if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, providerDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }

   bson_t   *projectDoc = PROJECT_DOC(projOriginal, expOriginal, actOriginal, ageOriginal);
   if (!mongoc_collection_insert(collection, MONGOC_INSERT_NONE, projectDoc, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
  
   bson_destroy (providerDoc);
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