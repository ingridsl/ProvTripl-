#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "documents.h"
#include "dataFile.h"
#include "machine.h"
#include "agent.h"

bool novo = false;
oid *oidNumbers = NULL;

oid *add_oid(oid *o, char new[N]){
  oid *aux = o;
  oid *aux2 = o;
  while(aux2!=NULL){ //impede que seja inserido um oid que já existe
    if(strcmp(aux2->oid, new)>0){
      //printf("\n\nIGUAIS ================= %s & %s", aux2->oid, new);
      novo = false;
      return o;
    }
    novo = true;
    aux2 = aux2->next;
  }
  //printf("\n\nINCLUIDO ================= %s & %s ", aux2->oid, new);

  oid *auxNew = (oid*)malloc(sizeof(oid));
  if(!auxNew){
    printf("\nError");
    exit(1);
  }

  auxNew->posto = false;
  strcpy(auxNew->oid, new);
  /*if(renew){
  //lastoid = auxNew;
  printf("\n\nLASTOID ================= %s & %s ", auxNew->oid, lastoid->oid);
  ////getchar();
}*/
if(aux==NULL){
  auxNew->next = NULL;
  return auxNew;
}
auxNew->next = aux;
return auxNew;
}

void freedomOid(){
  oid *aux1 = oidNumbers;
  printf("\n\nWORDS:");
  while(aux1!=NULL){
    printf("\n %s", aux1->oid);
    free(aux1);
    aux1 = aux1->next;
  }
}

bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log){
  dataFile *aux = macOriginal->dataFiles;
  bson_t   *provider, cluster, machine, dataFiles;
  char     *provider_str;
  bson_oid_t oid;

  //inicializa documento
  bson_oid_init (&oid, NULL);
  provider = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  //conversão para strings é necessária
  char str_clu_id[15];
  sprintf(str_clu_id, "%d", cluOriginal->id);

  char str_clu_number_machines[15];
  sprintf(str_clu_number_machines, "%d", cluOriginal->number_machines);

  char str_pro_id[15];
  sprintf(str_pro_id, "%d", proOriginal->id);

  char str_pro_localization_id[15];
  sprintf(str_pro_localization_id, "%d", proOriginal->localization_id);

  char str_mac_id[15];
  sprintf(str_mac_id, "%d", macOriginal->id);

  char str_mac_localization_id[15];
  sprintf(str_mac_localization_id, "%d", macOriginal->localization_id);

  char str_mac_ip[36];
  sprintf(str_mac_ip, "%ld", macOriginal->ip);

  char str_mac_cpu[15];
  sprintf(str_mac_cpu, "%d", macOriginal->cpu);

  char str_mac_ram_memory[15];
  sprintf(str_mac_ram_memory, "%d", macOriginal->ram_memory);

  char str_mac_disk[36];
  sprintf(str_mac_disk, "%ld", macOriginal->disk);

  char str_mac_price[36];
  sprintf(str_mac_price, "%ld", macOriginal->price);

  char str_mac_price_type[36];
  sprintf(str_mac_price_type, "%ld", macOriginal->price_type);

  provider = BCON_NEW (
    "id", str_pro_id,
    "name", proOriginal->name,
    "url", proOriginal->url,
    "description", proOriginal->description,
    "localization_id", str_pro_localization_id,
    "localization_region", proOriginal->localization_region,
    "localization_zone", proOriginal->localization_zone
  );

  BSON_APPEND_DOCUMENT_BEGIN(provider, "cluster", &cluster);
  BSON_APPEND_UTF8 (&cluster, "id", str_clu_id);
  BSON_APPEND_UTF8 (&cluster, "name", cluOriginal->name);
  BSON_APPEND_UTF8 (&cluster, "number_machines", str_clu_number_machines);
  BSON_APPEND_UTF8 (&cluster, "description", cluOriginal->description);

  BSON_APPEND_DOCUMENT_BEGIN(&cluster, "machine", &machine);
  BSON_APPEND_UTF8 (&machine, "id", str_mac_id);
  BSON_APPEND_UTF8 (&machine, "hostname", macOriginal->hostname);
  BSON_APPEND_UTF8 (&machine, "ip", str_mac_ip);
  BSON_APPEND_UTF8 (&machine, "type", macOriginal->type);
  BSON_APPEND_UTF8 (&machine, "operational_system", macOriginal->operational_system);
  BSON_APPEND_UTF8 (&machine, "cpu", str_mac_cpu);
  BSON_APPEND_UTF8 (&machine, "ram_memory", str_mac_ram_memory);
  BSON_APPEND_UTF8 (&machine, "disk", str_mac_disk);
  BSON_APPEND_UTF8 (&machine, "disk_type", macOriginal->disk_type);
  BSON_APPEND_UTF8 (&machine, "localization", macOriginal->localization);
  BSON_APPEND_UTF8 (&machine, "price", str_mac_price);
  BSON_APPEND_UTF8 (&machine, "price_type", str_mac_price_type);
  BSON_APPEND_UTF8 (&machine, "localization_id", str_mac_localization_id);
  BSON_APPEND_UTF8 (&machine, "localization_region", macOriginal->localization_region);
  BSON_APPEND_UTF8 (&machine, "localization_zone", macOriginal->localization_zone);
  /*char str_mac_dataFiles_id[36];
  uint32_t    i;
  char        buf[16];
  const       char *key;
  size_t      keylen;
  BSON_APPEND_ARRAY_BEGIN(&machine, "data_file_id", &dataFiles);
  while(aux != NULL){ //insere o id da lista de arquivos na máquina
  sprintf(str_mac_dataFiles_id, "%d", aux->id);
  keylen = bson_uint32_to_string (i, &key, buf, sizeof buf);
  bson_append_utf8 (&dataFiles, key, (int) keylen, str_mac_dataFiles_id, -1);

  i++;
  aux = aux->next;
}

bson_append_array_end(&machine, &dataFiles);*/
bson_append_document_end(&cluster, &machine);

bson_append_document_end(provider, &cluster);
/*
* Print the document as a JSON string.
*/
provider_str = bson_as_json (provider, NULL);
printf ("\n\t%s\n\n", provider_str);
fprintf(log,"\n\t%s\n\n", provider_str);
bson_free (provider_str);
/*
* Clean up allocated bson documents.
*/
return provider;
}



