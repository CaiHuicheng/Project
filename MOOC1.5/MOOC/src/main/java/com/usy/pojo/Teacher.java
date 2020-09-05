package com.usy.pojo;

import java.util.Date;

public class Teacher {

    //ID自增主键 不用
    private Integer teacherId;
    //姓名
    private String teacherName;
    //头像URL
    private String teacherHp;
    //性别
    private Integer teacherGender;
    //身份证ID
    private String teacherUid;
    //手机号
    private String teacherPnum;
    //教师所在机构
    private String teacherOrgan;
    //职称
    private String teacherTitle;
    //研究方向
    private String teacherDirect;
    //教师简介
    private String teacherIntro;
    //认证审批状态
    private Double teacherGrade;
    //审批状态
    private Integer teacherApprove;

    public Integer getTeacherId() {
        return teacherId;
    }

    public void setTeacherId(Integer teacherId) {
        this.teacherId = teacherId;
    }

    public String getTeacherName() {
        return teacherName;
    }

    public void setTeacherName(String teacherName) {
        this.teacherName = teacherName;
    }

    public String getTeacherHp() {
        return teacherHp;
    }

    public void setTeacherHp(String teacherHp) {
        this.teacherHp = teacherHp;
    }

    public Integer getTeacherGender() {
        return teacherGender;
    }

    public void setTeacherGender(Integer teacherGender) {
        this.teacherGender = teacherGender;
    }

    public String getTeacherUid() {
        return teacherUid;
    }

    public void setTeacherUid(String teacherUid) {
        this.teacherUid = teacherUid;
    }

    public String getTeacherPnum() {
        return teacherPnum;
    }

    public void setTeacherPnum(String teacherPnum) {
        this.teacherPnum = teacherPnum;
    }

    public String getTeacherOrgan() {
        return teacherOrgan;
    }

    public void setTeacherOrgan(String teacherOrgan) {
        this.teacherOrgan = teacherOrgan;
    }

    public String getTeacherTitle() {
        return teacherTitle;
    }

    public void setTeacherTitle(String teacherTitle) {
        this.teacherTitle = teacherTitle;
    }

    public String getTeacherDirect() {
        return teacherDirect;
    }

    public void setTeacherDirect(String teacherDirect) {
        this.teacherDirect = teacherDirect;
    }

    public String getTeacherIntro() {
        return teacherIntro;
    }

    public void setTeacherIntro(String teacherIntro) {
        this.teacherIntro = teacherIntro;
    }

    public Double getTeacherGrade() {
        return teacherGrade;
    }

    public void setTeacherGrade(Double teacherGrade) {
        this.teacherGrade = teacherGrade;
    }

    public Integer getTeacherApprove() {
        return teacherApprove;
    }

    public void setTeacherApprove(Integer teacherApprove) {
        this.teacherApprove = teacherApprove;
    }

    @Override
    public String toString() {
        return "Teacher{" +
                "teacherID=" + teacherId +
                ", teacherName='" + teacherName + '\'' +
                ", teacherHp='" + teacherHp + '\'' +
                ", teacherGender=" + teacherGender +
                ", teacherUid='" + teacherUid + '\'' +
                ", teacherPnum='" + teacherPnum + '\'' +
                ", teacherOrgan='" + teacherOrgan + '\'' +
                ", teacherTitle='" + teacherTitle + '\'' +
                ", teacherDirect='" + teacherDirect + '\'' +
                ", teacherIntro='" + teacherIntro + '\'' +
                ", teacherGrade=" + teacherGrade +
                ", teacherApprove=" + teacherApprove +
                '}';
    }
}
