package com.usy.pojo;

public class CourseClass {
    // 班级ID
    private Integer classId;
    // 课程ID
    private Integer courseId;
    // 班级名称
    private String className;
    // 课程人数上限
    private Integer classAmount;

    public Integer getClassId() {
        return classId;
    }

    public void setClassId(Integer classId) {
        this.classId = classId;
    }

    public Integer getCourseId() {
        return courseId;
    }

    public void setCourseId(Integer courseId) {
        this.courseId = courseId;
    }

    public String getClassName() {
        return className;
    }

    public void setClassName(String className) {
        this.className = className;
    }

    public Integer getClassAmount() {
        return classAmount;
    }

    public void setClassAmount(Integer classAmount) {
        this.classAmount = classAmount;
    }

    @Override
    public String toString() {
        return "CourseClass{" +
                "classId=" + classId +
                ", courseId=" + courseId +
                ", className='" + className + '\'' +
                ", classAmount=" + classAmount +
                '}';
    }
}
