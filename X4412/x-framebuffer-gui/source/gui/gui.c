﻿/****************************************************************************************
* 文件名：GUI.C
* 功能：GUI基本绘图函数。进行基本绘图运算，并调用相应的刷新程序更新LCD显示。
* 作者：黄绍斌
* 修改：冯建辉
* 日期：2006.09.13
* 备注：图形操作层，进行各种图形运算操作。
****************************************************************************************/
#include "gui.h"
#include <math.h>
#include <graphic/surface.h>
#include <exynos4412-fb.h>

void GUI_Point(unsigned int xx,unsigned int yy, unsigned int c)
{
	exynos4412_screen_surface()->maps.point(exynos4412_screen_surface(), xx, yy, c, BLEND_MODE_REPLACE);
}

/****************************************************************************
* 名称：GUI_HLine()
* 功能：画水平线。
* 入口参数：x0		水平线起点所在列的位置
*           y0		水平线起点所在行的位置
*           x1          水平线终点所在列的位置
*           color	显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：无
* 说明：操作失败原因是指定地址超出缓冲区范围。
****************************************************************************/
void  GUI_HLine(unsigned int x0, unsigned int y0, unsigned int x1, TCOLOR color)
{
    unsigned int  bak;
    if(x0>x1) 				// 对x0、x1大小进行排列，以便画图
    {
        bak = x1;
        x1 = x0;
        x0 = bak;
    }   
    do
    {
        GUI_Point(x0, y0, color);	// 逐点显示，描出垂直线
        x0++;
    }
    while(x1>=x0);
}

/***********************************************************************
* 名称：GUI_RLine()
* 功能：画竖直线。根据硬件特点，实现加速。
* 入口参数：x0		垂直线起点所在列的位置
*           y0		垂直线起点所在行的位置
*           y1          垂直线终点所在行的位置
*           color	显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：	无
* 说明：操作失败原因是指定地址超出缓冲区范围。
***********************************************************************/
void  GUI_RLine(unsigned int x0, unsigned int y0, unsigned int y1, TCOLOR color)
{
    unsigned int  bak;
    if(y0>y1)                           // 对y0、y1大小进行排列，以便画图
    {
        bak = y1;
        y1 = y0;
        y0 = bak;
    }
    do
    {
        GUI_Point(x0, y0, color);	// 逐点显示，描出垂直线
        y0++;
    }
    while(y1>=y0);
}

/****************************************************************************
* 名称：GUI_Rectangle()
* 功能：画矩形。
* 入口参数：x0		矩形左上角的x坐标值
*           y0		矩形左上角的y坐标值
*           x1          矩形右下角的x坐标值
*           y1          矩形右下角的y坐标值
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Rectangle(uint16 x0, uint16 y0, uint16 x1, uint16 y1, TCOLOR color)
{
   GUI_HLine(x0, y0, x1, color);
   GUI_HLine(x0, y1, x1, color);
   GUI_RLine(x0, y0, y1, color);
   GUI_RLine(x1, y0, y1, color);
}

/****************************************************************************
* 名称：GUI_RectangleFill()
* 功能：填充矩形。画一个填充的矩形，填充色与边框色一样。
* 入口参数：x0		矩形左上角的x坐标值
*           y0		矩形左上角的y坐标值
*           x1          矩形右下角的x坐标值
*           y1          矩形右下角的y坐标值
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_RectangleFill(uint16 x0, uint16 y0, uint16 x1, uint16 y1, TCOLOR color)
{
   uint32  i;

   /* 先找出矩形左上角与右下角的两个点，保存在(x0,y0)，(x1,y1) */
   if(x0>x1) 						// 若x0>x1，则x0与x1交换
   {
      i = x0;
      x0 = x1;
      x1 = i;
   }
   if(y0>y1)						// 若y0>y1，则y0与y1交换
   {
      i = y0;
      y0 = y1;
      y1 = i;
   }
   
   /* 判断是否只是直线 */
   if(y0==y1) 
   {
      GUI_HLine(x0, y0, x1, color);
      return;
   }
   if(x0==x1) 
   {
      GUI_RLine(x0, y0, y1, color);
      return;
   }

   while(y0<=y1)						
   {
      GUI_HLine(x0, y0, x1, color);	                        // 当前画水平线
      y0++;							// 下一行
   }
}

