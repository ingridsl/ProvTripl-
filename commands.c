#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commands.h"
#include <unistd.h>


//função para construir nome do arquivo que se diversifica usando o getFileNumber


commands *used_commands = NULL;
int amount = 1;
int getAmount(){

	return amount;
}
commands *returnCommands(){
	return used_commands;
}

void getCommands(){
	char line[N];
	FILE *fp = fopen("commands.txt", "r");
	if(!fp){
		exit(1);
	}

	while(fgets(line, sizeof(line), fp)!= NULL){

			if(strcmp(line, "")!= 0){
				commands *new = (commands*)malloc(sizeof(commands));
				if(!new){
				printf("\nError");
		    	exit(1);
				}
				strcpy(new->command, line);
				printf("reading file: %s  - %d", new->command, amount);
				commands * aux = used_commands;
				if(aux==NULL){
				    aux = new;
				    aux->next = NULL;
						used_commands = aux;
				}

				while(aux->next!=NULL){
					aux = aux->next;
				}
				aux->next = new;
				new->next = NULL;
				amount ++;
		}
	}
	fclose(fp);

}
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
	}else if(strstr(command, "abyss")!=NULL){
		return abyss;
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
	}else if(strstr(command, "abyss")!=NULL){
		return abyssversion;
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

				if(file[0]== '\''){

					char temp;
					int z;
					temp = file[0];
					for(z = 0; z < y-1 ; z++){
						file[z] = file[z + 1];
						file[z + 1] = temp;
					}

				}
				if(file[y-1]== '\''){
					file[y-1]='\0';
				}
				printf("\n\n::: input file depois %s", file);
				getchar();
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