bson_t   *PROJECT_DOC(project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, FILE *log){
  activity *actOriginal = activitys;
  const char* command1_input[] = {"3"}; //arquivos usados pelos comandos. ver na main qual é qual
  const char* command1_output[] = {"9"}; //arquivos usados pelos comandos. ver na main qual é qual

  const char* command2_input[] = {"1"};
  const char* command2_output[] = {"2"};

  const char* command3_input[] = {"2","9"};
  const char* command3_output[] = {"4"};

  const char* command4_input[] = {"4"};
  const char* command4_output[] = {"5"};

  const char* command5_input[] = {"5"};
  const char* command5_output[] = {"6"};

  const char* command6_input[] = {"6","7"};
  const char* command6_output[] = {"8"};

  bson_t   *project, experiment, agent, child;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;

  bson_oid_init (&oid, NULL);
  project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  char str_pro_id[15];
  sprintf(str_pro_id, "%d", proOriginal->id);

  char str_exp_id[15];
  sprintf(str_exp_id, "%d", expOriginal->id);

  char str_exp_version[15];
  sprintf(str_exp_version, "%d", expOriginal->version);

  char str_exp_execution_time[15];
  sprintf(str_exp_execution_time, "%d", expOriginal->execution_time);

  char str_exp_execution_cost[24];
  sprintf(str_exp_execution_cost, "%f", expOriginal->execution_cost);

  char str_act_execution_status[15];
  sprintf(str_act_execution_status, "%d", actOriginal->execution_status);

  project = BCON_NEW (
    "id", str_pro_id,
    "name", proOriginal->name,
    "description", proOriginal->description,
    "inst_funders", proOriginal->inst_funders,
    "inst_participants", proOriginal->inst_participants,
    "coordinator", proOriginal->coordinator,
    "start_date", proOriginal->start_date,
    "end_date", proOriginal->end_date
  );

  BSON_APPEND_DOCUMENT_BEGIN(project, "experiment", &experiment);
  BSON_APPEND_UTF8 (&experiment, "id", str_exp_id);
  BSON_APPEND_UTF8 (&experiment, "name", expOriginal->name);
  BSON_APPEND_UTF8 (&experiment, "description", expOriginal->description);
  BSON_APPEND_UTF8 (&experiment, "local", expOriginal->local);
  BSON_APPEND_UTF8 (&experiment, "start_date", expOriginal->start_date);
  BSON_APPEND_UTF8 (&experiment, "end_date", expOriginal->end_date);
  BSON_APPEND_UTF8 (&experiment, "annotation", expOriginal->annotation);
  BSON_APPEND_UTF8 (&experiment, "version", str_exp_version);
  BSON_APPEND_UTF8 (&experiment, "version_date", expOriginal->version_date);
  BSON_APPEND_UTF8 (&experiment, "execution_time", str_exp_execution_time);
  BSON_APPEND_UTF8 (&experiment, "execution_cost", str_exp_execution_cost);
  int y = 0;
  char str_age_id[15];
  sprintf(str_age_id, "%d", ageOriginal->id);

  bson_t activity, activities, child2;
  BSON_APPEND_ARRAY_BEGIN(&experiment, "activity", &activities);
  //comandos daqui
  while(actOriginal->next !=NULL){

    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);

    //BSON_APPEND_DOCUMENT_BEGIN(&activities, "", &activity);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;


    //for (y = 0; y < sizeof actOriginal->program_name / sizeof (char *); ++y) {
    keylen = bson_uint32_to_string (y, &key, buf, sizeof buf);
    bson_append_document_begin (&activities, key, (int) keylen, &activity);
    BSON_APPEND_UTF8 (&activity, "id", str_act_id);
    BSON_APPEND_UTF8 (&activity, "name", actOriginal->name);
    BSON_APPEND_UTF8 (&activity, "program_name", actOriginal->program_name);
    BSON_APPEND_UTF8 (&activity, "program_version", actOriginal->program_version);
    BSON_APPEND_UTF8 (&activity, "command_line", actOriginal->command_line);
    BSON_APPEND_UTF8 (&activity, "start_date", actOriginal->start_date);
    BSON_APPEND_UTF8 (&activity, "start_hour", actOriginal->start_hour);
    BSON_APPEND_UTF8 (&activity, "end_date", actOriginal->end_date);
    BSON_APPEND_UTF8 (&activity, "end_hour", actOriginal->end_hour);
    BSON_APPEND_UTF8 (&activity, "execution_status", str_act_execution_status);
    //}
    // USED FILES
    char str_mac_dataFiles_id[36];

    BSON_APPEND_ARRAY_BEGIN(&activity, "files", &child);
    if(actOriginal->id == 1){
      for(i = 0; i< sizeof command1_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command1_input[i], -1);

      }
      for(i = 0; i< sizeof command1_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command1_output[i], -1);

      }
    }
    if(actOriginal->id == 2){
      for(i = 0; i< sizeof command2_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command2_input[i], -1);

      }
      for(i = 0; i< sizeof command2_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command2_output[i], -1);

      }
    }
    if(actOriginal->id == 3){
      for(i = 0; i< sizeof command3_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command3_input[i], -1);

      }
      for(i = 0; i< sizeof command3_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command3_output[i], -1);

      }
    }
    if(actOriginal->id == 4){
      for(i = 0; i< sizeof command4_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command4_input[i], -1);

      }
      for(i = 0; i< sizeof command4_output/sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command4_output[i], -1);

      }
    }
    if(actOriginal->id == 5){
      for(i = 0; i< sizeof command5_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command5_input[i], -1);

      }
      for(i = 0; i< sizeof command5_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command5_output[i], -1);

      }
    }
    if(actOriginal->id == 6){
      for(i = 0; i< sizeof command6_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command6_input[i], -1);

      }
      for(i = 0; i< sizeof command6_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command6_output[i], -1);

      }
    }

    bson_append_array_end(&activity, &child);

    // END USED FILES
    BSON_APPEND_DOCUMENT_BEGIN(&activity, "agent", &agent);
    BSON_APPEND_UTF8 (&agent, "id", str_age_id);
    BSON_APPEND_UTF8 (&agent, "name", ageOriginal->name);
    BSON_APPEND_UTF8 (&agent, "login", ageOriginal->login);
    BSON_APPEND_UTF8 (&agent, "instituition", ageOriginal->instituition);
    BSON_APPEND_UTF8 (&agent, "position", ageOriginal->position);
    BSON_APPEND_UTF8 (&agent, "role", ageOriginal->role);
    BSON_APPEND_UTF8 (&agent, "annotation", ageOriginal->annotation);
    bson_append_document_end(&activity, &agent);


    actOriginal = actOriginal->next;

    bson_append_document_end(&activities, &activity);
    answer = 0;
  }

  bson_append_array_end(&experiment, &activities);
  //até aqui
  bson_append_document_end(project, &experiment);
  /*
  * Print the document as a JSON string.
  */
  project_str = bson_as_json (project, NULL);
  printf ("\n\t%s\n\n", project_str);
  fprintf(log,"\n\t%s\n\n", project_str);
  bson_free (project_str);
  /*
  * Clean up allocated bson documents.
  */
  return project;
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
    printf("\n>>>>FILE NAME: %s", name);
    strcpy(nameExtraFile, name);
    strcat(nameExtraFile, ".created.txt");
    FILE *fp = fopen(nameExtraFile, "w+");
    if(!fp){
      printf("Unable to create file");
      exit(1);

    }
    // VERSÃO MONGOC
    printf("\n1.0");
  /* grab a gridfs handle in test prefixed by fs */
  gridfs = mongoc_client_get_gridfs (client, db_name, "fs", &error);
  assert (gridfs);

  printf("\n1.1");

  stream = mongoc_stream_file_new_for_path (name, O_RDONLY, 0);
      assert (stream);

      printf("\n1.3");

      opt.filename = name;

      /* the driver generates a file_id for you */
      file = mongoc_gridfs_create_file_from_stream (gridfs, stream, &opt);
      assert (file);

      printf("\n1.5");
      id.value_type = BSON_TYPE_INT32;
      id.value.v_int32 = 1;

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
    //  //getchar();
