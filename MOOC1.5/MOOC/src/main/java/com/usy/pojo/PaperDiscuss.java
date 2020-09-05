package com.usy.pojo;

public class PaperDiscuss {

    //简答题题目ID	que_id
    private Integer queId;
    //简答题所属试卷ID	paper_id
    private Integer paperId;
    //简答题在试卷中题目编号	paper_number
    private Integer paperNumber;
    //简答题题目类型	que_type
    private Integer queType;
    //简答题题目	discuss_que
    private String discussQue;
    //简答题答案	discuss_answer
    private String discussAnswer;
    //简答题解析	discuss_analy
    private String discussAnaly;
    //简答题对应的知识点	discuss_know
    private String discussKnow;
    //简答题分数	discuss_grade
    private Integer discussGrade;

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

    public String getDiscussQue() {
        return discussQue;
    }

    public void setDiscussQue(String discussQue) {
        this.discussQue = discussQue;
    }

    public String getDiscussAnswer() {
        return discussAnswer;
    }

    public void setDiscussAnswer(String discussAnswer) {
        this.discussAnswer = discussAnswer;
    }

    public String getDiscussAnaly() {
        return discussAnaly;
    }

    public void setDiscussAnaly(String discussAnaly) {
        this.discussAnaly = discussAnaly;
    }

    public String getDiscussKnow() {
        return discussKnow;
    }

    public void setDiscussKnow(String discussKnow) {
        this.discussKnow = discussKnow;
    }

    public Integer getDiscussGrade() {
        return discussGrade;
    }

    public void setDiscussGrade(Integer discussGrade) {
        this.discussGrade = discussGrade;
    }

    @Override
    public String toString() {
        return "PaperDiscuss{" +
                "queId=" + queId +
                ", paperId=" + paperId +
                ", paperNumber=" + paperNumber +
                ", queType=" + queType +
                ", discussQue='" + discussQue + '\'' +
                ", discussAnswer='" + discussAnswer + '\'' +
                ", discussAnaly='" + discussAnaly + '\'' +
                ", discussKnow='" + discussKnow + '\'' +
                ", discussGrade=" + discussGrade +
                '}';
    }
}
