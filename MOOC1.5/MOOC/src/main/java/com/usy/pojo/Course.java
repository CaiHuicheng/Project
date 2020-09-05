package com.usy.pojo;

import java.sql.Date;

public class Course {

    //课程id
    private int courseId;
    //老师ID
    private int teacherId;
    // 课程名称
    private String courseName;
    // 课程类型
    private String courseType;
    // 课程简介
    private String courseIntro;
    // 课程开始时间
    private Date courseBegin;
    // 课程结束时间
    private Date courseEnd;
    // 课程开设状态 0 关闭 1开放
    private int courseOpen;
    // 课程公开性
    private int coursePublic;
    // 课程考核状态
    private int courseCheck;
    // 课程密码
    private String coursePassword;
    // 课程视频总数
    private int courseVnum;
    // 课程试卷总分
    private int courseGsum;
    // 课程视频分数比重
    private int courseVrate;
    // 课程作业分数比重
    private int coursePrate;
    // 课程考试分数比重
    private int courseErate;
    // 课程视频总点击量
    private int courseClick;
    // 课程评论总数
    private int courseCnum;
    // 课程所获评分
    private Double courseGrade;
    // 课程热度
    private Integer courseHeat;

    public int getCourseId() {
        return courseId;
    }

    public void setCourseId(int courseId) {
        this.courseId = courseId;
    }

    public int getTeacherId() {
        return teacherId;
    }

    public void setTeacherId(int teacherId) {
        this.teacherId = teacherId;
    }

    public String getCourseName() {
        return courseName;
    }

    public void setCourseName(String courseName) {
        this.courseName = courseName;
    }

    public String getCourseType() {
        return courseType;
    }

    public void setCourseType(String courseType) {
        this.courseType = courseType;
    }

    public String getCourseIntro() {
        return courseIntro;
    }

    public void setCourseIntro(String courseIntro) {
        this.courseIntro = courseIntro;
    }

    public Date getCourseBegin() {
        return courseBegin;
    }

    public void setCourseBegin(Date courseBegin) {
        this.courseBegin = courseBegin;
    }

    public Date getCourseEnd() {
        return courseEnd;
    }

    public void setCourseEnd(Date courseEnd) {
        this.courseEnd = courseEnd;
    }

    public int getCourseOpen() {
        return courseOpen;
    }

    public void setCourseOpen(int courseOpen) {
        this.courseOpen = courseOpen;
    }

    public int getCoursePublic() {
        return coursePublic;
    }

    public void setCoursePublic(int coursePublic) {
        this.coursePublic = coursePublic;
    }

    public int getCourseCheck() {
        return courseCheck;
    }

    public void setCourseCheck(int courseCheck) {
        this.courseCheck = courseCheck;
    }

    public String getCoursePassword() {
        return coursePassword;
    }

    public void setCoursePassword(String coursePassword) {
        this.coursePassword = coursePassword;
    }

    public int getCourseVnum() {
        return courseVnum;
    }

    public void setCourseVnum(int courseVnum) {
        this.courseVnum = courseVnum;
    }

    public int getCourseGsum() {
        return courseGsum;
    }

    public void setCourseGsum(int courseGsum) {
        this.courseGsum = courseGsum;
    }

    public int getCourseVrate() {
        return courseVrate;
    }

    public void setCourseVrate(int courseVrate) {
        this.courseVrate = courseVrate;
    }

    public int getCoursePrate() {
        return coursePrate;
    }

    public void setCoursePrate(int coursePrate) {
        this.coursePrate = coursePrate;
    }

    public int getCourseErate() {
        return courseErate;
    }

    public void setCourseErate(int courseErate) {
        this.courseErate = courseErate;
    }

    public int getCourseClick() {
        return courseClick;
    }

    public void setCourseClick(int courseClick) {
        this.courseClick = courseClick;
    }

    public int getCourseCnum() {
        return courseCnum;
    }

    public void setCourseCnum(int courseCnum) {
        this.courseCnum = courseCnum;
    }

    public Double getCourseGrade() {
        return courseGrade;
    }

    public void setCourseGrade(Double courseGrade) {
        this.courseGrade = courseGrade;
    }

    public Integer getCourseHeat() {
        return courseHeat;
    }

    public void setCourseHeat(Integer courseHeat) {
        this.courseHeat = courseHeat;
    }

    @Override
    public String toString() {
        return "Course{" +
                "courseId=" + courseId +
                ", teacherId=" + teacherId +
                ", courseName='" + courseName + '\'' +
                ", courseType='" + courseType + '\'' +
                ", courseIntro='" + courseIntro + '\'' +
                ", courseBegin=" + courseBegin +
                ", courseEnd=" + courseEnd +
                ", courseOpen=" + courseOpen +
                ", coursePublic=" + coursePublic +
                ", courseCheck=" + courseCheck +
                ", coursePassword='" + coursePassword + '\'' +
                ", courseVnum=" + courseVnum +
                ", courseGsum=" + courseGsum +
                ", courseVrate=" + courseVrate +
                ", coursePrate=" + coursePrate +
                ", courseErate=" + courseErate +
                ", courseClick=" + courseClick +
                ", courseCnum=" + courseCnum +
                ", courseGrade=" + courseGrade +
                ", courseHeat=" + courseHeat +
                '}';
    }
}
