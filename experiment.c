#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project.h"
#include "experiment.h"

experiment *create_experiment(){
	experiment *new = (experiment*)malloc(sizeof(experiment));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type experiment's id: ");
	scanf("%d", &new->id);
	printf("Type experiment's name: ");
	scanf("%s", new->name);
	printf("Type experiment's description: ");
	scanf("%s", new->description);
	printf("Type experiment's start_date: ");
	scanf("%s", new->start_date);
	printf("Type experiment's end_date: ");
	scanf("%s", new->end_date);
	printf("Type experiment's version: ");
	scanf("%s", new->version);
	printf("Type experiment's version date: ");
	scanf("%s", new->version_date);
	printf("Type experiment's version note: ");
	scanf("%s", new->note);
	printf("Type experiment's project's id: "); // checar se existe
	scanf("%d", &new->project_id);
	printf("Type experiment's execution cost: "); //deve ser calculado?
	scanf("%f", &new->execution_cost);
	printf("Type experiment's configuration cost: "); //deve ser calculado?
	scanf("%f", &new->configuration_cost);
	printf("Type experiment's total cost: "); //deve ser calculado?
	scanf("%f", &new->total_cost);
	return new;
}


experiment *insert_experiment(experiment *origin, project *originPro){
	experiment *aux = origin;
    
	experiment *new = create_experiment(new);
	if(!existsProjectId(new->project_id, originPro)){
		printf("\nError: There is no project with this name");
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

void freedom_experiment(experiment *origin){
    experiment *aux1 = origin;

    while(aux1!=NULL){
        free(aux1);
        aux1 = aux1->next;
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