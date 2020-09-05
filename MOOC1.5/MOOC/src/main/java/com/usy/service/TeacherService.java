package com.usy.service;

import com.usy.pojo.Teacher;
import com.usy.pojo.TeacherAccount;

public interface TeacherService {

    /**
     * 注册进入数据库
     * @param teacher
     * @return boolean
     */
    public boolean instrt(Teacher teacher);

    /**
     * 注册前对账号进行校验，检测是否已被注册
     * @param teacher
     * @return boolean
     */
    public boolean getAccount(Teacher teacher);

    /**
     * 账号登陆校对
     * @param teacher
     * @return
     */
    public Teacher selectAccountPwd(Teacher teacher);

    /**
     * 认证时 数据库 更新数据
     * @param teacher
     * @return boolean 更新是否成功
     */
    public boolean identificationUpdate(Teacher teacher);

    /**
     * 根据老师ID提取老师信息
     * @param teacherId
     * @return  Teacher
     */
    public Teacher getTeacher(Integer teacherId);
}
