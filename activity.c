#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "activity.h"
#include "commands.h"

//files *used_files = NULL;

dataFile *used_files = NULL;
int fileAmount = 0;

int getFileAmount(){

	return fileAmount;
}
dataFile *returnUsedFiles(){
	return used_files;
}

activity *define_activity(int *activityNumber, dataFile *dataFileOrig, bool teste, commands *thisCommand){ //falta incluir aquivos na lista de arquivos

	activity *original = (activity*)malloc(sizeof(activity));

   	time_t t;
	struct tm tm;
    if(!original){
		printf("\nError");
	    exit(1);
	}
	int value;
	char inputFile[N],inputFile1[N], inputFile2[N], inputFile3[N], inputFileDefault[N];
	char outputFile[N], outputFileDefault[N];
	char command[N] = "";
	switch((*activityNumber)){
		case 1:
			strcpy(command, " ");
			printf("thisCommand->command %s", thisCommand->command);
			//////////getchar();
		   	strcpy(command, thisCommand->command);
				getFileName(command);

				if(teste){
					strcpy(inputFile1, "SRR5181508.fastq");
		   		strcpy(outputFile, "SRR5181508_FILTERED.fastq");
				}else{
					strcpy(inputFile1, getInputFile());
		   		strcpy(outputFile, getOutputFile());
				}
				printf("\n INPUTFILE: %s, OUTPUTFILE %s\n", inputFile1, outputFile);
				//getchar();
				used_files = insert_dataFile(used_files, inputFile1);
				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);

				used_files = insert_dataFile(used_files, outputFile);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);


		    printf("\n\t:::::: COMANDO 1 :::::: \n%s \n", command);
   			printf("::::::");

   			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			system(command);

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
			resetInputFile();
			resetInputFile2();
			resetOutputFile();
		break;
		case 2:

				resetFileNumber();
				strcpy(command, " ");
				strcpy(command, thisCommand->command);
				printf("COMAND QUE CHEGOU: %s", command);
				//////////getchar();
				getFileName(command);


				if(teste){
					strcpy(inputFile1, "Homo_sapiens.GRCh38.dna.chromosome.22.fa");
				}else{
					strcpy(inputFile1, getInputFile());
				}

				used_files = insert_dataFile(used_files, inputFile1);
				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);

				if(teste){
					strcpy(outputFileDefault, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
				}else{
					strcpy(outputFileDefault, getOutputFile());
				}
				outputFileDefault[strlen(outputFileDefault)]='\0';
				//printf("\n\nentrou!!! %s\n", outputFileDefault);
				//printf("\n%d-%d", (int)strlen(outputFileDefault), (int)strlen("Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx"));

				if(outputFileDefault[strlen(outputFileDefault)-1]!='q'){
					outputFileDefault[strlen(outputFileDefault)-1]='\0';
				}
				//printf("\n\nentrou!!! %s\n", outputFileDefault);
				//printf("\n%c-H", outputFileDefault[0]);
				//printf("\n%d-%d", (int)strlen(outputFileDefault), (int)strlen("Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx"));


				//Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx
				if(strcmp(outputFileDefault, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx") ==0){
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[0],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[1],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[2],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[3],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[4],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[5],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[6],"%d", value);
					//////////////////////////////////////////////////////////////////////////
					buildFileName(outputFileDefault, outputFile);
					used_files = insert_dataFile(used_files, outputFile);

					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[7],"%d", value);
					printf("right input");
				}else{

					used_files = insert_dataFile(used_files, outputFileDefault);
					value = retrieveDataFileId(outputFileDefault, used_files);
					sprintf(original->command_output[0],"%d", value);
					printf("wrong input");

				}
				printf("\n INPUTFILE: %s, OUTPUTFILE %s\n", inputFile1, outputFileDefault);
				//////////getchar();

		    printf("\n\t:::::: COMANDO 2 :::::: \n%s \n", command);
   			printf("::::::");

   			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			system(command);

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
			resetInputFile();
			resetInputFile2();
			resetOutputFile();
			break;
		case 3:

			resetFileNumber();
			strcpy(command, " ");
			strcpy(command, thisCommand->command);


			getFileName(command);
			//strcpy(inputFile1, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
			if(teste){
				strcpy(inputFileDefault, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
				strcpy(inputFile1, "SRR5181508_FILTERED.fastq"); //file_1.fq
				strcpy(outputFile, "file.sam"); // file.sam
			}else{
				strcpy(inputFileDefault, getInputFile());
				//strcpy(inputFile2, getInputFile());
				if(strcmp(getInputFile2(), " ") != 0 ){
					printf("file2");
					strcpy(inputFile1, getInputFile2()); //file_1.fq
				}
				strcpy(outputFile, getOutputFile()); // file.sam
				printf("\noutpufile befpre %s", outputFile);
				abyssOutput(command);
				strcpy(outputFile, getOutputFile());
				outputFile[strlen(outputFile)-1]='\0';
				printf("\noutpufile afeter %s", outputFile);
			}
			used_files = insert_dataFile(used_files, inputFile1);

			//value = retrieveDataFileId(inputFile1, used_files);
			//sprintf(original->command_input[0],"%d", value);
			value = retrieveDataFileId(inputFile1, used_files);
			sprintf(original->command_input[0],"%d", value);

			printf("\n INPUTFILE: %s, INPUTFILE2: %s, OUTPUTFILE %s\n", inputFile1, inputFileDefault, outputFile);
			//////////getchar();

			printf("\n\nentrou!!! %s\n", inputFileDefault);
			printf("\n%c-H", inputFileDefault[0]);
			printf("\n%d-%d", (int)strlen(inputFileDefault), (int)strlen("Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx"));


			printf("\n INPUTFILE: %s, INPUTFILE2: %s, OUTPUTFILE %s\n", inputFile1, inputFileDefault, outputFile);


			if(strcmp(inputFileDefault, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx")==0){
				//strcpy(outputFile, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx");
				printf("input certo");
				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[1],"%d", value);
				printf("\n>>%s", original->command_input[1]);

				//////////////////////////////////////////////////////////////////////////

				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[2],"%d", value);
				printf("\n>>%s", original->command_input[2]);

				//////////////////////////////////////////////////////////////////////////

				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[3],"%d", value);
				printf("\n>>%s", original->command_input[3]);

				//////////////////////////////////////////////////////////////////////////
				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[4],"%d", value);
				printf("\n>>%s", original->command_input[4]);
				////////////getchar();
				//////////////////////////////////////////////////////////////////////////

				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[5],"%d", value);
				printf("\n>>%s", original->command_input[5]);
				////////////getchar();
				//////////////////////////////////////////////////////////////////////////

				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[6],"%d", value);
				printf("\n>>%s", original->command_input[6]);
				////////////getchar();
				//////////////////////////////////////////////////////////////////////////

				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files,inputFile);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[7],"%d", value);
				//////////////////////////////////////////////////////////////////////////

				buildFileName(inputFileDefault, inputFile);
				used_files = insert_dataFile(used_files, inputFile);

				value = retrieveDataFileId(inputFile, used_files);
				sprintf(original->command_input[8],"%d", value);
			}else{
				printf("input errado");
				used_files = insert_dataFile(used_files, inputFileDefault);
				value = retrieveDataFileId(inputFileDefault, used_files);
				sprintf(original->command_input[1],"%d", value);

			}


				printf("\n INPUTFILE: %s, INPUTFILE2: %s, OUTPUTFILE %s\n", inputFileDefault, inputFile1, outputFile);
				//////////getchar();
				if(strstr(command, "abyss")!=NULL){

					//"coverage.hist"
					used_files = insert_dataFile(used_files, "coverage.hist");
					value = retrieveDataFileId("coverage.hist", used_files);
					sprintf(original->command_output[0],"%d", value);

					//ERR885455_KMER_28-bubbles.fa
					char auxOutputFile[N];
					//outputFile[strlen(outputFile-1)]='';
					sprintf(auxOutputFile,"%s-bubbles.fa", outputFile);
					printf("\nAUX FILE>>>> %s", auxOutputFile);
					//strcpy(auxOutputFile, outputFile);
					//strncat(auxOutputFile, "-bubbles.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[1],"%d", value);

					//ERR885455_KMER_28-contings.fa
					sprintf(auxOutputFile,"%s-contigs.fa", outputFile);
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[2],"%d", value);

					//ERR885455_KMER_28-contings.dot
					sprintf(auxOutputFile,"%s-contigs.dot", outputFile);
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[3],"%d", value);

					//ERR885455_KMER_28-indel.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-indel.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[4],"%d", value);

					//ERR885455_KMER_28-scaffolds.dot
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-scaffolds.dot");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[5],"%d", value);

					//ERR885455_KMER_28-scaffolfs.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-scaffolds.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[6],"%d", value);

					//ERR885455_KMER_28-stats
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-stats");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[7],"%d", value);

					//ERR885455_KMER_28-unitigs.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-unitigs.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[8],"%d", value);

					//ERR885455_KMER_28-1.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-1.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[9],"%d", value);

					//ERR885455_KMER_28-1.adj
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-1.adj");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[10],"%d", value);

					//ERR885455_KMER_28-1.path
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-1.path");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[11],"%d", value);

					//ERR885455_KMER_28-2.adj
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-2.adj");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[12],"%d", value);

					//ERR885455_KMER_28-2.path
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-2.path");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[13],"%d", value);

					//ERR885455_KMER_28-3.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-3.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[14],"%d", value);

					//ERR885455_KMER_28-3.adj
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-3.adj");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[15],"%d", value);

					//ERR885455_KMER_28-3.dist
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-3.dist");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[16],"%d", value);

					//ERR885455_KMER_28-3.hist
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-3.hist");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[17],"%d", value);

					//ERR885455_KMER_28-4.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-4.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[18],"%d", value);

					//ERR885455_KMER_28-4.adj
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-4.adj");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[19],"%d", value);

					//ERR885455_KMER_28-4.path1
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-4.path1");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[20],"%d", value);

					//ERR885455_KMER_28-4.path2
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-4.path2");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[21],"%d", value);

					//ERR885455_KMER_28-4.path3
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-4.path3");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[22],"%d", value);

					//ERR885455_KMER_28-5.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-5.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[23],"%d", value);

					//ERR885455_KMER_28-5.adj
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-5.adj");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[24],"%d", value);

					//ERR885455_KMER_28-5.path
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-5.path");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[24],"%d", value);

					//ERR885455_KMER_28-6.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-6.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[25],"%d", value);

					//ERR885455_KMER_28-6.dot
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-6.dot");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[26],"%d", value);

					//ERR885455_KMER_28-6.hist
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-6.hist");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[27],"%d", value);

					//ERR885455_KMER_28-6.path
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-6.path");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[28],"%d", value);

					//ERR885455_KMER_28-6.dist.dot
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-6.dist.dot");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[29],"%d", value);

					//ERR885455_KMER_28-6.path.dot
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-6.path.dot");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[30],"%d", value);

					//ERR885455_KMER_28-7.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-7.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[31],"%d", value);

					//ERR885455_KMER_28-7.adj
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-7.adj");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[32],"%d", value);

					//ERR885455_KMER_28-7.path
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-7.path");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[33],"%d", value);

					//ERR885455_KMER_28-8.fa
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-8.fa");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[34],"%d", value);

					//ERR885455_KMER_28-8.dot
					strcpy(auxOutputFile, outputFile);
					strcat(auxOutputFile, "-8.dot");
					used_files = insert_dataFile(used_files, auxOutputFile);
					value = retrieveDataFileId(auxOutputFile, used_files);
					sprintf(original->command_output[35],"%d", value);
					fileAmount = 41;



				}else{
					used_files = insert_dataFile(used_files, outputFile);
					value = retrieveDataFileId(outputFile, used_files);
					sprintf(original->command_output[0],"%d", value);
					fileAmount = 14;
				}


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

			system(command);

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

			resetInputFile();
			resetInputFile2();
			resetOutputFile();
			break;
		case 4:
			strcpy(command, " ");
			strcpy(command,thisCommand->command);
			getFileName(command);
			if(teste){
				strcpy(inputFile1, "file.sam");
				strcpy(outputFile, "file.bam");
			}else{
				strcpy(inputFile1, getInputFile());
				strcpy(outputFile, getOutputFile());
				outputFile[strlen(outputFile)-1]='\0';
			}

				used_files = insert_dataFile(used_files, inputFile1);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);

				used_files = insert_dataFile(used_files, outputFile);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

			/*strcpy(command, "samtools view -bS ");
		    strcat(command, inputFile1);
		    strcat(command, " > ");
		    strcat(command, outputFile);*/

		    printf("\n:::::: COMANDO 4 :::::: \n%s \n", command);
   			printf("::::::");
			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			system(command);

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

			resetInputFile();
			resetInputFile2();
			resetOutputFile();
			break;
		case 5:
			strcpy(command, " ");
			strcpy(command, thisCommand->command);
			getFileName(command);

			if(teste){
				strcpy(inputFile1, "file.bam");
		    strcpy(outputFile, "file_sorted.sn.bam");
			}else{
				strcpy(inputFile1, getInputFile());
		    strcpy(outputFile, getOutputFile());
				printf("\n>> outputfile %s", outputFile);
				outputFile[strlen(outputFile)-1]='.';
				printf("\n>> outputfile %s", outputFile);
				strcat(outputFile, "bam");
				printf("\n>> outputfile %s", outputFile);
				//////getchar();
			}


				used_files = insert_dataFile(used_files, inputFile1);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);

				used_files = insert_dataFile(used_files, outputFile);

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

			system(command);

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

			resetInputFile();
			resetInputFile2();
			resetOutputFile();
			break;
		case 6:

			strcpy(command, " ");
			strcpy(command, thisCommand->command);
			getFileName(command);

			if(teste){
				strcpy(inputFile1, "file_sorted.sn.bam");
				strcpy(inputFile2, "Homo_sapiens.GRCh38.88.gtf");
			   	strcpy(outputFile, "file.count");
			}else{
				strcpy(inputFile1, getInputFile());
				strcpy(inputFile2, getInputFile2());
			   	strcpy(outputFile, getOutputFile());
					outputFile[strlen(outputFile)-1]='\0';
			}



				used_files = insert_dataFile(used_files, inputFile1);
				used_files = insert_dataFile(used_files, inputFile2);

				value = retrieveDataFileId(inputFile1, used_files);
				sprintf(original->command_input[0],"%d", value);
				value = retrieveDataFileId(inputFile2, used_files);

				used_files = insert_dataFile(used_files, outputFile);
				sprintf(original->command_input[1],"%d", value);
				value = retrieveDataFileId(outputFile, used_files);
				sprintf(original->command_output[0],"%d", value);

		    printf("\n:::::: COMANDO 6 :::::: \n%s \n", command);
   			printf("::::::");
			// GET TIME
   			t = time(NULL);
			tm = *localtime(&t);
			printf("now: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
			sprintf(original->start_date, "%d-%d-%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday);
			sprintf(original->start_hour,"%d:%d:%d", tm.tm_hour, tm.tm_min, tm.tm_sec);

			system(command);

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
			resetInputFile();
			resetInputFile2();
			resetOutputFile();
			break;
		default:
			(*activityNumber)++;
			break;

	}

	original->experiment_id = 1;
	original->agent_id = 1;
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
activity *insert_activity(activity *origin, int *activityNumber, dataFile *dataFileOrig, commands *thisCommand){
	activity *aux = origin;

	//activity *new = create_activity(); //trocar

	activity *new = define_activity(activityNumber, &(*dataFileOrig), false, thisCommand);


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
