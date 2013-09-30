/*
 * libconfigini tests
 */

#include <stdio.h>
#include <stdlib.h>

#include "../src/configini.h"


#define CONFIGREADFILE		"../etc/config.cnf"
#define CONFIGSAVEFILE		"../etc/new-config.cnf"

#define ENTER_TEST_FUNC																			\
	do {																						\
		printf("\n-----------------------------------------------------------------------\n");	\
		printf("<TEST: %s>\n\n", __FUNCTION__);													\
	} while (0)




/*
 * Read Config file
 */
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

/*
 * Create Config handle, read Config file, edit and save to new file
 */
static void Test2()
{
	Config *cfg = NULL;

	ENTER_TEST_FUNC;

	/* set settings */
	cfg = ConfigNew();
	ConfigSetBoolString(cfg, "yes", "no");

	/* we can give initialized handle (rules has been set) */
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

/*
 * Create Config handle and add sections & key-values
 */
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

/*
 * Create Config without any section
 */
static void Test4()
{
	Config *cfg = NULL;

	ENTER_TEST_FUNC;

	cfg = ConfigNew();

	ConfigAddString(cfg, CONFIG_SECTNAME_DEFAULT, "Mehmet Akif ERSOY", "Safahat");
	ConfigAddString(cfg, CONFIG_SECTNAME_DEFAULT, "Necip Fazil KISAKUREK", "Cile");
	ConfigAddBool(cfg, CONFIG_SECTNAME_DEFAULT, "isset", true);
	ConfigAddFloat(cfg, CONFIG_SECTNAME_DEFAULT, "degree", 35.0);

	ConfigPrintToStream(cfg, stdout);

	ConfigFree(cfg);
}


int main()
{
	Test1();
	Test2();
	Test3();
	Test4();

	return 0;
}
