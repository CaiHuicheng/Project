package com.usy.controller;

import com.usy.constant.ResponseCode;
import com.usy.pojo.Teacher;
import com.usy.service.FileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;
import org.springframework.web.multipart.MultipartFile;

import javax.servlet.http.HttpSession;
import java.io.File;
import java.io.IOException;
import java.util.Date;
import java.util.HashMap;
import java.util.Map;

@Controller
@RequestMapping("/file")
public class FileController {

    @Autowired
    private FileService fileService;

    private static String uploadPath = "E:\\UserHeadPortrait" + File.separator;

    @RequestMapping(value = "/uploadimage",method = RequestMethod.POST)
    @ResponseBody
    public Map<String,String> upload(@RequestParam("file")MultipartFile multipartFile, Model model, HttpSession session){
        //1.传到那里去
        //(1)判断
        Map<String,String> map = new HashMap<>();

        map.put(ResponseCode.CODE,ResponseCode.HAS_USE.toString());

        if (multipartFile != null && !multipartFile.isEmpty()){
            //不空才传
            //(2)构建新文件
            String originalFilename = multipartFile.getOriginalFilename();
            System.out.println(originalFilename);
            //(3)截取源文件的文件名前缀，不带后缀
            String fileNamePrefix = originalFilename.substring(0,originalFilename.lastIndexOf("."));
            //(4)加工处理文件名，将原文件名 + 时间戳
            String newFileNamefix = fileNamePrefix + new Date().getTime();
            //(5)得到新文件名
            String newFileName = newFileNamefix + originalFilename.substring(originalFilename.lastIndexOf("."));
            //(6)构建文件对象
            File file = new File(uploadPath + newFileName);
            //(7)上传
            try {
                multipartFile.transferTo(file);
                map.put(ResponseCode.CODE,ResponseCode.CAN_USE.toString());
            }catch (IOException e){
                e.printStackTrace();
            }
        }

        //2.我传什么东西
        //3.传的细节
        return map;
    }
}















