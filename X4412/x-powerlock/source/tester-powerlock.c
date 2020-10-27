#include <main.h>
#include <exynos4412/reg-others.h>

int tester_powerlock(int argc, char * argv[])
{
	serial_printf(3, "EXYNOS4412 Powerlock test...\r\n");
	serial_printf(3, "Five seconds later, System will shutdown\r\n");

	serial_printf(3, "5 seconds\r\n");
	mdelay(1000);
	serial_printf(3, "4 seconds\r\n");
	mdelay(1000);
	serial_printf(3, "3 seconds\r\n");
	mdelay(1000);
	serial_printf(3, "2 seconds\r\n");
	mdelay(1000);
	serial_printf(3, "1 seconds\r\n");
	mdelay(1000);

	serial_printf(3, "0 seconds, System shutdown...\r\n");
	writel(EXYNOS4412_PS_HOLD_CONTROL, readl(EXYNOS4412_PS_HOLD_CONTROL) & ~(0x1<<9));

	while(1)
	{
	}

	return 0;
}
