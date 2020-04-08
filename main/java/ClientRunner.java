import org.bouncycastle.jce.provider.BouncyCastleProvider;
import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
import org.eclipse.milo.opcua.sdk.client.api.config.OpcUaClientConfig;
import org.eclipse.milo.opcua.sdk.client.api.identity.IdentityProvider;
import org.eclipse.milo.opcua.stack.client.DiscoveryClient;
import org.eclipse.milo.opcua.stack.core.Stack;
import org.eclipse.milo.opcua.stack.core.security.SecurityPolicy;
import org.eclipse.milo.opcua.stack.core.types.builtin.LocalizedText;
import org.eclipse.milo.opcua.stack.core.types.structured.EndpointDescription;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.Security;
import java.util.List;
import java.util.concurrent.CompletableFuture;
import java.util.concurrent.ExecutionException;
import java.util.concurrent.TimeUnit;

import static org.eclipse.milo.opcua.stack.core.types.builtin.unsigned.Unsigned.uint;

public class ClientRunner implements Runnable{
    static {
        Security.addProvider(new BouncyCastleProvider());
    }
    private static final Logger logger = LoggerFactory.getLogger(ClientRunner.class);
    private final ClientThy clientHelper = new ClientThy();
    private final CompletableFuture<OpcUaClient> future = new CompletableFuture<>();

    private OpcUaClient createClient() throws Exception {
        Path securityTempDir = Paths.get(System.getProperty("java.io.tmpdir"), "security");
        Files.createDirectories(securityTempDir);
        List<EndpointDescription> endpoints = null;
        String endpointUrl = ClientThy.endpointUrl;
        SecurityPolicy securityPolicy = ClientThy.securityPolicy;
        IdentityProvider identityProvider = ClientThy.identityProvider;
        KeyStoreLoader loader = new KeyStoreLoader().load(securityTempDir);

        try {
            endpoints = DiscoveryClient.getEndpoints(endpointUrl).get();
        } catch (Exception e) {
            e.printStackTrace();
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
        return OpcUaClient.create(config);
    }


    @Override
    public void run() {
        try {
            logger.info("Starting create the client.");
            OpcUaClient client = createClient();

            future.whenCompleteAsync((c, ex) -> {
                if (ex != null) {
                    logger.error("Error running {}", ex.getMessage(), ex);
                }
                logger.info("Shutting down the client.");
                try {
                    client.disconnect().get();
                } catch (InterruptedException e) {
                    e.printStackTrace();
                } catch (ExecutionException e) {
                    e.printStackTrace();
                }
                Stack.releaseSharedResources();
                try {
                    Thread.sleep(1000);
                    System.exit(0);
                } catch (InterruptedException e) {
                    e.printStackTrace();
                }
            });

            try {
                clientHelper.run(client, future); // future complete后面的可能会比async里的晚执行
                future.get(10, TimeUnit.SECONDS);
            } catch (Throwable t) {
                logger.error("Error Running client example: {}", t.getMessage(), t);
                future.completeExceptionally(t);
            }
        } catch (Throwable t) {
            logger.error("Error getting client: {}", t.getMessage(), t);
            try {
                Thread.sleep(1000);
                System.exit(0);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
