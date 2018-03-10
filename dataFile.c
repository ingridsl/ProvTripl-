#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataFile.h"
#include "machine.h"
dataFile *create_dataFile(){
	dataFile *new = (dataFile*)malloc(sizeof(dataFile));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type Data File's id: ");
	scanf("%d", &new->id);
	printf("Type Data File's name: ");
	scanf("%s", new->name);
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


dataFile *insert_dataFile(dataFile *origin, machine *originMac){
	dataFile *aux = origin;
    
	dataFile *new = create_dataFile();
	if(!existsMachineIdForFile(new->machine_id, originMac)){
		printf("\nError: There is no machine with this number");
		return origin;
	}
	if(aux==NULL){
	    aux = new;
	    new->next = NULL;
	    return new;
	}
	aux->next = new;
	new->next = NULL;
	return aux;
}

void freedom_dataFile(dataFile *origin){
    dataFile *aux1 = origin;

    while(aux1!=NULL){
    	fclose(aux1->file);
        free(aux1);
        aux1 = aux1->next;
    }
}

bool existsMachineIdForFile(int expIdMac, machine *originMac){
 	machine *aux = originMac;
    while(aux!=NULL){
    	if(expIdMac == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}