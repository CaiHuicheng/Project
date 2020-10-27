#include <main.h>
#include <exynos4412-irq.h>
#include <exynos4412/reg-gpio.h>
#include <exynos4412/reg-gic.h>

#define EXYNOS4412_GPX1_DAT 	 		(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT)
#define EXYNOS4412_GPX1_PUD				(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD)
#define EXYNOS4412_EXT_INT41_CON 	 	(0x11000000 + 0x0E04)
#define EXYNOS4412_EXT_INT41_MASK 	 	(0x11000000 + 0x0F04)
#define EXYNOS4412_EXT_INT41_PEND 	 	(0x11000000 + 0x0F44)

/*
 * EINT8 interrupt function
 */
static void eint8_interrupt_func(void * data)
{
	serial_printf(3, "EINT8 interrupt\r\n");

	if((readl(EXYNOS4412_GPX1_DAT) & (0x1)) == 0)
		led_set_status(LED_NAME_LED1, LED_STATUS_ON);
	else
		led_set_status(LED_NAME_LED1, LED_STATUS_OFF);

	/* clear interrupt status bit */
	writel(EXYNOS4412_EXT_INT41_PEND, (readl(EXYNOS4412_EXT_INT41_PEND) & ~(0x1)) | (0x1));
}

int tester_key_interrupt(int argc, char * argv[])
{
	/* LEFT BUTTON - GPX1_0 */

	/* Config to EXT_INT[8] */
	writel(EXYNOS4412_GPX1_BASE, (readl(EXYNOS4412_GPX1_BASE) & ~(0xf)) | (0xf));
	/* Pull up */
	writel(EXYNOS4412_GPX1_PUD, (readl(EXYNOS4412_GPX1_PUD) & ~(0x3)) | (0x2));
	/* Both edge triggered */
	writel(EXYNOS4412_EXT_INT41_CON, (readl(EXYNOS4412_EXT_INT41_CON) & ~(0x7)) | (0x4));
	/* Enables Interrupt */
	writel(EXYNOS4412_EXT_INT41_MASK, (readl(EXYNOS4412_EXT_INT41_MASK) & ~(0x1)) | (0x0));
	
	/* Request EINT8 interrupt */
	request_irq("EINT8", eint8_interrupt_func, 0);

	while(1)
	{
	}
	return 0;
}
