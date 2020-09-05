package com.usy.controller;

import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.RequestMapping;

import javax.servlet.http.HttpServletResponse;
import java.io.File;
import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;

@Controller
@RequestMapping("/download")
public class DownloadControlller {

    private static String parentPath = "E:\\用户照片" + File.separator;

    @RequestMapping("/down")
    public String down(HttpServletResponse response){

        //通过输出流写到客户客户端，浏览器
        //1.获取文件下载名
        String fileName = "Numpy.mp4";

        //2.通过Paths工具类获取一个path对象，构建一个path对象
        Path path = Paths.get(parentPath,fileName);

        //3.判断它是否存在
        if (Files.exists(path)){
            //下载
            //通过response设定它的响应类型
            //4.获取文件后缀,文件类型
            String fileSuffix = fileName.substring(fileName.lastIndexOf(".") + 1);


            //5.设置content，只有设定它才能去下载
            response.setContentType("application/"+fileSuffix);
            //response.setContentType("application/IMG_20180703_2237151554360925223.jpg");
            //response.setContentType("application/json; charset=UTF-8");
            //response.addHeader("Content-Disposition","attachment;filename="+fileName);
            response.setHeader("Content-Disposition", "attachment; filename=\"" + fileName + "\"");
            //6.通过path 写出去
            try {
                Files.copy(path,response.getOutputStream());
            }catch (IOException e){
                e.printStackTrace();
            }

        }
        return "msg";
    }
}
