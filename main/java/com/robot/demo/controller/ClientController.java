package com.robot.demo.controller;

import com.robot.demo.service.ClientService;
import org.springframework.ui.Model;
import org.springframework.web.bind.annotation.RequestMapping;
import org.springframework.web.bind.annotation.RequestMethod;
import org.springframework.web.bind.annotation.RequestParam;
import org.springframework.web.bind.annotation.ResponseBody;

public interface ClientController {
    String connect() throws Exception;
    String createSubscription() throws Exception;
    String assignWorkToClient(int robotId) throws Exception;
    String robotFail(int robotId) throws Exception;
    boolean disconnect();
}
