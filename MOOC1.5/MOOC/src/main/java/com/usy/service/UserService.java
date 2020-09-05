package com.usy.service;

import com.usy.pojo.Teacher;
import com.usy.pojo.User;

public interface UserService {

    /**
     * 注册前对账号进行校验，检测是否已被注册
     * @param user
     * @return boolean
     */
    public boolean getUserAccount(User user);

    /**
     * 注册时写入数据库
     * @param user
     * @return boolean
     */
    public Boolean instrt(User user);

    /**
     * 查看该条数据 用于注册时
     * @param user
     * @return
     */
    public User getUser(User user);
}
