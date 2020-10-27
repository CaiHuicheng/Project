/*
 * exynos4412-fb.c
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
#include <stddef.h>
#include <malloc.h>
#include <io.h>
#include <graphic/surface.h>
#include <exynos4412-tick-delay.h>
#include <exynos4412/reg-gpio.h>
#include <exynos4412/reg-others.h>
#include <exynos4412/reg-lcd.h>
#include <exynos4412-clk.h>
#include <exynos4412-fb.h>

enum exynos4412_fb_output_t
{
	EXYNOS4412_FB_OUTPUT_RGB,
	EXYNOS4412_FB_OUTPUT_I80LDI0,
	EXYNOS4412_FB_OUTPUT_I80LDI1,
	EXYNOS4412_FB_OUTPUT_WB_RGB,
	EXYNOS4412_FB_OUTPUT_WB_I80LDI0,
	EXYNOS4412_FB_OUTPUT_WB_I80LDI1,
};

enum exynos4412_fb_rgb_mode_t
{
	EXYNOS4412_FB_MODE_RGB_P 	= 0,
	EXYNOS4412_FB_MODE_BGR_P 	= 1,
	EXYNOS4412_FB_MODE_RGB_S 	= 2,
	EXYNOS4412_FB_MODE_BGR_S 	= 3,
};

enum exynos4412_bpp_mode_t
{
	EXYNOS4412_FB_BPP_MODE_1BPP			= 0x0,
	EXYNOS4412_FB_BPP_MODE_2BPP			= 0x1,
	EXYNOS4412_FB_BPP_MODE_4BPP			= 0x2,
	EXYNOS4412_FB_BPP_MODE_8BPP_PAL		= 0x3,
	EXYNOS4412_FB_BPP_MODE_8BPP			= 0x4,
	EXYNOS4412_FB_BPP_MODE_16BPP_565	= 0x5,
	EXYNOS4412_FB_BPP_MODE_16BPP_A555	= 0x6,
	EXYNOS4412_FB_BPP_MODE_16BPP_X555	= 0x7,
	EXYNOS4412_FB_BPP_MODE_18BPP_666	= 0x8,
	EXYNOS4412_FB_BPP_MODE_18BPP_A665	= 0x9,
	EXYNOS4412_FB_BPP_MODE_19BPP_A666	= 0xa,
	EXYNOS4412_FB_BPP_MODE_24BPP_888	= 0xb,
	EXYNOS4412_FB_BPP_MODE_24BPP_A887	= 0xc,
	EXYNOS4412_FB_BPP_MODE_32BPP		= 0xd,
	EXYNOS4412_FB_BPP_MODE_16BPP_A444	= 0xe,
	EXYNOS4412_FB_BPP_MODE_15BPP_555	= 0xf,
};

enum {
	EXYNOS4412_FB_SWAP_WORD		= (0x1 << 0),
	EXYNOS4412_FB_SWAP_HWORD	= (0x1 << 1),
	EXYNOS4412_FB_SWAP_BYTE		= (0x1 << 2),
	EXYNOS4412_FB_SWAP_BIT		= (0x1 << 3),
};

struct exynos4412_fb_data_t
{
	/* Register base address */
	physical_addr_t regbase;

	/* horizontal resolution */
	s32_t width;

	/* vertical resolution */
	s32_t height;

	/* Bits per pixel */
	s32_t bits_per_pixel;

	/* Bytes per pixel */
	s32_t bytes_per_pixel;

	/* Vframe frequency */
	s32_t freq;

	/* Output path */
	enum exynos4412_fb_output_t output;

	/* RGB mode */
	enum exynos4412_fb_rgb_mode_t rgb_mode;

	/* bpp mode */
	enum exynos4412_bpp_mode_t bpp_mode;

	/* Swap flag */
	u32_t swap;

	struct {
		/* red color */
		s32_t r_mask;
		s32_t r_field;

		/* green color */
		s32_t g_mask;
		s32_t g_field;

		/* blue color */
		s32_t b_mask;
		s32_t b_field;

		/* alpha color */
		s32_t a_mask;
		s32_t a_field;
	} rgba;

	struct {
		/* horizontal front porch */
		s32_t h_fp;

		/* horizontal back porch */
		s32_t h_bp;

		/* horizontal sync width */
		s32_t h_sw;

		/* vertical front porch */
		s32_t v_fp;

		/* vertical front porch for even field */
		s32_t v_fpe;

		/* vertical back porch */
		s32_t v_bp;

		/* vertical back porch for even field */
		s32_t v_bpe;

		/* vertical sync width */
		s32_t v_sw;
	} timing;

	struct {
		/* if 1, video data is fetched at rising edge */
		s32_t rise_vclk;

		/* if HSYNC polarity is inversed */
		s32_t inv_hsync;

		/* if VSYNC polarity is inversed */
		s32_t inv_vsync;

		/* if VDEN polarity is inversed */
		s32_t inv_vden;
	} polarity;

	/* video ram front buffer */
	void * vram_front;

	/* video ram back buffer */
	void * vram_back;

	/* lcd init */
	void (*init)(void);

	/* lcd backlight */
	void (*backlight)(u8_t brightness);
};

