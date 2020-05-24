package com.robot.demo.domain;

import lombok.Data;

import java.util.Date;

@Data
public class Order {
    Date orderTime;
    int orderNum;
    int orderRobotNo;

    public Order(Date orderTime, int orderNum, int orderRobotNo) {
        this.orderTime = orderTime;
        this.orderNum = orderNum;
        this.orderRobotNo = orderRobotNo;
    }
}
