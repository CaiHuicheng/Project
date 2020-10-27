/*
 * exynos4412-tick.c
 *
 * Copyright(c) 2007-2013 jianjun jiang <jerryjianjun@gmail.com>
 * official site: http://xboot.org
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
#include <stddef.h>
#include <io.h>
#include <sizes.h>
#include <string.h>
#include <exynos4412-clk.h>
#include <exynos4412-irq.h>
#include <exynos4412/reg-timer.h>
#include <exynos4412-tick.h>

volatile u32_t jiffies = 0;
static u32_t tick_hz = 0;

extern void led_heartbeat_task(void);

static void timer_interrupt(void * data)
{
	/* tick count */
	jiffies++;

	/* led heartbeat task */
	led_heartbeat_task();

	/* Clear interrupt status bit */
	writel(EXYNOS4412_TINT_CSTAT, (readl(EXYNOS4412_TINT_CSTAT) & ~(0x1f<<5)) | (0x01<<9));
}

void exynos4412_tick_initial(void)
{
	u64_t pclk;

	if(!clk_get_rate("pclk", &pclk))
		return;

	if(!request_irq("TIMER4", timer_interrupt, 0))
		return;

	/* Using pwm timer 4, prescaler for timer 4 is 16 */
	writel(EXYNOS4412_TCFG0, (readl(EXYNOS4412_TCFG0) & ~(0xff<<8)) | (0x0f<<8));

	/* Select mux input for pwm timer4 is 1/2 */
	writel(EXYNOS4412_TCFG1, (readl(EXYNOS4412_TCFG1) & ~(0xf<<16)) | (0x01<<16));

	/* Load value for 10 ms timeout */
	writel(EXYNOS4412_TCNTB4, (u32_t)(pclk / (2 * 16 * 100)));

	/* Auto load, manaual update of timer 4 and stop timer4 */
	writel(EXYNOS4412_TCON, (readl(EXYNOS4412_TCON) & ~(0x7<<20)) | (0x06<<20));

	/* Enable timer4 interrupt and clear interrupt status bit */
	writel(EXYNOS4412_TINT_CSTAT, (readl(EXYNOS4412_TINT_CSTAT) & ~(0x1<<4)) | (0x01<<4) | (0x01<<9));

	/* Start timer4 */
	writel(EXYNOS4412_TCON, (readl(EXYNOS4412_TCON) & ~(0x7<<20)) | (0x05<<20));

	/* initial system tick */
	tick_hz = 100;
	jiffies = 0;
}

u32_t get_system_hz(void)
{
	return tick_hz;
}

u64_t clock_gettime(void)
{
	if(get_system_hz() > 0)
		return (u64_t)jiffies * 1000000 / get_system_hz();

	return 0;
}
