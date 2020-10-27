/*
 * exynos4412-serial-stdio.c
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
#include <malloc.h>
#include <stdio.h>
#include <sizes.h>
#include <exynos4412-serial.h>
#include <exynos4412-serial-stdio.h>

int serial_printf(int ch, const char * fmt, ...)
{
	va_list ap;
	char * buf;
	int len;
	int rv;

	va_start(ap, fmt);
	len = vsnprintf(NULL, 0, fmt, ap);
	if(len < 0)
		return 0;
	buf = malloc(len + 1);
	if(!buf)
		return 0;
	rv = vsnprintf(buf, len + 1, fmt, ap);
	va_end(ap);

	rv = (exynos4412_serial_write_string(ch, buf) < 0) ? 0 : rv;
	free(buf);

	return rv;
}
