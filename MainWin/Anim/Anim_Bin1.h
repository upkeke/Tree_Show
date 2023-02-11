
#pragma once
#ifndef __ANIM_BIN_H1__
#define __ANIM_BIN_H1__

/**
 * @brief 配置文件方便导出符号
 * 
 */
#ifdef ANIM_LIB_CCXX
#define ANIM_LIB_EXPORT_XX Q_DECL_EXPORT
#else
#define ANIM_LIB_EXPORT_XX Q_DECL_IMPORT
#endif

#endif
