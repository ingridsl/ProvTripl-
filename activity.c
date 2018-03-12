#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
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
	printf("Type activity's program name: ");
	scanf("%s", new->program_name);
	printf("Type activity's program version: "); // pegar a versao
	scanf("%d", &new->program_version);
	printf("Type activity's command line: "); // pegar o comando
	scanf("%s", new->command_line);
	printf("Type activity's start_date: ");
	scanf("%s", new->start_date);
	printf("Type activity's start_hour ");
	scanf("%s", new->start_hour);
	printf("Type activity's end_date: ");
	scanf("%s", new->end_date);
	printf("Type activity's end_hour: ");
	scanf("%s", new->end_hour);
	printf("Type activity's execution status: ");
	scanf("%d", &new->execution_status);
	printf("Type activity's experiment id: "); // checar se existe
	scanf("%d", &new->experiment_id);
	/*printf("Type activity's agent id: "); // checar se existe
	scanf("%d", &new->agent_id);*/
	printf("Type activity's machine id: "); // checar se existe
	scanf("%d", &new->machine_id);
	return new;
}

//insere o node
activity *insert_activity(activity *origin, experiment *originExp, machine *originMac){
	activity *aux = origin;
    
	activity *new = create_activity(new);
	if(!existsExperimentId(new->experiment_id, originExp)){
		printf("\nError: There is no experiment with this number");
		return origin;
	}
	if(!existsMachineIdForActivity(new->machine_id, originMac)){
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
/*
bool existsAgentId(int expIdAg, agent *originAg){
 	agent *aux = originAg;
    while(aux!=NULL){
    	if(expIdAg == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}*/

bool existsMachineIdForActivity(int expIdMac, machine *originMac){
 	machine *aux = originMac;
    while(aux!=NULL){
    	if(expIdMac == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}
