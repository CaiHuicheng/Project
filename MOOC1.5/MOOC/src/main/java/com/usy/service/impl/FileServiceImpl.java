package com.usy.service.impl;

import com.usy.mapper.TeacherMapper;
import com.usy.pojo.Teacher;
import com.usy.service.FileService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service("fileService")
public class FileServiceImpl implements FileService {

    @Autowired
    private TeacherMapper teacherMapper;


    /**
     * 老师 修改个人头像
     * @param teacher
     * @return
     */
    @Override
    public boolean updateUserHeadPortrait(Teacher teacher) {
        int result = teacherMapper.updateUserHeadPortrait(teacher);
        if (result > 0){
            return true;
        }else {
            return false;
        }
    }
}
