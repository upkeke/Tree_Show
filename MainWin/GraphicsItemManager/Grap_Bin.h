
#ifndef __GRAP_BIN__
#define __GRAP_BIN__

/**
 * @brief 配置文件方便导出符号
 * 
 */
#ifdef GRAP_LIB
#define GRAP_LIB_EXPORT Q_DECL_EXPORT
#else
#define GRAP_LIB_EXPORT Q_DECL_IMPORT
#endif

#endif
