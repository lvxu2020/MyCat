#ifndef DEBUG_H_
#define DEBUG_H_

//#include "platform.h"
#include <stdio.h>
#include "LogRecoder.h"

#define DEBUG_POS printf(" -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__);

//#define __WriteLogFile__     // 使能原始数据记录

#define ENABLE_DEBUG_I_RECOD // 使能DEBUG_I记录
//#define ENABLE_DEBUG_I_PRINT // 使能DEBUG_I输出

#if defined ENABLE_DEBUG_I_RECOD && defined ENABLE_DEBUG_I_PRINT
#define DEBUG_I(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_I]", str); printf("DEBUG_I: %s %s", dataStr, dataPos); }
#elif defined ENABLE_DEBUG_I_RECOD
#define DEBUG_I(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_I]", str); }
#elif defined ENABLE_DEBUG_I_PRINT
#define DEBUG_I(format, ...) { printf("DEBUG_I: "#format, ##__VA_ARGS__); DEBUG_POS }
#else
#define DEBUG_I(format, ...)
#endif

#define ENABLE_DEBUG_W_RECOD // 使能DEBUG_W记录
#define ENABLE_DEBUG_W_PRINT // 使能DEBUG_W输出

#if defined ENABLE_DEBUG_W_RECOD && defined ENABLE_DEBUG_W_PRINT
#define DEBUG_W(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_W]", str); printf("DEBUG_W: %s %s", dataStr, dataPos); }
#elif defined ENABLE_DEBUG_W_RECOD
#define DEBUG_W(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_W]", str); }
#elif defined ENABLE_DEBUG_W_PRINT
#define DEBUG_W(format, ...) { printf("DEBUG_W: "#format, ##__VA_ARGS__); DEBUG_POS }
#else
#define DEBUG_W(format, ...)
#endif

#define ENABLE_DEBUG_E_RECOD // 使能DEBUG_E记录
//#define ENABLE_DEBUG_E_PRINT // 使能DEBUG_E输出

#if defined ENABLE_DEBUG_E_RECOD && defined ENABLE_DEBUG_E_PRINT
#define DEBUG_E(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_E]", str); printf("DEBUG_E: %s %s", dataStr, dataPos);}
#elif defined ENABLE_DEBUG_E_RECOD
#define DEBUG_E(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_E]", str); }
#elif defined ENABLE_DEBUG_E_PRINT
#define DEBUG_E(format, ...) { printf("DEBUG_E: "#format, ##__VA_ARGS__); DEBUG_POS }
#else
#define DEBUG_E(format, ...)
#endif

#define ENABLE_DEBUG_D_RECOD // 使能DEBUG_D记录
//#define ENABLE_DEBUG_D_PRINT // 使能DEBUG_D输出

#if defined ENABLE_DEBUG_D_RECOD && defined ENABLE_DEBUG_D_PRINT
#define DEBUG_D(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n", __FILE__,__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_D]", str); printf("DEBUG_D: %s %s", dataStr, dataPos); }
#elif defined ENABLE_DEBUG_D_RECOD
#define DEBUG_D(format, ...) { std::string str; char dataStr[5000] = {}; char dataPos[1000] = {}; sprintf(dataStr, format, ##__VA_ARGS__); sprintf(dataPos, " -->%s:%d: [%s]\n",basename(__FILE__),__LINE__,__FUNCTION__); str.append(dataStr).append(dataPos); LogRecoder::instance().insertLog("[DEBUG_D]", str); }
#elif defined ENABLE_DEBUG_D_PRINT
#define DEBUG_D(format, ...) { printf("DEBUG_D: "#format, ##__VA_ARGS__); DEBUG_POS }
#else
#define DEBUG_D(format, ...)
#endif

#endif
