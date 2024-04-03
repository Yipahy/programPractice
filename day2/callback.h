#ifndef _CALLBACK_H
#define _CALLBACK_H
#include <stdio.h>

void myprint(void* data,void (*func)(void*));
void printInt(void* data);
void printDouble(void* data);
void printChar(void* data);
void printString(void* data);

#endif
