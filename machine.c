#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "environment.h"
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


machine *create_machine(){
	machine *new = (machine*)malloc(sizeof(machine));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type machine's id: ");
	scanf("%d", &new->id);
	printf("Type machine's hostname: ");
	scanf("%s", new->hostname);
	printf("Type machine's ip: ");
	scanf("%s", new->ip);
	printf("Type machine's type: ");
	scanf("%s", new->type);
	printf("Getting machine's operational system: ");
	strcpy(new->operational_system,operational_system);
	printf("Type machine's cpu: ");
	scanf("%s", new->cpu);
	printf("Type machine's ram memory: ");
	scanf("%f", &new->ram_memory);
	printf("Type machine's disk quantity: ");
	scanf("%d", &new->disk);
	printf("Type machine's disk type: "); 
	scanf("%s", new->disk_type);
	printf("Type machine's localization: "); 
	scanf("%s", new->localization);
	printf("Type machine's price: ");
	scanf("%f", &new->price);
	printf("Type machine's billing type: "); 
	scanf("%s", new->billing_type);
	printf("Type machine's setup time: "); 
	scanf("%s", new->setup_time);
	printf("Type machine's setup cost: "); 
	scanf("%f", &new->setup_cost);
	printf("Type machine's environment id: "); //checar se existe
	scanf("%d", &new->environment_id);
	return new;
}


machine *insert_machine(machine *origin, environment *originEnv){
	machine *aux = origin;
    
	machine *new = create_machine(new);
	if(!existsEnvironmentId(new->environment_id, originEnv)){
		printf("\nError: There is no Environment with this id");
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

void freedom_machine(machine *origin){
    machine *aux1 = origin;

    while(aux1!=NULL){
        free(aux1);
        aux1 = aux1->next;
    }
}

bool existsEnvironmentId(int expIdEnv, environment *originEnv){
 	environment *auxEnv = originEnv;
    while(auxEnv!=NULL){
    	if(expIdEnv == auxEnv->id)
    		return true;
       	auxEnv = auxEnv->next;
    }

return false;
}