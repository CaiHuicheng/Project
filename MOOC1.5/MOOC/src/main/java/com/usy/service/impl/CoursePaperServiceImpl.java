package com.usy.service.impl;

import com.usy.mapper.CoursePaperMapper;
import com.usy.pojo.PaperBlank;
import com.usy.pojo.PaperChoice;
import com.usy.pojo.PaperDiscuss;
import com.usy.pojo.PaperJudge;
import com.usy.service.CoursePaperService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.util.List;

@Service("coursePaperService")
public class CoursePaperServiceImpl implements CoursePaperService {


    @Autowired
    private CoursePaperMapper coursePaperMapper;

    /**
     * 查询该试卷所有的选择题
     *
     * @param paperId
     * @return
     */
    @Override
    public List<PaperChoice> selectPaperChoice(Integer paperId) {
        List<PaperChoice> paperChoiceList = coursePaperMapper.selectPaperChoice(paperId);
        return paperChoiceList;
    }

    /**
     * 查询该试卷所有的判断题
     *
     * @param paperId
     * @return
     */
    @Override
    public List<PaperJudge> selectPaperJudge(Integer paperId) {
        List<PaperJudge> paperJudgeList = coursePaperMapper.selectPaperJudge(paperId);
        return paperJudgeList;
    }

    /**
     * 查询该试卷所有的填空题
     *
     * @param paperId
     * @return
     */
    @Override
    public List<PaperBlank> selectPaperBlank(Integer paperId) {
        List<PaperBlank> paperBlankList = coursePaperMapper.selectPaperBlank(paperId);
        return paperBlankList;
    }

    /**
     * 查询所有试卷的简答题
     *
     * @param paperId
     * @return
     */
    @Override
    public List<PaperDiscuss> selectPaperDiscuss(Integer paperId) {
        List<PaperDiscuss> paperDiscussList = coursePaperMapper.selectPaperDiscuss(paperId);
        return paperDiscussList;
    }
}
