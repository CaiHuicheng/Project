<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/9
  Time: 19:34
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>

<form action="${ctx}/course/opencourse" method="post">
    教师ID：
    <input type="text" name="teacherId" >
    课程名称：
    <input type="text" name="courseName">
    课程类型：
    <input type="text" name="courseType">
    课程介绍：
    <input type="text" name="courseIntro">
    开设时间：
    <input type="date" name="courseBegin">
    结束时间：
    <input type="date" name="courseEnd">
    是否公开：
    <input type="text" name="coursePublic">
    开设状态：
    <input type="text" name="courseOpen">
    课程考核：
    <input type="text" name="courseCheck">

    <input type="submit" value="提交">
</form>
</body>
</html>





















































