/*
 * exynos4412-serial.c
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
#include <string.h>
#include <io.h>
#include <stddef.h>
#include <exynos4412/reg-gpio.h>
#include <exynos4412/reg-uart.h>
#include <exynos4412-clk.h>
#include <exynos4412-serial.h>

static void exynos4412_serial_init(int ch)
{
	switch(ch)
	{
	case 0:
		/* Configure GPA01, GPA00 for TXD0, RXD0 and pull up */
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<4)) | (0x2<<4));
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<0)) | (0x2<<0));
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<2)) | (0x2<<2));
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<0)) | (0x2<<0));

		writel(EXYNOS4412_UART0_BASE + EXYNOS4412_UCON, 0x00000005);
		writel(EXYNOS4412_UART0_BASE + EXYNOS4412_UFCON, 0x00000777);
		writel(EXYNOS4412_UART0_BASE + EXYNOS4412_UMCON, 0x00000000);
		break;

	case 1:
		/* Configure GPA05, GPA04 for TXD1, RXD1 */
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<20)) | (0x2<<20));
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<16)) | (0x2<<16));
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<10)) | (0x2<<10));
		writel(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<8)) | (0x2<<8));

		writel(EXYNOS4412_UART1_BASE + EXYNOS4412_UCON, 0x00000005);
		writel(EXYNOS4412_UART1_BASE + EXYNOS4412_UFCON, 0x00000777);
		writel(EXYNOS4412_UART1_BASE + EXYNOS4412_UMCON, 0x00000000);
		break;

	case 2:
		/* Configure GPA11, GPA10 for TXD2, RXD2 */
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<4)) | (0x2<<4));
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<0)) | (0x2<<0));
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<2)) | (0x2<<2));
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<0)) | (0x2<<0));

		writel(EXYNOS4412_UART2_BASE + EXYNOS4412_UCON, 0x00000005);
		writel(EXYNOS4412_UART2_BASE + EXYNOS4412_UFCON, 0x00000777);
		writel(EXYNOS4412_UART2_BASE + EXYNOS4412_UMCON, 0x00000000);
		break;

	case 3:
		/* Configure GPA15, GPA14 for TXD3, RXD3 */
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<20)) | (0x2<<20));
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<16)) | (0x2<<16));
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<10)) | (0x2<<10));
		writel(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPA1_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<8)) | (0x2<<8));

		writel(EXYNOS4412_UART3_BASE + EXYNOS4412_UCON, 0x00000005);
		writel(EXYNOS4412_UART3_BASE + EXYNOS4412_UFCON, 0x00000777);
		writel(EXYNOS4412_UART3_BASE + EXYNOS4412_UMCON, 0x00000000);
		break;

	default:
		return;
	}

	exynos4412_serial_setup(ch, B115200, DATA_BITS_8, PARITY_NONE, STOP_BITS_1);
}

void exynos4412_serial_initial(void)
{
	exynos4412_serial_init(0);
	exynos4412_serial_init(1);
	exynos4412_serial_init(2);
	exynos4412_serial_init(3);
}