iov.iov_base = (void*) buf;
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
          //getchar();
         if (fwrite (iov.iov_base, 1, r, fp) != r) {
           printf("ERROR");
           //getchar();
            MONGOC_ERROR ("Failed to write to stdout. Exiting.\n");
            exit (1);
         }
      }
      fclose(fp);
      mongoc_stream_destroy (stream);
      mongoc_gridfs_file_destroy (file);

      ////////////////// LIST

      printf("\n\n COMEÇANDO AQUI!! 2");
      ////getchar();
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

      mongoc_gridfs_file_list_destroy (list);
      if(strcmp(fileName, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")!=0){
        counter=9;
      }

  }
return 1;
}

//tentativa sem busca sequencial. não funciona.
void GetDocuments2(mongoc_database_t *database, mongoc_collection_t *collection){
  const bson_t *doc, *doc2;
  char *str;
  bson_error_t error;
  char partial[3000];
  mongoc_cursor_t *cursor, *cursor2;
  bson_t *opts, *opts2;
  printf("\nquery0");
  printf("\nquery1");
  bson_t *query = bson_new ();
  opts = BCON_NEW ( "limit", BCON_INT64 (1),"sort", "{", "_id", BCON_INT32 (1), "}");

  printf("\nquery2");
  cursor = mongoc_collection_find_with_opts (collection, query, opts, NULL);
  printf("\nquery3");
  /*	while (*/mongoc_cursor_next (cursor, &doc);//) {
  //printf(">> loop 0.2");
  str = bson_as_json(doc, NULL);
  strncpy(partial, str + 22, 24);
  partial[24]='\0';
  printf("\n>>> %s", partial);
  //printf ("\n\npartial = %s\n", partial);
  if(oidNumbers == NULL){
    printf("\n\né null!ta sussa!");
    oidNumbers = add_oid(oidNumbers,partial);
  }
  //bson_free (str);
  //}

  //bson_destroy (query);
  //	mongoc_cursor_destroy (cursor);

  printf("\nquery4");
  printf("\nquery4");
  printf("\nquery4");
  opts2 = BCON_NEW ( "limit", BCON_INT64 (1),"sort", "{", "_id", BCON_INT32 (-1), "}");
  printf("\nquery5");
  cursor2 = mongoc_collection_find_with_opts (collection, query, opts2, NULL);
  printf("\nquery6");
  mongoc_cursor_next (cursor2, &doc2);
  if (mongoc_cursor_error (cursor2, &error)) {
    fprintf (stderr, "An error occurred: %s\n", error.message);
  }
  printf("\nquery7");
  printf("\nquery7");
  printf("\nquery7");
  char *str2 = {'\0'};
  strcpy(str2,bson_as_json(doc2, NULL));
  if(str2[0]== '\0'){
    printf("nul nçao [e bom");
  }
  printf("\nquery8");
  printf("\nquery8");
  printf("\nquery8");
  printf("\n>>> %s ", partial);
  printf("\nquery8");
  printf("\nquery8");
  printf("\nquery8");
  printf("\n>>> %s ", str2);

  strncpy(partial, str2 + 22, 24);
  partial[24]='\0';
  printf("\nquery9");
  printf("\nquery9");
  printf("\nquery9");
  printf("\nquery9");
  printf("\n>>> %s", partial);
  oidNumbers = add_oid(oidNumbers,partial);

  printf("\nquery9.1");
  printf("\nquery9.1");
  printf("\nquery9.1");
  printf("\nquery9.1");
  /* bson_free (str);
  bson_destroy (query);
  mongoc_cursor_destroy (cursor);
  bson_free (str2);
  mongoc_cursor_destroy (cursor2);*/
  printf("\nquery10");
  printf("\nquery10");
  printf("\nquery10");
  printf("\nquery10");

}
//tentativa com busca sequencial. não funciona.
void GetDocuments(mongoc_database_t *database, mongoc_collection_t *collection){
  const bson_t *doc;
  bson_t *query;
  char *str, partial[30];
  mongoc_cursor_t *cursor;

  printf("\nquery0");
  query = bson_new ();
  printf("\nquery1");
  cursor = mongoc_collection_find_with_opts (collection, query, NULL, NULL);
  printf("\nquery2");printf("\nquery2");printf("\nquery2");printf("\nquery2");printf("\nquery2");printf("\nquery2");printf("\nquery2");
  while (mongoc_cursor_next (cursor, &doc)) {
    //printf(">> loop 0.2");
    str = bson_as_json (doc, NULL);
    //printf ("\n\n%s\n", str);
    if(*str)
    strncpy(partial, str + 22, 24);
    partial[24]='\0';
    //printf ("\n\npartial = %s\n", partial);
    oidNumbers = add_oid(oidNumbers,partial);
    bson_free (str);
  }
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");
  printf("\n>> loop 0.3");

  bson_destroy (query);
  mongoc_cursor_destroy (cursor);

}

