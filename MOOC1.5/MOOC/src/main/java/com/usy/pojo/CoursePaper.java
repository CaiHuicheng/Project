package com.usy.pojo;

public class CoursePaper {

    //试卷ID	paper_id
    private Integer paperId;
    //试卷所属小节ID	sub_id
    private Integer subId;
    //试卷类型	paper_type
    private Integer paperType;
    //试卷名称	paper_name
    private String paperName;
    //试卷说明	paper_intro
    private String paperIntro;
    //试卷总分	paper_sum
    private Integer paperSum;

    public Integer getPaperId() {
        return paperId;
    }

    public void setPaperId(Integer paperId) {
        this.paperId = paperId;
    }

    public Integer getSubId() {
        return subId;
    }

    public void setSubId(Integer subId) {
        this.subId = subId;
    }

    public Integer getPaperType() {
        return paperType;
    }

    public void setPaperType(Integer paperType) {
        this.paperType = paperType;
    }

    public String getPaperName() {
        return paperName;
    }

    public void setPaperName(String paperName) {
        this.paperName = paperName;
    }

    public String getPaperIntro() {
        return paperIntro;
    }

    public void setPaperIntro(String paperIntro) {
        this.paperIntro = paperIntro;
    }

    public Integer getPaperSum() {
        return paperSum;
    }

    public void setPaperSum(Integer paperSum) {
        this.paperSum = paperSum;
    }

    @Override
    public String toString() {
        return "CoursePaper{" +
                "paperId=" + paperId +
                ", subId=" + subId +
                ", paperType=" + paperType +
                ", paperName='" + paperName + '\'' +
                ", paperIntro='" + paperIntro + '\'' +
                ", paperSum=" + paperSum +
                '}';
    }

}
