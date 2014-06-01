#pragma once
#include "stdafx.h"

class Logger
{
public:
	Logger(void);
	~Logger(void);

	bool Open(char *filename, bool append = true);
	void Write(char *output);
	void Close();

private:
	FILE *fp;
};

