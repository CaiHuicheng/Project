package com.usy.service;


import com.usy.pojo.Course;
import org.codehaus.jackson.node.BooleanNode;

public interface CourseService {

    /**
     * 插入课程基本信息 用于课程开设时
     * @param course
     * @return boolean
     */
    public boolean insertCourse(Course course);


    /**
     * 插入数据
     * @param course
     * @return
     */
    public Boolean insert(Course course);
}
