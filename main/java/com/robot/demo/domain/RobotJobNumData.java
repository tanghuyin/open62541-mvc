package com.robot.demo.domain;

import lombok.Data;

@Data
public class RobotJobNumData {
    private int robotNo;
    private int jobNum;

    public RobotJobNumData(int robotNo, int jobNum) {
        this.robotNo = robotNo;
        this.jobNum = jobNum;
    }
}
