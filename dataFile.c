#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

#include "dataFile.h"
#include "machine.h"
#include "activity.h"

int dataFileId = 1;
int fileCounter = 1;

dataFile *create_dataFile(char file_name[N]){
	//getchar();
	dataFile *new = (dataFile*)malloc(sizeof(dataFile));

  if(!new){
		printf("\nError");
	    exit(1);
	}
	new->id = dataFileId;
	dataFileId ++;
	//printf("Type Data File's name: ");
	strcpy(new->name, file_name);
	strcpy(new->description, "description");
	strcpy(new->localization, "localization");
	strcpy(new->annotation, "annotation");
	strcpy(new->type, "type");
	new->machine_id = 1;

	strcpy(new->insertion_date, "insertion_date");
	new->size = 0;

	//pegando e referenciando arquivo
	/*new->file = fopen (new->name, "r");
	if(!new->file){
		printf("\n\nFailed to open file: %s\n", new->name);
	}*/
	return new;
}


dataFile *insert_dataFile(dataFile *origin, char file_name[N]){
	dataFile *aux = origin;
	if(existsDataFileId(file_name, origin)){
		return origin;
	}

	dataFile *new;
	//char fileNewName[N];
	/*if(strcmp(file_name, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")==0){
		while(fileCounter<9){
			printf("converted");
			file_name = convertMultipleFiles(file_name, file_name);
			if(existsDataFileId(file_name, origin)){
				return origin;
			}
			new = create_dataFile(file_name);
			while(aux->next!=NULL){
				aux = aux->next;
			}
			aux->next = new;
			new->next = NULL;
			strcpy(file_name,"Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
			fileCounter++;
		}
	}else{
		printf("not converted");*/
		new = create_dataFile(file_name);
	//}

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
char *convertMultipleFiles(char *fileName, char *name){
		char extensao[7];
		strcpy(name, fileName);
			//if(strcmp(fileName, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")==0){
				strcpy(name, fileName);
				sprintf(extensao, ".%d.ht2", fileCounter);
				strcat(name, extensao);
			//}
		return name;
}

void freedom_dataFile(dataFile *origin){
    dataFile *aux1 = origin;
    while(aux1!=NULL){
    	dataFile *aux2 = aux1->next;
        //fclose(aux1->file);
        free(aux1);
        aux1 = aux2;
    }
}

bool existsDataFileId(char fileName[N], dataFile *origin){
 	dataFile *aux = origin;
    while(aux!=NULL){
    	if(strcmp(aux->name, fileName) == 0)
    		return true;
       	aux = aux->next;
    }
return false;
}

int retrieveDataFileId(char fileName[N], dataFile *origin){

 	dataFile *aux = returnUsedFiles();
    while(aux!=NULL){
    	if(strcmp(aux->name, fileName) == 0)
    		return aux->id;
       	aux = aux->next;
    }
return 0;
}
