package com.usy.pojo;

public class TeacherAccount {

    //账号
    private String teacherAccount;
    //密码
    private String teacherPassword;

    public String getTeacherAccount() {
        return teacherAccount;
    }

    public void setTeacherAccount(String teacherAccount) {
        this.teacherAccount = teacherAccount;
    }

    public String getTeacherPassword() {
        return teacherPassword;
    }

    public void setTeacherPassword(String teacherPassword) {
        this.teacherPassword = teacherPassword;
    }

    @Override
    public String toString() {
        return "TeacherAccount{" +
                "teacher_account='" + teacherAccount + '\'' +
                ", teacherPassword='" + teacherPassword + '\'' +
                '}';
    }
}
