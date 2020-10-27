#ifndef __EXYNOS4412_SERIAL_STDIO_H__
#define __EXYNOS4412_SERIAL_STDIO_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

int serial_printf(int ch, const char * fmt, ...);

#ifdef __cplusplus
}
#endif

#endif /* __EXYNOS4412_SERIAL_STDIO_H__ */
