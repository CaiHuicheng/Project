#ifndef __EXYNOS4412_FB_H__
#define __EXYNOS4412_FB_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <types.h>
#include <graphic/surface.h>

void exynos4412_fb_initial(void);
struct surface_t * exynos4412_screen_surface(void);
void exynos4412_screen_swap(void);
void exynos4412_screen_flush(void);
void exynos4412_screen_backlight(u8_t brightness);

#ifdef __cplusplus
}
#endif

#endif /* __EXYNOS4412_FB_H__ */