/*
 * defined the structure of framebuffer.
 */
struct fb_t
{
	/* the framebuffer's surface */
	struct surface_t surface;

	/* framebuffer's lcd data */
	struct exynos4412_fb_data_t * dat;
};

static bool_t exynos4412_fb_set_output(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg;

	cfg = readl(dat->regbase + VIDCON0);
	cfg &= ~VIDCON0_VIDOUT_MASK;

	if(dat->output == EXYNOS4412_FB_OUTPUT_RGB)
		cfg |= VIDCON0_VIDOUT_RGB;
	else if(dat->output == EXYNOS4412_FB_OUTPUT_I80LDI0)
		cfg |= VIDCON0_VIDOUT_I80LDI0;
	else if(dat->output == EXYNOS4412_FB_OUTPUT_I80LDI1)
		cfg |= VIDCON0_VIDOUT_I80LDI1;
	else if(dat->output == EXYNOS4412_FB_OUTPUT_WB_RGB)
		cfg |= VIDCON0_VIDOUT_WB_RGB;
	else if(dat->output == EXYNOS4412_FB_OUTPUT_WB_I80LDI0)
		cfg |= VIDCON0_VIDOUT_WB_I80LDI0;
	else if(dat->output == EXYNOS4412_FB_OUTPUT_WB_I80LDI1)
		cfg |= VIDCON0_VIDOUT_WB_I80LDI1;
	else
		return FALSE;
	writel(dat->regbase + VIDCON0, cfg);

	cfg = readl(dat->regbase + VIDCON2);
	cfg |= 0x3 << 14;
	writel(dat->regbase + VIDCON2, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_set_display_mode(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg;

	cfg = readl(dat->regbase + VIDCON0);
	cfg &= ~(3 << 17);
	cfg |= (dat->rgb_mode << 17);
	writel(dat->regbase + VIDCON0, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_display_on(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg;

	cfg = readl(dat->regbase + VIDCON0);
	cfg |= 0x3 << 0;
	writel(dat->regbase + VIDCON0, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_display_off(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg;

	cfg = readl(dat->regbase + VIDCON0);
	cfg &= ~(1 << 1);
	writel(dat->regbase + VIDCON0, cfg);

	cfg &= ~(1 << 0);
	writel(dat->regbase + VIDCON0, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_set_clock(struct exynos4412_fb_data_t * dat)
{
	u64_t fimd, pixel_clock;
	u32_t div;
	u32_t cfg;

	if(!clk_get_rate("fimd", &fimd))
		return FALSE;

	pixel_clock = ( dat->freq * (dat->timing.h_fp + dat->timing.h_bp + dat->timing.h_sw + dat->width) *
			(dat->timing.v_fp + dat->timing.v_bp + dat->timing.v_sw + dat->height) );

	div = (u32_t)(fimd / pixel_clock);
	if((fimd % pixel_clock) > 0)
		div++;

	cfg = readl(dat->regbase + VIDCON0);
	cfg &= ~( (1 << 16) | (1 << 5) );
	cfg |= VIDCON0_CLKVAL_F(div - 1);
	writel(dat->regbase + VIDCON0, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_set_polarity(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg = 0;

	if(dat->polarity.rise_vclk)
		cfg |= (1 << 7);

	if(dat->polarity.inv_hsync)
		cfg |= (1 << 6);

	if(dat->polarity.inv_vsync)
		cfg |= (1 << 5);

	if(dat->polarity.inv_vden)
		cfg |= (1 << 4);

	writel(dat->regbase + VIDCON1, cfg);
	return TRUE;
}

static bool_t exynos4412_fb_set_timing(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg;

	cfg = 0;
	cfg |= VIDTCON0_VBPDE(dat->timing.v_bpe - 1);
	cfg |= VIDTCON0_VBPD(dat->timing.v_bp - 1);
	cfg |= VIDTCON0_VFPD(dat->timing.v_fp - 1);
	cfg |= VIDTCON0_VSPW(dat->timing.v_sw - 1);
	writel(dat->regbase + VIDTCON0, cfg);

	cfg = 0;
	cfg |= VIDTCON1_VFPDE(dat->timing.v_fpe - 1);
	cfg |= VIDTCON1_HBPD(dat->timing.h_bp - 1);
	cfg |= VIDTCON1_HFPD(dat->timing.h_fp - 1);
	cfg |= VIDTCON1_HSPW(dat->timing.h_sw - 1);
	writel(dat->regbase + VIDTCON1, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_set_lcd_size(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg = 0;

	cfg |= VIDTCON2_HOZVAL(dat->width - 1);
	cfg |= VIDTCON2_LINEVAL(dat->height - 1);
	writel(dat->regbase + VIDTCON2, cfg);

	return TRUE;
}

static bool_t exynos4412_fb_set_buffer_address(struct exynos4412_fb_data_t * dat, s32_t id, void * vram)
{
	u32_t start, end;
	u32_t shw;

	start = (u32_t)(vram);
	end = (u32_t)((start + dat->width * (dat->height * dat->bytes_per_pixel)) & 0x00ffffff);

	shw = readl(dat->regbase + SHADOWCON);
	shw |= SHADOWCON_PROTECT(id);
	writel(dat->regbase + SHADOWCON, shw);

	switch(id)
	{
	case 0:
		writel(dat->regbase + VIDW00ADD0B0, start);
		writel(dat->regbase + VIDW00ADD1B0, end);
		break;

	case 1:
		writel(dat->regbase + VIDW01ADD0B0, start);
		writel(dat->regbase + VIDW01ADD1B0, end);
		break;

	case 2:
		writel(dat->regbase + VIDW02ADD0B0, start);
		writel(dat->regbase + VIDW02ADD1B0, end);
		break;

	case 3:
		writel(dat->regbase + VIDW03ADD0B0, start);
		writel(dat->regbase + VIDW03ADD1B0, end);
		break;

	case 4:
		writel(dat->regbase + VIDW04ADD0B0, start);
		writel(dat->regbase + VIDW04ADD1B0, end);
		break;

	default:
		break;
	}

	shw = readl(dat->regbase + SHADOWCON);
	shw &= ~(SHADOWCON_PROTECT(id));
	writel(dat->regbase + SHADOWCON, shw);

	return TRUE;
}

static bool_t exynos4412_fb_set_buffer_size(struct exynos4412_fb_data_t * dat, s32_t id)
{
	u32_t cfg = 0;

	cfg = VIDADDR_PAGEWIDTH(dat->width * dat->bytes_per_pixel);
	cfg |= VIDADDR_OFFSIZE(0);

	switch(id)
	{
	case 0:
		writel(dat->regbase + VIDW00ADD2, cfg);
		break;

	case 1:
		writel(dat->regbase + VIDW01ADD2, cfg);
		break;

	case 2:
		writel(dat->regbase + VIDW02ADD2, cfg);
		break;

	case 3:
		writel(dat->regbase + VIDW03ADD2, cfg);
		break;

	case 4:
		writel(dat->regbase + VIDW04ADD2, cfg);
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

static bool_t exynos4412_fb_set_window_position(struct exynos4412_fb_data_t * dat, s32_t id)
{
	u32_t cfg, shw;

	shw = readl(dat->regbase + SHADOWCON);
	shw |= SHADOWCON_PROTECT(id);
	writel(dat->regbase + SHADOWCON, shw);

	switch(id)
	{
	case 0:
		cfg = VIDOSD_LEFT_X(0) | VIDOSD_TOP_Y(0);
		writel(dat->regbase + VIDOSD0A, cfg);
		cfg = VIDOSD_RIGHT_X(dat->width - 1) | VIDOSD_BOTTOM_Y(dat->height - 1);
		writel(dat->regbase + VIDOSD0B, cfg);
		break;

	case 1:
		cfg = VIDOSD_LEFT_X(0) | VIDOSD_TOP_Y(0);
		writel(dat->regbase + VIDOSD1A, cfg);
		cfg = VIDOSD_RIGHT_X(dat->width - 1) | VIDOSD_BOTTOM_Y(dat->height - 1);
		writel(dat->regbase + VIDOSD1B, cfg);
		break;

	case 2:
		cfg = VIDOSD_LEFT_X(0) | VIDOSD_TOP_Y(0);
		writel(dat->regbase + VIDOSD2A, cfg);
		cfg = VIDOSD_RIGHT_X(dat->width - 1) | VIDOSD_BOTTOM_Y(dat->height - 1);
		writel(dat->regbase + VIDOSD2B, cfg);
		break;

	case 3:
		cfg = VIDOSD_LEFT_X(0) | VIDOSD_TOP_Y(0);
		writel(dat->regbase + VIDOSD3A, cfg);
		cfg = VIDOSD_RIGHT_X(dat->width - 1) | VIDOSD_BOTTOM_Y(dat->height - 1);
		writel(dat->regbase + VIDOSD3B, cfg);
		break;

	case 4:
		cfg = VIDOSD_LEFT_X(0) | VIDOSD_TOP_Y(0);
		writel(dat->regbase + VIDOSD4A, cfg);
		cfg = VIDOSD_RIGHT_X(dat->width - 1) | VIDOSD_BOTTOM_Y(dat->height - 1);
		writel(dat->regbase + VIDOSD4B, cfg);
		break;

	default:
		break;
	}

	shw = readl(dat->regbase + SHADOWCON);
	shw &= ~(SHADOWCON_PROTECT(id));
	writel(dat->regbase + SHADOWCON, shw);

	return TRUE;
}

static bool_t exynos4412_fb_set_window_size(struct exynos4412_fb_data_t * dat, s32_t id)
{
	u32_t cfg;

	if(id > 2)
		return FALSE;

	cfg = VIDOSD_SIZE(dat->width * dat->height);
	switch(id)
	{
	case 0:
		writel(dat->regbase + VIDOSD0C, cfg);
		break;

	case 1:
		writel(dat->regbase + VIDOSD1D, cfg);
		break;

	case 2:
		writel(dat->regbase + VIDOSD2D, cfg);
		break;

	default:
		return FALSE;
	}

	return TRUE;
}

static bool_t exynos4412_fb_window0_enable(struct exynos4412_fb_data_t * dat)
{
	u32_t cfg;

	cfg = readl(dat->regbase + WINCON0);
	cfg &= ~((1 << 18) | (1 << 17) |
			(1 << 16) | (1 << 15) |
			(3 << 9) | (0xf << 2) |
			(1 << 13) | (1 << 22) |
			(1 << 1));
	cfg |= (0 << 1);
	cfg |= (0 << 13);
	cfg |= (0 << 22);
	cfg |= (1 << 0);

	if(dat->swap & EXYNOS4412_FB_SWAP_WORD)
		cfg |= (1 << 15);

	if(dat->swap & EXYNOS4412_FB_SWAP_HWORD)
		cfg |= (1 << 16);

	if(dat->swap & EXYNOS4412_FB_SWAP_BYTE)
		cfg |= (1 << 17);

	if(dat->swap & EXYNOS4412_FB_SWAP_BIT)
		cfg |= (1 << 18);

	cfg |= (dat->bpp_mode << 2);
	writel(dat->regbase + WINCON0, cfg);

	cfg = readl(dat->regbase + SHADOWCON);
	cfg |= 1 << 0;
	writel(dat->regbase + SHADOWCON, cfg);

	return TRUE;
}

static void lcd_init(void)
{
	/*
	 * Set GPD0_0 (backlight pwm pin) output and pull up and high level for disabled
	 */
	writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<0)) | (0x1<<0));
	writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<0)) | (0x2<<0));
	writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<0)) | (0x1<<0));

	/*
	 * Set GPX3_5 (backlight enable pin) output and pull up and low level for disabled
	 */
	writel(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_CON) & ~(0xf<<20)) | (0x1<<20));
	writel(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_PUD) & ~(0x3<<10)) | (0x2<<10));
	writel(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<5)) | (0x0<<5));
}

