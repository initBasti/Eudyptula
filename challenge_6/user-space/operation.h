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

#define NODE_MAX_LENGTH 50
#define DEV_NODE_MIN_LENGTH 6
#define DEV_NODE_MAX_LENGTH 50
#define MSG_LEN 1000
#define MIN_BUFFER 2

int open_device(char*);
int read_device(int, char *);
int write_device(int, char *);
void release_device(int);
int read_from_device(char*, char*);
int write_to_device(char*, char*);
#endif
