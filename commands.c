#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "commands.h"

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
