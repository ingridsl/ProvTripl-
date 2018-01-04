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
	printf("Type agent's role: ");
	scanf("%s", new->role);
	printf("Type agent's group: ");
	scanf("%s", new->group);
	printf("Type agent's note: ");
	scanf("%s", new->note);
	return new;
}


agent *insert_agent(agent *origin){
	agent *aux = origin;
    
	agent *new = create_agent();
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
