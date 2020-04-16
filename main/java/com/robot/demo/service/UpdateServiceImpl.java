package com.robot.demo.service;

import com.alibaba.fastjson.JSONObject;
import com.robot.demo.dao.RobotAngleDataDao;
import com.robot.demo.domain.RobotAngleData;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Component;

import java.io.IOException;

@Component
public class UpdateServiceImpl implements UpdateService {
    @Autowired
    RobotAngleDataDao robotAngleDataDao;

    @Autowired
    WebSocketServiceImpl webSocketService;

    private static final Logger logger = LoggerFactory.getLogger(UpdateServiceImpl.class);

    @Override
    public void updateAngleStart() {
        ReceivingAngleDataHandler handler = new ReceivingAngleDataHandler();
        Thread thread = new Thread(handler, "Receiving-Handler");
        thread.start();
    }

    class ReceivingAngleDataHandler implements Runnable {
        private volatile boolean interrupted = false;
        @Override
        public void run() {
            logger.info("更新数据线程启动");
            while (!interrupted) {
                RobotAngleData msg = robotAngleDataDao.get();
                JSONObject msgJson = new JSONObject();
                msgJson.put("angleNo", msg.getAngleNo());
                msgJson.put("angleValue", msg.getAngleValue());
                msgJson.put("robotNo", msg.getRobotNo());
                try {
                    webSocketService.broadCastMessage(msgJson.toJSONString());
                } catch (IOException e) {
                    logger.error("发送消息失败");
                }
            }
            logger.info("更新数据线程结束");
        }
        public void shutdown() {
            interrupted = true;
        }
    }
}
