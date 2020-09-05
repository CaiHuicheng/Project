package com.usy.interceptors;

import com.usy.pojo.Teacher;
import com.usy.service.TeacherService;
import org.apache.log4j.Logger;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.web.servlet.HandlerInterceptor;

import javax.net.ssl.HttpsURLConnection;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

public class SessionInterceptor implements HandlerInterceptor {


    private static final Logger LOGGER = Logger.getLogger(SessionInterceptor.class);

    @Autowired
    private TeacherService teacherService;

    @Override
    public boolean preHandle(HttpServletRequest request, HttpServletResponse response, Object handler) throws Exception {
        Object teacher = request.getSession().getAttribute("USER");
        if (teacher == null){
            request.getSession().setAttribute("code",404);
            response.sendRedirect("/MOOC/jsp/teacher/login.jsp");
            LOGGER.info("你的权限不足，请先登录");
            return false;
        }
        if (teacher instanceof Teacher){
            //再去数据检查,冻结等
            Teacher teacher1 = (Teacher)teacher;
            teacher1 = teacherService.selectAccountPwd(teacher1);
            if (teacher1 != null){
                request.getSession().setAttribute("SESSION_USER",teacher1);
                LOGGER.info(teacher1.getTeacherName() + "处于登陆状态,可以执行操作");
                return true;
            }else {
                LOGGER.warn("请你不要搞事情，请先登录");
                request.getSession().setAttribute("code",404);
                response.sendRedirect("/MOOC/jsp/teacher/login.jsp");
                return false;
            }
        }else {
            LOGGER.warn("请你不要搞事情，请先登录");
            request.getSession().setAttribute("code",404);
            response.sendRedirect("/MOOC/jsp/teacher/login.jsp");
            return false;
        }
    }
}
