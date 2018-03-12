#include <bson.h>
#include <bcon.h>
#include <mongoc.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "documents.h"

bson_t   *PROVIDER_DOC(provider *proOriginal, cluster *cluOriginal, machine *macOriginal){
	bson_t   *provider, cluster, machine;
	char     *provider_str;
	bson_oid_t oid;

	bson_oid_init (&oid, NULL);
	provider = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));
	//cluster = BCON_NEW ("_id", BCON_OID (&oid), "key", BCON_UTF8 ("old_value"));

	//falta machine

	char str_clu_id[15];
	sprintf(str_clu_id, "%d", cluOriginal->id);

	char str_clu_number_machines[15];
	sprintf(str_clu_number_machines, "%d", cluOriginal->number_machines);

	char str_pro_id[15];
	sprintf(str_pro_id, "%d", proOriginal->id);

	char str_pro_localization_id[15];
	sprintf(str_pro_localization_id, "%d", proOriginal->localization_id);

	char str_mac_id[15];
	sprintf(str_mac_id, "%d", macOriginal->id);

	char str_mac_localization_id[15];
	sprintf(str_mac_localization_id, "%d", macOriginal->localization_id);

	char str_mac_ip[36];
	sprintf(str_mac_ip, "%ld", macOriginal->ip);

	char str_mac_cpu[15];
	sprintf(str_mac_cpu, "%d", macOriginal->cpu);

	char str_mac_ram_memory[15];
	sprintf(str_mac_ram_memory, "%d", macOriginal->ram_memory);

	char str_mac_disk[36];
	sprintf(str_mac_disk, "%ld", macOriginal->disk);

	char str_mac_price[36];
	sprintf(str_mac_price, "%ld", macOriginal->price);

	char str_mac_price_type[36];
	sprintf(str_mac_price_type, "%ld", macOriginal->price_type);

	provider = BCON_NEW (
      "id", str_pro_id,
      "name", proOriginal->name,
      "url", proOriginal->url,
      "description", proOriginal->description,
      "localization_id", str_pro_localization_id,
      "localization_region", proOriginal->localization_region,
      "localization_zone", proOriginal->localization_zone
     );

	BSON_APPEND_DOCUMENT_BEGIN(provider, "cluster", &cluster);
	BSON_APPEND_UTF8 (&cluster, "id", str_clu_id);
	BSON_APPEND_UTF8 (&cluster, "name", cluOriginal->name);
	BSON_APPEND_UTF8 (&cluster, "number_machines", str_clu_number_machines);
	BSON_APPEND_UTF8 (&cluster, "description", cluOriginal->description);

	BSON_APPEND_DOCUMENT_BEGIN(&cluster, "machine", &machine);
	BSON_APPEND_UTF8 (&machine, "id", str_mac_id);
	BSON_APPEND_UTF8 (&machine, "hostname", macOriginal->hostname);
	BSON_APPEND_UTF8 (&machine, "ip", str_mac_ip);
	BSON_APPEND_UTF8 (&machine, "type", macOriginal->type);
	BSON_APPEND_UTF8 (&machine, "operational_system", macOriginal->operational_system);
	BSON_APPEND_UTF8 (&machine, "cpu", str_mac_cpu);
	BSON_APPEND_UTF8 (&machine, "ram_memory", str_mac_ram_memory);
	BSON_APPEND_UTF8 (&machine, "disk", str_mac_disk);
	BSON_APPEND_UTF8 (&machine, "disk_type", macOriginal->disk_type);
	BSON_APPEND_UTF8 (&machine, "localization", macOriginal->localization);
	BSON_APPEND_UTF8 (&machine, "price", str_mac_price);
	BSON_APPEND_UTF8 (&machine, "price_type", str_mac_price_type);
	BSON_APPEND_UTF8 (&machine, "localization_id", str_mac_localization_id);
	BSON_APPEND_UTF8 (&machine, "localization_region", macOriginal->localization_region);
	BSON_APPEND_UTF8 (&machine, "localization_zone", macOriginal->localization_zone);
	bson_append_document_end(&cluster, &machine);

	bson_append_document_end(provider, &cluster);
   /*
    * Print the document as a JSON string.
    */
	provider_str = bson_as_json (provider, NULL);
	printf ("%s\n", provider_str);
	bson_free (provider_str);
   /*
    * Clean up allocated bson documents.
    */
	return provider;
}