package com.usy.service.impl;

import com.usy.mapper.CourseClassMapper;
import com.usy.pojo.CourseClass;
import com.usy.service.CourseClassService;
import com.usy.service.CourseService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

/**
 * 开设课程时，班级行为类
 */
@Service("courseClassService")
public class CourseClassServiceImpl implements CourseClassService {

    @Autowired
    private CourseClassMapper courseClassMapper;

    /**
     * 开设班级时候，将课程班级信息插入
     *
     * @param courseClass
     * @return
     */
    @Override
    public Boolean insert(CourseClass courseClass) {

        Integer result = courseClassMapper.insert(courseClass);

        if (result > 0){
            return true;
        }else {
            return false;
        }
    }
}
