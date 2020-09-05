package com.usy.mapper;

import com.usy.pojo.CourseClass;

public interface CourseClassMapper {

    /**
     * 开设班级时候，插入信息并返回主键
     * @param courseClass
     * @return
     */
    public Integer insert(CourseClass courseClass);
}
