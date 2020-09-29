//  #define _TASK_TIMECRITICAL      // Enable monitoring scheduling overruns
#define _TASK_SLEEP_ON_IDLE_RUN // Enable 1 ms SLEEP_IDLE powerdowns between tasks if no callback methods were invoked during the pass
#define _TASK_STATUS_REQUEST    // Compile with support for StatusRequest functionality - triggering tasks on status change events in addition to time only
#define _TASK_WDT_IDS           // Compile with support for wdt control points and task ids
//  #define _TASK_LTS_POINTER       // Compile with support for local task storage pointer
//  #define _TASK_MICRO_RES         // Support for microsecond resolution
//  #define _TASK_STD_FUNCTION      // Support for std::function (ESP8266 ONLY)
#define _TASK_DEBUG             // Make all methods and variables public for debug purposes
#define _TASK_OO_CALLBACKS
#define _TASK_PRIORITY          // Support for layered scheduling priority
#define _TASK_TIMEOUT           // Support for overall task timeout

#include <TaskScheduler.h>
#include "utils/debug_utils.h"

void dumpTaskInfo(String title, Task *t)
{
    debugV("dumptaskinfo");
    char buffer[128];
    snprintf(buffer, 126, "%s\nTask ID: %u; interval: %lu; isEnabled: %d; runCounter: %lu; iterations: %ld; %lu;\n",
                        title.c_str(), t->getId(), t->getInterval(), t->isEnabled(), t->getRunCounter(), t->getIterations(), millis());
    debugV("TaskDump: %s", buffer);

}