static void lcd_backlight(u8_t brightness)
{
	if(brightness)
	{
		writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<0)) | (0x0<<0));
		writel(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<5)) | (0x1<<5));
	}
	else
	{
		writel(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPD0_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<0)) | (0x1<<0));
		writel(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_DAT, (readl(EXYNOS4412_GPX3_BASE + EXYNOS4412_GPIO_DAT) & ~(0x1<<5)) | (0x0<<5));
	}
}

static void fb_init(struct fb_t * fb)
{
	struct exynos4412_fb_data_t * dat = (struct exynos4412_fb_data_t *)(fb->dat);

	/*
	 * Initial lcd port
	 */
	writel(EXYNOS4412_GPF0_BASE + EXYNOS4412_GPIO_CON, 0x22222222);
	writel(EXYNOS4412_GPF0_BASE + EXYNOS4412_GPIO_DRV, 0xffffffff);
	writel(EXYNOS4412_GPF0_BASE + EXYNOS4412_GPIO_PUD, 0x0);
	writel(EXYNOS4412_GPF1_BASE + EXYNOS4412_GPIO_CON, 0x22222222);
	writel(EXYNOS4412_GPF1_BASE + EXYNOS4412_GPIO_DRV, 0xffffffff);
	writel(EXYNOS4412_GPF1_BASE + EXYNOS4412_GPIO_PUD, 0x0);
	writel(EXYNOS4412_GPF2_BASE + EXYNOS4412_GPIO_CON, 0x22222222);
	writel(EXYNOS4412_GPF2_BASE + EXYNOS4412_GPIO_DRV, 0xffffffff);
	writel(EXYNOS4412_GPF2_BASE + EXYNOS4412_GPIO_PUD, 0x0);
	writel(EXYNOS4412_GPF3_BASE + EXYNOS4412_GPIO_CON, (readl(EXYNOS4412_GPF3_BASE + EXYNOS4412_GPIO_CON) & ~(0xffff<<0)) | (0x2222<<0));
	writel(EXYNOS4412_GPF3_BASE + EXYNOS4412_GPIO_DRV, (readl(EXYNOS4412_GPF3_BASE + EXYNOS4412_GPIO_DRV) & ~(0xff<<0)) | (0xff<<0));
	writel(EXYNOS4412_GPF3_BASE + EXYNOS4412_GPIO_PUD, (readl(EXYNOS4412_GPF3_BASE + EXYNOS4412_GPIO_PUD) & ~(0xff<<0)) | (0x00<<0));

	/*
	 * Lcd init function
	 */
	if(dat->init)
		dat->init();

	/*
	 * Display path selection
	 */
	writel(EXYNOS4412_LCDBLK_CFG, (readl(EXYNOS4412_LCDBLK_CFG) & ~(0x3<<0)) | (0x2<<0));
	writel(EXYNOS4412_LCDBLK_CFG2, (readl(EXYNOS4412_LCDBLK_CFG2) & ~(0x1<<0)) | (0x1<<0));

	/*
	 * Turn off all windows
	 */
	writel(dat->regbase + WINCON0, (readl(dat->regbase + WINCON0) & ~0x1));
	writel(dat->regbase + WINCON1, (readl(dat->regbase + WINCON1) & ~0x1));
	writel(dat->regbase + WINCON2, (readl(dat->regbase + WINCON2) & ~0x1));
	writel(dat->regbase + WINCON3, (readl(dat->regbase + WINCON3) & ~0x1));
	writel(dat->regbase + WINCON4, (readl(dat->regbase + WINCON4) & ~0x1));

	/*
	 * Turn off all windows color map
	 */
	writel(dat->regbase + WIN0MAP, (readl(dat->regbase + WIN0MAP) & ~(1<<24)));
	writel(dat->regbase + WIN1MAP, (readl(dat->regbase + WIN1MAP) & ~(1<<24)));
	writel(dat->regbase + WIN2MAP, (readl(dat->regbase + WIN2MAP) & ~(1<<24)));
	writel(dat->regbase + WIN3MAP, (readl(dat->regbase + WIN3MAP) & ~(1<<24)));
	writel(dat->regbase + WIN4MAP, (readl(dat->regbase + WIN4MAP) & ~(1<<24)));

	/*
	 * Turn off all windows color key and blending
	 */
	writel(dat->regbase + W1KEYCON0, (readl(dat->regbase + W1KEYCON0) & ~(3<<25)));
	writel(dat->regbase + W2KEYCON0, (readl(dat->regbase + W2KEYCON0) & ~(3<<25)));
	writel(dat->regbase + W3KEYCON0, (readl(dat->regbase + W3KEYCON0) & ~(3<<25)));
	writel(dat->regbase + W4KEYCON0, (readl(dat->regbase + W4KEYCON0) & ~(3<<25)));

	/*
	 * Initial lcd controller
	 */
	exynos4412_fb_set_output(dat);
	exynos4412_fb_set_display_mode(dat);
	exynos4412_fb_display_off(dat);
	exynos4412_fb_set_polarity(dat);
	exynos4412_fb_set_timing(dat);
	exynos4412_fb_set_lcd_size(dat);
	exynos4412_fb_set_clock(dat);

	/*
	 * Set lcd video buffer
	 */
	exynos4412_fb_set_buffer_size(dat, 0);
	exynos4412_fb_set_window_position(dat, 0);
	exynos4412_fb_set_window_size(dat, 0);

	/*
	 * Enable window 0 for main display area
	 */
	exynos4412_fb_window0_enable(dat);

	/*
	 * Display on
	 */
	exynos4412_fb_display_on(dat);

	/*
	 * Wait a moment
	 */
	mdelay(100);
}

