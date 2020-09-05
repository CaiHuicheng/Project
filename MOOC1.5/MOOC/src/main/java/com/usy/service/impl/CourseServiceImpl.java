package com.usy.service.impl;

import com.usy.mapper.CourseMapper;
import com.usy.pojo.Course;
import com.usy.service.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service("courseService")
public class CourseServiceImpl implements CourseService {

    @Autowired
    private CourseMapper courseMapper;


    /**
     * 开设课程时将课程基本信息写入数据库
     * @param course
     * @return
     */
    @Override
    public boolean insertCourse(Course course) {

        Integer result = courseMapper.insertCourse(course);

        if (result > 0){
            return true;
        }else {
            return false;
        }
    }

    @Override
    public Boolean insert(Course course) {
        Integer result = courseMapper.insert(course);
        if(result > 0){
            return true;
        }
        return false;
    }
}
