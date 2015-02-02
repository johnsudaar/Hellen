#include "utils.h"

string to_string(int value) // MinGW Bug
{
	std::ostringstream os ;
	os << value ;
	return os.str() ;
}

void log(string message, int level){ // Logging
    switch(level){
        case INFO:
            cout << "[Info] "<<message<<endl;
            break;
        case WARNING:
            cout << "[Warning] "<<message <<endl;
            break;
        case ERROR:
            cout << "[Error] "<<message <<endl;
            exit(EXIT_FAILURE);
            break;
        default:
            log("WRONG LEVEL : "+message, WARNING);
            break;
    }
}

bool str2int (int &i, string str) // http://stackoverflow.com/questions/194465/how-to-parse-a-string-to-an-int-in-c
{
    const char *s = str.c_str();
    char *end;
    long  l;
    errno = 0;
    l = strtol(s, &end, 0);
    if ((errno == ERANGE && l == LONG_MAX) || l > INT_MAX) {
        return false;
    }
    if ((errno == ERANGE && l == LONG_MIN) || l < INT_MIN) {
        return false;
    }
    if (*s == '\0' || *end != '\0') {
        return false;
    }
    i = l;
    return true;
}