static void fb_swap(struct fb_t * fb)
{
	struct exynos4412_fb_data_t * dat = (struct exynos4412_fb_data_t *)(fb->dat);
	void * vram;

	vram = dat->vram_front;
	dat->vram_front = dat->vram_back;
	dat->vram_back = vram;

	fb->surface.pixels = dat->vram_front;
}

static void fb_flush(struct fb_t * fb)
{
	struct exynos4412_fb_data_t * dat = (struct exynos4412_fb_data_t *)(fb->dat);

	exynos4412_fb_set_buffer_address(dat, 0, dat->vram_front);
}

static void fb_backlight(struct fb_t * fb, u8_t brightness)
{
	struct exynos4412_fb_data_t * dat = (struct exynos4412_fb_data_t *)(fb->dat);

	if(dat->backlight)
		dat->backlight(brightness);
}

static u8_t vram[2][1024 * 600 * 32 / 8] __attribute__((aligned(4)));

static struct exynos4412_fb_data_t vs070cxn = {
	.regbase			= EXYNOS4412_LCD_BASE,

	.width				= 1024,
	.height				= 600,
	.bits_per_pixel		= 32,
	.bytes_per_pixel	= 4,
	.freq				= 60,

	.output				= EXYNOS4412_FB_OUTPUT_RGB,
	.rgb_mode			= EXYNOS4412_FB_MODE_BGR_P,
	.bpp_mode			= EXYNOS4412_FB_BPP_MODE_32BPP,
	.swap				= EXYNOS4412_FB_SWAP_WORD,

