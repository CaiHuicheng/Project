<%@ page import="javax.jws.soap.SOAPBinding" %>
<%@ page import="com.usy.pojo.User" %>
<%@ page import="com.usy.pojo.Teacher" %><%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/13
  Time: 15:59
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>开设课程</title>
</head>
<body>


<%
    Teacher teacher = (Teacher) request.getSession().getAttribute("TEACHER");
%>

    <form action="${ctx}/course/opencourse" method="post">
        <%--教师ID--%><input type="text" name="teacherId" value="<%=teacher.getTeacherId()%>" style="display:none">
        课程名称:<input type="text" name="courseName"><br>
        课程专业类型:<input type="text" name="courseType"><br>
        课程简介:<input type="text" name="courseIntro"><br>
        课程开始时间:<input type="date" name="courseBegin"><br>
        课程结束时间:<input type="date" name="courseEnd"><br>
        课程开设状态:<input type="text" name="courseOpen"><br>
        课程公开状态:<input type="text" name="coursePublic"><br>
        课程考核状态:<input type="text" name="courseCheck"><br>
        学生自行/老师导入名单:<input type="text" name="istolead"><br>

            <%--下面是下拉选择   可空字段--%>
<%--        课程密码:<input type="text" name="coursePassword"><br>
        课程考核时视频分数占比:<input type="text" name="courseVrate"><br>
        课程考核时作业分数占比:<input type="text" name="coursePrate"><br>
        课程考核时考试分数占比:<input type="text" name="courseErate"><br>--%>


        <input type="submit" value="发布课程">

    </form>
</body>
</html>
