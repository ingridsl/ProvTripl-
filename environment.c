// CLASSE OBSOLETA

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "environment.h"

environment *create_environment(){
	environment *new = (environment*)malloc(sizeof(environment));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type Environment's id: ");
	scanf("%d", &new->id);
	printf("Type Environment's name: ");
	scanf("%s", new->name);
	printf("Type Environment's key: ");
	scanf("%s", new->key);
	printf("Type Environment's url: ");
	scanf("%s", new->url);
	printf("Type Environment's ip: ");
	scanf("%s", new->ip);
	printf("Type Environment number of machines: "); // tem que calcular
	scanf("%d", &new->num_machines);
	printf("Type Environment's provider: ");
	scanf("%s", new->provider);
	printf("Type Environment's localization: ");
	scanf("%s", new->localization);

	return new;
}


environment *insert_environment(environment *origin){
	environment *aux = origin;
    
	environment *new = create_environment(new);
	if(aux==NULL){
	    aux = new;
	    new->next = NULL;
	    return new;
	}
	aux->next = new;
	new->next = NULL;
	return aux;
}

void freedom_environment(environment *origin){
    environment *aux1 = origin;

    while(aux1!=NULL){
        free(aux1);
        aux1 = aux1->next;
    }
}