//inserção documento data
bson_t   *DATA_DOC(dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection, FILE *log , mongoc_client_t *client){

  dataFile *auxData = dataOriginal;
  oid *aux = oidNumbers;
  int result = 0;
  bson_t   *dataFile, dataFiles;
  char     *dataFile_str;
  bson_oid_t oid;

  bson_oid_init (&oid, NULL);
  dataFile = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  //precisa converter para string os números
  char str_data_id[15];
  sprintf(str_data_id, "%d", dataOriginal->id);

  char str_data_size[15];
  sprintf(str_data_size, "%d", dataOriginal->size);

  char str_data_machine_id[15];
  sprintf(str_data_machine_id, "%d", dataOriginal->machine_id);

  dataFile = BCON_NEW (
    "id", str_data_id,
    "name", dataOriginal->name,
    "description", dataOriginal->description,
    "localization", dataOriginal->localization,
    "annotation", dataOriginal->annotation,
    "size", str_data_size,
    "insertion_date",dataOriginal->insertion_date,
    "machine_id", str_data_machine_id,
    "type", dataOriginal->type

  );

  Convert(auxData->name, "model10", client);

  //lista de ids dos arquivos brutos. não funciona
  /*
  printf("\nFILE NAME:  %s",auxData->name);*/
  //result = Convert(auxData->name, collection, database); DESCOMENTAR ESSA LINHA PARA INSERIR DADOS BRUTOS
  /*printf("\n file: %s", auxData->name);
  GetDocuments(database,collection); // NAO FUNCIONA - INSERÇÃO DOS IDS DOS DADOS BRUTOS
  printf("voltou0");
  printf("voltou0");
  printf("voltou0");
  aux = oidNumbers;
  char str_id[36];
  uint32_t    i;
  char        buf[16];
  const       char *key;
  size_t keylen;
  BSON_APPEND_ARRAY_BEGIN(dataFile, "data_file_id", &dataFiles);
  while(aux != NULL){

  //printf("voltou1");
  if(!aux->posto){
  sprintf(str_id, "%s", aux->oid);
  //printf("\n%s\n", aux->oid);
  aux->posto = true;
  keylen = bson_uint32_to_string (i, &key, buf, sizeof buf);
  bson_append_utf8 (&dataFiles, key, (int) keylen, str_id, -1);
  i++;
}
aux = aux->next;
//printf("aux");
////getchar();
if(aux == NULL){

//printf("tá null!");
}
}
printf("saiu!! ");
bson_append_array_end(dataFile, &dataFiles);*/
/*
* Print the document as a JSON string.
*/

/*
* Clean up allocated bson documents.
*/
dataFile_str = bson_as_json (dataFile, NULL);
printf ("\n\t%s\n\n", dataFile_str);
fprintf(log,"\n\t%s\n\n", dataFile_str);
bson_free (dataFile_str);
return dataFile;
}


