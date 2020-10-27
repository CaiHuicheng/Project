/*
 * hw-beep.c
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
#include <hw-beep.h>

/*
 * Beep Pin -> EXYNOS4_GPD0(1)
 */
void beep_initial(void)
{
	writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<4)) | (0x1<<4));
	writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<2)) | (0x2<<2));
	writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<1)) | (0x0<<1));
}

void beep_set_status(enum beep_status status)
{
	if(status == BEEP_STATUS_ON)
		writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<1)) | (0x1<<1));
	else if(status == BEEP_STATUS_OFF)
		writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<1)) | (0x0<<1));
}
