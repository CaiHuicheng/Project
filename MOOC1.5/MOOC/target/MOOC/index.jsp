<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<body>
<h2>Hello World!</h2>


<a>${ctx}</a><br>

<a href="${ctx}/jsp/signin.jsp">注册</a><br>
<a href="${ctx}/jsp/login.jsp">登陆</a><br>
<a href="${ctx}/jsp/teacher/identification.jsp" >认证</a><br>
<a href="${ctx}/jsp/course/opencourse.jsp" >开设课程</a><br>
<a href="${ctx}/jsp/teacher/upload.jsp">上传文件</a><br>
<a href="${ctx}/jsp/student/answer.jsp">下拉题</a>
</body>
</html>
