package com.usy.controller;

import com.sun.org.glassfish.external.probe.provider.annotations.ProbeParam;
import com.usy.pojo.PaperBlank;
import com.usy.pojo.PaperChoice;
import com.usy.pojo.PaperDiscuss;
import com.usy.pojo.PaperJudge;
import com.usy.service.CoursePaperService;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.web.bind.annotation.PathVariable;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

import java.util.HashMap;
import java.util.List;
import java.util.Map;


/**
 * 试卷相关操作
 */
@Controller
@RequestMapping("/coursePaperController")
public class CoursePaperController {

    @Autowired
    private CoursePaperService coursePaperService;


    /**
     * 拉取整个试卷 按试卷ID 用于学生答题时
     * @param paperId
     * @return
     */
    @RequestMapping("/pullTest")
    @ResponseBody
    public Map<String,Object> pullTest(@RequestParam("paperId") Integer paperId){

        Map<String,Object> map = new HashMap<>();

        map.put("code","200");

        System.out.println(paperId);
        //选择题查询结果
        List<PaperChoice> paperChoiceList = coursePaperService.selectPaperChoice(paperId);
        System.out.println(paperChoiceList);
        map.put("ChoiceList",paperChoiceList);

        //填空题查询结果
        List<PaperBlank> paperBlankList = coursePaperService.selectPaperBlank(paperId);
        System.out.println(paperBlankList);
        map.put("BlankList",paperBlankList);

        //简答题查询结果
        List<PaperDiscuss> paperDiscussList = coursePaperService.selectPaperDiscuss(paperId);
        System.out.println(paperDiscussList);
        map.put("DiscussList",paperDiscussList);

        //判断题查询结果
        List<PaperJudge> paperJudgeList = coursePaperService.selectPaperJudge(paperId);
        System.out.println(paperJudgeList);
        map.put("JudgeList",paperJudgeList);

        return map;
    }
}
