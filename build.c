/*
 *  BuildC - v0.1 - simple single file C build system
 *
 *  Author: Gwenivere Benzschawel
 *  Copyright: 2024
 *  License: MIT (see bottom of file)
 *  No warranty implied; use at your own risk
 *
 */

const char* BINARY_FOLDER = "bin";
const char* SOURCE_FOLDER = "src";

/* GCC/clang flags */
const char* GCC_WARN_FLAGS = "-Wall -Wextra -Wpedantic";
const char* GCC_C_STANDARD = "-std=c99";
const char* GCC_LIBRARIES = ""; /* -lm etc... */
const char* GCC_INCLUDE = ""; /* -Ilib/include etc... */

/* MSVC flags */
const char* MSVC_WARN_FLAGS = "/Wall";
const char* MSVC_C_STANDARD = "/std:c11";
const char* MSVC_LIBRARIES = ""; /* TODO learn MSVC better */
const char* MSVC_INCLUDE = ""; /* TODO learn MSVC better */

/*
 *  Uses above flags, the src, and selected compiler to build output with 
 *  chosen name.
 *
 *  returns 0 if success
 */
int compile(const char* src, const char* name);

/*
 *  Change this function to define your project
 */
int buildProject(void){
  /* return compile("main.c", "HelloWorld"); */
}

/* Determine BuildC platform */
#if defined(__linux__) && !defined(__ANDROID__)
#define BUILD_LINUX
#endif /*__linux__ and not __ANDROID__*/

#if defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__)
#define BUILD_BSD
#endif /*__FreeBSD__, __NetBSD__, __OpenBSD__*/

#if defined(macintosh) || defined(Macintosh) || \
  (defined(__APPLE__) && defined(__MACH__))
#define BUILD_APPLE
#endif /*macintosh, Macintosh, __APPLE__ and __MACH__*/

#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || \
  defined(TOS_WIN) || defined(__WINDOWS__)
#define BUILD_WINDOWS
#endif /*_WIN32, _WIN64, __WIN32__, TOS_WIN, __WINDOWS__*/

#if defined(__unix__) || defined(__unix) || defined(BUILD_C_APPLE)
#define BUILD_APPLE
#endif /*__unix__, __unix, BUILD_APPLE*/

/* Compilers suported */
#define CLANG_CC "clang"
#define GNU_CC "gcc"
#define MINGW64_64_CC "x86_64-w64-mingw32-gcc"
#define MINGW64_32_CC "i686-w64-mingw32-gcc"
#define MSVC_CC "cl"

/* Figure out default compiler 'DEFAULT_CC' for BuildC */
#ifdef __clang__
#define DEFAULT_CC CLANG_CC
#endif /*__clang__*/

#ifdef __GNUC__
#define DEFAULT_CC GNU_CC
#endif /*__GNUC__*/

#ifdef  __MINGW64__
#define DEFAULT_CC MINGW64_64_CC
#endif /*__MINGW64__*/

#ifdef __MINGW32__
#define DEFAULT_CC MINGW64_32_CC
#endif /*__MINGW32__*/

#ifdef _MSC_VER
#define DEFAULT_CC MSVC_CC
#endif /*_MSC_VER*/

#include <stdlib.h>
#include <string.h>
#include <alloca.h>
#include <stdio.h>

char* selected_CC;

/* Compile function */
int compile(const char* src, const char* name){
  
  /* MSVC */
  if(strcmp(selected_CC, MSVC_CC) == 0){
    int size = snprintf(NULL, 0, "%s %s %s %s %s %s\\%s /Fe \"%s\\%s\"",
        selected_CC,
        MSVC_WARN_FLAGS,
        MSVC_C_STANDARD,
        MSVC_LIBRARIES,
        MSVC_INCLUDE,
        SOURCE_FOLDER,
        src,
        BINARY_FOLDER,
        name);
    
    size++;

    char* command = alloca(size);
    
    snprintf(command, size, "%s %s %s %s %s %s\\%s /Fe \"%s\\%s\"",
        selected_CC,
        MSVC_WARN_FLAGS,
        MSVC_C_STANDARD,
        MSVC_LIBRARIES,
        MSVC_INCLUDE,
        SOURCE_FOLDER,
        src,
        BINARY_FOLDER,
        name);

    return system(command);
  
  /* GCC/Clang */
  }else{

    int size = snprintf(NULL, 0, "%s %s %s %s %s %s/%s -o %s/%s",
       selected_CC,
       GCC_WARN_FLAGS,
       GCC_C_STANDARD,
       GCC_LIBRARIES,
       GCC_INCLUDE,
       SOURCE_FOLDER,
       src,
       BINARY_FOLDER,
       name);

    size++;

    char* command = alloca(size);
   
    snprintf(command, size, "%s %s %s %s %s %s/%s -o %s/%s",
       selected_CC,
       GCC_WARN_FLAGS,
       GCC_C_STANDARD,
       GCC_LIBRARIES,
       GCC_INCLUDE,
       SOURCE_FOLDER,
       src,
       BINARY_FOLDER,
       name);

    return system(command);

  } 
}

/* Make Directory */
int makeDir(const char* dir){
#ifdef BUILD_WINDOWS
  int size = snprintf(NULL, 0, "mkdir %s", dir);
  size++;
  char* command = _alloca(size);
  snprintf(command, size, "mkdir %s", dir);
  return system(command);
#else
  int size = snprintf(NULL, 0, "mkdir -p %s", dir);
  size++;
  char* command = alloca(size);
  snprintf(command, size, "mkdir -p %s", dir);
  return system(command);
#endif /* BUILD_WINDOWS */
}

int main ( int argc, char **argv ) {
  
  int err;
  
  selected_CC = DEFAULT_CC;

  puts("BuildC building...");
  
  err = makeDir(BINARY_FOLDER);
  if(err != 0){
    printf("Failed to make %s directory!", BINARY_FOLDER);
    return err;
  }

  err =  buildProject();
  if(err == 0 ){
    puts("Success!");
  }else{
    puts("Failed to build!");
  }
  return err;
}
/*
  LICENSE (MIT)

  Copyright (c) 2024 Gwenivere Benzschawel

  Permission is hereby granted, free of charge, to any person obtaining a
  copy of this software and associated documentation files (the "Software"),
  to deal in the Software without restriction, including without limitation
  the rights to use, copy, modify, merge, publish, distribute, sublicense,
  and/or sell copies of the Software, and to permit persons to whom the
  Software is furnished to do so, subject to the following conditions:

  The above copyright notice and this permission notice shall be included
  in all copies or substantial portions of the Software.

  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
  OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
