package org.example;

import lombok.Data;

@Data
public class Message {
    private Client sourceClient;
    private Client targetClient;
    private byte[] encryptedMessage;
    private String time;
    private String publicKey;
}

