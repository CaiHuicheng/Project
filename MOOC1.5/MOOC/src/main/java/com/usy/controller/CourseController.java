package com.usy.controller;

import com.sun.org.glassfish.external.probe.provider.annotations.ProbeParam;
import com.usy.pojo.Course;
import com.usy.pojo.CourseClass;
import com.usy.service.CourseClassService;
import com.usy.service.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.http.HttpRequest;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestBody;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.HttpSession;

/**
 * 课程行为类 课程相关操作
 */
@Controller
@RequestMapping("/course")
public class CourseController {

    @Autowired
    private CourseService courseService;

    @Autowired
    private CourseClassService courseClassService;


    /**
     * 开设课程，将基本信息入库
     * @param course
     * @return
     */
    @RequestMapping("/opencourse")
    public String openCourse(Course course,@ProbeParam("istolead") Integer istolead,Model model){
        // coursePublic公开状态 ：0 不公开 1 公开   courseClick 考核状态 ：0 不考核 1 考核
        System.out.println(istolead);


        if (istolead == 1){
            // 老师上传学生名单的情况,并且后台自动生成班级号

            // 不公开 考核 ——> 需要班级密码  ——> 上传名单 ——>自动完成设置班级
            if (course.getCoursePublic() == 0 && course.getCourseCheck() == 1){

                Boolean result = courseService.insert(course);
                //将课程信息传入model
                model.addAttribute("COURSE",course);

                if (result){
                    //跳转设置班级

                    return "teacher/uploadstudent";
                }
            }

        }else {
            // 老师不上传学生名单  只管开设班级
            // 不公开不考核 ——> 需要班级密码 && 自动生成系统班级一个
            if (course.getCoursePublic() == 0 && course.getCourseClick() == 0){

                Boolean result = courseService.insert(course);
                //将课程信息传入model
                model.addAttribute("COURSE",course);
                if (result){
                    //跳转设置班级
                    return "teacher/specifiedclass";
                }else {
                    //跳回
                    return "";
                }
            }


            // 公开不考核 ——> 不需要班级密码 ——> 自动生成系统班级
            if (course.getCoursePublic() == 1 && course.getCourseCheck() == 0){
                if (courseService.insertCourse(course)){
                    //跳转设置班级
                    return "";
                }
            }

            // 公开考核 ——> 不需要班级密码 ——> 跳转到设置班级页面
            System.out.println(course);
            if (course.getCoursePublic() == 1 && course.getCourseCheck() == 1){
                // 插入数据
                Boolean result = courseService.insert(course);
                //将课程信息传入model
                model.addAttribute("COURSE",course);
                if (result){
                    //跳转设置班级

                    return "teacher/specifiedclass";
                }
            }
        }
        return "";
    }

    @RequestMapping("/specifiedclass")
    public String specifiedClass(CourseClass courseClass, Model model){
        System.out.println(courseClass);
        if (courseClassService.insert(courseClass)){
            model.addAttribute("COURSECLASS",courseClass);
            return "teacher/openingchapters";
        }else {
            //重定向，重新开设
            return "redirect:/jsp/teacher/specifiedclass.jsp";
        }
    }
}
