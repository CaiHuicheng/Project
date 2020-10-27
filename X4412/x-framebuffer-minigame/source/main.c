#include <main.h>

extern int tester_framebuffer_minigame(int argc, char * argv[]);

static void do_system_initial(void)
{
	malloc_init();

	exynos4412_clk_initial();
	exynos4412_serial_initial();
	exynos4412_irq_initial();
	exynos4412_tick_initial();
	exynos4412_tick_delay_initial();
	exynos4412_fb_initial();

	led_initial();
	beep_initial();
	key_initial();
}

int main(int argc, char * argv[])
{
	do_system_initial();

	tester_framebuffer_minigame(argc, argv);
	return 0;
}
