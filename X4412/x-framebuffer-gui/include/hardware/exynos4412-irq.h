#ifndef __EXYNOS4412_IRQ_H__
#define __EXYNOS4412_IRQ_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>

typedef void (*interrupt_function_t)(void * data);

void exynos4412_irq_initial(void);
bool_t request_irq(const char * name, interrupt_function_t func, void * data);
bool_t free_irq(const char * name);

#ifdef __cplusplus
}
#endif

#endif /* __EXYNOS4412_IRQ_H__ */