/****************************************************************************
* 名称：GUI_Square()
* 功能：画正方形。
* 入口参数：x0		正方形左上角的x坐标值
*           y0		正方形左上角的y坐标值
*           with        正方形的边长
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Square(uint32 x0, uint32 y0, uint32  with, TCOLOR  color)
{
   if(with==0)
      return;
   if( (x0+with) > GUI_LCM_XMAX )
      return;
   if( (y0+with) > GUI_LCM_YMAX )
      return;
   GUI_Rectangle(x0, y0, x0+with, y0+with, color);
}



/****************************************************************************
* 名称：GUI_Line()
* 功能：画任意两点之间的直线。
* 入口参数：x0		直线起点的x坐标值
*           y0		直线起点的y坐标值
*           x1          直线终点的x坐标值
*           y1          直线终点的y坐标值
*           color	显示颜色(对于黑白色LCM，为0时灭，为1时显示)
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Line(uint32 x0, uint32 y0, uint32 x1, uint32 y1, TCOLOR color)
{
   int32   dx;						// 直线x轴差值变量
   int32   dy;          			        // 直线y轴差值变量
   int8    dx_sym;					// x轴增长方向，为-1时减值方向，为1时增值方向
   int8    dy_sym;					// y轴增长方向，为-1时减值方向，为1时增值方向
   int32   dx_x2;					// dx*2值变量，用于加快运算速度
   int32   dy_x2;					// dy*2值变量，用于加快运算速度
   int32   di;						// 决策变量

   dx = x1-x0;						// 求取两点之间的差值
   dy = y1-y0;
   
   /* 判断增长方向，或是否为水平线、垂直线、点 */
   if(dx>0)						// 判断x轴方向
   {
      dx_sym = 1;					// dx>0，设置dx_sym=1
   }
   else
   {
      if(dx<0)
      {
         dx_sym = -1;				        // dx<0，设置dx_sym=-1
      }
      else
      {  // dx==0，画垂直线，或一点
         GUI_RLine(x0, y0, y1, color);
      	 return;
      }
   }
   
   if(dy>0)						// 判断y轴方向
   {
      dy_sym = 1;					// dy>0，设置dy_sym=1
   }
   else
   {
      if(dy<0)
      {
         dy_sym = -1;				        // dy<0，设置dy_sym=-1
      }
      else
      {  // dy==0，画水平线，或一点
         GUI_HLine(x0, y0, x1, color);
      	 return;
      }
   }
    
   /* 将dx、dy取绝对值 */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* 计算2倍的dx及dy值 */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* 使用Bresenham法进行画直线 */
   if(dx>=dy)						// 对于dx>=dy，则使用x轴为基准
   {
      di = dy_x2 - dx;
      while(x0!=x1)
      {
         GUI_Point(x0, y0, color);
         x0 += dx_sym;
         if(di<0)
         {
            di += dy_x2;			        // 计算出下一步的决策值
         }
         else
         {
            di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      GUI_Point(x0, y0, color);		                // 显示最后一点
   }
   else							// 对于dx<dy，则使用y轴为基准
   {
      di = dx_x2 - dy;
      while(y0!=y1)
      {
         GUI_Point(x0, y0, color);
         y0 += dy_sym;
         if(di<0)
         {
            di += dx_x2;
         }
         else
         {
            di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      GUI_Point(x0, y0, color);		// 显示最后一点
   }
}

/****************************************************************************
* 名称：GUI_LineWith()
* 功能：画任意两点之间的直线，并且可设置线的宽度。
* 入口参数：x0		直线起点的x坐标值
*           y0		直线起点的y坐标值
*           x1          直线终点的x坐标值
*           y1          直线终点的y坐标值
*           with        线宽(0-50)
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_LineWith(uint32 x0, uint32 y0, uint32 x1, uint32 y1, uint16 with, TCOLOR color)
{
   int32   dx;						// 直线x轴差值变量
   int32   dy;          			        // 直线y轴差值变量
   int8    dx_sym;					// x轴增长方向，为-1时减值方向，为1时增值方向
   int8    dy_sym;					// y轴增长方向，为-1时减值方向，为1时增值方向
   int32   dx_x2;					// dx*2值变量，用于加快运算速度
   int32   dy_x2;					// dy*2值变量，用于加快运算速度
   int32   di;						// 决策变量
   
   int32   wx, wy;					// 线宽变量
   int32   draw_a, draw_b;
   
   /* 参数过滤 */
   if(with==0)
      return;
   if(with>50)
      with = 50;
   
   dx = x1-x0;						// 求取两点之间的差值
   dy = y1-y0;
   
   wx = with/2;
   wy = with-wx-1;
   
   /* 判断增长方向，或是否为水平线、垂直线、点 */
   if(dx>0)						// 判断x轴方向
   {
      dx_sym = 1;					// dx>0，设置dx_sym=1
   }
   else
   {
      if(dx<0)
      {
         dx_sym = -1;				        // dx<0，设置dx_sym=-1
      }
      else
      {  /* dx==0，画垂直线，或一点 */
         wx = x0-wx;
         if(wx<0)
            wx = 0;
         wy = x0+wy;
         
         while(1)
         {
            x0 = wx;
            GUI_RLine(x0, y0, y1, color);
            if(wx>=wy)
               break;
            wx++;
         }
      	 return;
      }
   }
   
   if(dy>0)						// 判断y轴方向
   {
      dy_sym = 1;					// dy>0，设置dy_sym=1
   }
   else
   {
      if(dy<0)
      {
         dy_sym = -1;				        // dy<0，设置dy_sym=-1
      }
      else
      {  /* dy==0，画水平线，或一点 */
         wx = y0-wx;
         if(wx<0) wx = 0;
         wy = y0+wy;
         
         while(1)
         {
            y0 = wx;
            GUI_HLine(x0, y0, x1, color);
            if(wx>=wy)
               break;
            wx++;
         }
      	 return;
      }
   }
    
   /* 将dx、dy取绝对值 */
   dx = dx_sym * dx;
   dy = dy_sym * dy;
 
   /* 计算2倍的dx及dy值 */
   dx_x2 = dx*2;
   dy_x2 = dy*2;
   
   /* 使用Bresenham法进行画直线 */
   if(dx>=dy)						// 对于dx>=dy，则使用x轴为基准
   {
      di = dy_x2 - dx;
      while(x0!=x1)
      {  /* x轴向增长，则宽度在y方向，即画垂直线 */
         draw_a = y0-wx;
         if(draw_a<0) draw_a = 0;
         draw_b = y0+wy;
         GUI_RLine(x0, draw_a, draw_b, color);
         
         x0 += dx_sym;				
         if(di<0)
         {
            di += dy_x2;			        // 计算出下一步的决策值
         }
         else
         {
            di += dy_x2 - dx_x2;
            y0 += dy_sym;
         }
      }
      draw_a = y0-wx;
      if(draw_a<0)
         draw_a = 0;
      draw_b = y0+wy;
      GUI_RLine(x0, draw_a, draw_b, color);
   }
   else							// 对于dx<dy，则使用y轴为基准
   {
      di = dx_x2 - dy;
      while(y0!=y1)
      {  /* y轴向增长，则宽度在x方向，即画水平线 */
         draw_a = x0-wx;
         if(draw_a<0)
            draw_a = 0;
         draw_b = x0+wy;
         GUI_HLine(draw_a, y0, draw_b, color);
         
         y0 += dy_sym;
         if(di<0)
         {
            di += dx_x2;
         }
         else
         {
            di += dx_x2 - dy_x2;
            x0 += dx_sym;
         }
      }
      draw_a = x0-wx;
      if(draw_a<0)
         draw_a = 0;
      draw_b = x0+wy;
      GUI_HLine(draw_a, y0, draw_b, color);
   }
}

/****************************************************************************
* 名称：GUI_LineS()
* 功能：多个点之间的连续连线。从第一点连到第二点，再连到第三点...
* 入口参数：points      多个点坐标数据的指针，数据排列为(x0,y0)、(x1,y1)、(x2,y2)...
*           no          点数目，至少要大于1
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_LineS(uint32 const *points, uint16 no, TCOLOR color)
{
   uint32  x0, y0;
   uint32  x1, y1;
   uint16   i;

   /* 入口参数过滤 */
   if(0==no)
      return;
   if(1==no)						// 单点
   {
      x0 = *points++;
      y0 = *points;
      GUI_Point(x0, y0, color);
   }
   
   /* 画多条线条 */
   x0 = *points++;					// 取出第一点坐标值，作为原起点坐标值
   y0 = *points++;
   for(i=1; i<no; i++)
   {
      x1 = *points++;				        // 取出下一点坐标值
      y1 = *points++;
      GUI_Line(x0, y0, x1, y1, color);
      x0 = x1;						// 更新原起点坐标
      y0 = y1;
   }
}

/****************************************************************************
* 名称：GUI_Circle()
* 功能：指定圆心位置及半径，画圆。
* 入口参数：x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r           圆的半径
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Circle(uint32 x0, uint32 y0, uint32 r, TCOLOR color)
{
   int32  draw_x0, draw_y0;			        // 刽图点坐标变量
   int32  draw_x1, draw_y1;	
   int32  draw_x2, draw_y2;	
   int32  draw_x3, draw_y3;	
   int32  draw_x4, draw_y4;	
   int32  draw_x5, draw_y5;	
   int32  draw_x6, draw_y6;	
   int32  draw_x7, draw_y7;	
   int32  xx, yy;					// 画圆控制变量
 
   int32  di;						// 决策变量
   
   /* 参数过滤 */
   if(0==r)
      return;
   
   /* 计算出8个特殊点(0、45、90、135、180、225、270度)，进行显示 */
   draw_x0 = draw_x1 = x0;
   draw_y0 = draw_y1 = y0 + r;
   if(draw_y0<GUI_LCM_YMAX)
      GUI_Point(draw_x0, draw_y0, color);	        // 90度
	
   draw_x2 = draw_x3 = x0;
   draw_y2 = draw_y3 = y0 - r;
   if(draw_y2>=0)
      GUI_Point(draw_x2, draw_y2, color);		// 270度

   draw_x4 = draw_x6 = x0 + r;
   draw_y4 = draw_y6 = y0;
   if(draw_x4<GUI_LCM_XMAX)
      GUI_Point(draw_x4, draw_y4, color);	        // 0度
   
   draw_x5 = draw_x7 = x0 - r;
   draw_y5 = draw_y7 = y0;
   if(draw_x5>=0)
      GUI_Point(draw_x5, draw_y5, color);		// 180度   
   if(1==r)
      return;					        // 若半径为1，则已圆画完

   /* 使用Bresenham法进行画圆 */
   di = 3 - 2*r;					// 初始化决策变量
   
   xx = 0;
   yy = r;	
   while(xx<yy)
   {
      if(di<0)
      {
         di += 4*xx + 6;
      }
      else
      {
         di += 4*(xx - yy) + 10;
	  
         yy--;
         draw_y0--;
         draw_y1--;
         draw_y2++;
         draw_y3++;
         draw_x4--;
         draw_x5++;
         draw_x6--;
         draw_x7++;
      }
	  
      xx++;
      draw_x0++;
      draw_x1--;
      draw_x2++;
      draw_x3--;
      draw_y4++;
      draw_y5++;
      draw_y6--;
      draw_y7--;
	
      /* 要判断当前点是否在有效范围内 */
      if( (draw_x0<=GUI_LCM_XMAX)&&(draw_y0>=0) )
      {
         GUI_Point(draw_x0, draw_y0, color);
      }
      if( (draw_x1>=0)&&(draw_y1>=0) )
      {
         GUI_Point(draw_x1, draw_y1, color);
      }
      if( (draw_x2<=GUI_LCM_XMAX)&&(draw_y2<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x2, draw_y2, color);
      }
      if( (draw_x3>=0)&&(draw_y3<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x3, draw_y3, color);
      }
      if( (draw_x4<=GUI_LCM_XMAX)&&(draw_y4>=0) )
      {
         GUI_Point(draw_x4, draw_y4, color);
      }
      if( (draw_x5>=0)&&(draw_y5>=0) )
      {
         GUI_Point(draw_x5, draw_y5, color);
      }
      if( (draw_x6<=GUI_LCM_XMAX)&&(draw_y6<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x6, draw_y6, color);
      }
      if( (draw_x7>=0)&&(draw_y7<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x7, draw_y7, color);
      }
   }
}

