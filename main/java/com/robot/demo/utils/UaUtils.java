package com.robot.demo.utils;

import org.eclipse.milo.opcua.sdk.client.api.identity.AnonymousProvider;
import org.eclipse.milo.opcua.sdk.client.api.identity.IdentityProvider;
import org.eclipse.milo.opcua.stack.core.security.SecurityPolicy;

public class UaUtils {
    public static String endpointUrl = "opc.tcp://localhost:4840";
    public static SecurityPolicy securityPolicy = SecurityPolicy.None;
    public static IdentityProvider identityProvider = new AnonymousProvider();
}
