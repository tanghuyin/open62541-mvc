package com.robot.demo.domain;

import lombok.Data;

@Data
public class RobotAngleData {
    private int angleValue = 0;
    private int angleNo = 0;
    private int robotNo = 0;

    public RobotAngleData(int angleNo, int angleValue, int robotNo) {
        this.angleValue = angleValue;
        this.angleNo = angleNo;
        this.robotNo = robotNo;
    }
}
