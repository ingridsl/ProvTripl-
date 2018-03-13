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

int main (){

  //mainMenu();
  //char file[N];

  /*provider *providers = NULL;
  providers = insert_provider(providers);

  cluster *clusters = NULL;
  clusters = insert_cluster(clusters, providers);

  machine *machines = NULL;
  machines = insert_machine(machines, clusters);

  project *projects = NULL;
  projects = insert_project(projects);

  experiment *experiments = NULL;
  experiments = insert_experiment(experiments, projects);
*/
  activity *activitys = NULL;
  //activitys = insert_activity(activitys, experiments, machines);
  define_activity(activitys);
/*
  agent *agents = NULL;
  agents = insert_agent(agents, activitys);

  CreateDatabase(providers, clusters, machines, projects, experiments, activitys, agents);*/
  //montar documento arquivo

  //limpeza
  /*freedom_provider(providers);
  freedom_cluster(clusters);
  freedom_machine(machines);
  freedom_provider(projects);
  freedom_cluster(experimentss);
  freedom_machine(activitys);
  freedom_machine(agentss);*/

  printf("\n");
  return 0;
}
