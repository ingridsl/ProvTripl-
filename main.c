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
  char file[N];

  //montar documento project -> experiment -> activity -> agent
  //ao montar activity, roda os programas
  //montar documento provedor -> cluster -> maquina
  provider *providers = NULL;
  providers = insert_provider(providers);

  cluster *clusters = NULL;
  clusters = insert_cluster(clusters, providers);

  machine *machines = NULL;
  machines = insert_machine(machines, clusters);

  CreateDatabase(providers, clusters, machines);
  //montar documento arquivo

  //limpeza
  freedom_provider(providers);
  freedom_cluster(clusters);
  freedom_machine(machines);

  printf("\n");
  return 0;
}
