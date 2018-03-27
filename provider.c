#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "provider.h"

provider *create_provider(){
	provider *new = (provider*)malloc(sizeof(provider));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	new->id = 1;
	strcpy(new->name, "Google Cloud");
	strcpy(new->url, "url");
	strcpy(new->description, "description");
	
	//Localization
	new->localization_id = 1;
	strcpy(new->localization_region,"region");
	strcpy(new->localization_zone, "zone");


	return new;
}


provider *insert_provider(provider *origin){
	provider *aux = origin;
    
	provider *new = create_provider(new);
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

void freedom_provider(provider *origin){
    provider *aux1 = origin;

    while(aux1!=NULL){
    	provider *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}
