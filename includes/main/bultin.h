#ifndef BULTIN_H
#define BULTIN_H

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/errno.h>

int builtin_pwd(void);
int builtin_echo(char **args);


#endif