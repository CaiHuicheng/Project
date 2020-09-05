<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/7
  Time: 11:16
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    你的认证信息以及提交，后台认证中，我们的认证工作会在三天之内完成<br>
    欢迎教师${TEACHER}<br>
    <a href="${ctx}/teacher/personalcenter/${TEACHER.teacherId}">前往个人中心</a>
</body>
</html>
