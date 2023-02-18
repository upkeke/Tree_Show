
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





#endif