#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#ifndef commands_h
#define commands_h

#define N 300

#define hisatversion "2.0.5"
#define hisat "hisat2"

#define htseqversion "0.7.2"
#define htseq "htseq"

#define samtoolsversion "1.4.4"
#define samtools "samtools"

#define sickleversion "1.33"
#define sickle "sickle"

#define abyssversion "1.3.6"
#define abyss "abyss"


char inputFile[N];
char outputFile[N];
char inputFile2[N];


int fileNumber;


typedef struct commands{
  char command[N];
  struct commands *next;
}commands;

int getAmount();
commands *returnCommands();
void getCommands();

int getFileNumber();
void buildFileName(char *fileName, char *newFile);

char *getInputFile();
char *getInputFile2();
char *getOutputFile();

void resetFileNumber();
void resetInputFile();
void resetInputFile2();
void resetOutputFile();

char *searchProgramUsed(char command[N]);
char *searchProgramVersion(char command[N]);

#endif
