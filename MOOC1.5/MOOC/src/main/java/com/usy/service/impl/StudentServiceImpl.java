package com.usy.service.impl;

import com.usy.mapper.StudentMapper;
import com.usy.pojo.Student;
import com.usy.service.StudentService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

@Service("studentService")
public class StudentServiceImpl implements StudentService {

    @Autowired
    private StudentMapper studentMapper;

    @Override
    public boolean instrt(Student student) {
        Integer result = studentMapper.instrtIdHp(student);
        if (result > 0){
            return true;
        }else {
            return false;
        }
    }
}
