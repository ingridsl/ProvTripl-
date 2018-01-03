#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "database.h"


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

void CreateDatabase(workflow *wf/*char fileNames[N]*/){
  mongoc_client_t      *client;
  mongoc_database_t    *database;
  mongoc_collection_t  *collection;
  bson_t               *command,
                         reply,
                        *insert;
  bson_error_t          error;
  char                 *str;
  bool                  retval;

  char fileNames[N];

  /*
    * Required to initialize libmongoc's internals
    */
   mongoc_init ();

   /*
    * Create a new client instance
    */
   client = mongoc_client_new ("mongodb://localhost:27017");

   /*
    * Register the application name so we can track it in the profile logs
    * on the server. This can also be done from the URI (see other examples).
    */
   mongoc_client_set_appname (client, "connect-example");

   /*
    * Get a handle on the database "db_name" and collection "coll_name"
    */
   database = mongoc_client_get_database (client, "db_name");
   collection = mongoc_client_get_collection (client, "db_name", "coll_name");

   /*
    * Do work. This example pings the database, prints the result as JSON and
    * performs an insert
    */
   
   /*command = BCON_NEW ("ping", BCON_INT32 (1));

   retval = mongoc_client_command_simple (client, "admin", command, NULL, &reply, &error);
  
   if (!retval) {
      fprintf (stderr, "%s\n", error.message);
      //return EXIT_FAILURE;
   }*/

   /*str = bson_as_json (&reply, NULL);
   printf ("%s\n", str);

   insert = BCON_NEW ("hello", BCON_UTF8 ("world"));

   if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, insert, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }*/



  words *aux1 = files;
  while(aux1!=NULL){
    //fileNames = aux1->word;

    bson_t   *document  = FASTQ(aux1->word, collection, database);

    counter ++;
    insert = document;
    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, insert, NULL, &error)) {
       fprintf (stderr, "%s\n", error.message);
    }

    aux1 = aux1->next;
  }

   //bson_destroy (document);
   bson_t   *document1 = ACCOUNT();
   //insert1 = document1;
   if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, document1, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
    counter ++;

    ACTIVITY(wf, collection);
    bson_t   *document2 = PROJECT();
    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, document2, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
    counter ++;

    bson_t   *document3 = AGENT();
    if (!mongoc_collection_insert (collection, MONGOC_INSERT_NONE, document3, NULL, &error)) {
      fprintf (stderr, "%s\n", error.message);
   }
    counter ++;
   bson_destroy (insert);
   bson_destroy (document1);
   bson_destroy (document2);
   bson_destroy (document3);
   bson_destroy (&reply);
   bson_destroy (command);
   bson_free (str);

  //CleanDatabase(client, database, collection);

}
