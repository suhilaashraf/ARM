typedef enum 
{
    info,
    warning,
    Error,
    critical,
}LogPriority;

typedef enum 
{
    logfile,
    console
}OutputChannel;

void SelectFilePath(const char *LogFilePath);
void SetPriority(LogPriority priority);
void writeToLogFile ( LogPriority priority,const char* message , ...);
void SelectOutputchanel(OutputChannel channel);
