package com.usy.servlet;

import javax.servlet.ServletConfig;
import javax.servlet.ServletException;
import javax.servlet.annotation.WebServlet;
import javax.servlet.http.HttpServlet;

@WebServlet(urlPatterns = {}, loadOnStartup = 2)
public class WebPathInitServlet extends HttpServlet {

    @Override
    public void init(ServletConfig config) throws ServletException {
        //在整体的应用上下文当中存储一个ctx的值，用于引用上下文路径
        config.getServletContext().setAttribute("ctx",config.getServletContext().getContextPath());
        super.init();
    }
}
