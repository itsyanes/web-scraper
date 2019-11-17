#ifndef CONFIG_H

#define CONFIG_H

#include "shared/shared.h"

// Represente un element du type {key -> value}
struct ConfigElement
{
    char* key;
    char* value;
};
typedef struct ConfigElement ConfigElement;


// Represente un element du type {option -> value (entier)}
struct ConfigOption
{
    char* option;
    int value;
};
typedef struct ConfigOption ConfigOption;

// Represente une action

struct ConfigAction
{
    char* name;
    char* url;
    ConfigOption* options;
};
typedef struct ConfigAction ConfigAction;

// Represente une tache

struct ConfigTask
{
    char* name;
    int seconds;
    int minutes;
    int hours;
    ConfigAction* actions;
};

typedef struct ConfigTask ConfigTask;

// fonctions :

ConfigTask* readConfigFile(FILE* f);
ConfigTask readTask(FILE* f, ConfigAction* acts, int nbActs);
ConfigAction readAction(FILE* f);
ConfigElement readElement(FILE* f);
ConfigOption* readOptions(FILE* f);
ConfigAction* readSubActions(FILE* f,ConfigAction* acts, int nbActs);
int verifyElementSyntax(FILE* f);
int verifyActionSyntax(FILE* f);
int verifyTaskSyntax(FILE* f);

#endif