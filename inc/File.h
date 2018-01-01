/*
 * Copyright (C) AsiaLine
 * Copyright (C) kkk, Inc.
 */

#ifndef UBEE_FILE_H
#define UBEE_FILE_H

#include <uBEE.h>

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace uBEE
{

int SaveLine(const char *FileName, const char *Linebuf) ;
//int UpdateLine(const char *FileName, char *pc_line) ;
int SaveBin(const char *FileName, const char * buf, size_t len);
//int SaveTick(const char *pca_buf, int len);
//int DispTick(const char *buf) ;

}

#endif // end UBEE_FILE_H
