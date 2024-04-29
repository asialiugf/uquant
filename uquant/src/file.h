/*
 * Copyright (C) AsiaLine
 * Copyright (C) kkk, Inc.
 */

#ifndef UBEE_FILE_H
#define UBEE_FILE_H

// #include <uBEE.h>

#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

#include <fstream>
#include <iostream>
#include <string>

namespace uBEE {
using namespace std;
int SaveLine(const char *File, const char *Linebuf);
// int UpdateLine(const char *FileName, char *pc_line) ;
int SaveBin(const char *File, const char *buf, size_t len);
int CountLines(const char *File);
string ReadLine(const char *File, int line, int lines);
// int SaveTick(const char *pca_buf, int len);
// int DispTick(const char *buf) ;

}  // namespace uBEE

#endif  // end UBEE_FILE_H
