//author : keke
//date : 2023/02/01 
#pragma once
#ifndef __MYCONFIG__
#define __MYCONFIG__

#if USE_STL_VECTOR
#define _SPC std::
#include <vector>
#include<stack>
#include<queue>
#else
#define _SPC con::
#include<container.hpp>
#endif

#define HAS_QSTRING 1
#if HAS_QSTRING
#include<QString>
#else
#include<string>
using std::string;
#endif
#endif