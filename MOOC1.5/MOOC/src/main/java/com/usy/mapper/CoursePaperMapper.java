package com.usy.mapper;

import com.usy.pojo.PaperBlank;
import com.usy.pojo.PaperChoice;
import com.usy.pojo.PaperDiscuss;
import com.usy.pojo.PaperJudge;

import java.util.List;

public interface CoursePaperMapper {


    /**
     * 查询该试卷所有的选择题
     * @return
     */
    public List<PaperChoice> selectPaperChoice(Integer paperId);

    /**
     * 查询该试卷所有的判断题
     * @param paperId
     * @return
     */
    public List<PaperJudge> selectPaperJudge(Integer paperId);

    /**
     * 查询该试卷所有的填空题
     * @param paperId
     * @return
     */
    public List<PaperBlank> selectPaperBlank(Integer paperId);

    /**
     * 查询所有试卷的简答题
     * @param paperId
     * @return
     */
    public List<PaperDiscuss> selectPaperDiscuss(Integer paperId);

}
