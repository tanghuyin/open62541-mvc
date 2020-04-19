package com.robot.demo.service;

import com.robot.demo.dao.RobotAngleDataDao;
import com.robot.demo.domain.RobotAngleData;
import com.robot.demo.utils.KeyStoreLoader;
import com.robot.demo.utils.UaUtils;
import org.bouncycastle.jce.provider.BouncyCastleProvider;
import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.sdk.client.api.config.OpcUaClientConfig;
import org.eclipse.milo.opcua.sdk.client.api.identity.IdentityProvider;
import org.eclipse.milo.opcua.sdk.client.api.subscriptions.UaMonitoredItem;
import org.eclipse.milo.opcua.sdk.client.api.subscriptions.UaSubscription;
import org.eclipse.milo.opcua.stack.client.DiscoveryClient;
import org.eclipse.milo.opcua.stack.core.AttributeId;
import org.eclipse.milo.opcua.stack.core.Identifiers;
import org.eclipse.milo.opcua.stack.core.UaException;
import org.eclipse.milo.opcua.stack.core.security.SecurityPolicy;
import org.eclipse.milo.opcua.stack.core.types.builtin.*;
import org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.UInteger;
import org.eclipse.milo.opcua.stack.core.types.enumerated.MonitoringMode;
import org.eclipse.milo.opcua.stack.core.types.enumerated.TimestampsToReturn;
import org.eclipse.milo.opcua.stack.core.types.structured.*;
import org.eclipse.milo.opcua.stack.core.util.annotations.UInt16Primitive;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;
import org.springframework.beans.factory.annotation.Autowired;
import org.springframework.stereotype.Service;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.Security;
import java.util.*;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.atomic.AtomicBoolean;
import java.util.function.BiConsumer;

import static com.google.common.collect.Lists.newArrayList;
import static org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.Unsigned.uint;
import static org.eclipse.milo.opcua.stack.core.util.ConversionUtil.l;

@Service
public class ClientServiceImpl implements ClientService {
    private static final Logger logger = LoggerFactory.getLogger(ClientServiceImpl.class);
    private OpcUaClient client;
    private Map<Object, Integer> nodeIdToLink = new HashMap<>();
    @Autowired
    RobotAngleDataDao robotAngleDataDao;

    static {
        Security.addProvider(new BouncyCastleProvider());
    }
    @Override
    public boolean searchServer() throws Exception{
        // 搜寻配置
        Path securityTempDir = Paths.get(System.getProperty("java.io.tmpdir"), "security");
        Files.createDirectories(securityTempDir);
        List<EndpointDescription> endpoints = null;
        String endpointUrl = UaUtils.endpointUrl;
        SecurityPolicy securityPolicy = UaUtils.securityPolicy;
        IdentityProvider identityProvider = UaUtils.identityProvider;
        KeyStoreLoader loader = new KeyStoreLoader().load(securityTempDir);
        // 搜寻节点
        try {
            endpoints = DiscoveryClient.getEndpoints(endpointUrl).get();
        } catch (Exception e) {
            logger.error("寻找节点失败");
            return false;
        }

        EndpointDescription endpoint = endpoints.stream()
                .filter(e -> e.getSecurityPolicyUri().equals(securityPolicy.getUri()))
                .findFirst()
                .orElseThrow(() -> new Exception("no desired endpoints returned"));

        logger.info("Using endpoint: {} [{}/{}]", endpoint.getEndpointUrl(), securityPolicy, endpoint.getSecurityMode());

        OpcUaClientConfig config = OpcUaClientConfig.builder()
                .setApplicationName(LocalizedText.english("java opc-ua client"))
                .setCertificate(loader.getClientCertificate())
                .setKeyPair(loader.getClientKeyPair())
                .setEndpoint(endpoint)
                .setIdentityProvider(identityProvider)
                .setRequestTimeout(uint(5000))
                .build();

        client = OpcUaClient.create(config);
        logger.info("成功连接至OpcUa服务器!");
        return true;
    }

    @Override
    public boolean connectServer() {
        try {
            client.connect().get();
        } catch (Exception e) {
            logger.error("连接异常");
            return false;
        }
        return true;
    }

    @Override
    public boolean disconnectServer() {
        return false;
    }

