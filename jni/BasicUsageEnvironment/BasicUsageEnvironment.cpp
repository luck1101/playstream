/**********
This library is free software; you can redistribute it and/or modify it under
the terms of the GNU Lesser General Public License as published by the
Free Software Foundation; either version 2.1 of the License, or (at your
option) any later version. (See <http://www.gnu.org/copyleft/lesser.html>.)

This library is distributed in the hope that it will be useful, but WITHOUT
ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
FOR A PARTICULAR PURPOSE.  See the GNU Lesser General Public License for
more details.

You should have received a copy of the GNU Lesser General Public License
along with this library; if not, write to the Free Software Foundation, Inc.,
51 Franklin Street, Fifth Floor, Boston, MA 02110-1301  USA
**********/
// Copyright (c) 1996-2012 Live Networks, Inc.  All rights reserved.
// Basic Usage Environment: for a simple, non-scripted, console application
// Implementation

#include "BasicUsageEnvironment.hh"
#include <stdio.h>
#include <android/log.h>
#define LOG_TAG "live555lib"
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO   , LOG_TAG,__VA_ARGS__)
////////// BasicUsageEnvironment //////////

#if defined(__WIN32__) || defined(_WIN32)
extern "C" int initializeWinsockIfNecessary();
#endif

BasicUsageEnvironment::BasicUsageEnvironment(TaskScheduler& taskScheduler)
: BasicUsageEnvironment0(taskScheduler) {
#if defined(__WIN32__) || defined(_WIN32)
  if (!initializeWinsockIfNecessary()) {
    setResultErrMsg("Failed to initialize 'winsock': ");
    reportBackgroundError();
    internalError();
  }
#endif
}

BasicUsageEnvironment::~BasicUsageEnvironment() {
}

BasicUsageEnvironment*
BasicUsageEnvironment::createNew(TaskScheduler& taskScheduler) {
  return new BasicUsageEnvironment(taskScheduler);
}

int BasicUsageEnvironment::getErrno() const {
#if defined(__WIN32__) || defined(_WIN32) || defined(_WIN32_WCE)
  return WSAGetLastError();
#else
  return errno;
#endif
}

UsageEnvironment& BasicUsageEnvironment::operator<<(char const* str) {
  if (str == NULL) str = "(NULL)"; // sanity check
  LOGI("%s", str);
#ifdef ANDROID
  LOGI("%s", str);
#endif

  printf("%s", str);
  fprintf(stderr, "%s", str);
  return *this;
}

UsageEnvironment& BasicUsageEnvironment::operator<<(int i) {
  LOGI("%d", i);
  printf("%d", i);
  fprintf(stderr, "%d", i);
  return *this;
}

UsageEnvironment& BasicUsageEnvironment::operator<<(unsigned u) {
  LOGI("%u", u);
  printf( "%u", u);
  fprintf(stderr, "%u", u);
  return *this;
}

UsageEnvironment& BasicUsageEnvironment::operator<<(double d) {
  LOGI("%f", d);
  printf("%f", d);
  fprintf(stderr, "%f", d);
  return *this;
}

UsageEnvironment& BasicUsageEnvironment::operator<<(void* p) {
  LOGI("%p", p);
  printf("%p", p);
  fprintf(stderr, "%p", p);
  return *this;
}
