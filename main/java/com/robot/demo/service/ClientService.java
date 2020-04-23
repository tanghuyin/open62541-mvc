package com.robot.demo.service;

import org.eclipse.milo.opcua.sdk.client.OpcUaClient;

import java.util.concurrent.ExecutionException;

public interface ClientService {
    boolean searchServer() throws Exception;
    boolean connectServer();
    boolean createSubscription() throws ExecutionException, InterruptedException;
    boolean disconnectServer();
    void assignWork(int i);
    void robotFail(int i);
}
