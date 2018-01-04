#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "project.h"

project *create_project(){

	project *new = (project*)malloc(sizeof(project));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type project's id: ");
	scanf("%d", &new->id);
	printf("Type project's name: ");
	scanf("%s", new->name);
	printf("Type project's description: ");
	scanf("%s", new->description);
	printf("Type project's coordinator: ");
	scanf("%s", new->coordinator);
	printf("Type project's start_date: ");
	scanf("%s", new->start_date);
	printf("Type project's end_date: ");
	scanf("%s", new->end_date);
	return new;
}


project *insert_project(project *origin){
	project *aux = origin;
    
	project *new = create_project(new);
	if(aux==NULL){
	    aux = new;
	    new->next = NULL;
	    return new;
	}
	aux->next = new;
	new->next = NULL;
	return aux;
}

void freedom_project(project *origin){
    project *aux1 = origin;

    while(aux1!=NULL){
        free(aux1);
        aux1 = aux1->next;
    }
}
