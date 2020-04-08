import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.sdk.client.api.subscriptions.UaMonitoredItem;
import org.eclipse.milo.opcua.sdk.client.api.subscriptions.UaSubscription;
import org.eclipse.milo.opcua.stack.core.AttributeId;
import org.eclipse.milo.opcua.stack.core.Identifiers;
import org.eclipse.milo.opcua.stack.core.UaException;
import org.eclipse.milo.opcua.stack.core.types.builtin.*;
import org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.UInteger;
import org.eclipse.milo.opcua.stack.core.types.enumerated.MonitoringMode;
import org.eclipse.milo.opcua.stack.core.types.enumerated.TimestampsToReturn;
import org.eclipse.milo.opcua.stack.core.types.structured.*;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Queue;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.function.BiConsumer;

import static com.google.common.collect.Lists.newArrayList;
import static org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.Unsigned.uint;
import static org.eclipse.milo.opcua.stack.core.util.ConversionUtil.l;

public class ClientThy extends ClientBase {
    private static final Logger logger = LoggerFactory.getLogger(ClientThy.class);

    @Override
    void run(OpcUaClient client, CompletableFuture<OpcUaClient> future) throws Exception {
        client.connect().get();

        int numsInAngleSubscription = 6;
        String[] paths = {
                "link1_angle_angleValue_",
                "link2_angle_angleValue_",
                "link3_angle_angleValue_",
                "link4_angle_angleValue_",
                "link5_angle_angleValue_",
                "link6_angle_angleValue_",
        };
        NodeId getNodeIdMethodId = new NodeId(1, 62541);
        List<NodeId> nodeIdInAngleSubscription = translateBrowsePathToNodeId(client, paths, getNodeIdMethodId);

        // 6个关节值节点的订阅
        UaSubscription angleSubscription = client.getSubscriptionManager().createSubscription(500.0).get();

        // IMPORTANT: client handle must be unique per item within the context of a subscription.
        Queue<MonitoringParameters> parametersQueue = createParametersList(
                angleSubscription,
                numsInAngleSubscription,
                500.0,
                null,
                10,
                true
        );

        BiConsumer<UaMonitoredItem, Integer> onItemCreated =
                (item, id) -> item.setValueConsumer(this::onSubscriptionValue);

        List<MonitoredItemCreateRequest> requests =
                createMonitoredItemCreateRequest(nodeIdInAngleSubscription, parametersQueue);


        // 异步，利用semaphore申请create，向client申请create
        // .thenAccept 可以直接先执行后面的语句。一旦结果可用再回来执行，或者可以用.get()这样就会阻塞
        angleSubscription.createMonitoredItems(
                TimestampsToReturn.Both,
                requests,
                onItemCreated
        ).thenAccept(uaMonitoredItems -> {
            for (UaMonitoredItem item : uaMonitoredItems) {
                if (item.getStatusCode().isGood()) {
                    logger.info("item created for nodeId={}", item.getReadValueId().getNodeId());
                } else {
                    logger.warn(
                            "failed to create item for nodeId={} (status={})",
                            item.getReadValueId().getNodeId(), item.getStatusCode());
                }
            }
        });

        /*
        此处编写设定默认机器人参数的代码，要用到写函数，此处注意线程安全
         */
        String[] link1Size = {"link1_x_", "link1_y_", "link1_z_"};
        String[] link2Size = {"link2_x_", "link2_y_", "link2_z_"};
        String[] link3Size = {"link3_x_", "link3_y_", "link3_z_"};
        String[] link4Size = {"link4_x_", "link4_y_", "link4_z_"};
        String[] link5Size = {"link5_x_", "link5_y_", "link5_z_"};
        String[] link6Size = {"link6_x_", "link6_y_", "link6_z_"};


        Thread.sleep(50000);

        future.complete(client);
    }


    private void onSubscriptionValue(UaMonitoredItem item, DataValue value) {
        logger.info(
                "subscription value received: item={}, value={}",
                item.getReadValueId().getNodeId(), value.getValue());
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

    private List<NodeId> translateBrowsePathToNodeId(OpcUaClient client, String[] names, NodeId getNodeIdMethodId) throws ExecutionException, InterruptedException {
        List<NodeId> nodeIds = new ArrayList<>();
        for (int i = 0; i < names.length; i++) {
            nodeIds.add(executeGetNodeIdMethod(client, names[i], getNodeIdMethodId).get());
        }
        return nodeIds;
    }

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

    @Deprecated
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
        logger.info("Status={}", statusCode);
        ExpandedNodeId expandedNodeId = l(result.getTargets()).get(0).getTargetId();
        return new NodeId(expandedNodeId.getNamespaceIndex(), (UInteger) expandedNodeId.getIdentifier());
    }
}
