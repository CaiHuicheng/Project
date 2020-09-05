<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/7
  Time: 0:55
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>教师认证</title>
    <script src="${ctx}/static/plugins/jquery/jquery.js"></script>
</head>
<body>

    <script src="${ctx}/static/plugins/layui/layui.js"></script>
    <form action="${ctx}/teacher/identification" method="post">
        教师ID:<input type="text" name="teacherId" value="${USER.userId}" readonly="readonly"><br>
        账户*：<input type="text"  value="${USER.userAccount}" readonly="readonly"><br>
        密码*：<input type="password"  value="${USER.userPassword}" readonly="readonly"><br>
        姓名*：<input type="text" name="teacherName"><br>
        性别*：<input type="text" name="teacherGender"><br>
        身份证号码*：<input type="text" name="teacherUid"><br>
        手机号*：<input type="text" name="teacherPnum"><br>
        所属机构*：<input type="text" name="teacherOrgan"><br>
        职称：<input type="text" name="teacherTitle"><br>
        主攻方向*：<input type="text" name="teacherDirect"><br>
        个人简介(选填)：<input type="text" name="teacherIntro"><br>
        <input type="submit" value="提交认证信息">
    </form>

</body>
</html>
