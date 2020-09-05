package com.usy.service.impl;

import com.usy.mapper.TeacherAccountMapper;
import com.usy.pojo.TeacherAccount;
import com.usy.service.TeacherAccountService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service("teacherAccountService")
public class TeacherAccountServiceImpl implements TeacherAccountService {

    @Autowired
    private TeacherAccountMapper teacherAccountMapper;

    /**
     * 教师账号注册入库
     * @param teacherAccount
     * @return
     */
    @Override
    public boolean instrt(TeacherAccount teacherAccount) {
        //入库前判断
        if (teacherAccount != null){
            int result = teacherAccountMapper.insert(teacherAccount);
            if (result > 0){
                return true;
            }else {
                return false;
            }
        }else {
            return false;
        }
    }
}
