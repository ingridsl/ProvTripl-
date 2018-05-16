#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "experiment.h"
#include "project.h"

//inicializa variáveis
experiment *create_experiment(){
	experiment *new = (experiment*)malloc(sizeof(experiment));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	new->id = 1;
	strcpy(new->name, "BIBM2017");
	strcpy(new->description, "Workflow for mapping reads to a reference");
	strcpy(new->local,"local");
	strcpy(new->start_date, "2018-01-02");
	strcpy(new->end_date, "2018-04-01");
	strcpy(new->annotation, "annotation");
	new->version = 1;
	strcpy(new->version_date, "2018-01-02");
	new->execution_cost = 1; // no momento, esse valor é aleatório
	new->project_id = 1;
	return new;
}


experiment *insert_experiment(experiment *origin, project *originPro){
	experiment *aux = origin;

	experiment *new = create_experiment(new);
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

void freedom_experiment(experiment *origin){
    experiment *aux1 = origin;

    while(aux1!=NULL){
    	experiment *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}

bool existsProjectId(int expIdPro, project *originPro){
 	project *auxPro = originPro;
    while(auxPro!=NULL){
    	if(expIdPro == auxPro->id)
    		return true;
       	auxPro = auxPro->next;
    }

return false;
}
