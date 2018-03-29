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

	new->id = 1;
	strcpy(new->name, "Ingrid Santana");
	strcpy(new->login, "ingrid.santana");
	strcpy(new->instituition, "Universidade de Brasília");
	strcpy(new->position, "Undergraduate student");
	strcpy(new->annotation, "Systems Developer");
	return new;
}


agent *insert_agent(agent *origin){
	agent *aux = origin;
    
	agent *new = create_agent();
	if(aux==NULL){
	    new->next = NULL;
	    return new;
	}
	new->next = aux;
	return new;
}

void freedom_agent(agent *origin){
    agent *aux1 = origin;

    while(aux1!=NULL){
    	agent *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
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

