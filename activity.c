#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "activity.h"

files *used_files = NULL;

activity *define_activity(int *activityNumber, char fileBaseName[N], dataFile *dataFiles){ //falta incluir aquivos na lista de arquivos
	activity *original = (activity*)malloc(sizeof(activity));
    if(!original){
		printf("\nError");
	    exit(1);
	}

	char inputFile1[N], outputFile[N], inputFile2[N], inputFile[N];
	char command[N] = "";
	switch((*activityNumber)){
		case 1: 
			strcpy(command, " ");
			strcpy(inputFile, fileBaseName);
		   	strcpy(outputFile, fileBaseName);
		   	printf("insert datafile");
		   	strcat(inputFile, ".fa"); //22_20-21M.fasta
		   	(dataFiles) = insert_dataFile(dataFiles, inputFile);
		   	strcat(outputFile, ".hisat2.idx"); //22_20-21M.hisat2.idx
		   	(dataFiles) = insert_dataFile(dataFiles, outputFile);

			strcpy(command, "hisat2-build -p 30 ");
		    strcat(command, fileBaseName);
		    strcat(command, ".fa ");
		    strcat(command, outputFile);

		    printf("\n\t:::::: COMANDO 1 :::::: \n%s \n", command);
   			printf("::::::");
   			getchar();
   			getchar();
			//system(command); descomentar

			original->id = *activityNumber;
			printf("\n\n %d", original->id);
			strcpy(original->name, "nome");
			strcpy(original->program_name, hisat);
			strcpy(original->program_version, hisatversion);
			strcpy(original->command_line,command);
			/*strcpy(original->start_date,);
			strcpy(original->start_hour,);
			strcpy(original->end_date,);
			strcpy(original->end_hour,);*/
			//original->execution_status;
			(*activityNumber)++;
			printf("antes de sair\n\n:%d", *activityNumber);
			break;
		case 2: 
			strcpy(command, " ");

			strcpy(inputFile, fileBaseName);

		   	strcat(inputFile, ".hisat2.idx"); //22_20-21M.hisat2.idx
		   	strcpy(inputFile1, "file_1.fq"); //file_1.fq
		   	strcpy(inputFile2, "file_2.fq"); //file_2.fq
			strcpy(outputFile, "file.sam"); // file.sam

			strcpy(command, "hisat2-build -p 30 -x ");
		    strcat(command, inputFile);
		    strcat(command, " -1 ");
		    strcat(command, inputFile1);
		    strcat(command, " -2 ");
		    strcat(command, inputFile2);
		    strcat(command, " -S ");
		    strcat(command, outputFile);

		    printf("\n:::::: COMANDO 2 :::::: \n%s \n", command);
   			printf("::::::");
   			getchar();
			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, hisat);
			strcpy(original->program_version, hisatversion);
			strcpy(original->command_line,command);

			/*original->id = activityNumber;
			strcpy(original->name);
			original->program_name[N];
			original->program_version;
			original->command_line[N];
			original->start_date[N];
			original->start_hour[N];
			original->end_date[N];
			original->end_hour[N];
			original->execution_status;*/
			(*activityNumber)++;
			break;
		case 3: 
			strcpy(command, " ");

		   	strcpy(inputFile, "file.sam");
		   	strcpy(outputFile, "file.bam");

			strcpy(command, "samtools view -bS ");
		    strcat(command, inputFile);
		    strcat(command, " > ");
		    strcat(command, outputFile);

		    printf("\n:::::: COMANDO 3 :::::: \n%s \n", command);
   			printf("::::::");
   			getchar();

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, hisat);
			strcpy(original->program_version, hisatversion);
			strcpy(original->command_line,command);
			/*original->id = activityNumber;
			strcpy(original->name);
			original->program_name[N];
			original->program_version;
			original->command_line[N];
			original->start_date[N];
			original->start_hour[N];
			original->end_date[N];
			original->end_hour[N];
			original->execution_status;*/
			(*activityNumber)++;
			break;
		case 4: 
			strcpy(command, " ");
		   	strcpy(inputFile, "file.bam");
			strcpy(outputFile, "file_sorted.sn");

			strcpy(command, "samtools sort -n ");
		    strcat(command, inputFile);
		    strcat(command, " ");
		    strcat(command, outputFile);

		    printf("\n:::::: COMANDO 4 :::::: \n%s \n", command);
   			printf("::::::");
   			getchar();

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, hisat);
			strcpy(original->program_version, hisatversion);
			strcpy(original->command_line,command);
			/*original->id = activityNumber;
			strcpy(original->name);
			original->program_name[N];
			original->program_version;
			original->command_line[N];
			original->start_date[N];
			original->start_hour[N];
			original->end_date[N];
			original->end_hour[N];
			original->execution_status;*/
			(*activityNumber)++;
			break;
		case 5: 

			strcpy(inputFile, fileBaseName);
		   	strcpy(outputFile, fileBaseName);

		   	strcpy(inputFile, "file_sorted.sn.sam");
		   	strcpy(outputFile, "file.bam");

			strcpy(command, "samtools view -h -o ");
		    strcat(command, inputFile);
		    strcat(command, " ");
		    strcat(command, outputFile);

		    printf("\n:::::: COMANDO 5 :::::: \n%s \n", command);
   			printf("::::::");
   			getchar();

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, hisat);
			strcpy(original->program_version, hisatversion);
			strcpy(original->command_line,command);
			/*original->id = activityNumber;
			strcpy(original->name);
			original->program_name[N];
			original->program_version;
			original->command_line[N];
			original->start_date[N];
			original->start_hour[N];
			original->end_date[N];
			original->end_hour[N];
			original->execution_status;*/
			(*activityNumber)++;
			break;
		case 6: 

			strcpy(inputFile1, "file_sorted.sn.sam");
			strcpy(inputFile2, "Homo_sapiens.GRCh38.88.gtf");
		   	strcpy(outputFile, "subset.counts");

			strcpy(command, "htseq-count -m intersection-nonempty -s no ");
		    strcat(command, inputFile1);
		    strcat(command, " ");
		    strcat(command, inputFile2);
		    strcat(command, " > ");
			strcat(command, outputFile);

		    printf("\n:::::: COMANDO 6 :::::: \n%s \n", command);
   			printf("::::::");
   			getchar();

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, hisat);
			strcpy(original->program_version, hisatversion);
			strcpy(original->command_line,command);
			/*original->id = activityNumber;
			strcpy(original->name);
			original->program_name[N];
			original->program_version;
			original->command_line[N];
			original->start_date[N];
			original->start_hour[N];
			original->end_date[N];
			original->end_hour[N];
			original->execution_status;*/
			(*activityNumber)++;
			break;
		default: 
			(*activityNumber)++;
			break;
	}
	return original;
}
// cria o node
activity *create_activity(){
	activity *new = (activity*)malloc(sizeof(activity));

    if(!new){
		printf("\nError");
	    exit(1);
	}

	printf("Type activity's id: ");
	scanf("%d", &new->id);
	printf("Type activity's name: ");
	scanf("%s", new->name);
	printf("Type activity's program name: ");
	scanf("%s", new->program_name);
	printf("Type activity's program version: "); // pegar a versao
	scanf("%s", new->program_version);
	printf("Type activity's command line: "); // pegar o comando
	scanf("%s", new->command_line);
	printf("Type activity's start_date: ");
	scanf("%s", new->start_date);
	printf("Type activity's start_hour ");
	scanf("%s", new->start_hour);
	printf("Type activity's end_date: ");
	scanf("%s", new->end_date);
	printf("Type activity's end_hour: ");
	scanf("%s", new->end_hour);
	printf("Type activity's execution status: ");
	scanf("%d", &new->execution_status);
	printf("Type activity's experiment id: "); // checar se existe
	scanf("%d", &new->experiment_id);
	/*printf("Type activity's agent id: "); // checar se existe
	scanf("%d", &new->agent_id);*/
	printf("Type activity's machine id: "); // checar se existe
	scanf("%d", &new->machine_id);
	return new;
}

