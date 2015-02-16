#ifndef UTILS_H_INCLUDED
#define UTILS_H_INCLUDED

#include <iostream>
#include <cstdlib>
#include <string>
#include <cerrno>
#include <climits>
#include <sstream>

#define INFO 0
#define WARNING 1
#define ERROR 2

using namespace std;

string to_string(int value);
void log(string message, int level); // Logging
bool str2int (int &i, string s); // string to int conversion


#endif // UTILS_H_INCLUDED
