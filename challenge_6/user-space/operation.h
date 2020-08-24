#ifndef OPERATION_H
#define OPERATION_H

#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <error.h>
#include <errno.h>
#include <unistd.h>
#include <fcntl.h>

#define MSG_LEN 100

int read_from_device(char*, char*);
int write_to_device(char*, char*);
#endif
