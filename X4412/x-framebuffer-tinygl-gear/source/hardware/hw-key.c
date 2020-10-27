/*
 * hw-key.c
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
#include <stddef.h>
#include <exynos4412/reg-gpio.h>
#include <hw-key.h>

/*
 * POWER -> EXYNOS4_GPX0(1)
 * LEFT  -> EXYNOS4_GPX1(0)
 * DOWN  -> EXYNOS4_GPX1(1)
 * UP    -> EXYNOS4_GPX1(2)
 * RIGHT -> EXYNOS4_GPX1(3)
 * BACK  -> EXYNOS4_GPX1(4)
 * MENU  -> EXYNOS4_GPX1(5)
 */
void key_initial(void)
{
	/* POWER */
	writel(EXYNOS4412_GPX0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<4)) | (0x0<<4));
	writel(EXYNOS4412_GPX0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<2)) | (0x2<<2));

	/* LEFT */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<0)) | (0x0<<0));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<0)) | (0x2<<0));

	/* DOWN */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<4)) | (0x0<<4));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<2)) | (0x2<<2));

	/* UP */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<8)) | (0x0<<8));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<4)) | (0x2<<4));

	/* RIGHT */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<12)) | (0x0<<12));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<6)) | (0x2<<6));

	/* BACK */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<16)) | (0x0<<16));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<8)) | (0x2<<8));

	/* MENU */
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<20)) | (0x0<<20));
	writel(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<10)) | (0x2<<10));
}

static u32_t __get_key_status(void)
{
	u32_t key = 0;

	if((readl(EXYNOS4412_GPX0_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<1)) == 0)
		key |= KEY_NAME_POWER;

	if((readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<0)) == 0)
		key |= KEY_NAME_LEFT;

	if((readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<1)) == 0)
		key |= KEY_NAME_DOWN;

	if((readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<2)) == 0)
		key |= KEY_NAME_UP;

	if((readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<3)) == 0)
		key |= KEY_NAME_RIGHT;

	if((readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<4)) == 0)
		key |= KEY_NAME_BACK;

	if((readl(EXYNOS4412_GPX1_BASE + EXYNOS4412_GPIO_DAT) & (0x1<<5)) == 0)
		key |= KEY_NAME_MENU;

	return key;
}

bool_t get_key_status(u32_t * key)
{
	static u32_t a = 0, b = 0, c = 0;

	a = __get_key_status();
	b = __get_key_status();
	c = __get_key_status();

	if((a == b) && (a == c))
	{
		*key = a;
		return TRUE;
	}

	return FALSE;
}

bool_t get_key_event(u32_t * keyup, u32_t * keydown)
{
	static u32_t key_old = 0x0;
	u32_t key;

	if(!get_key_status(&key))
		return FALSE;

	if(key != key_old)
	{
		*keyup = (key ^ key_old) & key_old;
		*keydown = (key ^ key_old) & key;
		key_old = key;

		return TRUE;
	}

	return FALSE;
}

