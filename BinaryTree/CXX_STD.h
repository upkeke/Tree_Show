//author : keke
//date : 2023/01/28 
#pragma once
#ifndef __CXX_STD__
#define __CXX_STD__

#define CXX11 201103L
#define CXX14 201402L
#define CXX17 201703L
#define CXX20 202002L

#if defined(__clang__) || defined(__GNUC__)

#define CXX_STD __cplusplus

#elif defined(_MSC_VER)

#define CXX_STD _MSVC_LANG

#endif


#endif