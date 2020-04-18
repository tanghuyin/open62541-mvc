package com.robot.demo.controller;

import com.robot.demo.service.ClientService;
import com.robot.demo.service.ClientServiceImpl;
import com.robot.demo.service.UpdateService;
import com.robot.demo.service.UpdateServiceImpl;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Controller;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

@Controller
public class ClientControllerImpl implements ClientController {
    private static Logger logger = LoggerFactory.getLogger(ClientControllerImpl.class);

    @Autowired
    ClientServiceImpl clientService;
    @Autowired
    UpdateServiceImpl updateService;

    @RequestMapping("/index")
    public String index() {
        return "index";
    }

    @Override
    @RequestMapping(path = {"/connectServer"}, method = {RequestMethod.GET})
    @ResponseBody
    public String connect() throws Exception {
        if (!clientService.searchServer() || !clientService.connectServer()) {
            logger.error("客户端连接异常");
            return "error";
        }
        return "success";
    }

    @Override
    @RequestMapping(path = {"createSubscription"}, method = {RequestMethod.GET})
    @ResponseBody
    public String createSubscription() throws Exception {
        // 两步走
        // 1. 启动订阅
        if (!clientService.createSubscription()) {
            return "false";
        }
        // 2. 更新数据线程启动以更新数据，通过ws发送到前端
        updateService.updateAngleStart();
        return "success";
    }

    @Override
    @RequestMapping(path = {"assignWork"}, method = {RequestMethod.GET})
    @ResponseBody
    public String assignWorkToClient(@RequestParam(value = "robotId", required = true) int robotId) throws Exception {
        clientService.assignWork(robotId);
        return "success";
    }



    @Override
    public boolean disconnect() {
        if (!clientService.disconnectServer()) {
            return false;
        }
        return true;
    }
}
