#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cluster.h"

cluster *create_cluster(){
	cluster *new = (cluster*)malloc(sizeof(cluster));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	new->id = 1;
	strcpy(new->name,"ProvBio-BIBM");
	new->number_machines = 1;
	new->provider_id = 1;
	strcpy(new->description,"description here");
	return new;
}


cluster *insert_cluster(cluster *origin, provider *originPro){
	cluster *aux = origin;

	cluster *new = create_cluster(new);
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

void freedom_cluster(cluster *origin){
    cluster *aux1 = origin;

    while(aux1!=NULL){
    	cluster *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}

bool existsProviderId(int expIdPro, provider *originPro){
 	provider *auxPro = originPro;
    while(auxPro!=NULL){
    	if(expIdPro == auxPro->id)
    		return true;
       	auxPro = auxPro->next;
    }

	return false;
}
