
#pragma once
#ifndef __ANIM_BIN_H__
#define __ANIM_BIN_H__

/**
 * @brief 配置文件方便导出符号
 * 
 */
#ifdef ANIM_LIB_X
#define ANIM_LIB_EXPORT Q_DECL_EXPORT
#else
#define ANIM_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif
