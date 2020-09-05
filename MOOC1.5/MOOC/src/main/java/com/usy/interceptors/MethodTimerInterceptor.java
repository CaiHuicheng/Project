package com.usy.interceptors;


import org.apache.log4j.Logger;
import org.springframework.web.servlet.HandlerInterceptor;
import org.springframework.web.servlet.ModelAndView;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * 方法耗时统计器
 */
public class MethodTimerInterceptor implements HandlerInterceptor {

    private static final Logger LOGGER = Logger.getLogger(MethodTimerInterceptor.class);


    //前置功能  开始到结束，两个点减法
    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        //1.定义开始时间
        long start = System.currentTimeMillis();
        request.setAttribute("start",start);
        //返回true，才会找到下一个拦截器，如果没有下一个则是 Controller
        LOGGER.info(request.getRequestURI() + ",请求达到");
        return true;
    }

    //后置功能
    @Override
    public void postHandle(HttpServletRequest request, HttpServletResponse response, Object handler, ModelAndView modelAndView) throws Exception {
        //1.取出start
        long start = (long)request.getAttribute("start");
        //2.得到end
        long end  = System.currentTimeMillis();
        //3 记录一下耗时
        long spendTime = end - start;
        if (spendTime >= 1000){
            LOGGER.warn("方法耗时严重，请及时处理,耗时：" + spendTime + "毫秒");
        }else{
            LOGGER.info("方法耗时：" + spendTime + "毫秒,速度正常");
        }
    }

    @Override
    public void afterCompletion(HttpServletRequest request, HttpServletResponse response, Object handler, Exception ex) throws Exception {

    }

    public MethodTimerInterceptor() {

    }
}
