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
#include "menu.h"
#define N 300

int activityNumber = 1;
int main (){

  //mainMenu();
  //char file[N];

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
  //insert_activity(activitys);

  dataFiles = insert_dataFile(dataFiles, "Homo_sapiens.GRCh38.dna.chromosome.22.fa"); //1
  dataFiles = insert_dataFile(dataFiles, "Homo_sapiens.GRCh38.dna.chromosome.22.hisat2.idx"); //2
  dataFiles = insert_dataFile(dataFiles, "SRR5181508_1.fastq"); //3
  dataFiles = insert_dataFile(dataFiles, "file.sam"); //4
  dataFiles = insert_dataFile(dataFiles, "file.bam"); //5
  dataFiles = insert_dataFile(dataFiles, "file_sorted.sn.bam"); //6
  dataFiles = insert_dataFile(dataFiles, "Homo_sapiens.GRCh38.88.gtf"); //7
  dataFiles = insert_dataFile(dataFiles, "file.count"); //8

  provider *providers = NULL;
  providers = insert_provider(providers);

  cluster *clusters = NULL;
  clusters = insert_cluster(clusters, providers);

  machine *machines = NULL;
  machines = insert_machine(machines, dataFiles);

  CreateDatabase(providers, clusters, machines, projects, experiments, activitys, agents, dataFiles);
  
  //limpeza

  
  freedom_provider(providers);
  freedom_cluster(clusters);
  freedom_machine(machines);
  freedom_project(projects);
  freedom_experiment(experiments);
  freedom_activity(activitys);
  //freedom_dataFile(dataFiles);

  //freedom_activity(activitys);

  printf("\n");
  return 0;
}