bson_t   *PROVIDER_DOC_S(provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log){
  dataFile *aux = macOriginal->dataFiles;
  bson_t   *provider, cluster, machine, dataFiles;
  char     *provider_str;
  bson_oid_t oid;

  //inicializa documento
  bson_oid_init (&oid, NULL);
  provider = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  //conversão para strings é necessária
  char str_clu_id[15];
  sprintf(str_clu_id, "%d", cluOriginal->id);

  char str_clu_number_machines[15];
  sprintf(str_clu_number_machines, "%d", cluOriginal->number_machines);

  char str_pro_id[15];
  sprintf(str_pro_id, "%d", proOriginal->id);

  char str_pro_localization_id[15];
  sprintf(str_pro_localization_id, "%d", proOriginal->localization_id);

  char str_mac_id[15];
  sprintf(str_mac_id, "%d", macOriginal->id);

  char str_mac_localization_id[15];
  sprintf(str_mac_localization_id, "%d", macOriginal->localization_id);

  char str_mac_ip[36];
  sprintf(str_mac_ip, "%ld", macOriginal->ip);

  char str_mac_cpu[15];
  sprintf(str_mac_cpu, "%d", macOriginal->cpu);

  char str_mac_ram_memory[15];
  sprintf(str_mac_ram_memory, "%d", macOriginal->ram_memory);

  char str_mac_disk[36];
  sprintf(str_mac_disk, "%ld", macOriginal->disk);

  char str_mac_price[36];
  sprintf(str_mac_price, "%ld", macOriginal->price);

  char str_mac_price_type[36];
  sprintf(str_mac_price_type, "%ld", macOriginal->price_type);

  provider = BCON_NEW (
    "id", str_pro_id,
    "isProvider", "true",
    "name", proOriginal->name,
    "url", proOriginal->url,
    "description", proOriginal->description,
    "localization_id", str_pro_localization_id,
    "localization_region", proOriginal->localization_region,
    "localization_zone", proOriginal->localization_zone
  );

  BSON_APPEND_DOCUMENT_BEGIN(provider, "cluster", &cluster);
  BSON_APPEND_UTF8 (&cluster, "id", str_clu_id);
  BSON_APPEND_UTF8 (&cluster, "name", cluOriginal->name);
  BSON_APPEND_UTF8 (&cluster, "number_machines", str_clu_number_machines);
  BSON_APPEND_UTF8 (&cluster, "description", cluOriginal->description);

  BSON_APPEND_DOCUMENT_BEGIN(&cluster, "machine", &machine);
  BSON_APPEND_UTF8 (&machine, "id", str_mac_id);
  BSON_APPEND_UTF8 (&machine, "hostname", macOriginal->hostname);
  BSON_APPEND_UTF8 (&machine, "ip", str_mac_ip);
  BSON_APPEND_UTF8 (&machine, "type", macOriginal->type);
  BSON_APPEND_UTF8 (&machine, "operational_system", macOriginal->operational_system);
  BSON_APPEND_UTF8 (&machine, "cpu", str_mac_cpu);
  BSON_APPEND_UTF8 (&machine, "ram_memory", str_mac_ram_memory);
  BSON_APPEND_UTF8 (&machine, "disk", str_mac_disk);
  BSON_APPEND_UTF8 (&machine, "disk_type", macOriginal->disk_type);
  BSON_APPEND_UTF8 (&machine, "localization", macOriginal->localization);
  BSON_APPEND_UTF8 (&machine, "price", str_mac_price);
  BSON_APPEND_UTF8 (&machine, "price_type", str_mac_price_type);
  BSON_APPEND_UTF8 (&machine, "localization_id", str_mac_localization_id);
  BSON_APPEND_UTF8 (&machine, "localization_region", macOriginal->localization_region);
  BSON_APPEND_UTF8 (&machine, "localization_zone", macOriginal->localization_zone);
  /*char str_mac_dataFiles_id[36];
  uint32_t    i;
  char        buf[16];
  const       char *key;
  size_t      keylen;
  BSON_APPEND_ARRAY_BEGIN(&machine, "data_file_id", &dataFiles);
  while(aux != NULL){ //insere o id da lista de arquivos na máquina
  sprintf(str_mac_dataFiles_id, "%d", aux->id);
  keylen = bson_uint32_to_string (i, &key, buf, sizeof buf);
  bson_append_utf8 (&dataFiles, key, (int) keylen, str_mac_dataFiles_id, -1);

  i++;
  aux = aux->next;
}

bson_append_array_end(&machine, &dataFiles);*/
bson_append_document_end(&cluster, &machine);

bson_append_document_end(provider, &cluster);
/*
* Print the document as a JSON string.
*/
provider_str = bson_as_json (provider, NULL);
printf ("\n\t%s\n\n", provider_str);
fprintf(log,"\n\t%s\n\n", provider_str);
bson_free (provider_str);
/*
* Clean up allocated bson documents.
*/
return provider;
}



