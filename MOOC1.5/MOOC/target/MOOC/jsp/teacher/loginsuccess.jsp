<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/6
  Time: 13:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    登陆成功<br>
    欢迎${SESSION_USER}<br>
    <a href="${ctx}/jsp/teacher/identification.jsp"> 去认证 </a>
    <br>
    <a href="${ctx}/jsp/teacher/personalcenter.jsp">个人中心</a>
</body>
</html>