	.rgba = {
		.r_mask			= 8,
		.r_field		= 0,
		.g_mask			= 8,
		.g_field		= 8,
		.b_mask			= 8,
		.b_field		= 16,
		.a_mask			= 8,
		.a_field		= 24,
	},

	.timing = {
		.h_fp			= 160,
		.h_bp			= 140,
		.h_sw			= 20,
		.v_fp			= 12,
		.v_fpe			= 1,
		.v_bp			= 20,
		.v_bpe			= 1,
		.v_sw			= 3,
	},

	.polarity = {
		.rise_vclk		= 0,
		.inv_hsync		= 1,
		.inv_vsync		= 1,
		.inv_vden		= 0,
	},

	.vram_front			= &vram[0][0],
	.vram_back			= &vram[1][0],

	.init				= lcd_init,
	.backlight			= lcd_backlight,
};

static struct fb_t exynos4412_fb;

void exynos4412_fb_initial(void)
{
	struct exynos4412_fb_data_t * dat = &vs070cxn;

	if( (dat->bits_per_pixel != 16) && (dat->bits_per_pixel != 24) && (dat->bits_per_pixel != 32) )
		return;

	exynos4412_fb.dat = dat;
	exynos4412_fb.surface.info.bits_per_pixel = dat->bits_per_pixel;
	exynos4412_fb.surface.info.bytes_per_pixel = dat->bytes_per_pixel;
	exynos4412_fb.surface.info.red_mask_size = dat->rgba.r_mask;
	exynos4412_fb.surface.info.red_field_pos = dat->rgba.r_field;
	exynos4412_fb.surface.info.green_mask_size = dat->rgba.g_mask;
	exynos4412_fb.surface.info.green_field_pos = dat->rgba.g_field;
	exynos4412_fb.surface.info.blue_mask_size = dat->rgba.b_mask;
	exynos4412_fb.surface.info.blue_field_pos = dat->rgba.b_field;
	exynos4412_fb.surface.info.alpha_mask_size = dat->rgba.a_mask;
	exynos4412_fb.surface.info.alpha_field_pos = dat->rgba.a_field;
	exynos4412_fb.surface.info.fmt = get_pixel_format(&(exynos4412_fb.surface.info));

	exynos4412_fb.surface.w = dat->width;
	exynos4412_fb.surface.h = dat->height;
	exynos4412_fb.surface.pitch = dat->width * dat->bytes_per_pixel;
	exynos4412_fb.surface.flag = SURFACE_PIXELS_DONTFREE;
	exynos4412_fb.surface.pixels = dat->vram_front;

	exynos4412_fb.surface.clip.x = 0;
	exynos4412_fb.surface.clip.y = 0;
	exynos4412_fb.surface.clip.w = dat->width;
	exynos4412_fb.surface.clip.h = dat->height;

	memset(&exynos4412_fb.surface.maps, 0, sizeof(struct surface_maps));
	surface_set_maps(&exynos4412_fb.surface.maps);

	fb_init(&exynos4412_fb);

	if(dat->backlight)
		dat->backlight(255);
}

struct surface_t * exynos4412_screen_surface(void)
{
	return &exynos4412_fb.surface;
}

void exynos4412_screen_swap(void)
{
	fb_swap(&exynos4412_fb);
}

void exynos4412_screen_flush(void)
{
	fb_flush(&exynos4412_fb);
}

void exynos4412_screen_backlight(u8_t brightness)
{
	fb_backlight(&exynos4412_fb, brightness);
}
