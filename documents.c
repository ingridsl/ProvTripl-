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

bson_t   *PROVIDER_DOC(bool index, provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log){
  //parametros
  dataFile *aux = macOriginal->dataFiles;
  bson_t   *provider, cluster, machine, dataFiles;
  char     *provider_str;
  bson_oid_t oid;

  //inicializa documento com index
  if(index){
  bson_oid_init (&oid, NULL);
  provider = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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

bson_t   *PROJECT_DOC(bool index, project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, FILE *log){
  activity *actOriginal = activitys;
  bson_t   *project, experiment, agent;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;

  if(index){
    bson_oid_init (&oid, NULL);
    project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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

  bson_t activity, activities,child1, child2;
  BSON_APPEND_ARRAY_BEGIN(&experiment, "activity", &activities);
  //comandos daqui
  while(actOriginal->next !=NULL){

    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;

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
    // USED FILES
    char str_mac_dataFiles_id[36];

    BSON_APPEND_ARRAY_BEGIN(&activity, "input_files", &child1);
      for(i = 0; i < 2; ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        if(strlen(actOriginal->command_input[i])>0)
          bson_append_utf8(&child1, key, (int) keylen, actOriginal->command_input[i], -1);

      }
    bson_append_array_end(&activity, &child1);
    BSON_APPEND_ARRAY_BEGIN(&activity, "output_files", &child2);
      for(i = 0; i< 1; ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child2, key, (int) keylen, actOriginal->command_output[i], -1);

      }
    bson_append_array_end(&activity, &child2);


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

//inserção documento data
bson_t   *DATA_DOC(bool index, char databaseName[N], dataFile *dataOriginal, FILE *log , mongoc_client_t *client){

  dataFile *auxData = dataOriginal;
  oid *aux = oidNumbers;
  int result = 0;
  bson_t   *dataFile, dataFiles;
  char     *dataFile_str;
  bson_oid_t oid;

  if(index){
    bson_oid_init (&oid, NULL);
    dataFile = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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
  printf("\n FILE = %s", auxData->name);
  Convert(auxData->name, databaseName, client);

dataFile_str = bson_as_json (dataFile, NULL);
printf ("\n\t%s\n\n", dataFile_str);
fprintf(log,"\n\t%s\n\n", dataFile_str);
bson_free (dataFile_str);
return dataFile;
}


bson_t   *PROVIDER_DOC_S(bool index, provider *proOriginal, cluster *cluOriginal, machine *macOriginal, FILE *log){
  dataFile *aux = macOriginal->dataFiles;
  bson_t   *provider, cluster, machine, dataFiles;
  char     *provider_str;
  bson_oid_t oid;

  //inicializa documento
  if(index){
    bson_oid_init (&oid, NULL);
    provider = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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

bson_t   *PROJECT_DOC_S(bool index, project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, FILE *log){
  activity *actOriginal = activitys;
  bson_t   *project, experiment, agent;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;

  if(index){
    bson_oid_init (&oid, NULL);
    project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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

  bson_t activity, activities, child1, child2;
  BSON_APPEND_ARRAY_BEGIN(&experiment, "activity", &activities);
  //comandos daqui
  while(actOriginal->next !=NULL){

    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;
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

    BSON_APPEND_ARRAY_BEGIN(&activity, "input_files", &child1);
      for(i = 0; i < 2; ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        if(strlen(actOriginal->command_input[i])>0)
          bson_append_utf8(&child1, key, (int) keylen, actOriginal->command_input[i], -1);

      }
    bson_append_array_end(&activity, &child1);
    BSON_APPEND_ARRAY_BEGIN(&activity, "output_files", &child2);
      for(i = 0; i< 1; ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child2, key, (int) keylen, actOriginal->command_output[i], -1);

      }
    bson_append_array_end(&activity, &child2);

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
bson_t   *DATA_DOC_S(bool index, char *databaseName, dataFile *dataOriginal, FILE *log, mongoc_client_t *client){

  dataFile *auxData = dataOriginal;
  oid *aux = oidNumbers;
  int result = 0;
  bson_t   *dataFile, dataFiles;
  char     *dataFile_str;
  bson_oid_t oid;

  if(index){
    bson_oid_init (&oid, NULL);
    dataFile = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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

  Convert(auxData->name, databaseName, client);

/*
* Clean up allocated bson documents.
*/
dataFile_str = bson_as_json (dataFile, NULL);
printf ("\n\t%s\n\n", dataFile_str);
fprintf(log,"\n\t%s\n\n", dataFile_str);
bson_free (dataFile_str);
return dataFile;
}

bson_t   *SINGLE_DOC_2(bool index, char *databaseName, project *proOriginal, experiment *expOriginal, activity *activitys, agent *ageOriginal, dataFile *dataOriginal, FILE *log, mongoc_client_t *client){
  activity *actOriginal = activitys;
  dataFile *auxData = dataOriginal;
  char str_mac_dataFiles_id[36];
  char  buf2[16];
  const char *key2;
  size_t  keylen2;
  char filesId[2];
  bson_t   *project, experiment, agent, child;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;
  if(index){
    bson_oid_init (&oid, NULL);
    project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
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

  bson_t activity, activities,child1, child2, dataFile, dataFiles;
  BSON_APPEND_ARRAY_BEGIN(&experiment, "activity", &activities);
  //comandos daqui
  while(actOriginal !=NULL){
    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);
    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;
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

      //input files
      BSON_APPEND_ARRAY_BEGIN(&activity, "inputFiles", &dataFiles);
      auxData = dataOriginal;
      while(auxData != NULL){
        sprintf(filesId, "%d", auxData->id);
        for(i = 0; i < 2 ; i++){
          if(strlen(actOriginal->command_input[i])>0){
            if(strcmp(filesId, actOriginal->command_input[i])== 0){
              char str_data_id[15];
              sprintf(str_data_id, "%d", auxData->id);
              char str_data_size[15];
              sprintf(str_data_size, "%d", auxData->size);
              char str_data_machine_id[15];
              sprintf(str_data_machine_id, "%d", auxData->machine_id);
              keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
              bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
              BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
              BSON_APPEND_UTF8 (&dataFile,"name", auxData->name);
              BSON_APPEND_UTF8 (&dataFile, "description", auxData->description);
              BSON_APPEND_UTF8 (&dataFile,"localization",auxData->localization);
              BSON_APPEND_UTF8 (&dataFile,"annotation", auxData->annotation);
              BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
              BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxData->insertion_date);
              BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
              BSON_APPEND_UTF8 (&dataFile,"type", auxData->type);
              bson_append_document_end(&dataFiles, &dataFile);
            }
          }
        }
        auxData = auxData->next;
      }
      //bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of input files
      //output files
      BSON_APPEND_ARRAY_BEGIN(&activity, "outputFiles", &dataFiles);
      auxData = dataOriginal;
      while(auxData != NULL){
        sprintf(filesId, "%d", auxData->id);
        for(i = 0; i<2; i++){
          if(strlen(actOriginal->command_output[i])){
            if(strcmp(filesId,actOriginal->command_output[i]) == 0){
              printf("achei!");
              char str_data_id[15];
              sprintf(str_data_id, "%d", auxData->id);
              char str_data_size[15];
              sprintf(str_data_size, "%d", auxData->size);
              char str_data_machine_id[15];
              sprintf(str_data_machine_id, "%d", auxData->machine_id);
              keylen2 = bson_uint32_to_string (y, &key2, buf2, sizeof buf2);
              bson_append_document_begin (&dataFiles, key2, (int) keylen2, &dataFile);
              BSON_APPEND_UTF8 (&dataFile,"id", str_data_id);
              BSON_APPEND_UTF8 (&dataFile,"name", auxData->name);
              BSON_APPEND_UTF8 (&dataFile, "description", auxData->description);
              BSON_APPEND_UTF8 (&dataFile,"localization", auxData->localization);
              BSON_APPEND_UTF8 (&dataFile,"annotation", auxData->annotation);
              BSON_APPEND_UTF8 (&dataFile,"size", str_data_size);
              BSON_APPEND_UTF8 (&dataFile,"insertion_date",auxData->insertion_date);
              BSON_APPEND_UTF8 (&dataFile,"machine_id", str_data_machine_id);
              BSON_APPEND_UTF8 (&dataFile,"type", auxData->type);
              bson_append_document_end(&dataFiles, &dataFile);
            }
          }
        }
        auxData = auxData->next;
      }
      //bson_append_document_end(&dataFiles, &dataFile);
      bson_append_array_end(&activity, &dataFiles);
      // end of output files
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

  auxData = dataOriginal;
  while(auxData!=NULL){
    Convert(auxData->name, databaseName, client);
    auxData = auxData->next;
  }
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


bson_t   *PROJECT_DOC_3(bool index, project *proOriginal, FILE *log){

  bson_t   *project;
  char     *project_str;
  bson_oid_t oid;
  int answer = 0;

  if(index){
    bson_oid_init (&oid, NULL);
    project = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
  char str_pro_id[15];
  sprintf(str_pro_id, "%d", proOriginal->id);


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

bson_t   *EXPERIMENT_DOC_3(bool index, experiment *expOriginal, FILE *log){

  bson_t   *experiment;
  char     *experiment_str;
  bson_oid_t oid;
  int answer = 0;
  if(index){
    bson_oid_init (&oid, NULL);
    experiment = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
  char str_exp_id[15];
  sprintf(str_exp_id, "%d", expOriginal->id);

  char str_exp_version[15];
  sprintf(str_exp_version, "%d", expOriginal->version);

  char str_exp_execution_time[15];
  sprintf(str_exp_execution_time, "%d", expOriginal->execution_time);

  char str_exp_execution_cost[24];
  sprintf(str_exp_execution_cost, "%f", expOriginal->execution_cost);

  char str_exp_project_id[24];
  sprintf(str_exp_project_id, "%d", expOriginal->project_id);

  experiment = BCON_NEW (
    "id", str_exp_id,
    "name", expOriginal->name,
    "description", expOriginal->description,
    "local", expOriginal->local,
    "start_date", expOriginal->start_date,
    "end_date", expOriginal->end_date,
    "annotation", expOriginal->annotation,
    "version", str_exp_version,
    "version_date", expOriginal->version_date,
    "execution_time", str_exp_execution_time,
    "execution_cost", str_exp_execution_cost,
    "project_id",str_exp_project_id

  );

  experiment_str = bson_as_json (experiment, NULL);
  printf ("\n\t%s\n\n", experiment_str);
  fprintf(log,"\n\t%s\n\n", experiment_str);
  bson_free (experiment_str);
  /*
  * Clean up allocated bson documents.
  */
  return experiment;
}

bson_t   *ACTIVITY_DOC_3(bool index, activity *activitys, FILE *log){
  activity *actOriginal = activitys;
  bson_t   child1, child2, *activity;
  char * activity_str;
  bson_oid_t oid;
  int answer = 0;

  if(index){
    bson_oid_init (&oid, NULL);
    activity = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }
  int y = 0;
  //comandos daqui

    char str_act_id[15];
    sprintf(str_act_id, "%d", actOriginal->id);
    char str_act_experiment_id[15];
    sprintf(str_act_experiment_id, "%d", actOriginal->experiment_id);
    char str_act_agent_id[15];
    sprintf(str_act_agent_id, "%d", actOriginal->agent_id);


      char str_act_execution_status[15];
      sprintf(str_act_execution_status, "%d", actOriginal->execution_status);

    //BSON_APPEND_DOCUMENT_BEGIN(&activities, "", &activity);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;
    activity = BCON_NEW(
        "id", str_act_id,
        "name", actOriginal->name,
        "program_name", actOriginal->program_name,
        "program_version", actOriginal->program_version,
        "command_line", actOriginal->command_line,
        "start_date", actOriginal->start_date,
        "start_hour", actOriginal->start_hour,
        "end_date", actOriginal->end_date,
        "end_hour", actOriginal->end_hour,
        "execution_status", str_act_execution_status,
        "experiment_id", str_act_experiment_id,
        "agent_id", str_act_agent_id

    );
    // USED FILES
    char str_mac_dataFiles_id[36];

    BSON_APPEND_ARRAY_BEGIN(activity, "input_files", &child1);
      for(i = 0; i < 2; ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        if(strlen(actOriginal->command_input[i])>0)
          bson_append_utf8(&child1, key, (int) keylen, actOriginal->command_input[i], -1);

      }
    bson_append_array_end(activity, &child1);
    BSON_APPEND_ARRAY_BEGIN(activity, "output_files", &child2);
      for(i = 0; i< 1; ++i){
        keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
        bson_append_utf8(&child2, key, (int) keylen, actOriginal->command_output[i], -1);

      }
    bson_append_array_end(activity, &child2);

    actOriginal = actOriginal->next;
    answer = 0;


    activity_str = bson_as_json (activity, NULL);
    printf ("\n\t%s\n\n", activity_str);
    fprintf(log,"\n\t%s\n\n", activity_str);
    bson_free (activity_str);
    /*
    * Clean up allocated bson documents.
    */
  //}
return activity;
}

bson_t   *AGENT_DOC_3(bool index, mongoc_database_t *db, agent *ageOriginal, FILE *log){
  bson_t   *agent, child;
  char     *agent_str;
  int answer = 0;
  bson_oid_t oid;
  mongoc_client_t *client;

  //query = bson_new ();
    // BSON_APPEND_UTF8 (query, "hello", "world");
  /*if(index){
    printf("INDEXADO");
    //getchar();
    bson_oid_init (&oid, NULL);
    agent = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
  }else{*/
    agent = bson_new ();
//}
  int y = 0;

  char str_age_id[15];
  sprintf(str_age_id, "%d", ageOriginal->id);

    uint32_t    i;
    char        buf[16];
    const       char *key;
    size_t      keylen;

    char        buf2[16];
    const       char *key2;
    size_t      keylen2;

      BSON_APPEND_UTF8 (agent,"id", str_age_id);
      BSON_APPEND_UTF8 (agent,"name", ageOriginal->name);
      BSON_APPEND_UTF8 (agent,"login", ageOriginal->login);
      BSON_APPEND_UTF8 (agent,"instituition", ageOriginal->instituition);
      BSON_APPEND_UTF8 (agent,"position", ageOriginal->position);
      BSON_APPEND_UTF8 (agent,"role", ageOriginal->role);
      BSON_APPEND_UTF8 (agent,"annotation", ageOriginal->annotation);

      if(index){
          indexingDocument("agent3", db, "_id");
      }
  /*
  * Print the document as a JSON string.
  */
  agent_str = bson_as_json (agent, NULL);
  printf ("\n\t%s\n\n", agent_str);
  fprintf(log,"\n\t%s\n\n", agent_str);
  bson_free (agent_str);
  /*
  * Clean up allocated bson documents.
  */
  return agent;
}

void indexingDocument (char *collection_name, mongoc_database_t *db, char *label) {

  char *index_name;
  bson_t *create_indexes;
  bson_t reply;
  char *reply_str;
  bson_error_t error;
  bool r;
   bson_t keys;

  bson_init (&keys);
   BSON_APPEND_INT32 (&keys, label, 1);
   index_name = mongoc_collection_keys_to_index_string (&keys);
   create_indexes = BCON_NEW ("createIndexes",
                              BCON_UTF8 (collection_name),
                              "indexes",
                              "[",
                              "{",
                              "key",
                              BCON_DOCUMENT (&keys),
                              "name",
                              BCON_UTF8 (index_name),
                              "}",
                              "]");

   r = mongoc_database_write_command_with_opts (
      db, create_indexes, NULL /* opts */, &reply, &error);

   reply_str = bson_as_json (&reply, NULL);
   printf ("%s\n", reply_str);

   if (!r) {
      fprintf (stderr, "Error in createIndexes: %s\n", error.message);
   }

   //bson_free (index_name);
   bson_free (reply_str);
   bson_destroy (&reply);
   bson_destroy (create_indexes);

}