/****************************************************************************
* 名称：GUI_CircleFill()
* 功能：指定圆心位置及半径，画圆并填充，填充色与边框色一样。
* 入口参数：x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r           圆的半径
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_CircleFill(uint32 x0, uint32 y0, uint32 r, TCOLOR color)
{
   int32  draw_x0, draw_y0;			        // 刽图点坐标变量
   int32  draw_x1, draw_y1;	
   int32  draw_x2, draw_y2;	
   int32  draw_x3, draw_y3;	
   int32  draw_x4, draw_y4;	
   int32  draw_x5, draw_y5;	
   int32  draw_x6, draw_y6;	
   int32  draw_x7, draw_y7;	
   int32  fill_x0, fill_y0;			        // 填充所需的变量，使用垂直线填充
   int32  fill_x1;
   int32  xx, yy;					// 画圆控制变量
 
   int32  di;						// 决策变量
   
   /* 参数过滤 */
   if(0==r)
      return;
   
   /* 计算出4个特殊点(0、90、180、270度)，进行显示 */
   draw_x0 = draw_x1 = x0;
   draw_y0 = draw_y1 = y0 + r;
   if(draw_y0<GUI_LCM_YMAX)
   {
      GUI_Point(draw_x0, draw_y0, color);	// 90度
   }
    	
   draw_x2 = draw_x3 = x0;
   draw_y2 = draw_y3 = y0 - r;
   if(draw_y2>=0)
   {
      GUI_Point(draw_x2, draw_y2, color);	// 270度
   }
  	
   draw_x4 = draw_x6 = x0 + r;
   draw_y4 = draw_y6 = y0;
   if(draw_x4<GUI_LCM_XMAX) 
   {
      GUI_Point(draw_x4, draw_y4, color);	// 0度
      fill_x1 = draw_x4;
   }
   else
   {
      fill_x1 = GUI_LCM_XMAX;
   }
   fill_y0 = y0;							// 设置填充线条起始点fill_x0
   fill_x0 = x0 - r;						// 设置填充线条结束点fill_y1
   if(fill_x0<0)
      fill_x0 = 0;
   GUI_HLine(fill_x0, fill_y0, fill_x1, color);
   
   draw_x5 = draw_x7 = x0 - r;
   draw_y5 = draw_y7 = y0;
   if(draw_x5>=0) 
   {
      GUI_Point(draw_x5, draw_y5, color);	// 180度
   }
   if(1==r)
      return;
   
   
   /* 使用Bresenham法进行画圆 */
   di = 3 - 2*r;				// 初始化决策变量
   
   xx = 0;
   yy = r;
   while(xx<yy)
   {
      if(di<0)
      {
         di += 4*xx + 6;
      }
      else
      {
         di += 4*(xx - yy) + 10;

         yy--;
         draw_y0--;
         draw_y1--;
         draw_y2++;
         draw_y3++;
         draw_x4--;
         draw_x5++;
         draw_x6--;
         draw_x7++;
      }
	  
      xx++;
      draw_x0++;
      draw_x1--;
      draw_x2++;
      draw_x3--;
      draw_y4++;
      draw_y5++;
      draw_y6--;
      draw_y7--;
		
	
      /* 要判断当前点是否在有效范围内 */
      if( (draw_x0<=GUI_LCM_XMAX)&&(draw_y0>=0) )
      {
         GUI_Point(draw_x0, draw_y0, color);
      }
      if( (draw_x1>=0)&&(draw_y1>=0) )
      {
         GUI_Point(draw_x1, draw_y1, color);
      }
	  
      /* 第二点水直线填充(下半圆的点) */
      if(draw_x1>=0)
      {  /* 设置填充线条起始点fill_x0 */
         fill_x0 = draw_x1;
      /* 设置填充线条起始点fill_y0 */
         fill_y0 = draw_y1;
         if(fill_y0>GUI_LCM_YMAX)
            fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0)
            fill_y0 = 0;
      /* 设置填充线条结束点fill_x1 */
         fill_x1 = x0*2 - draw_x1;
         if(fill_x1>GUI_LCM_XMAX)
            fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }

      if( (draw_x2<=GUI_LCM_XMAX)&&(draw_y2<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x2, draw_y2, color);
      }
	    	  
      if( (draw_x3>=0)&&(draw_y3<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x3, draw_y3, color);
      }
	  
      /* 第四点垂直线填充(上半圆的点) */
      if(draw_x3>=0)
      {  /* 设置填充线条起始点fill_x0 */
         fill_x0 = draw_x3;
         /* 设置填充线条起始点fill_y0 */
         fill_y0 = draw_y3;
         if(fill_y0>GUI_LCM_YMAX)
            fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0)
            fill_y0 = 0;
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x3;				
         if(fill_x1>GUI_LCM_XMAX)
            fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }

      if( (draw_x4<=GUI_LCM_XMAX)&&(draw_y4>=0) )
      {
         GUI_Point(draw_x4, draw_y4, color);
      }
      if( (draw_x5>=0)&&(draw_y5>=0) )
      {
         GUI_Point(draw_x5, draw_y5, color);
      }
	  
      /* 第六点垂直线填充(上半圆的点) */
      if(draw_x5>=0)
      {  /* 设置填充线条起始点fill_x0 */
         fill_x0 = draw_x5;
         /* 设置填充线条起始点fill_y0 */
         fill_y0 = draw_y5;
         if(fill_y0>GUI_LCM_YMAX)
            fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0)
            fill_y0 = 0;
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x5;				
         if(fill_x1>GUI_LCM_XMAX)
            fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }

      if( (draw_x6<=GUI_LCM_XMAX)&&(draw_y6<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x6, draw_y6, color);
      }

      if( (draw_x7>=0)&&(draw_y7<=GUI_LCM_YMAX) )
      {
         GUI_Point(draw_x7, draw_y7, color);
      }
	  
      /* 第八点垂直线填充(上半圆的点) */
      if(draw_x7>=0)
      {  /* 设置填充线条起始点fill_x0 */
         fill_x0 = draw_x7;
         /* 设置填充线条起始点fill_y0 */
         fill_y0 = draw_y7;
         if(fill_y0>GUI_LCM_YMAX)
            fill_y0 = GUI_LCM_YMAX;
         if(fill_y0<0)
            fill_y0 = 0;
         /* 设置填充线条结束点fill_x1 */									
         fill_x1 = x0*2 - draw_x7;				
         if(fill_x1>GUI_LCM_XMAX)
            fill_x1 = GUI_LCM_XMAX;
         GUI_HLine(fill_x0, fill_y0, fill_x1, color);
      }
   }
}

