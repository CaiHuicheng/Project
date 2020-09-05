<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/6
  Time: 22:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>
    ${code}
    <form action="${ctx}/user/login" method="post">
        用户名：<input type="text" name="userAccount"><br>
        密码：<input type="password" name="userPassword"><br>
        老师：<input type="radio" name="userType" value="2" /><br />
        学生：<input type="radio" name="userType" value="1" /> <br />
        <input type="submit" value="登陆">
    </form>



</body>
</html>
