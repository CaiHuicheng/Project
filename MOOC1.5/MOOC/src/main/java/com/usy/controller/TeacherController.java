package com.usy.controller;


import com.usy.constant.ResponseCode;
import com.usy.constant.SystemConstant;
import com.usy.pojo.Student;
import com.usy.pojo.Teacher;
import com.usy.pojo.User;
import com.usy.service.TeacherService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpSession;
import javax.xml.ws.Action;
import java.sql.Date;
import java.util.HashMap;
import java.util.Map;


/**
 * 老师行为类
 */
@Controller
@RequestMapping("/teacher")
public class TeacherController {

    @Autowired
    private TeacherService teacherService;

/*    *//**
     *  该注册方法遗弃 改为UserController类中实现
     * @param teacher
     * @return
     *//*
    @RequestMapping("/signin")
    public String signIn(Teacher teacher){
        teacher.setTeacherHp(SystemConstant.SYSTEMHEADPICTURE);
        if(teacherService.instrt(teacher)){
            return "teacher/success";
        }else {
            return "404";
        }
    }*/

    /**
     * 该登陆方法遗弃
     * @param teacher
     * @param session
     * @return
     *//*
    @RequestMapping("/login")
    public String login(Teacher teacher,HttpSession session){

        teacher = teacherService.selectAccountPwd(teacher);

        if (teacher != null){
            //将登陆信息注入 session
            session.setAttribute("SESSION_USER",teacher);
            session.setAttribute("IDEENTIFICATION",teacher);
            return "teacher/loginsuccess";
        }else {
            return "redirect:/jsp/teacher/login.jsp";
        }
    }*/

/*    *//**
     * 该方法已经遗弃
     * @param teacher
     * @return
     *//*
    @RequestMapping("/checkaccount")
    @ResponseBody
    public Map<String,Integer> checkAccount(@RequestBody Teacher teacher){

        Map<String,Integer> map = new HashMap<>();

        int code = ResponseCode.HAS_USE;                //默认为400即  该账号已经被注册

        if (teacherService.getAccount(teacher)){
            code = ResponseCode.CAN_USE;
            map.put(ResponseCode.CODE,code);
            return map;
        }else{
            map.put(ResponseCode.CODE,code);
            return map;
        }
    }*/

    /**
     *  老师认证方法
     * @param teacher
     * @param model
     * @return
     */
    @RequestMapping("/identification")
    public String identification(Teacher teacher, Model model){

        teacher.setTeacherHp(SystemConstant.SYSTEMHEADPICTURE);
        teacher.setTeacherApprove(2);

        if (teacherService.instrt(teacher)){
            model.addAttribute("TEACHER",teacher);
            return "teacher/idfsuccess";
        }else {
            return "redirect:/jsp/teacher/identification.jsp";
        }
    }

    /**
     *  老师个人信息提取方法，主要用于个人中心信息展示
     * @param teacherId
     * @param model
     * @return 跳转到个人中心
     */
    @RequestMapping("/personalcenter/{userId}")
    public String personalcenter(@PathVariable("userId") Integer teacherId, Model model){
        Teacher teacher = teacherService.getTeacher(teacherId);
        System.out.println("已经得到该老师信息： "  + teacher);
        model.addAttribute("TEACHER",teacher);
        return "teacher/personalcenter";
    }
}
