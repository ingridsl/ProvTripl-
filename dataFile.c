#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataFile.h"
#include "machine.h"

int dataFileId = 1;
dataFile *create_dataFile(char file_name[N]){
	dataFile *new = (dataFile*)malloc(sizeof(dataFile));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	new->id = dataFileId;
	dataFileId ++;
	//printf("Type Data File's name: ");
	strcpy(new->name, file_name);
	strcpy(new->description, "description");
	strcpy(new->localization, "localization");
	strcpy(new->annotation, "annotation");
	strcpy(new->type, "type");
	new->machine_id = 1;
	strcpy(new->insertion_date, "insertion_date");
	new->size = 0;

	//pegando e referenciando arquivo
	/*new->file = fopen (new->name, "r");
	if(!new->file){
		printf("\n\nFailed to open file: %s\n", new->name);
	}*/
	return new;
}


dataFile *insert_dataFile(dataFile *origin, char file_name[N]){
	dataFile *aux = origin;
	dataFile *new = create_dataFile(file_name);
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
        //fclose(aux1->file);
        free(aux1);
        aux1 = aux2;
    }
}
