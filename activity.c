#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "project.h"
#include "agent.h"
#include "activity.h"

// cria o node
activity *create_activity(){
	activity *new = (activity*)malloc(sizeof(activity));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type activity's id: ");
	scanf("%d", &new->id);
	printf("Type activity's name: ");
	scanf("%s", new->name);
	printf("Type activity's program: ");
	scanf("%s", new->program);
	printf("Type activity's version: "); // pegar a versao
	scanf("%s", new->version);
	printf("Type activity's command: "); // pegar o comando
	scanf("%s", new->command);
	printf("Type activity's function: "); // qual a diferença pra comando?
	scanf("%s", new->function);
	printf("Type activity's start_date: ");
	scanf("%s", new->start_date);
	printf("Type activity's end_date: ");
	scanf("%s", new->end_date);
	printf("Type activity's status: ");
	scanf("%s", new->status);
	printf("Type activity's cost: ");
	scanf("%s", new->cost);
	printf("Type activity's experiment id: "); // checar se existe
	scanf("%d", &new->experiment_id);
	printf("Type activity's agent id: "); // checar se existe
	scanf("%d", &new->agent_id);
	/* se cloud
	printf("Type activity's machine id: "); // checar se existe
	scanf("%d", &new->machine_id);*/
	return new;
}

//insere o node
activity *insert_activity(activity *origin, experiment *originExp, agent *originAg){
	activity *aux = origin;
    
	activity *new = create_activity(new);
	if(!existsExperimentId(new->experiment_id, originExp)){
		printf("\nError: There is no experiment with this name");
		return origin;
	}
	if(!existsAgentId(new->agent_id, originAg)){
		printf("\nError: There is no agent with this name");
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

void freedom_activity(activity *origin){
    activity *aux1 = origin;

    while(aux1!=NULL){
        free(aux1);
        aux1 = aux1->next;
    }
}

bool existsExperimentId(int expIdExp, experiment *originExp){
 	experiment *aux = originExp;
    while(aux!=NULL){
    	if(expIdExp == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}

bool existsAgentId(int expIdAg, agent *originAg){
 	agent *aux = originAg;
    while(aux!=NULL){
    	if(expIdAg == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}