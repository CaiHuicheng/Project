package com.usy.mapper;

import com.usy.pojo.Course;

public interface CourseMapper {

    /**
     * 插入课程信息到数据库
     * @param course
     * @return
     */
    public int insertCourse(Course course);

    /**
     * 插入数据 并返回该条记录
     * @param course
     * @return
     */
    public Integer insert(Course course);
}
