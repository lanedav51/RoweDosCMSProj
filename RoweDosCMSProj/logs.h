#pragma once

#include <string>
#include "logEntry.h"
using namespace std;

bool logEvent(string username, string logDesc);
bool logFileExist();
bool createLogCsv();

void printReport();
bool downloadReport();