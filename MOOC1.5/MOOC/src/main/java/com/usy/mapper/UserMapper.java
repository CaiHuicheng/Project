package com.usy.mapper;

import com.usy.pojo.User;

public interface UserMapper {

    /**
     * 注册前账号校验 校验：是否注册过
     * @param user
     * @return 返回一个账号对象 或 null
     */
    User getUserAccount(User user);

    /**
     * 注册前账号校验 校验：是否注册过
     * @param user
     * @return 返回一个账号对象 或 null
     */
    Integer instrt(User user);

    /**
     * 注册时 用于查看账户ID
     * @param user
     * @return
     */
    User getUser(User user);

}
