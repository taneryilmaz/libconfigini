/*
 * libconfig tests
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/config.h"


#define CONFIGREADFILE		"../etc/config.cnf"
#define CONFIGSAVEFILE		"../etc/new-config.cnf"

#define ENTER_TEST_FUNC																			\
	do {																						\
		printf("\n-----------------------------------------------------------------------\n");	\
		printf("<TEST: %s>\n\n", __FUNCTION__);													\
	} while (0)





static void Test1()
{
	Config *cfg = NULL;

	ENTER_TEST_FUNC;

	if (ConfigOpenFile(CONFIGREADFILE, &cfg) != CONFIG_RET_OK) {
		fprintf(stderr, "ConfigOpenFile failed for %s\n", CONFIGREADFILE);
		return;
	}

	ConfigPrintSettings(cfg, stdout);
	ConfigPrintToStream(cfg, stdout);

	ConfigFree(cfg);
}

static void Test2()
{
	Config *cfg = NULL;

	ENTER_TEST_FUNC;

	if (ConfigOpenFile(CONFIGREADFILE, &cfg) != CONFIG_RET_OK) {
		fprintf(stderr, "ConfigOpenFile failed for %s\n", CONFIGREADFILE);
		return;
	}

	ConfigRemoveKey(cfg, "SECT1", "a");
	ConfigRemoveKey(cfg, "SECT2", "aa");
	ConfigRemoveKey(cfg, "owner", "title");
	ConfigRemoveKey(cfg, "database", "file");

	ConfigAddBool(cfg, "SECT1", "isModified", true);
	ConfigAddString(cfg, "owner", "country", "Turkey");

	ConfigPrintSettings(cfg, stdout);
	ConfigPrintToStream(cfg, stdout);
	ConfigPrintToFile(cfg, CONFIGSAVEFILE);

	ConfigFree(cfg);
}

static void Test3()
{
	Config *cfg = NULL;

	ENTER_TEST_FUNC;

	cfg = ConfigNew();

	ConfigSetBoolString(cfg, "true", "false");

	ConfigAddString(cfg, "SECTION1", "Istanbul", "34");
	ConfigAddInt(cfg, "SECTION1", "Malatya", 44);

	ConfigAddBool(cfg, "SECTION2", "enable", true);
	ConfigAddDouble(cfg, "SECTION2", "Lira", 100);

	ConfigPrintSettings(cfg, stdout);
	ConfigPrintToStream(cfg, stdout);

	ConfigFree(cfg);
}

int main()
{
	Test1();
	Test2();
	Test3();

	return 0;
}
