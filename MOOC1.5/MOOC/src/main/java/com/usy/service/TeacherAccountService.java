package com.usy.service;

import com.usy.pojo.TeacherAccount;

public interface TeacherAccountService {
    /**
     * 注册进入数据库
     * @param teacherAccount
     * @return Integer
     */
    public boolean instrt(TeacherAccount teacherAccount);
}
