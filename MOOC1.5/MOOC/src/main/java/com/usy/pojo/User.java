package com.usy.pojo;

import java.sql.Date;

public class User {

    //自增主键一般不使用
    private Integer userId;

    private Integer userType;   //用户类型,类型也代表了权限,1学生,2未完成审核或审核中的教师,3审核通过的教师,4管理员,5超级管理员,由后台写入

    private String userAccount;

    private String userPassword;

    private Date userRegdate;

    public Integer getUserId() {
        return userId;
    }

    public void setUserId(Integer userId) {
        this.userId = userId;
    }

    public Integer getUserType() {
        return userType;
    }

    public void setUserType(Integer userType) {
        this.userType = userType;
    }

    public String getUserAccount() {
        return userAccount;
    }

    public void setUserAccount(String userAccount) {
        this.userAccount = userAccount;
    }

    public String getUserPassword() {
        return userPassword;
    }

    public void setUserPassword(String userPassword) {
        this.userPassword = userPassword;
    }

    public Date getUserRegdate() {
        return userRegdate;
    }

    public void setUserRegdate(Date userRegdate) {
        this.userRegdate = userRegdate;
    }

    @Override
    public String toString() {
        return "User{" +
                "userId='" + userId + '\'' +
                ", userType=" + userType +
                ", userAccount='" + userAccount + '\'' +
                ", userPassword='" + userPassword + '\'' +
                ", userRegdate=" + userRegdate +
                '}';
    }
}