/****************************************************************************
* 名称：GUI_Ellipse()
* 功能：画正椭圆。给定椭圆的四个点的参数，最左、最右点的x轴坐标值为x0、x1，最上、最下点
*      的y轴坐标为y0、y1。
* 入口参数：x0		最左点的x坐标值
*           x1		最右点的x坐标值
*           y0		最上点的y坐标值
*           y1          最下点的y坐标值
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Ellipse(uint32 x0, uint32 x1, uint32 y0, uint32 y1, TCOLOR color)
{
   int32  draw_x0, draw_y0;			// 刽图点坐标变量
   int32  draw_x1, draw_y1;
   int32  draw_x2, draw_y2;
   int32  draw_x3, draw_y3;
   int32  xx, yy;				// 画图控制变量
    
   int32  center_x, center_y;		        // 椭圆中心点坐标变量
   int32  radius_x, radius_y;		        // 椭圆的半径，x轴半径和y轴半径
   int32  radius_xx, radius_yy;		        // 半径乘平方值
   int32  radius_xx2, radius_yy2;	        // 半径乘平方值的两倍
   int32  di;					// 定义决策变量
	
   /* 参数过滤 */
   if( (x0==x1) || (y0==y1) )
      return;
   	
   /* 计算出椭圆中心点坐标 */
   center_x = (x0 + x1) >> 1;			
   center_y = (y0 + y1) >> 1;
   
   /* 计算出椭圆的半径，x轴半径和y轴半径 */
   if(x0 > x1)
   {
      radius_x = (x0 - x1) >> 1;
   }
   else
   {
      radius_x = (x1 - x0) >> 1;
   }
   if(y0 > y1)
   {
      radius_y = (y0 - y1) >> 1;
   }
   else
   {
      radius_y = (y1 - y0) >> 1;
   }
		
   /* 计算半径平方值 */
   radius_xx = radius_x * radius_x;
   radius_yy = radius_y * radius_y;
	
   /* 计算半径平方值乘2值 */
   radius_xx2 = radius_xx<<1;
   radius_yy2 = radius_yy<<1;
	
   /* 初始化画图变量 */
   xx = 0;
   yy = radius_y;
  
   di = radius_yy2 + radius_xx - radius_xx2*radius_y ;	// 初始化决策变量 
	
   /* 计算出椭圆y轴上的两个端点坐标，作为作图起点 */
   draw_x0 = draw_x1 = draw_x2 = draw_x3 = center_x;
   draw_y0 = draw_y1 = center_y + radius_y;
   draw_y2 = draw_y3 = center_y - radius_y;
  
	 
   GUI_Point(draw_x0, draw_y0, color);			// 画y轴上的两个端点 
   GUI_Point(draw_x2, draw_y2, color);
	
   while( (radius_yy*xx) < (radius_xx*yy) ) 
   {
      if(di<0)
      {
         di+= radius_yy2*(2*xx+3);
      }
      else
      {
         di += radius_yy2*(2*xx+3) + 4*radius_xx - 4*radius_xx*yy;
	 	  
         yy--;
         draw_y0--;
         draw_y1--;
         draw_y2++;
         draw_y3++;
      }
	  
      xx ++;						// x轴加1
	 		
      draw_x0++;
      draw_x1--;
      draw_x2++;
      draw_x3--;
		
      GUI_Point(draw_x0, draw_y0, color);
      GUI_Point(draw_x1, draw_y1, color);
      GUI_Point(draw_x2, draw_y2, color);
      GUI_Point(draw_x3, draw_y3, color);
   }
  
   di = radius_xx2*(yy-1)*(yy-1) + radius_yy2*xx*xx + radius_yy + radius_yy2*xx - radius_xx2*radius_yy;
   while(yy>=0) 
   {
      if(di<0)
      {
         di+= radius_xx2*3 + 4*radius_yy*xx + 4*radius_yy - 2*radius_xx2*yy;
	 	  
         xx ++;						// x轴加1
         draw_x0++;
         draw_x1--;
         draw_x2++;
         draw_x3--;
      }
      else
      {
         di += radius_xx2*3 - 2*radius_xx2*yy;
      }
	  
      yy--;
      draw_y0--;
      draw_y1--;
      draw_y2++;
      draw_y3++;
		
      GUI_Point(draw_x0, draw_y0, color);
      GUI_Point(draw_x1, draw_y1, color);
      GUI_Point(draw_x2, draw_y2, color);
      GUI_Point(draw_x3, draw_y3, color);
   }     
}

