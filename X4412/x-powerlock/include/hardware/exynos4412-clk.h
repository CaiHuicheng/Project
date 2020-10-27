#ifndef __EXYNOS4412_CLK_H__
#define __EXYNOS4412_CLK_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

void exynos4412_clk_initial(void);
bool_t clk_get_rate(const char * name, u64_t * rate);

#ifdef __cplusplus
}
#endif

#endif /* __EXYNOS4412_CLK_H__ */
