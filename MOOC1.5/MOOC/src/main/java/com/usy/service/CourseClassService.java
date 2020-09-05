package com.usy.service;

import com.usy.pojo.CourseClass;

public interface CourseClassService {

    /**
     * 开设班级时候，将课程班级信息插入
     * @param courseClass
     * @return
     */
    public Boolean insert(CourseClass courseClass);
}
