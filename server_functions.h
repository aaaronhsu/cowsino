#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>

#ifndef SERVER_FUNCTIONS_H
#define SERVER_FUNCTIONS_H

void exit_function(int to_client, char buffer[], int size);

#endif