    @Override
    public boolean createSubscription() throws ExecutionException, InterruptedException {
        int numsInAngleSubscription = 6;
        String[][] paths = {
                {"myFirstRobot", "link1", "angle", "angleValue"},
                {"myFirstRobot", "link2", "angle", "angleValue"},
                {"myFirstRobot", "link3", "angle", "angleValue"},
                {"myFirstRobot", "link4", "angle", "angleValue"},
                {"myFirstRobot", "link5", "angle", "angleValue"},
                {"myFirstRobot", "link6", "angle", "angleValue"},
        };
//        NodeId getNodeIdMethodId = new NodeId(1, 62541);
        List<NodeId> nodeIdInAngleSubscription = translateBrowsePathToNodeId(client, paths);

        String[][] paths2 = {
                {"mySecondRobot", "link1", "angle", "angleValue"},
                {"mySecondRobot", "link2", "angle", "angleValue"},
                {"mySecondRobot", "link3", "angle", "angleValue"},
                {"mySecondRobot", "link4", "angle", "angleValue"},
                {"mySecondRobot", "link5", "angle", "angleValue"},
                {"mySecondRobot", "link6", "angle", "angleValue"},
        };
        List<NodeId> nodeIdInAngleSubscription2 = translateBrowsePathToNodeId(client, paths2);
        // 关节值节点的订阅
        UaSubscription angleSubscription = client.getSubscriptionManager().createSubscription(50.0).get();
        UaSubscription angleSubscription2 = client.getSubscriptionManager().createSubscription(50.0).get();
        
        // IMPORTANT: client handle must be unique per item within the context of a subscription.
        // ROBOT1
        Queue<MonitoringParameters> parametersQueue = createParametersList(
                angleSubscription,
                numsInAngleSubscription,
                50.0,
                null,
                10,
                true
        );

        BiConsumer<UaMonitoredItem, Integer> onItemCreated =
                (item, id) -> item.setValueConsumer(this::onSubscriptionValue); // 接收到新值的回调函数

        List<MonitoredItemCreateRequest> requests =
                createMonitoredItemCreateRequest(nodeIdInAngleSubscription, parametersQueue);

        // ROBOT1 END

        // ROBOT2
        Queue<MonitoringParameters> parametersQueue2 = createParametersList(
                angleSubscription2,
                numsInAngleSubscription,
                50.0,
                null,
                10,
                true
        );
        BiConsumer<UaMonitoredItem, Integer> onItemCreated2 =
                (item, id) -> item.setValueConsumer(this::onSubscriptionValue2);

        List<MonitoredItemCreateRequest> requests2 =
                createMonitoredItemCreateRequest(nodeIdInAngleSubscription2, parametersQueue2);

        // 异步，利用semaphore申请create，向client申请create
        // .thenAccept 可以直接先执行后面的语句。一旦结果可用再回来执行，或者可以用.get()这样就会阻塞
        Boolean isSuccess = true;
        List<UaMonitoredItem> uaMonitoredItems = angleSubscription.createMonitoredItems(
                TimestampsToReturn.Both,
                requests,
                onItemCreated
        ).get();

        for (UaMonitoredItem item : uaMonitoredItems) {
            if (item.getStatusCode().isGood()) {
                logger.info("item created for nodeId={}", item.getReadValueId().getNodeId());
                nodeIdToLink.put(item.getReadValueId().getNodeId().getIdentifier(), nodeIdToLink.size()+1);
            } else {
                logger.warn(
                        "failed to create item for nodeId={} (status={})",
                        item.getReadValueId().getNodeId(), item.getStatusCode());
                isSuccess = false;
            }
        }

        List<UaMonitoredItem> uaMonitoredItems2 = angleSubscription2.createMonitoredItems(
                TimestampsToReturn.Both,
                requests2,
                onItemCreated2
        ).get();

        for (UaMonitoredItem item : uaMonitoredItems2) {
            if (item.getStatusCode().isGood()) {
                logger.info("item created for nodeId={}", item.getReadValueId().getNodeId());
                nodeIdToLink.put(item.getReadValueId().getNodeId().getIdentifier(), nodeIdToLink.size()+1);
            } else {
                logger.warn(
                        "failed to create item for nodeId={} (status={})",
                        item.getReadValueId().getNodeId(), item.getStatusCode());
                isSuccess = false;
            }
        }

        return isSuccess;
    }

    @Override
    public void assignWork(int i) {
        logger.info("分配给第 {} 个机器人拾取任务", i);
        // 开始修改某个值，并且机器人客户端订阅该值
        NodeId objectId = Identifiers.ObjectsFolder;
        NodeId generateRobotJobEventMethodId = new NodeId(1, 62542);
        short input = (short) i;
        CallMethodRequest request = new CallMethodRequest(
                objectId,
                generateRobotJobEventMethodId,
                new Variant[]{new Variant(input)}
        );
        this.client.call(request).thenAccept(result -> {
            StatusCode statusCode = result.getStatusCode();
            if (statusCode.isGood()) {
                logger.info("分配任务给{}成功", i);
            } else {
                logger.info("分配任务失败");
            }
        });
    }

    private void onSubscriptionValue(UaMonitoredItem item, DataValue value) {
        if (value.getValue().getValue() != null) {
            logger.info(
                    "robot1: subscription value received: item={}, value={}",
                    nodeIdToLink.getOrDefault(item.getReadValueId().getNodeId().getIdentifier(), -1), value.getValue());
            RobotAngleData data = new RobotAngleData(
                    nodeIdToLink.getOrDefault(item.getReadValueId().getNodeId().getIdentifier(), -1), (Double) value.getValue().getValue(), 1
            );
            robotAngleDataDao.put(data);
        }
    }

