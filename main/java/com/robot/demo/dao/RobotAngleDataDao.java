package com.robot.demo.dao;

import com.robot.demo.domain.RobotAngleData;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

@Component
public class RobotAngleDataDao {
    private static final Logger logger = LoggerFactory.getLogger(RobotAngleDataDao.class);
    private ArrayBlockingQueue fairQueue = new ArrayBlockingQueue(50, true);

    public void put(RobotAngleData robotAngleData) {
        try {
            fairQueue.offer(robotAngleData, 20, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            logger.error("无法将值放入阻塞队列");
        }
    }

    public RobotAngleData get() {
        try {
            RobotAngleData angleData = (RobotAngleData) fairQueue.take();
            return angleData;
        } catch (InterruptedException e) {
            logger.error("无法从阻塞队列中取值");
        }
        return null;
    }
}
