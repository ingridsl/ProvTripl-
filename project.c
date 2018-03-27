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

	new->id = 1;
	strcpy(new->name, "Management of data provenance for bioinformatics workflows using NoSQL database systems and a cloud computing environment");
	strcpy(new->description, "Cloud bioinformatics workflow provenance");
	strcpy(new->inst_funders, "funders");
	strcpy(new->inst_participants, "University of Brasilia");
	strcpy(new->coordinator, "Maristela Holanda");
	strcpy(new->start_date, "2018-01-02");
	strcpy(new->end_date, "2018-04-01");
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
	while(aux->next!=NULL){
		aux = aux->next;
	}
	aux->next = new;
	new->next = NULL;
	return origin;
}

void freedom_project(project *origin){
	project *aux1 = origin;
	while(aux1!=NULL){
    		project *aux2 = aux1->next;
        	free(aux1);
        	aux1 = aux2;
    	}
}

