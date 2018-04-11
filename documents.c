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
		//getchar();
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
	const char* command1[] = {"3","9"}; //arquivos usados pelos comandos. ver na main qual é qual
	const char* command2[] = {"1","2"};
	const char* command3[] = {"2","9","4"};
	const char* command4[] = {"4","5"};
	const char* command5[] = {"5","6"};
	const char* command6[] = {"6","7", "8"};

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




   /*
    * Array of subdocuments:
    *    degrees: [ { degree: "BA", school: "Vassar" }, ... ]
    
   BSON_APPEND_ARRAY_BEGIN (document, "degrees", &child);
   for (i = 0; i < sizeof degrees / sizeof (char *); ++i) {
      keylen = bson_uint32_to_string (i, &key, buf, sizeof buf);
      bson_append_document_begin (&child, key, (int) keylen, &child2);
      BSON_APPEND_UTF8 (&child2, "degree", degrees[i]);
      BSON_APPEND_UTF8 (&child2, "school", schools[i]);
      bson_append_document_end (&child, &child2);
   }
   bson_append_array_end (document, &child);

*/
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
			for(i = 0; i< sizeof command1 /sizeof(char *); ++i){
				keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
				bson_append_utf8(&child, key, (int) keylen, command1[i], -1);

			}
		}
		if(actOriginal->id == 2){
			for(i = 0; i< sizeof command2 /sizeof(char *); ++i){
				keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
				bson_append_utf8(&child, key, (int) keylen, command2[i], -1);

			}
		}
		if(actOriginal->id == 3){
			for(i = 0; i< sizeof command3 /sizeof(char *); ++i){
				keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
				bson_append_utf8(&child, key, (int) keylen, command3[i], -1);

			}
		}
		if(actOriginal->id == 4){
			for(i = 0; i< sizeof command4 /sizeof(char *); ++i){
				keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
				bson_append_utf8(&child, key, (int) keylen, command4[i], -1);

			}
		}
		if(actOriginal->id == 5){
			for(i = 0; i< sizeof command5 /sizeof(char *); ++i){
				keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
				bson_append_utf8(&child, key, (int) keylen, command5[i], -1);

			}
		}
		if(actOriginal->id == 6){
			for(i = 0; i< sizeof command6 /sizeof(char *); ++i){
				keylen = bson_uint32_to_string(i, &key, buf, sizeof buf);
				bson_append_utf8(&child, key, (int) keylen, command6[i], -1);

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
int Convert(char fileName[N], mongoc_collection_t  *collection, mongoc_database_t    *database){
  char comando[N];
  char name[N], extensao[7];
  strcpy(name, fileName);
  int i = 1;
  while(i<9){
  		printf("\n\n i> %d", i); // os hisat2.idx são fragmentados em 8 arquivos durante o workflow. deve-se considerar os 8
	  if(strcmp(fileName, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")==0){
	  	strcpy(name, fileName);
		sprintf(extensao, ".%d.ht2", i);
		strcat(name, extensao);
		i++;
		printf("\n \n file name: %s", name);
	  }else{
	  	i=9;
	  }

	  /*if(access(name, F_OK)==-1){
	    return 0;
	  }*/

	  strcpy(comando, "tr ' ' \\\\t < ");
	  strcat(comando, name);
	  strcat(comando," > ");
	  strcat(comando, name);
	  strcat(comando,".tsv");

	  printf("\nCOMANDO: %s", comando);
	  system(comando);  //DESCOMENTAR DEPOIS

	  strcpy(comando, " ");
	  strcat (comando, "mongoimport -d db_name -c collection --type tsv --file ");
	  strcat(comando, name);
	  strcat(comando, ".tsv -f id --numInsertionWorkers 2");

	  system(comando);
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
bson_t   *DATA_DOC(dataFile *dataOriginal, mongoc_database_t *database, mongoc_collection_t *collection, FILE *log){
	
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
		//getchar();
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