/****************************************************************************
* 名称：GUI_EllipseFill()
* 功能：画正椭圆，并填充。给定椭圆的四个点的参数，最左、最右点的x轴坐标值为x0、x1，最上、最下点
*      的y轴坐标为y0、y1。
* 入口参数：x0		最左点的x坐标值
*           x1		最右点的x坐标值
*           y0		最上点的y坐标值
*           y1          最下点的y坐标值
*           color	填充颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_EllipseFill(uint32 x0, uint32 x1, uint32 y0, uint32 y1, TCOLOR color)
{
   int32  draw_x0, draw_y0;			// 刽图点坐标变量
   int32  draw_x1, draw_y1;
   int32  draw_x2, draw_y2;
   int32  draw_x3, draw_y3;
   int32  xx, yy;				// 画图控制变量
    
   int32  center_x, center_y;		        // 椭圆中心点坐标变量
   int32  radius_x, radius_y;		        // 椭圆的半径，x轴半径和y轴半径
   int32  radius_xx, radius_yy;		        // 半径乘平方值
   int32  radius_xx2, radius_yy2;	        // 半径乘平方值的两倍
   int32  di;					// 定义决策变量
	
   /* 参数过滤 */
   if( (x0==x1) || (y0==y1) )
       return;
   
   /* 计算出椭圆中心点坐标 */
   center_x = (x0 + x1) >> 1;			
   center_y = (y0 + y1) >> 1;
   
   /* 计算出椭圆的半径，x轴半径和y轴半径 */
   if(x0 > x1)
   {
      radius_x = (x0 - x1) >> 1;
   }
   else
   {
      radius_x = (x1 - x0) >> 1;
   }
   if(y0 > y1)
   {
      radius_y = (y0 - y1) >> 1;
   }
   else
   {
      radius_y = (y1 - y0) >> 1;
   }
		
   /* 计算半径乘平方值 */
   radius_xx = radius_x * radius_x;
   radius_yy = radius_y * radius_y;
	
   /* 计算半径乘4值 */
   radius_xx2 = radius_xx<<1;
   radius_yy2 = radius_yy<<1;
   
    /* 初始化画图变量 */
   xx = 0;
   yy = radius_y;
  
   di = radius_yy2 + radius_xx - radius_xx2*radius_y ;	// 初始化决策变量 
	
   /* 计算出椭圆y轴上的两个端点坐标，作为作图起点 */
   draw_x0 = draw_x1 = draw_x2 = draw_x3 = center_x;
   draw_y0 = draw_y1 = center_y + radius_y;
   draw_y2 = draw_y3 = center_y - radius_y;
  
	 
   GUI_Point(draw_x0, draw_y0, color);					// 画y轴上的两个端点
   GUI_Point(draw_x2, draw_y2, color);
	
   while( (radius_yy*xx) < (radius_xx*yy) ) 
   {
      if(di<0)
      {
         di+= radius_yy2*(2*xx+3);
      }
      else
      {
         di += radius_yy2*(2*xx+3) + 4*radius_xx - 4*radius_xx*yy;
	 	  
         yy--;
         draw_y0--;
         draw_y1--;
         draw_y2++;
         draw_y3++;
      }
	  
      xx ++;						// x轴加1
	 		
      draw_x0++;
      draw_x1--;
      draw_x2++;
      draw_x3--;
		
      GUI_Point(draw_x0, draw_y0, color);
      GUI_Point(draw_x1, draw_y1, color);
      GUI_Point(draw_x2, draw_y2, color);
      GUI_Point(draw_x3, draw_y3, color);
	  
      /* 若y轴已变化，进行填充 */
      if(di>=0)
      {
         GUI_HLine(draw_x0, draw_y0, draw_x1, color);
         GUI_HLine(draw_x2, draw_y2, draw_x3, color);
      }
   }
  
   di = radius_xx2*(yy-1)*(yy-1) + radius_yy2*xx*xx + radius_yy + radius_yy2*xx - radius_xx2*radius_yy;
   while(yy>=0) 
   {
      if(di<0)
      {
         di+= radius_xx2*3 + 4*radius_yy*xx + 4*radius_yy - 2*radius_xx2*yy;
	 	  
         xx ++;						// x轴加1
         draw_x0++;
         draw_x1--;
         draw_x2++;
         draw_x3--;
      }
      else
      {
         di += radius_xx2*3 - 2*radius_xx2*yy;
      }
	  
      yy--;
      draw_y0--;
      draw_y1--;
      draw_y2++;
      draw_y3++;
		
      GUI_Point(draw_x0, draw_y0, color);
      GUI_Point(draw_x1, draw_y1, color);
      GUI_Point(draw_x2, draw_y2, color);
      GUI_Point(draw_x3, draw_y3, color);
	  
      /* y轴已变化，进行填充 */
      GUI_HLine(draw_x0, draw_y0, draw_x1, color);
      GUI_HLine(draw_x2, draw_y2, draw_x3, color); 
   }     
}

