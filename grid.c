#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "grid.h"

char *getGridID(char *modelName, char *fileName, char str[25]){
  const char *uri_str = "mongodb://localhost:27017";
  mongoc_client_t *client;
  char     *id_str;
  bson_error_t error;
  mongoc_gridfs_file_t *file;
  mongoc_gridfs_t *gridfs;
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


  gridfs = mongoc_client_get_gridfs (client, modelName, "fs", &error);
  assert (gridfs);
  file = mongoc_gridfs_find_one_by_filename (gridfs, fileName, &error);
  if(!file){
    printf("\n\n  FILE NOT FOUND : %s\n\n", fileName);
    return "notFound";
  }
  const bson_value_t *returnedValue = mongoc_gridfs_file_get_id (file);

  printf ("%d\n", returnedValue->value.v_int32);
  bson_oid_to_string(&returnedValue->value.v_oid, str);
  printf("\n\n%s", str);
  return str;
}

//pegar arquivo bruto, converter, fragmentar e inserir no mongo
int Convert(char fileName[N], char db_name[N], mongoc_client_t *client){
  printf("\nCONVERT\n");
  char comando[N];
  char name[N], extensao[7];
  mongoc_gridfs_t *gridfs;
  mongoc_gridfs_file_t *file;
  mongoc_gridfs_file_list_t *list;
  mongoc_gridfs_file_opt_t opt = {0};
  mongoc_stream_t *stream;
  bson_t filter;
  bson_t opts;
  bson_t child;
  bson_error_t error;
  ssize_t r;
  char buf[4096];
  mongoc_iovec_t iov;
  const char *filename;
  const char *command;
  bson_value_t id;
  strcpy(name, fileName);
  int counter = 1;
  char nameExtraFile[N];
  while(counter<9){
    //printf("\n\n i> %d", i); // os hisat2.idx são fragmentados em 8 arquivos durante o workflow. deve-se considerar os 8
    if(strcmp(fileName, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")==0){
      strcpy(name, fileName);
      sprintf(extensao, ".%d.ht2", counter);
      strcat(name, extensao);
      counter++;
      //printf("\n \n file name: %s", name);
    }

  /*  strcpy(nameExtraFile, name);
    strcat(nameExtraFile, ".created.txt");
    FILE *fp = fopen(nameExtraFile, "w+");
    if(!fp){
      printf("Unable to create file");
      exit(1);

    }
    printf("\n(%s)\n", name);
    printf("%d - %d", (int)strlen(name), (int)strlen("file.sam"));
    if(access(name, F_OK) != -1 ){
      printf("file does not exist");
    }*/
    // VERSÃO MONGOC
    printf("\n1.0");
  /* grab a gridfs handle in test prefixed by fs */
      gridfs = mongoc_client_get_gridfs (client, db_name, "fs", &error);
      assert (gridfs);

      printf("\n1.1");

      stream = mongoc_stream_file_new_for_path (name, O_RDONLY, 0);
      assert (stream);
      printf("\n1.1.0");
      printf("\n1.3 >>>>>>>>>>>>> %s", name);

      opt.filename = name;

      printf("\n1.3.0");
      /* the driver generates a file_id for you */
      file = mongoc_gridfs_create_file_from_stream (gridfs, stream, &opt);
      printf("\n1.3.1");
      assert (file);

      printf("\n1.3.2");

      id.value_type = BSON_TYPE_INT32;

      printf("\n1.3.3");
      id.value.v_int32 = 1;

      printf("\n1.3.4");

      /* optional: the following method specifies a file_id of any
         BSON type
      if (!mongoc_gridfs_file_set_id (file, &id, &error)) {
         fprintf (stderr, "%s\n", error.message);
         return 1;
      }*/

      mongoc_gridfs_file_save (file);
      mongoc_gridfs_file_destroy (file);

      printf("\n2.0");
      /////////////////////////

      printf("\n\n COMEÇANDO AQUI!! 1");
    //  ////getchar();
  /*    iov.iov_base = (void*) buf;
      iov.iov_len = sizeof buf;
      file = mongoc_gridfs_find_one_by_filename (gridfs, name, &error);
      assert (file);

      stream = mongoc_stream_gridfs_new (file);
      assert (stream);

      for (;;) {
         r = mongoc_stream_readv (stream, &iov, 1, -1, 0);

         assert (r >= 0);

         if (r == 0) {
            break;
         }
          ////getchar();
         if (fwrite (iov.iov_base, 1, r, fp) != r) {
           printf("ERROR");
           ////getchar();
            MONGOC_ERROR ("Failed to write to stdout. Exiting.\n");
            exit (1);
         }
      }
      fclose(fp);
      mongoc_stream_destroy (stream);
      mongoc_gridfs_file_destroy (file);*/

      ////////////////// LIST

      printf("\n\n COMEÇANDO AQUI!! 2");
      //////getchar();
      /*
      bson_init (&filter);

      bson_init (&opts);
      bson_append_document_begin (&opts, "sort", -1, &child);
      BSON_APPEND_INT32 (&child, "filename", 1);
      bson_append_document_end (&opts, &child);

      list = mongoc_gridfs_find_with_opts (gridfs, &filter, &opts);

      bson_destroy (&filter);
      bson_destroy (&opts);

      while ((file = mongoc_gridfs_file_list_next (list))) {
         const char *name2 = mongoc_gridfs_file_get_filename (file);
         printf ("%s\n", name2 ? name2 : "?");

         mongoc_gridfs_file_destroy (file);
      }

      mongoc_gridfs_file_list_destroy (list);*/
      if(strcmp(fileName, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")!=0){
        counter=9;
      }

  }
return 1;
}
