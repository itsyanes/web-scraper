#ifndef TASK_H

#define TASK_H

#include "shared/shared.h"
#include "utils/utils.h"

#define PROCESS_CREATION_FAILED -1
#define SIGKILL 9

typedef struct Task Task;
struct Task
{
    time_t delay;
    ArrayList *scrapers;
    pid_t _pid;
    void (*start)(Task *task);
    void (*stop)(Task *task);
};

Task *newTask(time_t delay, ArrayList *scrapers);

#endif