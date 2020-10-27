/*
 * exynos4412-irom.c
 *
 * this file used by start.s assembler code, and the linker script
 * must make sure this file is linked within the first 8kB. DO NOT
 * use any .bss segment and .data segment, just use irom's small
 * stack. it's just a small c routline.
 *
 * NOTE:
 *     please do not use 'switch, case' instead of 'if, else if',
 *     because switch statement may be compiled as a jump table,
 *     which belong to .data segment, if it has many cases.
 *
 *     to make sure this file is linked within the first 8KB, please
 *     look at the file of xboot.map.
 *
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
#include <exynos4412/reg-gpio.h>
#include <exynos4412/reg-pmu.h>

extern u8_t	__text_start[];
extern u8_t __text_end[];
extern u8_t __data_shadow_start[];
extern u8_t __data_shadow_end[];
extern u8_t __data_start[];
extern u8_t __data_end[];
extern u8_t __bss_start[];
extern u8_t __bss_end[];
extern u8_t __heap_start[];
extern u8_t __heap_end[];
extern u8_t __stack_start[];
extern u8_t __stack_end[];

#define irom_sdmmc_to_mem(sector, count, mem)		\
		(((u32_t(*)(u32_t, u32_t, u32_t *))(*((u32_t *)(0x02020030))))(sector, count, mem))

/*
 * read a 32-bits value from register.
 */
static u32_t reg_read(u32_t addr)
{
	return( *((volatile u32_t *)(addr)) );
}

/*
 * only support irom booting.
 */
void irom_copyself(void)
{
	u32_t om;
	u32_t * mem;
	u32_t size;

	/*
	 * read om register, om[5..1]
	 */
	om = (u32_t)((reg_read(EXYNOS4412_PMU_OM_STAT) >> 1) & 0x1f);

	/* SDMMC CH2 */
	if(om == 0x2)
	{
		/*
		 * the xboot's memory base address.
		 */
		mem = (u32_t *)__text_start;

		/*
		 * the size which will be copyed, the 'size' is
		 * 1 : 256KB, 2 : 512KB, 3 : 768KB, 4 : 1024KB ...
		 */
		size = (__data_shadow_end - __text_start + 0x00040000) >> 18;

		/*
		 * how many blocks the 'size' is , 512 bytes per block.
		 * size * 256 *1024 / 512 = size * 2^9 = size << 9
		 */
		size = size << 9;

		/*
		 * copy xboot to memory from sdmmc ch2.
		 */
		irom_sdmmc_to_mem(1, size, mem);
	}

	/* eMMC43 CH0 */
	else if(om == 0x3)
	{

	}

	/* eMMC44 CH4 */
	else if(om == 0x4)
	{

	}

	/* NAND 512B 8ECC */
	else if(om == 0x8)
	{

	}

	/* NAND 2KB OVER */
	else if(om == 0x9)
	{

	}

	/*=============*/
	/* eMMC43 CH0 */
	else if(om == 0x13)
	{

	}

	/* eMMC44 CH4 */
	else if(om == 0x14)
	{

	}

	/* NAND 512B 8ECC */
	else if(om == 0x18)
	{

	}

	/* NAND 2KB OVER */
	else if(om == 0x19)
	{

	}

	/* Not support */
	else
	{
		return;
	}
}
