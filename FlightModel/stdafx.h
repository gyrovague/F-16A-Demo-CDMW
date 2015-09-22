// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#define DH_COMMON_D3D_H
#pragma once

#pragma warning(disable: 4996) 
#pragma warning(disable: 4244) 
#pragma warning(disable: 4800)
#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers
// Windows Header Files:
#include <windows.h>

// Visual Studio is rather dumb at times..
// -> moved to project settings
/*#define _USE_MATH_DEFINES*/ 
#include <cmath>

#include <malloc.h>
#include <memory.h>
#include <mmsystem.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <d3dx9math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <time.h>
#include <psapi.h>
#include <TlHelp32.h>
#include <fcntl.h>
#include <io.h>
#include <random>
#include <algorithm>

#include <cstdint>
#include <Dwmapi.h> 

#include <string>
#include <stdio.h>
#include <tchar.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <intrin.h>
#include <vector>
#include <math.h>
#include <WinInet.h>
#include <Winsock2.h>
#include <intrin.h>
#include <detours.h>



#pragma comment(lib,"detours.lib")
#pragma comment(lib,"Psapi.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "d3d9.lib")
#pragma comment(lib,"wininet.lib")
#pragma comment (lib, "Dwmapi.lib")


