package com.usy.mapper;


import com.usy.pojo.Student;

public interface StudentMapper {

    /**
     * 注册时插入一个学生 账号的ID 和 头像
     * @param student
     * @return
     */
    Integer instrtIdHp(Student student);
}
