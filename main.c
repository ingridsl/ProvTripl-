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

  provider *providers = NULL;
  providers = insert_provider(providers);

  cluster *clusters = NULL;
  clusters = insert_cluster(clusters, providers);

  machine *machines = NULL;
  machines = insert_machine(machines, clusters);

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
    activitys = insert_activity(activitys, &(*dataFiles), &activityNumber, "22_20-21M");
  }
  //insert_activity(activitys);

 

  CreateDatabase(providers, clusters, machines, projects, experiments, activitys, agents);
  
  //limpeza
  freedom_provider(providers);
  freedom_cluster(clusters);
  freedom_machine(machines);
  freedom_project(projects);
  freedom_experiment(experiments);
  freedom_activity(activitys);
  freedom_dataFile(dataFiles);

  //freedom_activity(activitys);

  printf("\n");
  return 0;
}
