<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/14
  Time: 13:26
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>上传学生名单</title>
</head>
<body>
    <form action="${ctx}/uploading/student" method="post" enctype="multipart/form-data">
        <%--教师ID--%><input type="text" name="teacherId" value="${COURSE.teacherId}" style="display:none">
        <%--课程编号--%><input type="text" name="courseId" value="${COURSE.courseId}" style="display:none">
        课程名称:<input type="text" name="courseName" value="${COURSE.courseName}" readonly="readonly" ><br>
        课程专业类型:<input type="text" name="courseType" value="${COURSE.courseType}" readonly="readonly"><br>
        课程简介:<input type="text" name="courseIntro" value="${COURSE.courseIntro}" readonly="readonly"><br>
        课程开始时间:<input type="date" name="courseBegin" value="${COURSE.courseBegin}" readonly="readonly"><br>
        课程结束时间:<input type="date" name="courseEnd" value="${COURSE.courseEnd}" readonly="readonly"><br>
        课程开设状态:<input type="text" name="courseOpen" value="${COURSE.courseOpen}" readonly="readonly"><br>
        课程公开状态:<input type="text" name="coursePublic" value="${COURSE.coursePublic}" readonly="readonly"><br>
        课程考核状态:<input type="text" name="courseCheck" value="${COURSE.courseCheck}" readonly="readonly"><br>
        <input type="file" name="file" value="选择文件">
        <input type="submit" value="上传学生名单">
    </form>
</body>
</html>
