/*
   libconfig - a configuration file parser library
   Copyright (C) 2013-present Taner YILMAZ


   This library is free software; you can redistribute it and/or
   modify it under the terms of the GNU Lesser General Public License
   as published by the Free Software Foundation; either version 2.1 of
   the License, or (at your option) any later version.

   This library is distributed in the hope that it will be useful, but
   WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
   Lesser General Public License for more details.

   You should have received a copy of the GNU Library General Public
   License along with this library; if not, see
   <http://www.gnu.org/licenses/>.
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdio.h>


#ifndef __cplusplus

typedef unsigned char bool;
#undef  false
#define false 	0
#undef  true
#define true	(!false)

#endif


typedef struct Config Config;


/**
 * \brief Return types
 */
typedef enum
{
	CONFIG_RET_OK,                /* no error */
	CONFIG_ERR_FILE,              /* file io error (file not exists, cannot open file, ...) */
	CONFIG_ERR_NO_SECTION,        /* section does not exist */
	CONFIG_ERR_NO_KEY,            /* key does not exist */
	CONFIG_ERR_MEMALLOC,          /* memory allocation failed */
	CONFIG_ERR_INVALID_PARAM,     /* invalid parametrs (as NULL) */
	CONFIG_ERR_INVALID_VALUE,     /* value of key is invalid (inconsistent data, empty data) */
	CONFIG_ERR_PARSING,           /* parsing error of data (does not fit to config format) */
} ConfigRet;



#ifdef __cplusplus
extern "C" {
#endif


ConfigRet   ConfigOpenFile(const char *filename, Config **cfg);
ConfigRet   ConfigPrintToFile(const Config *cfg, char *filename);
ConfigRet   ConfigPrintToStream(const Config *cfg, FILE *stream);
ConfigRet   ConfigPrintSettings(const Config *cfg, FILE *stream);

Config*     ConfigNew();
void 	    ConfigFree(Config *cfg);

ConfigRet   ConfigSetCommentCharset(Config *cfg, const char *comment_ch);
ConfigRet   ConfigSetKeyValSepChar(Config *cfg, char ch);
ConfigRet   ConfigSetBoolString(Config *cfg, const char *true_str, const char *false_str);

ConfigRet   ConfigReadString(const Config *cfg, const char *section, const char *key, char *value, int size);
ConfigRet   ConfigReadInt(const Config *cfg, const char *section, const char *key, int *value);
ConfigRet   ConfigReadUnsignedInt(const Config *cfg, const char *section, const char *key, unsigned int *value);
ConfigRet   ConfigReadFloat(const Config *cfg, const char *section, const char *key, float *value);
ConfigRet   ConfigReadDouble(const Config *cfg, const char *section, const char *key, double *value);
ConfigRet   ConfigReadBool(const Config *cfg, const char *section, const char *key, bool *value);

ConfigRet   ConfigAddString(Config * cfg, const char *section, const char *key, const char *value);
ConfigRet   ConfigAddInt(Config * cfg, const char *section, const char *key, int value);
ConfigRet   ConfigAddUnsignedInt(Config * cfg, const char *section, const char *key, unsigned int value);
ConfigRet   ConfigAddFloat(Config * cfg, const char *section, const char *key, float value);
ConfigRet   ConfigAddDouble(Config *cfg, const char *section, const char *key, double value);
ConfigRet   ConfigAddBool(Config * cfg, const char *section, const char *key, bool value);

bool        ConfigHasSection(const Config *cfg, const char *section);

ConfigRet   ConfigRemoveSection(Config *cfg, const char *section);
ConfigRet   ConfigRemoveKey(Config *cfg, const char *section, const char *key);


#ifdef __cplusplus
}
#endif


#endif /* CONFIG_H_ */