bool_t exynos4412_serial_setup(int ch, enum baud_rate_t baud, enum data_bits_t data, enum parity_bits_t parity, enum stop_bits_t stop)
{
	const u32_t udivslot_code[16] = {0x0000, 0x0080, 0x0808, 0x0888,
									 0x2222, 0x4924, 0x4a52, 0x54aa,
									 0x5555, 0xd555, 0xd5d5, 0xddd5,
									 0xdddd, 0xdfdd, 0xdfdf, 0xffdf};
	u32_t ibaud, baud_div_reg, baud_divslot_reg;
	u8_t data_bit_reg, parity_reg, stop_bit_reg;
	u64_t sclk_uart;

	switch(baud)
	{
	case B50:
		ibaud = 50;
		break;
	case B75:
		ibaud = 75;
		break;
	case B110:
		ibaud = 110;
		break;
	case B134:
		ibaud = 134;
		break;
	case B200:
		ibaud = 200;
		break;
	case B300:
		ibaud = 300;
		break;
	case B600:
		ibaud = 600;
		break;
	case B1200:
		ibaud = 1200;
		break;
	case B1800:
		ibaud = 1800;
		break;
	case B2400:
		ibaud = 2400;
		break;
	case B4800:
		ibaud = 4800;
		break;
	case B9600:
		ibaud = 9600;
		break;
	case B19200:
		ibaud = 19200;
		break;
	case B38400:
		ibaud = 38400;
		break;
	case B57600:
		ibaud = 57600;
		break;
	case B76800:
		ibaud = 76800;
		break;
	case B115200:
		ibaud = 115200;
		break;
	case B230400:
		ibaud = 230400;
		break;
	case B380400:
		ibaud = 380400;
		break;
	case B460800:
		ibaud = 460800;
		break;
	case B921600:
		ibaud = 921600;
		break;
	default:
		return FALSE;
	}

	switch(data)
	{
	case DATA_BITS_5:
		data_bit_reg = 0x0;		break;
	case DATA_BITS_6:
		data_bit_reg = 0x1;		break;
	case DATA_BITS_7:
		data_bit_reg = 0x2;		break;
	case DATA_BITS_8:
		data_bit_reg = 0x3;		break;
	default:
		return FALSE;
	}

	switch(parity)
	{
	case PARITY_NONE:
		parity_reg = 0x0;		break;
	case PARITY_EVEN:
		parity_reg = 0x5;		break;
	case PARITY_ODD:
		parity_reg = 0x4;		break;
	default:
		return FALSE;
	}

	switch(stop)
	{
	case STOP_BITS_1:
		stop_bit_reg = 0;		break;
	case STOP_BITS_1_5:
		return -1;
	case STOP_BITS_2:
		stop_bit_reg = 1;		break;
	default:
		return FALSE;
	}

	switch(ch)
	{
	case 0:
		if(!clk_get_rate("sclk_uart0", &sclk_uart))
			return FALSE;
		break;
	case 1:
		if(!clk_get_rate("sclk_uart1", &sclk_uart))
			return FALSE;
		break;
	case 2:
		if(!clk_get_rate("sclk_uart2", &sclk_uart))
			return FALSE;
		break;
	case 3:
		if(!clk_get_rate("sclk_uart3", &sclk_uart))
			return FALSE;
		break;
	default:
		return FALSE;
	}

	baud_div_reg = (u32_t)((sclk_uart / (ibaud * 16)) ) - 1;
	baud_divslot_reg = udivslot_code[( (u32_t)((sclk_uart % (ibaud*16)) / ibaud) ) & 0xf];

	switch(ch)
	{
	case 0:
		writel(EXYNOS4412_UART0_BASE + EXYNOS4412_UBRDIV, baud_div_reg);
		writel(EXYNOS4412_UART0_BASE + EXYNOS4412_UFRACVAL, baud_divslot_reg);
		writel(EXYNOS4412_UART0_BASE + EXYNOS4412_ULCON, (data_bit_reg<<0 | stop_bit_reg <<2 | parity_reg<<3));
		break;
	case 1:
		writel(EXYNOS4412_UART1_BASE + EXYNOS4412_UBRDIV, baud_div_reg);
		writel(EXYNOS4412_UART1_BASE + EXYNOS4412_UFRACVAL, baud_divslot_reg);
		writel(EXYNOS4412_UART1_BASE + EXYNOS4412_ULCON, (data_bit_reg<<0 | stop_bit_reg <<2 | parity_reg<<3));
		break;
	case 2:
		writel(EXYNOS4412_UART2_BASE + EXYNOS4412_UBRDIV, baud_div_reg);
		writel(EXYNOS4412_UART2_BASE + EXYNOS4412_UFRACVAL, baud_divslot_reg);
		writel(EXYNOS4412_UART2_BASE + EXYNOS4412_ULCON, (data_bit_reg<<0 | stop_bit_reg <<2 | parity_reg<<3));
		break;
	case 3:
		writel(EXYNOS4412_UART3_BASE + EXYNOS4412_UBRDIV, baud_div_reg);
		writel(EXYNOS4412_UART3_BASE + EXYNOS4412_UFRACVAL, baud_divslot_reg);
		writel(EXYNOS4412_UART3_BASE + EXYNOS4412_ULCON, (data_bit_reg<<0 | stop_bit_reg <<2 | parity_reg<<3));
		break;
	default:
		return FALSE;
	}

	return TRUE;
}

ssize_t exynos4412_serial_read(int ch, u8_t * buf, size_t count)
{
	u32_t base = EXYNOS4412_UART0_BASE;
	ssize_t i;

	switch(ch)
	{
	case 0:
		base = EXYNOS4412_UART0_BASE;
		break;
	case 1:
		base = EXYNOS4412_UART1_BASE;
		break;
	case 2:
		base = EXYNOS4412_UART2_BASE;
		break;
	case 3:
		base = EXYNOS4412_UART3_BASE;
		break;
	default:
		break;
	}

	for(i = 0; i < count; i++)
	{
		if( (readl(base + EXYNOS4412_UTRSTAT) & EXYNOS4412_UTRSTAT_RXDR) )
			buf[i] = readb(base + EXYNOS4412_URXH);
		else
			break;
	}

	return i;
}

ssize_t exynos4412_serial_write(int ch, u8_t * buf, size_t count)
{
	u32_t base = EXYNOS4412_UART0_BASE;
	ssize_t i;

	switch(ch)
	{
	case 0:
		base = EXYNOS4412_UART0_BASE;
		break;
	case 1:
		base = EXYNOS4412_UART1_BASE;
		break;
	case 2:
		base = EXYNOS4412_UART2_BASE;
		break;
	case 3:
		base = EXYNOS4412_UART3_BASE;
		break;
	default:
		break;
	}

	for(i = 0; i < count; i++)
	{
		while( !(readl(base + EXYNOS4412_UTRSTAT) & EXYNOS4412_UTRSTAT_TXFE) );
		writeb(base + EXYNOS4412_UTXH, buf[i]);
	}

	return i;
}

ssize_t exynos4412_serial_write_string(int ch, const char * buf)
{
	return exynos4412_serial_write(ch, (u8_t *)buf, strlen(buf));
}
