#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "activity.h"
#include "commands.h"

//files *used_files = NULL;

dataFile *used_files = NULL;

dataFile *returnUsedFiles(){
	return used_files;
}

activity *define_activity(int *activityNumber, char fileBaseName[N], dataFile *dataFileOrig){ //falta incluir aquivos na lista de arquivos
	activity *original = (activity*)malloc(sizeof(activity));

   	time_t t;
	struct tm tm;
    if(!original){
		printf("\nError");
	    exit(1);
	}
	int value;
	char inputFile[N],inputFile1[N], inputFile2[N], inputFile3[N], outputFile[N];
	char command[N] = "";
	switch((*activityNumber)){
		case 1:
			strcpy(command, " ");
				strcpy(inputFile1, "SRR5181508.fastq");
		   	strcpy(outputFile, "SRR5181508_FILTERED.fastq");

				used_files = insert_dataFile(used_files, inputFile1);
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);
		   	strcpy(command, "sickle se --fastq-file SRR5181508.fastq --qual-type sanger --output-file SRR5181508_FILTERED.fastq -q 30 -l 25");

		    printf("\n\t:::::: COMANDO 1 :::::: \n%s \n", command);
   			printf("::::::");

   			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			//system(command);

			//GET TIME
			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->end_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->end_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			original->id = *activityNumber;
			printf("\n\n %d", original->id);
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version, searchProgramVersion(command));
			strcpy(original->command_line,command);
			(*activityNumber)++;
		break;
		case 2:
			strcpy(command, " ");
				strcpy(inputFile1, "Homo_sapiens.GRCh38.dna.chromosome.22.fa");
				used_files = insert_dataFile(used_files, inputFile1);
				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);
		   	//strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.1.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.2.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[1],"%d", value);
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.3.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[2],"%d", value);
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.4.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[3],"%d", value);
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.5.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[4],"%d", value);
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.6.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[5],"%d", value);
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.7.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[6],"%d", value);
				strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.8.ht2");
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[7],"%d", value);
		   	//printf("insertd");
		   	//strcat(inputFile1, ".fa");
		   	//strcat(outputFile, ".hisat2.idx"); //22_20-21M.hisat2.idx




			strcpy(command, "hisat2-build -p 4 Homo_sapiens.GRCh38.dna.chromosome.22.fa Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");

		    printf("\n\t:::::: COMANDO 2 :::::: \n%s \n", command);
   			printf("::::::");

   			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			//system(command);

			//GET TIME
			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->end_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->end_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			original->id = *activityNumber;
			printf("\n\n %d", original->id);
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version,searchProgramVersion(command));
			strcpy(original->command_line,command);
			//original->execution_status;
			(*activityNumber)++;
			break;
		case 3:
			strcpy(command, " ");

			//strcpy(inputFile1, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");

			//strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.1.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[0],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.2.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[1],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.3.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[2],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.4.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[3],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.5.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[4],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.6.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[5],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.7.ht2");
			used_files = insert_dataFile(used_files,inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[6],"%d", value);

			strcpy(inputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx.8.ht2");
			used_files = insert_dataFile(used_files, inputFile);

			value = retrieveDataFileId(inputFile, used_files);
			sprintf(original->command_input[7],"%d", value);
		   	//strcat(inputFile, ".hisat2.idx"); //22_20-21M.hisat2.idx
		   	strcpy(inputFile1, "SRR5181508_FILTERED.fastq"); //file_1.fq
		   	//strcpy(inputFile2, "file_2.fq"); //file_2.fq
				strcpy(outputFile, "file.sam"); // file.sam
				used_files = insert_dataFile(used_files, inputFile1);
				//used_files = insert_dataFile(used_files, inputFile2);
				used_files = insert_dataFile(used_files, outputFile);

				//value = retrieveDataFileId(inputFile1, used_files);
				//sprintf(original->command_input[0],"%d", value);
				//value = retrieveDataFileId(inputFile2, used_files);
				sprintf(original->command_input[8],"%d", value);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

			strcpy(command, "hisat2 -p 2 -x Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx -q SRR5181508_FILTERED.fastq -S file.sam");


		    printf("\n:::::: COMANDO 3 :::::: \n%s \n", command);
   			printf("::::::");
			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version, searchProgramVersion(command));
			strcpy(original->command_line,command);

			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			//system(command);

			//GET TIME
			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->end_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->end_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);


			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version, searchProgramVersion(command));
			strcpy(original->command_line,command);
			(*activityNumber)++;
			break;
		case 4:
			strcpy(command, " ");

		   	strcpy(inputFile1, "file.sam");
		   	strcpy(outputFile, "file.bam");
				used_files = insert_dataFile(used_files, inputFile1);
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

			strcpy(command, "samtools view -bS ");
		    strcat(command, inputFile1);
		    strcat(command, " > ");
		    strcat(command, outputFile);

		    printf("\n:::::: COMANDO 4 :::::: \n%s \n", command);
   			printf("::::::");
			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			//system(command);

			//GET TIME
			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->end_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->end_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version,searchProgramVersion(command));
			strcpy(original->command_line,command);
			(*activityNumber)++;
			break;
		case 5:
			strcpy(command, " ");
		   	strcpy(inputFile1, "file.bam");
			strcpy(outputFile, "file_sorted.sn");

			strcpy(command, "samtools sort -n ");
		    strcat(command, inputFile1);
		    strcat(command, " ");
		    strcat(command, outputFile);

				strcat(outputFile, ".bam");

				used_files = insert_dataFile(used_files, inputFile1);
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

		    printf("\n:::::: COMANDO 5 :::::: \n%s \n", command);
   			printf("::::::");
			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			//system(command);

			//GET TIME
			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->end_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->end_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version, searchProgramVersion(command));
			strcpy(original->command_line,command);
			(*activityNumber)++;
			break;
		case 6:

			strcpy(inputFile1, "file_sorted.sn.bam");
			strcpy(inputFile2, "Homo_sapiens.GRCh38.88.gtf");
		   	strcpy(outputFile, "file.count");

				used_files = insert_dataFile(used_files, inputFile1);
				used_files = insert_dataFile(used_files, inputFile2);
				used_files = insert_dataFile(used_files, outputFile);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);
				value = retrieveDataFileId(inputFile2, used_files);
				sprintf(original->command_input[1],"%d", value);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

			strcpy(command, "htseq-count -m intersection-nonempty -s no -a 10 ");
		    strcat(command, inputFile1);
		    strcat(command, " ");
		    strcat(command, inputFile2);
		    strcat(command, " -o ");
			strcat(command, outputFile);

		    printf("\n:::::: COMANDO 6 :::::: \n%s \n", command);
   			printf("::::::");
			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			//system(command);

			//GET TIME
			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->end_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->end_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			original->id = *activityNumber;
			strcpy(original->name, "nome");
			strcpy(original->program_name, searchProgramUsed(command));
			strcpy(original->program_version,searchProgramVersion(command));
			strcpy(original->command_line,command);
			(*activityNumber)++;
			break;
		default:
			(*activityNumber)++;
			break;
		original->experiment_id = 1;
		original->agent_id = 1;

	}
	return original;
}
// cria o node - não usada
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
activity *insert_activity(activity *origin, int *activityNumber, char fileBaseName[N], dataFile *dataFileOrig){
	activity *aux = origin;
	//activity *new = create_activity(); //trocar

	activity *new = define_activity(activityNumber, fileBaseName, &(*dataFileOrig));
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
