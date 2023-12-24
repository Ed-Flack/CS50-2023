package org.example;

public class Application {
    public static void main(String[] args) {
        ChatServer chatServer = new ChatServer("localhost", 18000);
        chatServer.start();
    }
}