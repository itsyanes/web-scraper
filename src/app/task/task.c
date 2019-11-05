#include "task.h"

static void TaskStop(Task *task);
static void TaskStart(Task *task);
static void TaskStartScrap(void *element, size_t index);
static void TaskSleep(Task *task);
static pid_t TaskInit();
static void TaskDestroy(Task *task);
static void TaskScrapersDestroyHook(void *element);

Task *newTask(time_t delay, ArrayList *scrapers)
{
    Task *t = xmalloc(1, sizeof(Task));
    t->delay = delay;
    t->scrapers = scrapers;
    t->start = &TaskStart;
    t->stop = &TaskStop;
    return t;
}

void TaskStop(Task *task)
{
    kill(task->_pid, SIGKILL);
    TaskDestroy(task);
}

void TaskStart(Task *task)
{
    pid_t pid = TaskInit();

    if (pid == PROCESS_CREATION_FAILED)
    {
        TaskDestroy(task);
        return;
    }

    if (pid != 0)
    {
        task->_pid = pid;
        return;
    }

    while (true)
    {
        task->scrapers->proto->forEach(task->scrapers, TaskStartScrap);
        TaskSleep(task);
    }
}

void TaskStartScrap(void *element, size_t index)
{
    Scraper *s = element;
    s->scrap(s);
}

void TaskSleep(Task *task)
{
    struct timeval wait = {task->delay, 0};
    select(0, NULL, NULL, NULL, &wait);
}

pid_t TaskInit()
{
    pid_t pid = fork();

    if (pid == PROCESS_CREATION_FAILED)
    {
        logger.error("Task creation failed!");
    }

    return pid;
}

void TaskDestroy(Task *task)
{
    task->scrapers->proto->destroy(task->scrapers, TaskScrapersDestroyHook);
    free(task);
}

void TaskScrapersDestroyHook(void *element)
{
    Scraper *s = element;
    s->destroy(s);
}