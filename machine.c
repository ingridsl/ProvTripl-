#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "machine.h"

#if defined(_WIN32) || defined(_WIN64)
        const char* operational_system = "Windows";
#else
#ifdef __linux
        const char* operational_system = "Linux";
#else
        const char* operational_system = "Unknown";
#endif
#endif


machine *create_machine(dataFile *data){
	machine *new = (machine*)malloc(sizeof(machine));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	new->id = 1;
	strcpy(new->hostname, "hostname");
	new->ip = 0;
	strcpy( new->type, "type");
	strcpy(new->operational_system, operational_system);
	new->cpu = 1;
	new->ram_memory = 2;
	new->disk = 1;
	strcpy(new->disk_type, "disk type");
	new->price = 0;
	new->price_type = 0;
	//Localization
	new->localization_id = 1;
	strcpy(new->localization_region, "region");
	strcpy(new->localization_zone, "zone");

	new->dataFiles = data;

	return new;
}


machine *insert_machine(machine *origin, dataFile *originDataFile){
	machine *aux = origin;
    
	machine *new = create_machine(originDataFile);
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

void freedom_machine(machine *origin){
    machine *aux1 = origin;

    while(aux1!=NULL){
    	machine *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}

bool existsClusterId(int expIdClu, cluster *originClu){
 	cluster *auxClu = originClu;
    while(auxClu!=NULL){
    	if(expIdClu == auxClu->id)
    		return true;
       	auxClu = auxClu->next;
    }

return false;
}