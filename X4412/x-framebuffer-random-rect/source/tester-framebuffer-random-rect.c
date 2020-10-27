#include <main.h>

int randomInt(int min, int max)
{
	return min + rand() % (max - min + 1);
}

static void random_rect(void)
{
	struct surface_t * screen;
    struct rect_t rect;
	u32_t c;

	screen = exynos4412_screen_surface();
	exynos4412_screen_swap();
	exynos4412_screen_flush();

    while (1)
	{
    	rect.x = randomInt(0, 1024-1);
    	rect.y = randomInt(0, 600-1);
    	rect.w = randomInt(1, 200);
    	rect.h = randomInt(1, 120);
    	c = randomInt(0, 0x00ffffff);

		surface_fill(screen, &rect, c, BLEND_MODE_REPLACE);
	}
}

int tester_framebuffer_random_rect(int argc, char * argv[])
{
	random_rect();
	return 0;
}
