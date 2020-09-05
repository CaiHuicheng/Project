package com.usy.service.impl;

import com.usy.mapper.UserMapper;
import com.usy.pojo.User;
import com.usy.service.UserService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service("userService")
public class UserServiceImpl implements UserService {

    @Autowired
    private UserMapper userMapper;

    /**
     * 注册前对账号进行校验，检测是否已被注册
     * @param user
     * @return boolean
     */
    @Override
    public boolean getUserAccount(User user) {
        User user1 = userMapper.getUserAccount(user);
        if (user1 != null){
            return false;
        }else {
            return true;
        }
    }

    /**
     * 注册时写入数据库
     * @param user
     * @return boolean
     */
    @Override
    public Boolean instrt(User user) {
        Integer result = userMapper.instrt(user);
        if (result > 0){
            return true;
        }else {
            return false;
        }

    }

    /**
     * 查看该条数据 用于注册时
     * @param user
     * @return
     */
    @Override
    public User getUser(User user) {
        User resultUser = userMapper.getUser(user);
        return resultUser;
    }
}
