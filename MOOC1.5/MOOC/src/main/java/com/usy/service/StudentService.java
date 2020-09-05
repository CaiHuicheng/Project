package com.usy.service;

import com.usy.pojo.Student;


public interface StudentService {

    /**
     * 注册进入数据库
     * @param student
     * @return Integer
     */
    public boolean instrt(Student student);
}
