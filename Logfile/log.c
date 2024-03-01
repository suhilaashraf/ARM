#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdarg.h>
#include "log.h"

static unsigned int SelectedPriority = 0;
static unsigned int SelectedChannel = 0;
static const char *SelectedLogFilePath = "logfile.txt";

void SelectFilePath(const char *LogFilePath)
{
    SelectedLogFilePath = LogFilePath;
}

void SetPriority(LogPriority priority)
{
    SelectedPriority = priority;
}

void SelectOutputchanel(OutputChannel channel)
{
    SelectedChannel = channel;
}

void writeToLogFile(LogPriority priority,const char *message, ...)
{
    if (priority >= SelectedPriority)
    {
        char * Priority[4]={"INFO","WARNING","ERROR","CRITICAL"};
        time_t t = time(NULL);
        struct tm *now = localtime(&t);
        // Format the date and time
        char buffer[80];
        strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", now);
        FILE *logFile = fopen(SelectedLogFilePath, "a");

        if (logFile != NULL)
        {
            if (SelectedChannel == logfile)
            {
                // Write the timestamp and message to the log file
                fprintf(logFile, "[%s] [%s]: ", buffer, Priority[priority]);

                va_list args;
                va_start(args, message);
                vfprintf(logFile, message, args);
                va_end(args);
                fprintf(logFile, "\n");
                // Close the log file
                fclose(logFile);
            }
            else
            {
                printf("[%s] [%s]: ", buffer, Priority[priority]);
                va_list args;
                va_start(args, message);
                vprintf(message, args);
                va_end(args);
                printf("\n");
            }
        }
        else
        {
            perror("Error opening the log file");
        }
    }
}

