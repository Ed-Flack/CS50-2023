package org.example;

import com.corundumstudio.socketio.Configuration;
import com.corundumstudio.socketio.SocketIOClient;
import com.corundumstudio.socketio.SocketIOServer;

import java.nio.charset.StandardCharsets;
import java.util.HashMap;
import java.util.Map;
import java.util.UUID;

public class ChatServer {

    private final SocketIOServer server;
    private final Map<UUID, UUID> connectedUsers;

    public ChatServer(String hostName, int port) {
        Configuration config = new Configuration();
        config.setHostname(hostName);
        config.setPort(port);
        server = new SocketIOServer(config);
        connectedUsers = new HashMap<>();
    }

    public void start() {
        server.addConnectListener(client -> {
            System.out.println("Client connected: " + client.getSessionId());
            connectedUsers.put(client.getSessionId(), null);
            client.sendEvent("id", client.getSessionId());
        });

        server.addDisconnectListener(client -> {
            if (connectedUsers.containsKey(client.getSessionId())) {
                UUID partner = connectedUsers.get(client.getSessionId());
                connectedUsers.remove(client.getSessionId());
                if (partner != null) {
                    connectedUsers.put(partner, null);
                    server.getClient(partner).sendEvent("partnerDisconnected");
                }
            }
            System.out.println("Client disconnected: " + client.getSessionId());
        });

        server.addEventListener("disconnectFromPartner", Message.class, (client, data, ackSender) -> {
            if (connectedUsers.containsKey(client.getSessionId())) {
                UUID partner = connectedUsers.get(client.getSessionId());
                connectedUsers.put(client.getSessionId(), null);
                if (partner != null) {
                    connectedUsers.put(partner, null);
                    server.getClient(partner).sendEvent("partnerDisconnected");
                }
            }
        });

        server.addEventListener("chatRequest", Message.class, (client, data, ackSender) -> {
            try {
                UUID targetUUID = UUID.fromString(data.getTargetClient().getId());
                if (connectedUsers.containsKey(targetUUID)) {
                    SocketIOClient targetClient = server.getClient(targetUUID);
                    targetClient.sendEvent("chatRequest", data);
                } else {
                    client.sendEvent("invalidSessionId");
                }
            } catch (IllegalArgumentException e) {
                client.sendEvent("invalidSessionId");
            }
        });

        server.addEventListener("accept", Message.class, (client, data, ackSender) -> {
            SocketIOClient targetClient = server.getClient(UUID.fromString(data.getTargetClient().getId()));
            targetClient.sendEvent("accepted", data);
            connectedUsers.put(client.getSessionId(), targetClient.getSessionId());
            connectedUsers.put(targetClient.getSessionId(), client.getSessionId());
        });

        server.addEventListener("decline", Message.class, (client, data, ackSender) -> {
            SocketIOClient targetClient = server.getClient(UUID.fromString(data.getTargetClient().getId()));
            targetClient.sendEvent("declined", data);
        });

        server.addEventListener("sendMessage", Message.class, (client, data, ackSender) -> {
            System.out.println("Attempt to sniff message:");
            System.out.println(new String(data.getEncryptedMessage(), StandardCharsets.UTF_8)); // Sniffing demo
            if (connectedUsers.containsKey(client.getSessionId())) {
                SocketIOClient targetClient = server.getClient(connectedUsers.get(client.getSessionId()));
                targetClient.sendEvent("receiveMessage", data);
            }
        });

        server.start();
        Runtime.getRuntime().addShutdownHook(new Thread(server::stop));
    }
}