    private void onSubscriptionValue2(UaMonitoredItem item, DataValue value) {
        if (value.getValue().getValue() != null) {
            logger.info(
                    "robot2: subscription value received: item={}, value={}",
                    nodeIdToLink.getOrDefault(item.getReadValueId().getNodeId().getIdentifier(), -1) - 6, value.getValue());
            RobotAngleData data = new RobotAngleData(
                    nodeIdToLink.getOrDefault(item.getReadValueId().getNodeId().getIdentifier(), -1) - 6, (Double) value.getValue().getValue(), 2
            );
            robotAngleDataDao.put(data);
        }
    }


    /*
    因为一个subscription中的每一个item都需要一个不同的clienthandle，不然nodeid会相同
     */
    private Queue<MonitoringParameters> createParametersList(UaSubscription subscription, int nums, double samplingInterval, ExtensionObject filter, int queueSize, boolean discardOldest) {
        Queue<MonitoringParameters> parametersList = new ArrayDeque<>();
        for (int i = 0; i < nums; i++) {
            parametersList.add(new MonitoringParameters(
                    subscription.nextClientHandle(),
                    samplingInterval,
                    null,
                    uint(queueSize),
                    discardOldest
            ));
        }
        return parametersList;
    }

    private List<MonitoredItemCreateRequest> createMonitoredItemCreateRequest(List<NodeId> nodeIdInAngleSubscription, Queue<MonitoringParameters> parametersQueue) {
        assert nodeIdInAngleSubscription.size() == parametersQueue.size(); // 确保size相同
        List<MonitoredItemCreateRequest> requestList = new ArrayList<>();
        for (int i = 0; i < nodeIdInAngleSubscription.size(); i++) {
            requestList.add(
                    new MonitoredItemCreateRequest(
                            new ReadValueId(nodeIdInAngleSubscription.get(i),
                                    AttributeId.Value.uid(), null, QualifiedName.NULL_VALUE),
                            MonitoringMode.Reporting,
                            parametersQueue.poll()
                    )
            );
        }
        return requestList;
    }


    private List<NodeId> translateBrowsePathToNodeId(OpcUaClient client, String[][] names) throws ExecutionException, InterruptedException {
        List<NodeId> nodeIds = new ArrayList<>();
        for (int i = 0; i < names.length; i++) {
            // nodeIds.add(executeGetNodeIdMethod(client, names[i], getNodeIdMethodId).get());
            nodeIds.add(translateBrowsePathToNodeId(client, names[i]));
        }
        return nodeIds;
    }

    // 不明原因不稳定
    @Deprecated
    private CompletableFuture<NodeId> executeGetNodeIdMethod(OpcUaClient client, String name, NodeId getNodeIdMethodId) {
        NodeId objectId = Identifiers.ObjectsFolder;

        String input = name;
        CallMethodRequest request = new CallMethodRequest(
                objectId,
                getNodeIdMethodId,
                new Variant[]{new Variant(input)}
        );

        return client.call(request).thenCompose(callMethodResult -> {
            StatusCode statusCode = callMethodResult.getStatusCode();
            if (statusCode.isGood()) {
                NodeId nodeId = (NodeId) l(callMethodResult.getOutputArguments()).get(0).getValue();
                logger.info("FOUND Node{}: {}", name, nodeId);
                return CompletableFuture.completedFuture(nodeId);
            } else {
                StatusCode[] inputArgumentResults = callMethodResult.getInputArgumentResults();
                for (int i = 0; i < inputArgumentResults.length; i++) {
                    logger.error("inputArgumentResults[{}]={}", i, inputArgumentResults[i]);
                }
                CompletableFuture<NodeId> f = new CompletableFuture<>();
                f.completeExceptionally(new UaException(statusCode));
                return f;
            }
        });
    }


    private NodeId translateBrowsePathToNodeId(OpcUaClient client, String[] names) throws ExecutionException, InterruptedException {
        TranslateBrowsePathsToNodeIdsResponse response = client.translateBrowsePaths(newArrayList(new BrowsePath(
                Identifiers.ObjectsFolder,
                new RelativePath(new RelativePathElement[]{
                        new RelativePathElement(
                                Identifiers.HierarchicalReferences,
                                false,
                                true,
                                new QualifiedName(1, names[0])
                        ),
                        new RelativePathElement(
                                Identifiers.HierarchicalReferences,
                                false,
                                true,
                                new QualifiedName(2, names[1])
                        ),
                        new RelativePathElement(
                                Identifiers.HierarchicalReferences,
                                false,
                                true,
                                new QualifiedName(2, names[2])
                        ),
                        new RelativePathElement(
                                Identifiers.HierarchicalReferences,
                                false,
                                true,
                                new QualifiedName(2, names[3])
                        )
                })
        ))).get();

        BrowsePathResult result = l(response.getResults()).get(0);
        StatusCode statusCode = result.getStatusCode();
        logger.info("Node={}, Status={}", names, statusCode.isGood());
        ExpandedNodeId expandedNodeId = l(result.getTargets()).get(0).getTargetId();
        return new NodeId(expandedNodeId.getNamespaceIndex(), (UInteger) expandedNodeId.getIdentifier());
    }
}
