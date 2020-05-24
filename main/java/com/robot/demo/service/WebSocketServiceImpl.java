package com.robot.demo.service;

import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.stereotype.Component;

import javax.websocket.OnClose;
import javax.websocket.OnMessage;
import javax.websocket.OnOpen;
import javax.websocket.Session;
import javax.websocket.server.PathParam;
import javax.websocket.server.ServerEndpoint;
import java.io.IOException;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.atomic.AtomicInteger;

@Component
@ServerEndpoint(value = "/websocket/{userId}")
public class WebSocketServiceImpl implements WebSocketService {
    private static final Logger logger = LoggerFactory.getLogger(WebSocketServiceImpl.class);

    private static AtomicInteger onlineClients = new AtomicInteger(0); // 统计在线人数
    private static ConcurrentHashMap<String, WebSocketServiceImpl> clientMap = new ConcurrentHashMap<>(); // session的map

    private Session session;

    @OnOpen
    public void onOpen(Session session, @PathParam("userId") String userId) {
        this.session = session;
        clientMap.put(session.getId(), this); // TODO: array will add session repeatedly? use set?
        onlineClients.incrementAndGet();
        logger.info("有新连接加入！" + onlineClients.get());
    }

    @OnClose
    public void onClose() {
        clientMap.remove(session.getId());
        onlineClients.decrementAndGet();
        logger.info("有连接关闭！" + onlineClients.get());
    }

    @OnMessage
    public void onMessage(String message, Session session) {
        // NOT Applicable NOW!
    }

    public synchronized void sendMessage(String message) throws IOException {
        this.session.getBasicRemote().sendText(message);
    }

    public static void broadCastMessage(String message) throws IOException {
        for (WebSocketServiceImpl socket : clientMap.values()) {
            socket.sendMessage(message);
        }
    }
}
