package com.usy.pojo;

public class PaperBlank {
    //填空题题目ID	que_id
    private Integer queId;
    //填空题所属试卷ID	paper_id
    private Integer paperId;
    //填空题在试卷中题目编号	paper_number
    private Integer paperNumber;
    //填空题题目类型	que_type
    private Integer queType;
    //填空题题目	blank_que
    private String blankQue;
    //填空题答案1	blank_answer1
    private String blankAnswer1;
    //填空题答案2	blank_answer2
    private String blankAnswer2;
    //填空题答案3	blank_answer3
    private String blankAnswer3;
    //填空题答案4	blank_answer4
    private String blankAnswer4;
    //填空题答案5	blank_answer5
    private String blankAnswer5;
    //填空题答案6	blank_answer6
    private String blankAnswer6;
    //填空题答案7	blank_answer7
    private String blankAnswer7;
    //填空题答案8	blank_answer8
    private String blankAnswer8;
    //填空题答案9	blank_answer9
    private String blankAnswer9;
    //填空题答案10	blank_answer10
    private String blankAnswer10;
    //填空题解析	blank_analy
    private String blankAnaly;
    //填空题对应的知识点	blank_know
    private String blankKnow;
    //填空题分数	blank_grade
    private Integer blankGrade;

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

    public String getBlankQue() {
        return blankQue;
    }

    public void setBlankQue(String blankQue) {
        this.blankQue = blankQue;
    }

    public String getBlankAnswer1() {
        return blankAnswer1;
    }

    public void setBlankAnswer1(String blankAnswer1) {
        this.blankAnswer1 = blankAnswer1;
    }

    public String getBlankAnswer2() {
        return blankAnswer2;
    }

    public void setBlankAnswer2(String blankAnswer2) {
        this.blankAnswer2 = blankAnswer2;
    }

    public String getBlankAnswer3() {
        return blankAnswer3;
    }

    public void setBlankAnswer3(String blankAnswer3) {
        this.blankAnswer3 = blankAnswer3;
    }

    public String getBlankAnswer4() {
        return blankAnswer4;
    }

    public void setBlankAnswer4(String blankAnswer4) {
        this.blankAnswer4 = blankAnswer4;
    }

    public String getBlankAnswer5() {
        return blankAnswer5;
    }

    public void setBlankAnswer5(String blankAnswer5) {
        this.blankAnswer5 = blankAnswer5;
    }

    public String getBlankAnswer6() {
        return blankAnswer6;
    }

    public void setBlankAnswer6(String blankAnswer6) {
        this.blankAnswer6 = blankAnswer6;
    }

    public String getBlankAnswer7() {
        return blankAnswer7;
    }

    public void setBlankAnswer7(String blankAnswer7) {
        this.blankAnswer7 = blankAnswer7;
    }

    public String getBlankAnswer8() {
        return blankAnswer8;
    }

    public void setBlankAnswer8(String blankAnswer8) {
        this.blankAnswer8 = blankAnswer8;
    }

    public String getBlankAnswer9() {
        return blankAnswer9;
    }

    public void setBlankAnswer9(String blankAnswer9) {
        this.blankAnswer9 = blankAnswer9;
    }

    public String getBlankAnswer10() {
        return blankAnswer10;
    }

    public void setBlankAnswer10(String blankAnswer10) {
        this.blankAnswer10 = blankAnswer10;
    }

    public String getBlankAnaly() {
        return blankAnaly;
    }

    public void setBlankAnaly(String blankAnaly) {
        this.blankAnaly = blankAnaly;
    }

    public String getBlankKnow() {
        return blankKnow;
    }

    public void setBlankKnow(String blankKnow) {
        this.blankKnow = blankKnow;
    }

    public Integer getBlankGrade() {
        return blankGrade;
    }

    public void setBlankGrade(Integer blankGrade) {
        this.blankGrade = blankGrade;
    }

    @Override
    public String toString() {
        return "PaperBlank{" +
                "queId=" + queId +
                ", paperId=" + paperId +
                ", paperNumber=" + paperNumber +
                ", queType=" + queType +
                ", blankQue='" + blankQue + '\'' +
                ", blankAnswer1='" + blankAnswer1 + '\'' +
                ", blankAnswer2='" + blankAnswer2 + '\'' +
                ", blankAnswer3='" + blankAnswer3 + '\'' +
                ", blankAnswer4='" + blankAnswer4 + '\'' +
                ", blankAnswer5='" + blankAnswer5 + '\'' +
                ", blankAnswer6='" + blankAnswer6 + '\'' +
                ", blankAnswer7='" + blankAnswer7 + '\'' +
                ", blankAnswer8='" + blankAnswer8 + '\'' +
                ", blankAnswer9='" + blankAnswer9 + '\'' +
                ", blankAnswer10='" + blankAnswer10 + '\'' +
                ", blankAnaly='" + blankAnaly + '\'' +
                ", blankKnow='" + blankKnow + '\'' +
                ", blankGrade=" + blankGrade +
                '}';
    }
}
