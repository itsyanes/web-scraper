
#include "config.h"

ConfigTask* readConfigFile(FILE* f) {
    //int valid = verifySyntax(f);
    //if(valid==0) printf("Unvalid FILE");

    fseek(f,0,SEEK_SET);
    ConfigAction* appActions = malloc(sizeof(ConfigAction)*5);
    ConfigTask* appTasks = malloc(sizeof(ConfigTask)*5);
    int i = 0;
    int j = 0;
    int nbActs = 0;
    char c = fgetc(f);
        appActions[i] = readAction(f);
        i++;
        nbActs++;
        c = fgetc(f);
        char c2 = fgetc(f);
    while(c2 != '=') {
        fseek(f,-1,SEEK_CUR);
        appActions[i] = readAction(f);
        i++;
        nbActs++;
        c = fgetc(f);
        c2 = fgetc(f);
    }
    ConfigTask t;
    t = readTask(f,appActions,nbActs);
    appTasks[j]=t;
    j++;
    c = fgetc(f);
    c = fgetc(f);
    c = fgetc(f);
    c = fgetc(f);
    while(c != EOF) {
        t = readTask(f,appActions,nbActs);
        appTasks[j]=t;
        j++;
        c = fgetc(f);
        c = fgetc(f);
        c = fgetc(f);
        c = fgetc(f);
    }
    return appTasks;
}

ConfigAction readAction(FILE* f) {
    char c = fgetc(f);
    ConfigAction action;
    ConfigElement n = readElement(f);
    action.name = n.value;
    ConfigElement u = readElement(f);
    action.url = u.value;
    c = fgetc(f); // Read the +;
    c = fgetc(f);
    ConfigOption* ops = readOptions(f);
    action.options=ops;
    return action;
}

ConfigTask readTask(FILE* f, ConfigAction* acts, int nbActs) {
    char c = fgetc(f);
    ConfigTask task;
    ConfigElement n = readElement(f);
    task.name = n.value;
    c = fgetc(f);
    while(c!='+') {
        fseek(f,-1,SEEK_CUR);
        ConfigElement n = readElement(f);
        if(n.key[0]=='s') {
            task.seconds = atoi(n.value);
        } else if(n.key[0]=='m') {
            task.minutes = atoi(n.value);
        } else {
            task.hours = atoi(n.value);
        }
        c = fgetc(f);
    }
    c = fgetc(f);
    ConfigAction* l;
    l = readSubActions(f,acts, nbActs);
    task.actions = l;
    return task;
}

ConfigElement readElement(FILE* f) {
    char c = fgetc(f);
    if(c=='{') c = fgetc(f);
    char* left = malloc(sizeof(char)*30);
    char* right = malloc(sizeof(char)*30);
    int i = 0;
    int j = 0;
    int cpt = 0;
    while(c!='-') {
        i++;
        c = fgetc(f);
    }
    fseek(f,-i-1,SEEK_CUR);
    left = fgets(left,i,f);
    c = fgetc(f);
    c = fgetc(f);
    c = fgetc(f);
    c = fgetc(f);
    while(c!='}') {
        j++;
        c = fgetc(f);
    }
    fseek(f,-j,SEEK_CUR);
    right = fgets(right,j,f);
    c = fgetc(f);
    checkComment(f);
    ConfigElement el;
    el.key=left;
    el.value=right;
    return el;
}

void checkComment(FILE* f) {
    char c = fgetc(f);
    if(c==' ') {
        while(c!='\n') {
            c = fgetc(f);
        }
    }
}

ConfigOption* readOptions(FILE* f) {
    ConfigOption* ops = malloc(sizeof(ConfigOption)*10);
    int i = 0;
    ConfigElement e = readElement(f);
    ConfigOption op;
    op.option=e.key;
    op.value=atoi(e.value);
    ops[i]=op;
    i++;
    char c = fgetc(f);
    c = fgetc(f);
    while(c!='\n') {
        fseek(f,-1,SEEK_CUR);
        ConfigElement ee = readElement(f);
        ConfigOption opp;
        opp.option=ee.key;
        opp.value=atoi(ee.value);
        ops[i]=opp;
        i++;
        c = fgetc(f);
    }
    return ops;
}

ConfigAction* readSubActions(FILE* f,ConfigAction* acts,int nbActs) {
    char c = fgetc(f);
    c = fgetc(f);
    ConfigAction* result = malloc(sizeof(ConfigAction)*10);
    int i = 0;
    int j = 0;
    int o = 0;
    int length = 0;
    while(c!=')') {
        char* word = malloc(sizeof(char)*20);
        while(c!=',' && c!=')') {

            word[i]=c;
            i++;
            length++;
            c = fgetc(f);
        }
        if(c!=')') c=fgetc(f);
        i=0;
        for(int z = 0; z < nbActs; z++) {
            if(strcmp(word,acts[z].name)==0) {
                ConfigAction temp;
                temp.name=acts[z].name;
                temp.url=acts[z].url;
                temp.options=acts[z].options;
                result[j]=temp;
            j++;
            }
        }
        length=0;
    }
    return result;
}

int verifySyntax(FILE* f) {
    char c = fgetc(f);
    int cng = 0;
    if(c!='=') {
        printf("Missing Actions");
        return 0;
    }
    fseek(f,-1,SEEK_CUR);
    int act = verifyActionSyntax(f);
    if(act==0) return 0;
    while(c!=EOF) {
        c = fgetc(f);
        if(c != '\n' && c != EOF) {
            printf("Missing RETURN TO LINE");
            return 0;
        }
        c = fgetc(f);
        char c2 = fgetc(f);
        if(c=='=' && c2=='=') {
            cng = 1;
            fseek(f,-3,SEEK_CUR);
            int task = verifyTaskSyntax(f);
            if(task == 0) return 0;
        } else if(c=='=' && c2!='=' && cng == 1) {
            printf("Cant put action after a task");
            return 0;
        } else {
            fseek(f,-3,SEEK_CUR);
            int act2 = verifyActionSyntax(f);
            if(act2 == 0) return 0;
        }
    }
    return 1;
}

