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
#include "database.h"
#include "database11.h"
#define N 300

int activityNumber = 1;
int main (){
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
    activitys = insert_activity(activitys, &activityNumber, "Homo_sapiens.GRCh38.dna.chromosome.22");
  }

  dataFiles = insert_dataFile(dataFiles, "Homo_sapiens.GRCh38.dna.chromosome.22.fa"); //1
  dataFiles = insert_dataFile(dataFiles, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx"); //2
  dataFiles = insert_dataFile(dataFiles, "SRR5181508.fastq"); //3
  dataFiles = insert_dataFile(dataFiles, "file.sam"); //4
  dataFiles = insert_dataFile(dataFiles, "file.bam"); //5
  dataFiles = insert_dataFile(dataFiles, "file_sorted.sn.bam"); //6
  dataFiles = insert_dataFile(dataFiles, "Homo_sapiens.GRCh38.88.gtf"); //7
  dataFiles = insert_dataFile(dataFiles, "file.count"); //8
  dataFiles = insert_dataFile(dataFiles, "SRR5181508_FILTERED.fastq"); //9

  provider *providers = NULL;
  providers = insert_provider(providers);

  cluster *clusters = NULL;
  clusters = insert_cluster(clusters, providers);

  machine *machines = NULL;
  machines = insert_machine(machines, dataFiles);

  //////////////////////////// MODEL 1.0 - N COLLECTIONS - N DOCUMENTS /////////////////////////////////
  fprintf(log," \t---- MODEL 1.0 ----");
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  CreateDatabase10(providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

 //////////////////////////// MODEL 1.1 - 1 COLLECTIONS - N DOCUMENTS/////////////////////////////////
  fprintf(log," \t---- MODEL 1.1 ----");
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  CreateDatabase11(providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
  t = time(NULL);
  tm = *localtime(&t);
  fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

  //////////////////////////// MODEL 2.0 - 1 COLLECTION - 1 DOCUMENT/////////////////////////////////
   fprintf(log," \t---- MODEL 2.0 ----");
   t = time(NULL);
   tm = *localtime(&t);
   fprintf(log,"\nBEGIN: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

   CreateDatabase20(providers, clusters, machines, projects, experiments, activitys, agents, dataFiles, log);
   t = time(NULL);
   tm = *localtime(&t);
   fprintf(log,"\nEND: %d-%d-%d %d:%d:%d\n", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);

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
