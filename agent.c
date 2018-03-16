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
	printf("scanf(, new->annotation);");
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

