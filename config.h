
#pragma once
#ifndef __MYCONFIG__
#define __MYCONFIG__


#define USE_STL_VECTOR 1
#if USE_STL_VECTOR
#define _SPC std::
#include <vector>
#include<stack>
#include<queue>
#else
#define _SPC con::
#include<container.hpp>
#endif

#define HAS_QSTRING 0
#if HAS_QSTRING
#include<QString>
using _string = QString;
#else
#include<string>
using std::string;
using _string = string;
#endif

#endif