#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "providerDoc.h"

bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal){
	bson_t   *provider, *cluster, *machine;
	char     *provider_str, *cluster_str;
	bson_oid_t oid;

	bson_oid_init (&oid, NULL);
	provider = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
	//cluster = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

	//falta machine

	char str_clu_id[15];
	sprintf(str_clu_id, "%d", cluOriginal->id);

	char str_clu_number_machines[15];
	sprintf(str_clu_number_machines, "%d", cluOriginal->number_machines);

	cluster = BCON_NEW(
		"id", str_clu_id,
		"name", cluOriginal->name,
		"number_machines", str_clu_number_machines,
		"description", cluOriginal->description
	);

	cluster_str = bson_as_json (cluster, NULL);
	printf (">>>>>>>>>%s\n", cluster_str);


	char str_pro_id[15];
	sprintf(str_pro_id, "%d", proOriginal->id);

	char str_pro_localization_id[15];
	sprintf(str_pro_localization_id, "%d", proOriginal->localization_id);

	provider = BCON_NEW (
      "id", str_pro_id,
      "name", proOriginal->name,
      "url", proOriginal->url,
      "description", proOriginal->description,
      "localization_id", str_pro_localization_id,
      "localization_region", proOriginal->localization_region,
      "localization_zone", proOriginal->localization_zone,
      "cluster",
      	 "[", 
      	 cluster,
      	 "]"
     );
   /*
    * Print the document as a JSON string.
    */
   	/*provider = BCON_NEW (
      //"_id", "userid",
      //"_id", BCON_OID (&oid),
      "id", "10",
      "name", "this project has a name",
      //"seq", counter,
      "OSversion", "os",
      "description", "this is a oroject",
      "Project_ID", "17");*/

   //counter++;

   /*
    * Print the document as a JSON string.
    */
	provider_str = bson_as_json (provider, NULL);
	printf ("%s\n", provider_str);

	bson_free (cluster_str);
	bson_free (provider_str);
   /*
    * Clean up allocated bson documents.
    */
   //bson_destroy (document);
   //counter ++;
	return provider;

}