//insere o node
activity *insert_activity(activity *origin, dataFile *dataFiles, int *activityNumber, char fileBaseName[N]){
	activity *aux = origin;
	//activity *new = create_activity(); //trocar
	
	activity *new = define_activity(activityNumber, fileBaseName, dataFiles); 
	/*if(!existsExperimentId(new->experiment_id, originExp)){
		printf("\nError: There is no experiment with this number");
		return origin;
	}
	if(!existsMachineIdForActivity(new->machine_id, originMac)){
		printf("\nError: There is no machine with this number");
		return origin;
	}*/
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

void freedom_activity(activity *origin){
    activity *aux1 = origin;
    while(aux1!=NULL){
    	activity *aux2 = aux1->next;
        free(aux1);
        aux1 = aux2;
    }
}

bool existsExperimentId(int expIdExp, experiment *originExp){
 	experiment *aux = originExp;
    while(aux!=NULL){
    	if(expIdExp == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}
/*
bool existsAgentId(int expIdAg, agent *originAg){
 	agent *aux = originAg;
    while(aux!=NULL){
    	if(expIdAg == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}*/

bool existsMachineIdForActivity(int expIdMac, machine *originMac){
 	machine *aux = originMac;
    while(aux!=NULL){
    	if(expIdMac == aux->id)
    		return true;
       	aux = aux->next;
    }

return false;
}
