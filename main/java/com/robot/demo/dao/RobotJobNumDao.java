package com.robot.demo.dao;

import com.robot.demo.domain.RobotJobNumData;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

@Component
public class RobotJobNumDao {
    private static final Logger logger = LoggerFactory.getLogger(RobotJobNumDao.class);
    private ArrayBlockingQueue fairQueue = new ArrayBlockingQueue(5, true);

    public void put(RobotJobNumData robotJobNumData) {
        try {
            fairQueue.offer(robotJobNumData, 20, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            logger.error("无法将值放入阻塞队列");
        }
    }

    public RobotJobNumData get() {
        try {
            RobotJobNumData angleData = (RobotJobNumData) fairQueue.take();
            return angleData;
        } catch (InterruptedException e) {
            logger.error("无法从阻塞队列中取值");
        }
        return null;
    }
}