/* 定义折点个数 */
#ifndef  DOWNP_N
#define  DOWNP_N		20
#endif
#ifndef	 UPP_N
#define  UPP_N			20
#endif

/****************************************************************************
* 名称：GUI_Arc4()
* 功能：画弧。起点及终点只能为0度-90度、90度-180度、180度-270度、270度-0度等。即分别
*      为第1-4像限的90度弧。
* 入口参数：x0		圆心的x坐标值
*           y0		圆心的y坐标值
*           r           圆弧的半径
*           angle	画弧的像限(1-4)
*           color	显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Arc4(uint32 x, uint32 y, uint32 r, uint16 angle, TCOLOR color)
{
   int32  draw_x, draw_y;

   int32  op_x, op_y;
   int32  op_2rr;
   
   if(r==0)
      return;
   
   op_2rr = 2*r*r;							// 计算r平方乖以2
   
   switch(angle)
   {  case  1:
            draw_x = x+r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);	         	// 开始画图
                 
               /* 计算下一点 */
               op_y++;
               draw_y++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) // 使用逐点比较法实现画圆弧
               {
                  op_x--;
                  draw_x--;
               }
               if(op_y>=op_x)
                  break;
            }
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		        // 开始画图
                 
               /* 计算下一点 */
               op_x--;
               draw_x--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 )// 使用逐点比较法实现画圆弧
               {
                  op_y++;
                  draw_y++;
               }
               if(op_x<=0)
               {
                  GUI_Point(draw_x, draw_y, color);		        // 开始画图
                  break;
               }
            }
            break;      
   				
      case  2:
            draw_x = x-r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		// 开始画图
                 
               /* 计算下一点 */
               op_y++;
               draw_y++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
               {
                  op_x--;
                  draw_x++;
               }
               if(op_y>=op_x)
                  break;
            }
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		// 开始画图
                 
               /* 计算下一点 */
               op_x--;
               draw_x++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// 使用逐点比较法实现画圆弧
               {
                  op_y++;
                  draw_y++;
               }
               if(op_x<=0)
               {
                  GUI_Point(draw_x, draw_y, color);		// 开始画图
                  break;
               }
            }
            break;
            
      case  3:
            draw_x = x-r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		// 开始画图
                 
               /* 计算下一点 */
               op_y++;
               draw_y--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
               {
                  op_x--;
                  draw_x++;
               }
               if(op_y>=op_x)
                  break;
            }
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		// 开始画图
                 
               /* 计算下一点 */
               op_x--;
               draw_x++;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// 使用逐点比较法实现画圆弧
               {
                  op_y++;
                  draw_y--;
               }
               if(op_x<=0)
               {
                  GUI_Point(draw_x, draw_y, color);		// 开始画图
                  break;
               }
            }
            break;
            
      case  4:
            draw_x = x+r;
            draw_y = y;
            
            op_x = r;
            op_y = 0;
 
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		// 开始画图
                 
               /* 计算下一点 */
               op_y++;
               draw_y--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
               {
                  op_x--;
                  draw_x--;
               }
               if(op_y>=op_x)
                  break;
            }
            while(1)
            {
               GUI_Point(draw_x, draw_y, color);		// 开始画图
                 
               /* 计算下一点 */
               op_x--;
               draw_x--;
               if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) 	// 使用逐点比较法实现画圆弧
               {
                  op_y++;
                  draw_y--;
               }
               if(op_x<=0)
               {
                  GUI_Point(draw_x, draw_y, color);		// 开始画图
                  break;
               }
            }
            break;
            
      default:
            break;
   }
}