bson_t   *PROJECT_DOC_S(project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, FILE *log){
  activity *actOriginal = activitys;
  const char* command1_input[] = {"3"}; //arquivos usados pelos comandos. ver na main qual é qual
  const char* command1_output[] = {"9"}; //arquivos usados pelos comandos. ver na main qual é qual

  const char* command2_input[] = {"1"};
  const char* command2_output[] = {"2"};

  const char* command3_input[] = {"2","9"};
  const char* command3_output[] = {"4"};

  const char* command4_input[] = {"4"};
  const char* command4_output[] = {"5"};

  const char* command5_input[] = {"5"};
  const char* command5_output[] = {"6"};

  const char* command6_input[] = {"6","7"};
  const char* command6_output[] = {"8"};

  bson_t   *project, experiment, agent, child;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;

  bson_oid_init (&oid, NULL);
  project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  char str_pro_id[15];
  sprintf(str_pro_id, "%d", proOriginal->id);

  char str_exp_id[15];
  sprintf(str_exp_id, "%d", expOriginal->id);

  char str_exp_version[15];
  sprintf(str_exp_version, "%d", expOriginal->version);

  char str_exp_execution_time[15];
  sprintf(str_exp_execution_time, "%d", expOriginal->execution_time);

  char str_exp_execution_cost[24];
  sprintf(str_exp_execution_cost, "%f", expOriginal->execution_cost);

  char str_act_execution_status[15];
  sprintf(str_act_execution_status, "%d", actOriginal->execution_status);

  project = BCON_NEW (
    "id", str_pro_id,
    "isProject", "true",
    "name", proOriginal->name,
    "description", proOriginal->description,
    "inst_funders", proOriginal->inst_funders,
    "inst_participants", proOriginal->inst_participants,
    "coordinator", proOriginal->coordinator,
    "start_date", proOriginal->start_date,
    "end_date", proOriginal->end_date
  );

  BSON_APPEND_DOCUMENT_BEGIN(project, "experiment", &experiment);
  BSON_APPEND_UTF8 (&experiment, "id", str_exp_id);
  BSON_APPEND_UTF8 (&experiment, "name", expOriginal->name);
  BSON_APPEND_UTF8 (&experiment, "description", expOriginal->description);
  BSON_APPEND_UTF8 (&experiment, "local", expOriginal->local);
  BSON_APPEND_UTF8 (&experiment, "start_date", expOriginal->start_date);
  BSON_APPEND_UTF8 (&experiment, "end_date", expOriginal->end_date);
  BSON_APPEND_UTF8 (&experiment, "annotation", expOriginal->annotation);
  BSON_APPEND_UTF8 (&experiment, "version", str_exp_version);
  BSON_APPEND_UTF8 (&experiment, "version_date", expOriginal->version_date);
  BSON_APPEND_UTF8 (&experiment, "execution_time", str_exp_execution_time);
  BSON_APPEND_UTF8 (&experiment, "execution_cost", str_exp_execution_cost);
  int y = 0;

  char str_age_id[15];
  sprintf(str_age_id, "%d", ageOriginal->id);

  bson_t activity, activities, child2;
  BSON_APPEND_ARRAY_BEGIN(&experiment, "activity", &activities);
  //comandos daqui
  while(actOriginal->next !=NULL){

    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);

    //BSON_APPEND_DOCUMENT_BEGIN(&activities, "", &activity);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;


    //for (y = 0; y < sizeof actOriginal->program_name / sizeof (char *); ++y) {
    keylen = bson_uint32_to_string (y, &key, buf, sizeof buf);
    bson_append_document_begin (&activities, key, (int) keylen, &activity);
    BSON_APPEND_UTF8 (&activity, "id", str_act_id);
    BSON_APPEND_UTF8 (&activity, "name", actOriginal->name);
    BSON_APPEND_UTF8 (&activity, "program_name", actOriginal->program_name);
    BSON_APPEND_UTF8 (&activity, "program_version", actOriginal->program_version);
    BSON_APPEND_UTF8 (&activity, "command_line", actOriginal->command_line);
    BSON_APPEND_UTF8 (&activity, "start_date", actOriginal->start_date);
    BSON_APPEND_UTF8 (&activity, "start_hour", actOriginal->start_hour);
    BSON_APPEND_UTF8 (&activity, "end_date", actOriginal->end_date);
    BSON_APPEND_UTF8 (&activity, "end_hour", actOriginal->end_hour);
    BSON_APPEND_UTF8 (&activity, "execution_status", str_act_execution_status);
    //}
    // USED FILES
    char str_mac_dataFiles_id[36];

    BSON_APPEND_ARRAY_BEGIN(&activity, "files", &child);
    if(actOriginal->id == 1){
      for(i = 0; i< sizeof command1_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command1_input[i], -1);

      }
      for(i = 0; i< sizeof command1_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command1_output[i], -1);

      }
    }
    if(actOriginal->id == 2){
      for(i = 0; i< sizeof command2_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command2_input[i], -1);

      }
      for(i = 0; i< sizeof command2_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command2_output[i], -1);

      }
    }
    if(actOriginal->id == 3){
      for(i = 0; i< sizeof command3_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command3_input[i], -1);

      }
      for(i = 0; i< sizeof command3_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command3_output[i], -1);

      }
    }
    if(actOriginal->id == 4){
      for(i = 0; i< sizeof command4_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command4_input[i], -1);

      }
      for(i = 0; i< sizeof command4_output/sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command4_output[i], -1);

      }
    }
    if(actOriginal->id == 5){
      for(i = 0; i< sizeof command5_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command5_input[i], -1);

      }
      for(i = 0; i< sizeof command5_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command5_output[i], -1);

      }
    }
    if(actOriginal->id == 6){
      for(i = 0; i< sizeof command6_input /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command6_input[i], -1);

      }
      for(i = 0; i< sizeof command6_output /sizeof(char *); ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child, key, (int) keylen, command6_output[i], -1);

      }
    }

    bson_append_array_end(&activity, &child);

    // END USED FILES
    BSON_APPEND_DOCUMENT_BEGIN(&activity, "agent", &agent);
    BSON_APPEND_UTF8 (&agent, "id", str_age_id);
    BSON_APPEND_UTF8 (&agent, "name", ageOriginal->name);
    BSON_APPEND_UTF8 (&agent, "login", ageOriginal->login);
    BSON_APPEND_UTF8 (&agent, "instituition", ageOriginal->instituition);
    BSON_APPEND_UTF8 (&agent, "position", ageOriginal->position);
    BSON_APPEND_UTF8 (&agent, "role", ageOriginal->role);
    BSON_APPEND_UTF8 (&agent, "annotation", ageOriginal->annotation);
    bson_append_document_end(&activity, &agent);


    actOriginal = actOriginal->next;

    bson_append_document_end(&activities, &activity);
    answer = 0;
  }

  bson_append_array_end(&experiment, &activities);
  //até aqui
  bson_append_document_end(project, &experiment);
  /*
  * Print the document as a JSON string.
  */
  project_str = bson_as_json (project, NULL);
  printf ("\n\t%s\n\n", project_str);
  fprintf(log,"\n\t%s\n\n", project_str);
  bson_free (project_str);
  /*
  * Clean up allocated bson documents.
  */
  return project;
}
//inserção documento data
bson_t   *DATA_DOC_S(dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection, FILE *log, mongoc_client_t *client){

  dataFile *auxData = dataOriginal;
  oid *aux = oidNumbers;
  int result = 0;
  bson_t   *dataFile, dataFiles;
  char     *dataFile_str;
  bson_oid_t oid;

  bson_oid_init (&oid, NULL);
  dataFile = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  //precisa converter para string os números
  char str_data_id[15];
  sprintf(str_data_id, "%d", dataOriginal->id);

  char str_data_size[15];
  sprintf(str_data_size, "%d", dataOriginal->size);

  char str_data_machine_id[15];
  sprintf(str_data_machine_id, "%d", dataOriginal->machine_id);

  dataFile = BCON_NEW (
    "id", str_data_id,
    "isDataFile", "true",
    "name", dataOriginal->name,
    "description", dataOriginal->description,
    "localization", dataOriginal->localization,
    "annotation", dataOriginal->annotation,
    "size", str_data_size,
    "insertion_date",dataOriginal->insertion_date,
    "machine_id", str_data_machine_id,
    "type", dataOriginal->type

  );


  Convert(auxData->name, "model11", client);
  //lista de ids dos arquivos brutos. não funciona
  /*
  printf("\nFILE NAME:  %s",auxData->name);*/
  //result = Convert(auxData->name, collection, database); DESCOMENTAR ESSA LINHA PARA INSERIR DADOS BRUTOS
  /*printf("\n file: %s", auxData->name);
  GetDocuments(database,collection); // NAO FUNCIONA - INSERÇÃO DOS IDS DOS DADOS BRUTOS
  printf("voltou0");
  printf("voltou0");
  printf("voltou0");
  aux = oidNumbers;
  char str_id[36];
  uint32_t    i;
  char        buf[16];
  const       char *key;
  size_t keylen;
  BSON_APPEND_ARRAY_BEGIN(dataFile, "data_file_id", &dataFiles);
  while(aux != NULL){

  //printf("voltou1");
  if(!aux->posto){
  sprintf(str_id, "%s", aux->oid);
  //printf("\n%s\n", aux->oid);
  aux->posto = true;
  keylen = bson_uint32_to_string (i, &key, buf, sizeof buf);
  bson_append_utf8 (&dataFiles, key, (int) keylen, str_id, -1);
  i++;
}
aux = aux->next;
//printf("aux");
////getchar();
if(aux == NULL){

//printf("tá null!");
}
}
printf("saiu!! ");
bson_append_array_end(dataFile, &dataFiles);*/
/*
* Print the document as a JSON string.
*/

/*
* Clean up allocated bson documents.
*/
dataFile_str = bson_as_json (dataFile, NULL);
printf ("\n\t%s\n\n", dataFile_str);
fprintf(log,"\n\t%s\n\n", dataFile_str);
bson_free (dataFile_str);
return dataFile;
}

