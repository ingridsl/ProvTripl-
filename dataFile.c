#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project.h"
#include "dataFile.h"

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
	printf("Type Data File's type: ");
	scanf("%s", new->type);
	printf("Type Data File's insert_date: ");
	scanf("%s", new->insert_date);
	printf("Type Data File's size: "); // tem que calcular
	scanf("%f", &new->size);
	printf("Type Data File's activity's id: "); // checar se existe
	scanf("%d", &new->activity_id);

	new->file = fopen (new->name, "r");
	if(!new->file){
		printf("Failed to open file");
	}
	return new;
}


dataFile *insert_dataFile(dataFile *origin, activity *originAct){
	dataFile *aux = origin;
    
	dataFile *new = create_dataFile(new);
	if(!existsActivityId(new->activity_id, originAct)){
		printf("\nError: There is no activity with this name");
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

bool existsActivityId(int expIdAct, activity *originAct){
 	activity *aux = originAct;
    while(aux!=NULL){
    	if(expIdAct == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}