/****************************************************************************
* 名称：GUI_Arc()
* 功能：指定起点、终点及半径画弧(不能画圆)。使用的是顺时针方向画图。
* 入口参数：x			圆心的x轴坐标值
*           y			圆心的y轴坐标值
*           stangle 	        起始角度(0-359度)
*           endangle	        终止角度(0-359度)
*           r  			圆的半径终点
*           color		显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Arc(uint32 x, uint32 y, uint32 r, uint32 stangle, uint32 endangle, TCOLOR color)
{
   int32  draw_x, draw_y;					// 画图坐标变量
   int32  op_x, op_y;						// 操作坐标
   int32  op_2rr;							// 2*r*r值变量
   
   int32  pno_angle;						// 度角点的个数
   uint16  draw_on;							// 画点开关，为1时画点，为0时不画
   
   
   /* 参数过滤 */
   if(r==0)
      return;							// 半径为0则直接退出
   if(stangle==endangle)
      return;			// 起始角度与终止角度相同，退出
   if( (stangle>=360) || (endangle>=360) )
      return;

   op_2rr = 2*r*r;							// 计算r平方乖以2
   pno_angle = 0;
   /* 先计算出在此半径下的45度的圆弧的点数 */       
   op_x = r;
   op_y = 0;
   while(1)
   {
      pno_angle++; 							// 画点计数
      /* 计算下一点 */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
      {
         op_x--;
      }
      if(op_y>=op_x)
         break;
   }
   
   draw_on = 0;								// 最开始关画点开关
   /* 设置起始点及终点 */
   if(endangle>stangle)
      draw_on = 1;		// 若终点大于起点，则从一开始即画点(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0)
      stangle=1;
   if(endangle==0)
      endangle=1;
   
   /* 开始顺时针画弧，从359度开始(第4像限) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* 计算下一点 */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
      {
         op_x--;
         draw_x--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // 使用逐点比较法实现画圆弧
      {
         op_y++;
         draw_y--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		// 开始画图
         break;
      }
   }

   /* 开始顺时针画弧，从269度开始(第3像限) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* 计算下一点 */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // 使用逐点比较法实现画圆弧
      {
         op_y--;
         draw_y++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		// 开始画图
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // 使用逐点比较法实现画圆弧
      {
         op_x++;
         draw_x--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }

   /* 开始顺时针画弧，从179度开始(第2像限) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* 计算下一点 */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
      {
         op_x--;
         draw_x++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // 使用逐点比较法实现画圆弧
      {
         op_y++;
         draw_y++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		// 开始画图
         break;
      }
   }

   /* 开始顺时针画弧，从89度开始(第1像限) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* 计算下一点 */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 ) // 使用逐点比较法实现画圆弧
      {
         op_y--;
         draw_y--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		// 开始画图
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 ) // 使用逐点比较法实现画圆弧
      {
         op_x++;
         draw_x++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
}

