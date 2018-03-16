#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataFile.h"
#include "machine.h"
dataFile *create_dataFile(char file_name[N]){
	dataFile *new = (dataFile*)malloc(sizeof(dataFile));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type Data File's id: ");
	scanf("%d", &new->id);
	//printf("Type Data File's name: ");
	strcpy(new->name, file_name);
	printf("Type Data File's description: ");
	scanf("%s", new->description);
	printf("Type Data File's localization: ");
	scanf("%s", new->localization);
	printf("Type Data File's annotation: ");
	scanf("%s", new->annotation);
	printf("Type Data File's type: ");
	scanf("%s", new->type);
	printf("Type Data File's insert_date: ");
	scanf("%s", new->insertion_date);
	printf("Type Data File's size: "); // tem que pegar
	scanf("%d", &new->size);
	printf("Type Data File's machine's id: "); // checar se existe
	scanf("%d", &new->machine_id);
	//pegando e referenciando arquivo
	new->file = fopen (new->name, "r");
	if(!new->file){
		printf("Failed to open file");
	}
	return new;
}


dataFile *insert_dataFile(dataFile *origin, char file_name[N]){
	dataFile *aux = origin;
	dataFile *new = create_dataFile(file_name);
	/*if(!existsMachineIdForFile(new->machine_id, originMac)){
		printf("\nError: There is no machine with this number");
		return origin;
	}*/
	if(aux==NULL){
	    aux = new;
	    new->next = NULL;
	    return new;
	}
	while(aux->next!=NULL){
		aux = aux->next;
	}
	aux->next = new;
	new->next = NULL;
	return origin;
}

void freedom_dataFile(dataFile *origin){
    dataFile *aux1 = origin;
    while(aux1!=NULL){
    	dataFile *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}

int Convert(char name[N], mongoc_collection_t  *collection, mongoc_database_t *database){
  char comando[N];
  if(access(name, F_OK)==-1){
    return 0;
  }

  strcpy(comando, "tr ' ' \\\\t < ");
  strcat(comando, name);
  strcat(comando," > ");
  strcat(comando, name);
  strcat(comando,".tsv");

  system(comando);  //DESCOMENTAR DEPOIS

  strcpy(comando, " ");
  strcat (comando, "mongoimport -d db_name -c coll_name --type tsv --file ");
  strcat(comando, name);
  strcat(comando, ".tsv -f id --numInsertionWorkers 2");

  system(comando);
  return 1;
}