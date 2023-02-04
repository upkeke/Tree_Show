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

#endif