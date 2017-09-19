#ifndef _COMPRESSTO_H_
#define _COMPRESSTO_H_
#include <fstream>
#include <iostream>
#include <string>
#include <time.h>
#include <stdio.h>

#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>
#include <errno.h>
#include <zlib.h>
#include <sys/timeb.h>
#include "gcommon.h"
#include "picsearch.h"
using namespace std;

int compressto(const char *pStart, char * pCompr, size_t nLen, size_t &nRetLen);

int uncompressto(const char *pStart, char * pCompr, size_t nLen, size_t &nRetLen);

#endif
