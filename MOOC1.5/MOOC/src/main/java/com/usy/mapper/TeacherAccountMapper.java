package com.usy.mapper;

import com.usy.pojo.TeacherAccount;

public interface TeacherAccountMapper {
    /**
     * 注册账号到数据库
     */
    int insert(TeacherAccount teacherAccount);
}