bson_t   *SINGLE_DOC_2(project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, dataFile *dataOriginal, FILE *log){
  activity *actOriginal = activitys;
  dataFile *auxFiles = dataOriginal;

  int command1_input[1] = {3}; //arquivos usados pelos comandos. ver na main qual é qual
  int command1_output[1] = {9}; //arquivos usados pelos comandos. ver na main qual é qual

  int command2_input[1] = {1};
  int command2_output[1] = {2};

  int command3_input[2] = {2,9};
  int command3_output[1] = {4};

  int command4_input[1] = {4};
  int command4_output[1] = {5};

  int command5_input[2] = {5};
  int command5_output[1] = {6};

  int command6_input[2] = {6,7};
  int command6_output[1] = {8};

  bson_t   *project, experiment, agent, child;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;

  bson_oid_init (&oid, NULL);
  project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

  char str_pro_id[15];
  sprintf(str_pro_id, "%d", proOriginal->id);

  char str_exp_id[15];
  sprintf(str_exp_id, "%d", expOriginal->id);

  char str_exp_version[15];
  sprintf(str_exp_version, "%d", expOriginal->version);

  char str_exp_execution_time[15];
  sprintf(str_exp_execution_time, "%d", expOriginal->execution_time);

  char str_exp_execution_cost[24];
  sprintf(str_exp_execution_cost, "%f", expOriginal->execution_cost);

  char str_act_execution_status[15];
  sprintf(str_act_execution_status, "%d", actOriginal->execution_status);

  project = BCON_NEW (
    "id", str_pro_id,
    "name", proOriginal->name,
    "description", proOriginal->description,
    "inst_funders", proOriginal->inst_funders,
    "inst_participants", proOriginal->inst_participants,
    "coordinator", proOriginal->coordinator,
    "start_date", proOriginal->start_date,
    "end_date", proOriginal->end_date
  );

  BSON_APPEND_DOCUMENT_BEGIN(project, "experiment", &experiment);
  BSON_APPEND_UTF8 (&experiment, "id", str_exp_id);
  BSON_APPEND_UTF8 (&experiment, "name", expOriginal->name);
  BSON_APPEND_UTF8 (&experiment, "description", expOriginal->description);
  BSON_APPEND_UTF8 (&experiment, "local", expOriginal->local);
  BSON_APPEND_UTF8 (&experiment, "start_date", expOriginal->start_date);
  BSON_APPEND_UTF8 (&experiment, "end_date", expOriginal->end_date);
  BSON_APPEND_UTF8 (&experiment, "annotation", expOriginal->annotation);
  BSON_APPEND_UTF8 (&experiment, "version", str_exp_version);
  BSON_APPEND_UTF8 (&experiment, "version_date", expOriginal->version_date);
  BSON_APPEND_UTF8 (&experiment, "execution_time", str_exp_execution_time);
  BSON_APPEND_UTF8 (&experiment, "execution_cost", str_exp_execution_cost);

  int y = 0;

  char str_age_id[15];
  sprintf(str_age_id, "%d", ageOriginal->id);

  bson_t activity, activities, child2, dataFile, dataFiles;
  BSON_APPEND_ARRAY_BEGIN(&experiment, "activity", &activities);
  //comandos daqui
  while(actOriginal !=NULL){

    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);

    //BSON_APPEND_DOCUMENT_BEGIN(&activities, "", &activity);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;


    //for (y = 0; y < sizeof actOriginal->program_name / sizeof (char *); ++y) {
    keylen = bson_uint32_to_string (y, &key, buf, sizeof buf);
    bson_append_document_begin (&activities, key, (int) keylen, &activity);
    BSON_APPEND_UTF8 (&activity, "id", str_act_id);
    BSON_APPEND_UTF8 (&activity, "name", actOriginal->name);
    BSON_APPEND_UTF8 (&activity, "program_name", actOriginal->program_name);
    BSON_APPEND_UTF8 (&activity, "program_version", actOriginal->program_version);
    BSON_APPEND_UTF8 (&activity, "command_line", actOriginal->command_line);
    BSON_APPEND_UTF8 (&activity, "start_date", actOriginal->start_date);
    BSON_APPEND_UTF8 (&activity, "start_hour", actOriginal->start_hour);
    BSON_APPEND_UTF8 (&activity, "end_date", actOriginal->end_date);
    BSON_APPEND_UTF8 (&activity, "end_hour", actOriginal->end_hour);
    BSON_APPEND_UTF8 (&activity, "execution_status", str_act_execution_status);
    //}
    // USED FILES
    char str_mac_dataFiles_id[36];

    char        buf2[16];
    const       char *key2;
    size_t      keylen2;
    if(actOriginal->id == 1){
      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command1_input[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization",auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command1_output[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
    }
    else if(actOriginal->id == 2){
      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command2_input[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name",auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command2_output[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d",auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization",auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
    }
    else if(actOriginal->id == 3){
      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n -----> TRES \n", auxFiles->id);
        if(auxFiles->id == command3_input[0] || auxFiles->id == command3_input[1]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);
          bson_append_document_end(&dataFiles, &dataFile);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d OUTPUT\n", auxFiles->id);
        if(auxFiles->id == command3_output[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description",auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
    }
    else if(actOriginal->id == 4){
      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n----> QUATRO \n", auxFiles->id);
        if(auxFiles->id == command4_input[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation",auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command4_output[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
    }
    else if(actOriginal->id == 5){
      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command5_input[0] || auxFiles->id == command5_input[1]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);
          bson_append_document_end(&dataFiles, &dataFile);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command5_output[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
    }
    else if(actOriginal->id == 6){
      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command6_input[0] || auxFiles->id == command6_input[1]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name",auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);
          bson_append_document_end(&dataFiles, &dataFile);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxFiles = dataOriginal;
      while(auxFiles != NULL){
        printf("While \n: auxFiles->id %d \n", auxFiles->id);
        if(auxFiles->id == command6_output[0]){
          printf("achei!");
          char str_data_id[15];
          sprintf(str_data_id, "%d", auxFiles->id);
          char str_data_size[15];
          sprintf(str_data_size, "%d", auxFiles->size);
          char str_data_machine_id[15];
          sprintf(str_data_machine_id, "%d", auxFiles->machine_id);
          keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
          bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
          BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
          BSON_APPEND_UTF8 (&dataFile,"name", auxFiles->name);
          BSON_APPEND_UTF8 (&dataFile, "description", auxFiles->description);
          BSON_APPEND_UTF8 (&dataFile,"localization", auxFiles->localization);
          BSON_APPEND_UTF8 (&dataFile,"annotation", auxFiles->annotation);
          BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
          BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxFiles->insertion_date);
          BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
          BSON_APPEND_UTF8 (&dataFile,"type", auxFiles->type);

        }
        auxFiles = auxFiles->next;
      }
      bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
    }
    printf("sai2!\n");
    BSON_APPEND_DOCUMENT_BEGIN(&activity, "agent", &agent);
    BSON_APPEND_UTF8 (&agent, "id", str_age_id);
    BSON_APPEND_UTF8 (&agent, "name", ageOriginal->name);
    BSON_APPEND_UTF8 (&agent, "login", ageOriginal->login);
    BSON_APPEND_UTF8 (&agent, "instituition", ageOriginal->instituition);
    BSON_APPEND_UTF8 (&agent, "position", ageOriginal->position);
    BSON_APPEND_UTF8 (&agent, "role", ageOriginal->role);
    BSON_APPEND_UTF8 (&agent, "annotation", ageOriginal->annotation);
    bson_append_document_end(&activity, &agent);


    actOriginal = actOriginal->next;

    bson_append_document_end(&activities, &activity);
    answer = 0;
  }

  bson_append_array_end(&experiment, &activities);
  //até aqui
  bson_append_document_end(project, &experiment);
  /*
  * Print the document as a JSON string.
  */
  project_str = bson_as_json (project, NULL);
  printf ("\n\t%s\n\n", project_str);
  fprintf(log,"\n\t%s\n\n", project_str);
  bson_free (project_str);
  /*
  * Clean up allocated bson documents.
  */
  return project;
}
