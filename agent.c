#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "agent.h"

agent *create_agent(){

	agent *new = (agent*)malloc(sizeof(agent));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type agent's id: ");
	scanf("%d", &new->id);
	printf("Type agent's name: ");
	scanf("%s", new->name);
	printf("Type agent's login: ");
	scanf("%s", new->login);
	printf("Type agent's instituition: ");
	scanf("%s", new->instituition);
	printf("Type agent's position: ");
	scanf("%s", new->position);
	printf("Type agent's annotation: ");
	scanf("%s", new->annotation);
	printf("Type machine's activity id: "); //checar se existe
	scanf("%d", &new->activity_id);
	return new;
}


agent *insert_agent(agent *origin, activity *originAct){
	agent *aux = origin;
    
	agent *new = create_agent();
	if(!existsActivityId(new->activity_id, originAct)){
		printf("\nError: There is no Activity with this id");
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

void freedom_agent(agent *origin){
    agent *aux1 = origin;

    while(aux1!=NULL){
        free(aux1);
        aux1 = aux1->next;
    }
}

bool existsActivityId(int expIdAct, activity *originAct){
 	activity *auxAct = originAct;
    while(auxAct!=NULL){
    	if(expIdAct == auxAct->id)
    		return true;
       	auxAct = auxAct->next;
    }

return false;
}

