<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/14
  Time: 15:13
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>开设章节</title>
</head>
<body>
    ${COURSECLASS}
    <form action="">
        <%--章节ID--%>
        <%--章节所属课程ID--%><input type="text" name="courseId" value="${COURSECLASS.courseId}" style="display:none">
        章节名称:<input type="text" name="">
        章节开设状态:<input type="text" name="">
        章节开始时间
        章节结束时间
    </form>
</body>
</html>
