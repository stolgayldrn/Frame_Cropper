#ifndef __HELPERS_FC_H__
#define __HELPERS_FC_H__

#include <string>     // std::string, std::to_string
#include <iostream>
#include <Windows.h>
#include <io.h>     // For access().
#include <sys/types.h>  // For stat().
#include <sys/stat.h>   // For stat().
#define __TY_VIDEO_SEARCH___FPS_PROCESS 4
#define __TY_VIDEO_SEARCH___FRAME_WIDTH 480
#define __TY_VIDEO_SEARCH___FRAME_HEIGHT 360

using namespace std;

int dirExists(const char *path);/*! !*/
void pathControl(string Path);
string int2string(int number);

#endif