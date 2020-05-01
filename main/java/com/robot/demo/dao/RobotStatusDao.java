package com.robot.demo.dao;

import com.robot.demo.domain.RobotAngleData;
import com.robot.demo.domain.RobotStatusData;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import java.util.concurrent.ArrayBlockingQueue;
import java.util.concurrent.TimeUnit;

@Component
public class RobotStatusDao {
    private static final Logger logger = LoggerFactory.getLogger(RobotAngleDataDao.class);
    private ArrayBlockingQueue fairQueue = new ArrayBlockingQueue(5, true);

    public void put(RobotStatusData robotStatusData) {
        try {
            fairQueue.offer(robotStatusData, 20, TimeUnit.MILLISECONDS);
        } catch (InterruptedException e) {
            logger.error("无法将值放入阻塞队列");
        }
    }

    public RobotStatusData get() {
        try {
            RobotStatusData statusData = (RobotStatusData) fairQueue.take();
            return statusData;
        } catch (InterruptedException e) {
            logger.error("无法从阻塞队列中取值");
        }
        return null;
    }
}
