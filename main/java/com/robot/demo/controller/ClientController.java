package com.robot.demo.controller;

import com.robot.demo.service.ClientService;
import org.springframework.ui.Model;

public interface ClientController {
    String connect() throws Exception;
    String createSubscription() throws Exception;
    boolean disconnect();
}