/****************************************************************************
* 名称：GUI_Pieslice()
* 功能：指定起点、终点及半径扇形(不能画圆)。使用的是顺时针方向画图。
* 入口参数：x			圆心的x轴坐标值
*           y			圆心的y轴坐标值
*           stangle 	        起始角度(0-359度)
*           endangle	        终止角度(0-359度)
*           r  			圆的半径终点
*           color		显示颜色
* 出口参数：无
* 说明：操作失败原因是指定地址超出有效范围。
****************************************************************************/
void  GUI_Pieslice(uint32 x, uint32 y, uint32 r, uint32 stangle, uint32 endangle, TCOLOR color)
{
   int32  draw_x, draw_y;					// 画图坐标变量
   int32  op_x, op_y;						// 操作坐标
   int32  op_2rr;							// 2*r*r值变量
   
   int32  pno_angle;						// 度角点的个数
   uint16  draw_on;							// 画点开关，为1时画点，为0时不画
   
   
   /* 参数过滤 */
   if(r==0) return;							// 半径为0则直接退出
   if(stangle==endangle)
      return;			// 起始角度与终止角度相同，退出
   if( (stangle>=360) || (endangle>=360) )
      return;

   op_2rr = 2*r*r;							// 计算r平方乖以2
   pno_angle = 0;
   /* 先计算出在此半径下的45度的圆弧的点数 */       
   op_x = r;
   op_y = 0;
   while(1)
   {
      pno_angle++; 							// 画点计数
      /* 计算下一点 */
      op_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
      {
         op_x--;
      }
      if(op_y>=op_x)
         break;
   }
   
   draw_on = 0;								// 最开始关画点开关
   /* 设置起始点及终点 */
   if(endangle>stangle)
      draw_on = 1;		// 若终点大于起点，则从一开始即画点(359)
   stangle = (360-stangle)*pno_angle/45;
   endangle = (360-endangle)*pno_angle/45;
   if(stangle==0)
      stangle=1;
   if(endangle==0)
      endangle=1;
   
   /* 开始顺时针画弧，从359度开始(第4像限) */
   pno_angle = 0;
   
   draw_x = x+r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* 计算下一点 */
      op_y++;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 ) 	// 使用逐点比较法实现画圆弧
      {
         op_x--;
         draw_x--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_x--;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 ) // 使用逐点比较法实现画圆弧
      {
         op_y++;
         draw_y--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		// 开始画图
         break;
      }
   }
    
    
   /* 开始顺时针画弧，从269度开始(第3像限) */
   draw_y = y-r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* 计算下一点 */
      op_x++;
      draw_x--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 )          // 使用逐点比较法实现画圆弧
      {
         op_y--;
         draw_y++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);		         	// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		                // 开始画图
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_y--;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 )         // 使用逐点比较法实现画圆弧
      {
         op_x++;
         draw_x--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			        // 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }

   /* 开始顺时针画弧，从179度开始(第2像限) */
   draw_x = x-r;
   draw_y = y;         
   op_x = r;
   op_y = 0;
   while(1)
   {  /* 计算下一点 */
      op_y++;
      draw_y++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_x +1)>0 )         // 使用逐点比较法实现画圆弧
      {
         op_x--;
         draw_x++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			       // 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )		       // 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y>=op_x)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_x--;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_y +1)<=0 )        // 使用逐点比较法实现画圆弧
      {
         op_y++;
         draw_y++;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			       // 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )		       // 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		                // 开始画图
         break;
      }
   }
  
  
   /* 开始顺时针画弧，从89度开始(第1像限) */
   draw_y = y+r;
   draw_x = x;         
   op_y = r;
   op_x = 0;
   while(1)
   {  /* 计算下一点 */
      op_x++;
      draw_x++;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr - 2*op_y +1)>0 )          // 使用逐点比较法实现画圆弧
      {
         op_y--;
         draw_y--;
      }
      if(draw_on==1)
         GUI_Point(draw_x, draw_y, color);			        // 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      
      if(op_x>=op_y)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);		                // 开始画图
         break;
      }
   }
   
   while(1)
   {  /* 计算下一点 */
      op_y--;
      draw_y--;
      if( (2*op_x*op_x + 2*op_y*op_y - op_2rr + 2*op_x +1)<=0 )         // 使用逐点比较法实现画圆弧
      {
         op_x++;
         draw_x++;
      }
      if(draw_on==1) GUI_Point(draw_x, draw_y, color);			// 开始画图
      pno_angle++;
      if( (pno_angle==stangle)||(pno_angle==endangle) )			// 若遇到起点或终点，画点开关取反
      {
         draw_on = 1-draw_on;
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         GUI_Line(x, y, draw_x, draw_y, color);
      } 
      if(op_y<=0)
      {
         if(draw_on==1)
            GUI_Point(draw_x, draw_y, color);
         break;
      }
   }
}
