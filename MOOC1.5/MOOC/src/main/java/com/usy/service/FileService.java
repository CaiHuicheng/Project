package com.usy.service;

import com.usy.pojo.Teacher;

public interface FileService {

    /**
     * 个人中心修改头像
     * @param teacher
     * @return
     */
    public boolean updateUserHeadPortrait(Teacher teacher);

}
