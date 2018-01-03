#include <stdio.h>
#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include "database.h"

int main (){
  char file[N];

/*
  //words *files = NULL;  //FAZER LISTA DE NOMES DE DOCUMENTOS. SEM REPETIR!

  printf("Write fasta file name: ");
  scanf("%s", file); //provenance -  what
  //printf("%s", file);
  //return file;
  //strcpy(file, getFileName("fasta"));
  printf("\n%s", file);
  workflow *wf = NULL;
*/
  wf = create_wf (NULL, getlogin(), os);
 
	
  wf = command1(file, wf, files);
  printf("\n");
  wf = command2(file, wf, files);
  printf("\n");
  wf = command3(wf, files);
  printf("\n");
  wf = command4(wf, files);
  printf("\n");
  wf = command5(wf, files);
  printf("\n");
  wf = command6(wf, files);
  printf("\n");

  //print(wf);
  //files = searchFileName(wf, files);
  CreateDatabase(wf);
  //runWord();


  freedom(wf);
  freedomWord(files);


  printf("\n");
  return 0;
}


