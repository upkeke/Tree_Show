
#pragma once
#ifndef __GRAPUI_BIN__
#define __GRAPUI_BIN__

/**
 * @brief 配置文件方便导出符号
 * 
 */
#ifdef GRAPUI_BIN
#define GRAPUI_LIB_EXPORT Q_DECL_EXPORT
#else
#define GRAPUI_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif
