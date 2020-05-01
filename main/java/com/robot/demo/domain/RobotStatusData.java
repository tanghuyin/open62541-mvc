package com.robot.demo.domain;

import lombok.Data;

@Data
public class RobotStatusData {
    private int robotNo;
    private boolean statusCode;

    public RobotStatusData(int robotNo, boolean statusCode) {
        this.robotNo = robotNo;
        this.statusCode = statusCode;
    }
}
