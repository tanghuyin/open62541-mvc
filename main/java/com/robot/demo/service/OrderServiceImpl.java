package com.robot.demo.service;

import com.robot.demo.domain.Order;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Service;

import java.util.Date;

@Service
public class OrderServiceImpl implements OrderService {
    private static Logger logger = LoggerFactory.getLogger(OrderServiceImpl.class);
    @Override
    public void createOrder(int robotNo, int JobNum) {
        Date d = new Date();
        Order order = new Order(d, JobNum, robotNo);
        logger.info("建立一个订单：时间 {}, 机器人号 {}, 任务数 {}", order.getOrderTime().toString(), order.getOrderRobotNo(), order.getOrderNum());
    }
}
