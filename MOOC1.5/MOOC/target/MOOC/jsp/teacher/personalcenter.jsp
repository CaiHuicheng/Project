<%--
  Created by IntelliJ IDEA.
  User: Administrator
  Date: 2019/4/7
  Time: 12:42
  To change this template use File | Settings | File Templates.
--%>
<%@ page contentType="text/html;charset=UTF-8" language="java" %>
<html>
<head>
    <title>Title</title>
</head>
<body>



    我的头像:<a><img src="${ctx}/${TEACHER.teacherHp}"/></a><br>

    <form action="${ctx}/file/upload" method="post" enctype="multipart/form-data">
        上传头像:<input type="file" name="file"><br>
        <input type="submit" value="修改头像"><br>
    </form>

    用户姓名*：<a>${TEACHER.teacherName}</a><br>
    性别*：<a>${TEACHER.teacherGender}</a><br>
    身份证*：<a>${TEACHER.teacherUid}</a><br>
    手机号码*：<a>${TEACHER.teacherPnum}</a><br>
    所属机构*：<a>${TEACHER.teacherOrgan}</a><br>
    职称*：<a>${TEACHER.teacherTitle}</a><br>
    主攻方向*：<a>${TEACHER.teacherDirect}</a><br>
    个人简介*：<a>${TEACHER.teacherIntro}</a><br>
    审批状态：<a>${TEACHER.teacherApprove}</a><br>

</body>
</html>
