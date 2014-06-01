#include "Logger.h"


Logger::Logger(void)
{
	fp = 0;
}

//----------------------------------------------------------------------------

Logger::~Logger(void)
{
	if (fp != 0)
	{
		fclose(fp);
		fp = 0;
	}
}

//----------------------------------------------------------------------------

bool Logger::Open(char *filename, bool append)
{
	
	if (append)
	{
		fp = fopen(filename, "w+");
	}
	else
	{
		fp = fopen(filename, "w");
	}
	time_t curTime = time(0);
	char *curDate = ctime(&curTime);
	char buffer [50];
	int bufferLen = sprintf (buffer, "\n--- Opening Log --- %s\n", curDate);
	//std::cout << "Using OpenGL: " << glVersion[0] << "." << glVersion[1] << std::endl;
	Write(buffer);
	
	return fp != NULL;
}

//----------------------------------------------------------------------------

void Logger::Write(char *output)
{
	if (fp == 0)
	{
		return;
	}
	/*
	time_t curTime = time(0);
	char *curDate = ctime(&curTime);
	char buffer [100]; // TODO: Make this flexible
	int bufferLen = sprintf (buffer, "%s %s", output, curDate);
	*/
	fwrite(output, sizeof(char), strlen(output), fp);
	fwrite("\n", sizeof(char), 1, fp);
}

//----------------------------------------------------------------------------

void Logger::Close()
{
	if (fp != 0)
	{
		fclose(fp);
	}
}

//----------------------------------------------------------------------------
