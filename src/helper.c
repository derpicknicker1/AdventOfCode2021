#include "advent.h"

int toI(char *s) {
	int sum = 0, min = false;
	if(*s == '-') {
		*s++;
		min = true;
	}
	if(*s == '+')
		*s++;
    while (*s && *s != '\n')
        sum = sum * 10 + (*s++ - '0');
    return min?-sum:sum;
}

char *ltrim(char *s) {
    while(isspace(*s)) s++;
    return s;
}

char *rtrim(char *s) {
    char* back = s + strlen(s);
    while(isspace(*--back));
    *(back+1) = '\0';
    return s;
}

char *trim(char *s) {
    return rtrim(ltrim(s)); 
}

int isDigit(char c) {
	if(c >= 48 && c <= 57)
		return true;
	return false;
}

int isHexDigit(char c) {
	if( isDigit(c) || (c >= 97 && c <= 102))
		return true;
	return false;
}