package com.usy.controller;

import com.usy.constant.ResponseCode;
import com.usy.constant.SystemConstant;
import com.usy.pojo.Student;
import com.usy.pojo.Teacher;
import com.usy.pojo.User;
import com.usy.service.StudentService;
import com.usy.service.TeacherService;
import com.usy.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.ResponseBody;

import javax.servlet.http.HttpSession;
import java.sql.Date;
import java.util.HashMap;
import java.util.Map;

@Controller
@RequestMapping("/user")
public class UserController {

    @Autowired
    private UserService userService;

    @Autowired
    private TeacherService teacherService;

    @Autowired
    private StudentService studentService;


    /**
     * 注册时校验账号是否注册过
     * @param user
     * @return
     */
    @RequestMapping("/checkaccount")
    @ResponseBody
    public Map<String,Integer> checkAccount(@RequestBody User user){

        Map<String,Integer> map = new HashMap<>();

        int code = ResponseCode.HAS_USE;                //默认为400即  该账号已经被注册

        if (userService.getUserAccount(user)){
            code = ResponseCode.CAN_USE;
            map.put(ResponseCode.CODE,code);
            return map;
        }else{
            map.put(ResponseCode.CODE,code);
            return map;
        }
    }

    /**
     * 账户登录
     * @param user
     * @param model
     * @param session
     * @return
     */
    @RequestMapping("/login")
    public String login(User user, Model model,HttpSession session){
        if (user != null){
            User resultUser = userService.getUser(user);
            //将值压入 视图
            System.out.println("返回值：" + resultUser);
            session.setAttribute("USER",resultUser);
            model.addAttribute("USER",resultUser);
            if (resultUser != null){
                if (user.getUserPassword().equals(resultUser.getUserPassword()) &&
                    user.getUserType() <= resultUser.getUserType()){

                    if (resultUser.getUserType() == 1){
                        //前往学生主页
                        return "student/index";
                    }else if (resultUser.getUserType() == 2){
                        //前往认证页面

                        //前往认证表中查看该老师是否已经提交认证信息
                        Teacher teacher = teacherService.getTeacher(resultUser.getUserId());
                        if (teacher != null){
                            //去认证提交 后页面
                            model.addAttribute("TEACHER",teacher);
                            session.setAttribute("TEACHER",teacher);
                            return "teacher/idfsuccess";
                        }else {
                            //去认证信息提交页面
                            return "teacher/identification";
                        }
                    }else if (resultUser.getUserType() == 3){
                        // 去老师主页页面
                        Teacher teacher = teacherService.getTeacher(resultUser.getUserId());
                        session.setAttribute("TEACHER",teacher);
                        return "teacher/index";
                    }else {
                        //前往管理员页面
                        return "";
                    }

                }
            }else {
                return "redirect:/jsp/login.jsp";
            }
        }else {
            return "redirect:/jsp/login.jsp";
        }
        return "redirect:/jsp/login.jsp";
    }

    /**
     * 注册账号
     * @param user
     * @return
     */
    @RequestMapping("/signin")
    public String signin(User user){

        if (user != null){

            // 得到系统时间
            Date date = new Date(new java.util.Date().getTime());
            user.setUserRegdate(date);

            if (user.getUserType() == 1){
                //注册的是一个学生账号
                if (userService.instrt(user)){
                    // 查找刚才插入的账号的ID
                    User resultUser = userService.getUser(user);

                    if (resultUser != null){
                        Student student = new Student(resultUser.getUserId(),SystemConstant.SYSTEMHEADPICTURE);
                        if (studentService.instrt(student)){
                            return "login";
                        }
                    }

                }else {
                    return "signin";
                }
            }
            if (user.getUserType() == 2){
                //注册的是一个未审核/审核中的老师账号
                System.out.println(user);
                if (userService.instrt(user)){
                    return "login";
                }else {
                    return "singin";
                }
            }
        }
        return "singin";
    }
}
