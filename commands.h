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

char *searchProgramUsed(char command[N]);
char *searchProgramVersion(char command[N]);



#endif
