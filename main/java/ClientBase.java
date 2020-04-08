import org.eclipse.milo.opcua.sdk.client.OpcUaClient;
        import org.eclipse.milo.opcua.sdk.client.api.identity.AnonymousProvider;
        import org.eclipse.milo.opcua.sdk.client.api.identity.IdentityProvider;
        import org.eclipse.milo.opcua.stack.core.security.SecurityPolicy;

        import java.util.concurrent.CompletableFuture;

public abstract class ClientBase {

    static String endpointUrl = "opc.tcp://localhost:4840";
    static SecurityPolicy securityPolicy = SecurityPolicy.None;
    static IdentityProvider identityProvider = new AnonymousProvider();

    abstract void run(OpcUaClient client, CompletableFuture<OpcUaClient> future) throws Exception;
}
