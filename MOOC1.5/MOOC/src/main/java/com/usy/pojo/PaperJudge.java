package com.usy.pojo;

public class PaperJudge {

    //判断题题目ID	que_id
    private Integer queId;
    //判断题所属试卷ID	paper_id
    private Integer paperId;
    //判断题在试卷中题目编号	paper_number
    private Integer paperNumber;
    //判断题题目类型	que_type
    private Integer queType;
    //判断题题目	judge_que
    private String judgeQue;
    //判断题答案	judge_answer
    private Integer judgeAnswer;
    //判断题解析	judge_analy
    private String judgeAnaly;
    //判断题对应的知识点	judge_know
    private String judgeKnow;
    //判断题分数	judge_grade
    private Integer judgeGrade;

    public Integer getQueId() {
        return queId;
    }

    public void setQueId(Integer queId) {
        this.queId = queId;
    }

    public Integer getPaperId() {
        return paperId;
    }

    public void setPaperId(Integer paperId) {
        this.paperId = paperId;
    }

    public Integer getPaperNumber() {
        return paperNumber;
    }

    public void setPaperNumber(Integer paperNumber) {
        this.paperNumber = paperNumber;
    }

    public Integer getQueType() {
        return queType;
    }

    public void setQueType(Integer queType) {
        this.queType = queType;
    }

    public String getJudgeQue() {
        return judgeQue;
    }

    public void setJudgeQue(String judgeQue) {
        this.judgeQue = judgeQue;
    }

    public Integer getJudgeAnswer() {
        return judgeAnswer;
    }

    public void setJudgeAnswer(Integer judgeAnswer) {
        this.judgeAnswer = judgeAnswer;
    }

    public String getJudgeAnaly() {
        return judgeAnaly;
    }

    public void setJudgeAnaly(String judgeAnaly) {
        this.judgeAnaly = judgeAnaly;
    }

    public String getJudgeKnow() {
        return judgeKnow;
    }

    public void setJudgeKnow(String judgeKnow) {
        this.judgeKnow = judgeKnow;
    }

    public Integer getJudgeGrade() {
        return judgeGrade;
    }

    public void setJudgeGrade(Integer judgeGrade) {
        this.judgeGrade = judgeGrade;
    }

    @Override
    public String toString() {
        return "PaperJudge{" +
                "queId=" + queId +
                ", paperId=" + paperId +
                ", paperNumber=" + paperNumber +
                ", queType=" + queType +
                ", judgeQue='" + judgeQue + '\'' +
                ", judgeAnswer=" + judgeAnswer +
                ", judgeAnaly='" + judgeAnaly + '\'' +
                ", judgeKnow='" + judgeKnow + '\'' +
                ", judgeGrade=" + judgeGrade +
                '}';
    }


}
