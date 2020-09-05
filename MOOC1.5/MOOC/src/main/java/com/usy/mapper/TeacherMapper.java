package com.usy.mapper;

import com.usy.pojo.Teacher;

public interface TeacherMapper {

    /**
     * 认证账号到数据库
     */
    Integer insert(Teacher teacher);

    /**
     * 注册之前检测是否被注册
     */
    Teacher getAccount(Teacher teacher);

    /**
     * 登陆时校对
     * @param teacher
     * @return
     */
    Teacher selectAccountPwd(Teacher teacher);

    /**
     * 认证时 数据库  数据更新
     * @param teacher
     * @return
     */
    int update(Teacher teacher);

    /**
     * 个人中心修改 账户头像
     * @param teacher
     * @return
     */
    int updateUserHeadPortrait(Teacher teacher);

    /**
     * 根据老师ID提取老师信息
     * @param teacherId
     * @return
     */
    Teacher getTeacher(Integer teacherId);
}