int test(FILE* f) {
    int act = verifyTaskSyntax(f);
    char c = fgetc(f);
    int task = verifyTaskSyntax(f);
    if(act == 0 || task == 0) {
        return 0;
    }
    return 1;
}

int verifyTaskSyntax(FILE* f) {
    char c = fgetc(f);
    char c2 = fgetc(f);
    int a = 0;
    int b1 = 0;
    int b2 = 0;
    int b3 = 1;
    int cc = 0;
    if(c != '=' || c2 != '=') {
        printf("Missing == sign");
        return 0;
    }
    c = fgetc(f);
    a = verifyElementSyntax(f);
    c = fgetc(f);
    if(c!='{' && c!='+') {
        printf("Missing + sign");
        return 0;
    }
    if(c=='{') {
        fseek(f,-1,SEEK_CUR);
        b1 = verifyElementSyntax(f);
        c = fgetc(f);
    }
    if(c!='{' && c!='+') {
        printf("Missing + sign");
        return 0;
    }
    if(c=='{') {
        fseek(f,-1,SEEK_CUR);
        b2 = verifyElementSyntax(f);
        c = fgetc(f);
    }
    if(c!='{' && c!='+') {
        printf("Missing + sign");
        return 0;
    }
    if(c=='{') {
        fseek(f,-1,SEEK_CUR);
        b3 = verifyElementSyntax(f);
        c = fgetc(f);
    }
    if(c!='+') {
        printf("Missing + sign");
        return 0;
    }
    c = fgetc(f);
    cc = verifySubActionsSyntax(f);
    c = fgetc(f);
    if(a==0 || b1==0 || b2==0 || b3==0 || cc==0) {
        printf("Syntax Error 2");
        return 0;
    }
    return 1;
}

int verifyActionSyntax(FILE* f) {
    char c = fgetc(f);
    if(c != '=') {
        printf("Missing = signnn");
        return 0;
    }
    c = fgetc(f);
    if(c != '\n') {
        printf("Must return to line after = sign");
        return 0;
    }
    int a = verifyElementSyntax(f);
    int b = verifyElementSyntax(f);
    if(a==0 || b==0) {
        return 0;
    }
    c = fgetc(f);
    if(c != '+') {
        printf("Missing + sign");
        return 0;
    }
    c = fgetc(f);
    if(c != '\n') {
        printf("Must return to line after + sign");
        return 0;
    }
    int a1 = verifyElementSyntax(f);
    int b1 = verifyElementSyntax(f);
    if(a1==0 || b1==0) {
        return 0;
    }
    return 1;
}

int verifySubActionsSyntax(FILE* f) {
    int ind = 0;
    char c = fgetc(f);
    if(c != '(') {
        printf("Missing { sign");
        return 0;
    }
    c = fgetc(f);
    if(c == ',') {
        printf("must have a first action before , sing");
        return 0;
    }
    if(c == ' ') {
        printf("must not leave a space before key");
        return 0;
    }
    while(c != '\n') {
        c = fgetc(f);
        while(c!=')' && c!='\n') {
        if(c==',') {
            fseek(f,-2,SEEK_CUR);
            c = fgetc(f);
            if(c==' ') {
                printf("must not leave space between actions");
                return 0;
            }
            c = fgetc(f);
            c = fgetc(f);
            if(c==' ') {
                printf("must not leave space between actions");
                return 0;
            }
            if(c==',') {
                printf("must not put two commas");
                return 0;
            }
        }
        c = fgetc(f);
        }
        if(c==')') {
            return 1;
        }
    }
    printf("Error in syntax");
    return 0;
}

int verifyElementSyntax(FILE* f) {
    int ind = 0;
    char c = fgetc(f);
    if(c != '{') {
        printf("Missing { sign");
        return 0;
    }
    c = fgetc(f);
    if(c == '-') {
        printf("must have a key");
        return 0;
    }
    if(c == ' ') {
        printf("must not leave a space before key");
        return 0;
    }
    while(c != '\n') {
        c = fgetc(f);
        if(c == ' ') {
            c = fgetc(f);
            if(c!='-') {
                printf("syntax error");
                return 0;
            }
        }
        if(c == '-') {
            fseek(f,-2,SEEK_CUR);
            c = fgetc(f);
            if(c!=' ') {
                printf("must leave space after key");
                return 0;
            }
            c = fgetc(f);
            c = fgetc(f);
            if(c == '>') {
                c = fgetc(f);
                if(c == ' ') {
                    while(c != '\n') {
                        c = fgetc(f);
                        if(c == ' ' && ind == 0) {
                            printf("must not leave two spaces before value");
                            return 0;
                        }
                        ind = 1;
                        if(c=='}') {
                            fseek(f,-2,SEEK_CUR);
                            c = fgetc(f);
                            if(c==' ') {
                                printf("must not leave space after value");
                                return 0;
                            }
                            c = fgetc(f);
                            c = fgetc(f);
                            return 1;
                        }
                    }
                }
            }
        }
    }
    printf("Error in syntax");
    return 0;
}

int verifyOptionsSyntax(FILE* f) {
    int a = verifyElementSyntax(f);
    int b = verifyElementSyntax(f);
    if(a==0 || b==0) {
        return 0;
    }
    return 1;
}
