#include "stdafx.h"
#include "CustomLogger.h"
#include <iostream>

using namespace std;

CustomLogger::CustomLogger()
{
}


CustomLogger::~CustomLogger()
{
}

void CustomLogger::write(const LogEntry & entry)
{
	cout << "[" << entry.level << "] [" << entry.threadId << "] " << entry.threadName << " - " << entry.msg;
}
