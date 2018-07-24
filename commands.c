#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commands.h"
#include <unistd.h>


//função para construir nome do arquivo que se diversifica usando o getFileNumber

void buildFileName(char *fileName, char *newFile){
	char num[2];

	strcpy(newFile, fileName);
		sprintf(num, "%d", fileNumber);
			strcat(newFile, ".");
			strcat(newFile, num);
			strcat(newFile, ".ht2");
			printf("\n\n%s", newFile);
			fileNumber++;
	//}
	//return newFile;
}

int getFileNumber(){
	return fileNumber;
}

char *getInputFile(){
	return inputFile;
}
char *getInputFile2(){
	return inputFile2;
}
char *getOutputFile(){
	return outputFile;
}
void resetInputFile(){
	strcpy(inputFile, " ");
}
void resetInputFile2(){
	strcpy(inputFile2, " ");
}
void resetOutputFile(){
	strcpy(outputFile, " ");
}
void resetFileNumber(){
	fileNumber = 1;
}
char *searchProgramUsed(char command[N]){
	if(strstr(command, "sickle")!=NULL){
		return sickle;
	}else if(strstr(command, "hisat2")!=NULL){
		return hisat;
	}else if(strstr(command, "samtools")!=NULL){
		return samtools;
	}else if(strstr(command, "htseq")!=NULL){
		return htseq;
	}
}

char *searchProgramVersion(char command[N]){
	if(strstr(command, "sickle")!=NULL){
		return sickleversion;
	}else if(strstr(command, "hisat2")!=NULL){
		return hisatversion;
	}else if(strstr(command, "samtools")!=NULL){
		return samtoolsversion;
	}else if(strstr(command, "htseq")!=NULL){
		return htseqversion;
	}
}

void getFileName(char command[N]){
	int begin=0, final=0;
	char file[N];
	int i, y=0;
	for (i=0; i< strlen(command);i++){
		begin=0;
		final=0;
		y =0;
		if(command[i] == '.'){
				while(command[i] != ' '){
					i--;
				}
				begin = i++;
				while(command[i] != ' ' && i < strlen(command)){
					file[y] = command[i];
					i++;
					y++;
				}
				file[y]='\0';
				final = i--;
				//printf("\n\n>>>>>>>>>>>> %s", file);
				if(access(file, F_OK) != -1){ // file exists
					if(strlen(inputFile)>1){
						strcpy(inputFile2, file);
					}
					else{
						strcpy(inputFile, file);
					}
				}else{ // file dont exist
					strcpy(outputFile, file);
				}
				strcpy(file, " ");
				//printf("\n\n>>>>>>>>>>>> %s - %s - %s", inputFile, inputFile2, outputFile);
				////getchar();
				//resetInputFile();
				//resetInputFile2();
				//resetOutputFile();

		}
		//getFileName(command, i);
	}
	//return NULL;
}
