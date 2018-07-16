#include <stdio.h>
#include <stdlib.h>
#include "project.h"
#include "experiment.h"
#include "activity.h"
#include "agent.h"
#include "dataFile.h"
#include "provider.h"
#include "cluster.h"
#include "machine.h"
#include "database10.h"
#include "database11.h"
#include "database20.h"
#include "database30.h"
#include "grid.h"
#include "commands.h"
#define N 300

int activityNumber = 1;
int main (){

//  getFileName("sickle se --fastq-file SRR5181508.fastq --qual-type sanger --output-file SRR5181508_FILTERED.fastq -q 30 -l 25");


  ////getchar();
  time_t t;
  struct tm tm;
  FILE *log = fopen("log.txt", "a+");
  fprintf(log,"\n\n\t--------- LOG ---------");

  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nbegin: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  project *projects = NULL;
  projects = insert_project(projects);

  experiment *experiments = NULL;
  experiments = insert_experiment(experiments, projects);

  agent *agents = NULL;
  agents = insert_agent(agents);

  dataFile *dataFiles = NULL;
  char fileBaseName[N];


  activity *activitys = NULL;
  while(activityNumber < 7){
    activitys = insert_activity(activitys, &activityNumber, "Homo_sapiens.GRCh38.dna.chromosome.22", dataFiles);
    printf("\n >>. %d", activityNumber);
      printf("\n >>. %d", activityNumber);
        printf("\n >>. %d", activityNumber);
          printf("\n >>. %d", activityNumber);
    //getchar();

  }
  dataFiles = returnUsedFiles();
  provider *providers = NULL;
  providers = insert_provider(providers);

  cluster *clusters = NULL;
  clusters = insert_cluster(clusters, providers);

  machine *machines = NULL;
  machines = insert_machine(machines, dataFiles);

  /// NO INDEXES
  //////////////////////////// MODEL 1.0 - N COLLECTIONS - N DOCUMENTS /////////////////////////////////
  fprintf(log," \t---- MODEL 1.0 ----");
 printf(" \t---- MODEL 1.0 ----");
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  CreateDatabase10(false, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

 //////////////////////////// MODEL 1.1 - 1 COLLECTIONS - N DOCUMENTS/////////////////////////////////
/*  fprintf(log," \t---- MODEL 1.1 ----");
 printf(" \t---- MODEL 1.1 ----");
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  CreateDatabase11(false, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
*/
  //////////////////////////// MODEL 2.0 - 1 COLLECTION - 1 DOCUMENT/////////////////////////////////
   fprintf(log," \t---- MODEL 2.0 ----");
  printf(" \t---- MODEL 2.0 ----");
   t = time(NULL);
   tm = *localtime(&t);
   fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

   CreateDatabase20(false, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
   t = time(NULL);
   tm = *localtime(&t);
   fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


   //////////////////////////// MODEL 3.0 - REFERENCIA  /////////////////////////////////
    fprintf(log," \t---- MODEL 3.0 ----");
   printf(" \t---- MODEL 3.0 ----");
    t = time(NULL);
    tm = *localtime(&t);
    fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

    CreateDatabase30(false, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
    t = time(NULL);
    tm = *localtime(&t);
    fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


/*

      /// INDEXES
      //////////////////////////// MODEL 1.0 - N COLLECTIONS - N DOCUMENTS /////////////////////////////////
      fprintf(log," \t---- MODEL 1.0 ----");
     printf(" \t---- MODEL 1.0 ----");
      t = time(NULL);
      tm = *localtime(&t);
      fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

      CreateDatabase10(true, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
      t = time(NULL);
      tm = *localtime(&t);
      fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

     //////////////////////////// MODEL 1.1 - 1 COLLECTIONS - N DOCUMENTS/////////////////////////////////
      fprintf(log," \t---- MODEL 1.1 ----");
     printf(" \t---- MODEL 1.1 ----");
      t = time(NULL);
      tm = *localtime(&t);
      fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

      CreateDatabase11(true, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
      t = time(NULL);
      tm = *localtime(&t);
      fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

      //////////////////////////// MODEL 2.0 - 1 COLLECTION - 1 DOCUMENT/////////////////////////////////
       fprintf(log," \t---- MODEL 2.0 ----");
      printf(" \t---- MODEL 2.0 ----");
       t = time(NULL);
       tm = *localtime(&t);
       fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

       CreateDatabase20(true, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
       t = time(NULL);
       tm = *localtime(&t);
       fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);


       //////////////////////////// MODEL 3.0 - REFERENCIA  /////////////////////////////////
        fprintf(log," \t---- MODEL 3.0 ----");
       printf(" \t---- MODEL 3.0 ----");
        t = time(NULL);
        tm = *localtime(&t);
        fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

        CreateDatabase30(true, providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
        t = time(NULL);
        tm = *localtime(&t);
        fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
*/
  //limpeza


  freedom_provider(providers);
  freedom_cluster(clusters);
  freedom_machine(machines);
  freedom_project(projects);
  freedom_experiment(experiments);
  freedom_activity(activitys);
  freedom_dataFile(dataFiles);


  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nend: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  fprintf(log," \t---- END OF EXECUTION ----");

  fclose(log);


  printf("\n");
  return 0;
}
