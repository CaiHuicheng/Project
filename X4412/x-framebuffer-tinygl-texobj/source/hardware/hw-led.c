/*
 * hw-led.c
 *
 * Copyright(c) 2007-2014 Jianjun Jiang <8192542@qq.com>
 * Official site: http://xboot.org
 * Mobile phone: +86-18665388956
 * QQ: 8192542
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software Foundation,
 * Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 */

#include <types.h>
#include <io.h>
#include <exynos4412/reg-gpio.h>
#include <hw-led.h>

/*
 * LED1 -> EXYNOS4412_GPX1(6)
 * LED2 -> EXYNOS4412_GPX1(7)
 * LED3 -> EXYNOS4412_GPX2(6)
 * LED4 -> EXYNOS4412_GPX2(7)
 */
void led_initial(void)
{
	/* LED1 */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<24)) | (0x1<<24));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<12)) | (0x2<<12));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<6)) | (0x1<<6));

	/* LED2 */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<28)) | (0x1<<28));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<14)) | (0x2<<14));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<7)) | (0x1<<7));

	/* LED3 */
	writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<24)) | (0x1<<24));
	writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<12)) | (0x2<<12));
	writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<6)) | (0x1<<6));

	/* LED4 */
	writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<28)) | (0x1<<28));
	writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<14)) | (0x2<<14));
	writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<7)) | (0x1<<7));
}

void led_set_status(enum led_name name, enum led_status status)
{
	switch(name)
	{
	case LED_NAME_LED1:
		if(status == LED_STATUS_ON)
			writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<6)) | (0x0<<6));
		else if(status == LED_STATUS_OFF)
			writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<6)) | (0x1<<6));
		break;

	case LED_NAME_LED2:
		if(status == LED_STATUS_ON)
			writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<7)) | (0x0<<7));
		else if(status == LED_STATUS_OFF)
			writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<7)) | (0x1<<7));
		break;

	case LED_NAME_LED3:
		if(status == LED_STATUS_ON)
			writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<6)) | (0x0<<6));
		else if(status == LED_STATUS_OFF)
			writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<6)) | (0x1<<6));
		break;

	case LED_NAME_LED4:
		if(status == LED_STATUS_ON)
			writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<7)) | (0x0<<7));
		else if(status == LED_STATUS_OFF)
			writel(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX2_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<7)) | (0x1<<7));
		break;

	default:
		break;
	}
}
