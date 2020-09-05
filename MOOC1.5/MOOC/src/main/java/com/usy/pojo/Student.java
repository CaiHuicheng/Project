package com.usy.pojo;

public class Student {

    // 学生ID 自增主键 一般不使用
    private Integer studentId;
    //学生姓名
    private String studentName;
    // 头像
    private String studentHp;
    // 性别
    private int studentGender;
    // 学号
    private String studentNumber;
    // 手机号
    private String studentPnum;
    // 所属机构
    private String studentOrgan;
    // 偏好
    private String studentPrefer;


    public Student(Integer studentId, String studentHp) {
        this.studentId = studentId;
        this.studentHp = studentHp;
    }

    public Integer getStudentId() {
        return studentId;
    }

    public void setStudentId(Integer studentId) {
        this.studentId = studentId;
    }

    public String getStudentName() {
        return studentName;
    }

    public void setStudentName(String studentName) {
        this.studentName = studentName;
    }

    public String getStudentHp() {
        return studentHp;
    }

    public void setStudentHp(String studentHp) {
        this.studentHp = studentHp;
    }

    public int getStudentGender() {
        return studentGender;
    }

    public void setStudentGender(int studentGender) {
        this.studentGender = studentGender;
    }

    public String getStudentNumber() {
        return studentNumber;
    }

    public void setStudentNumber(String studentNumber) {
        this.studentNumber = studentNumber;
    }

    public String getStudentPnum() {
        return studentPnum;
    }

    public void setStudentPnum(String studentPnum) {
        this.studentPnum = studentPnum;
    }

    public String getStudentOrgan() {
        return studentOrgan;
    }

    public void setStudentOrgan(String studentOrgan) {
        this.studentOrgan = studentOrgan;
    }

    public String getStudentPrefer() {
        return studentPrefer;
    }

    public void setStudentPrefer(String studentPrefer) {
        this.studentPrefer = studentPrefer;
    }

    @Override
    public String toString() {
        return "Student{" +
                "studentId=" + studentId +
                ", studentName='" + studentName + '\'' +
                ", studentHp='" + studentHp + '\'' +
                ", studentGender=" + studentGender +
                ", studentNumber='" + studentNumber + '\'' +
                ", studentPnum='" + studentPnum + '\'' +
                ", studentOrgan='" + studentOrgan + '\'' +
                ", studentPrefer='" + studentPrefer + '\'' +
                '}';
    }
}
