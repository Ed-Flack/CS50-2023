"use client";
import "./Chat.css";
import ChatWindow from "@/app/chat/chat-window/ChatWindow";
import {useEffect, useState} from "react";
import Controls from "@/app/chat/controls/Controls";
import io, {Socket} from "socket.io-client";
import {User} from "@/app/chat/user/User";
import {Request} from "@/app/chat/request/Request";
import ReceiveRequest from "@/app/chat/request/receive-request/ReceiveRequest";
import {MessageData} from "@/app/chat/message-data/MessageData";
import {Encryption} from "@/app/chat/encryption/Encryption";
import {buildChatRequest, buildMessage,} from "@/app/chat/message-data/MessageDataBuilder";
import SendRequest from "@/app/chat/request/send-request/SendRequest";
import {buildRequestFromMessageData, buildRequestFromUser,} from "@/app/chat/request/RequestBuilder";

const encryption: Encryption = new Encryption();
const socket: Socket = io("http://localhost:18000");

interface Props {
    encrypted: boolean;
}

export default function Chat(props: Props) {
    const [currentMessage, setCurrentMessage] = useState<string>("");
    const [messageHistory, setMessageHistory] = useState<MessageData[]>([]);
    const [me, setMe] = useState<User>({name: "", id: ""});
    const [partner, setPartner] = useState<User>({name: "", id: ""});
    const [receivedRequest, setReceivedRequest] = useState<Request | null>();
    const [sentRequest, setSentRequest] = useState<Request | null>();
    const [connected, setConnected] = useState<boolean>(false);
    const [partnerDisconnected, setPartnerDisconnected] = useState<string>("");

    useEffect(() => {
        socket.on("id", (id) => {
            setMe({name: me.name, id: id});
        });

        socket.on("chatRequest", (data: MessageData) => {
            setReceivedRequest(buildRequestFromMessageData(data));
        });

        socket.on("accepted", async (data: MessageData) => {
            if (props.encrypted && data.publicKey) {
                await encryption.setPartnersPublicKey(data.publicKey);
            }
            setPartner(data.sourceClient);
            setSentRequest(null);
            setConnected(true);
        });

        socket.on("declined", async () => {
            if (sentRequest) {
                setPartner({name: "", id: ""});
                const declinedSentRequest = {...sentRequest};
                declinedSentRequest.declined = true;
                setSentRequest(declinedSentRequest);
                setTimeout((): void => {
                    setSentRequest(null);
                }, 3000);
            }
        });

        socket.on("invalidSessionId", () => {
            if (sentRequest) {
                const invalidSentRequest = {...sentRequest};
                invalidSentRequest.user = null;
                setSentRequest(invalidSentRequest);
                setTimeout((): void => {
                    setSentRequest(null);
                }, 3000);
            }
        });

        socket.on("partnerDisconnected", () => {
            setConnected(false);
            setMessageHistory([]);
            setPartnerDisconnected(partner.name ? partner.name : "Partner");
            setPartner({name: "", id: ""});
            setTimeout((): void => {
                setPartnerDisconnected("");
            }, 3000);
        });

        socket
            .off("receiveMessage")
            .on("receiveMessage", async (messageData: MessageData) => {
                if (
                    messageData.encryptedMessage &&
                    messageData.encryptedMessage instanceof ArrayBuffer
                ) {
                    if (props.encrypted) {
                        messageData.plainTextMessage =
                            await encryption.decryptWithPrivateKey(
                                messageData.encryptedMessage,
                            );
                    } else {
                        messageData.plainTextMessage = encryption.arrayBufferToString(
                            messageData.encryptedMessage,
                        );
                    }
                    setMessageHistory((history) => [...history, messageData]);
                }
            });
    });

    const acceptChatRequest = async (): Promise<void> => {
        if (receivedRequest?.user) {
            let messageData: MessageData;
            if (props.encrypted) {
                messageData = buildChatRequest(
                    me,
                    receivedRequest.user,
                    await encryption.exportPublicCryptoKey(),
                );
            } else {
                messageData = buildChatRequest(me, receivedRequest.user, null);
            }
            socket?.emit("accept", messageData);
            setPartner(receivedRequest.user);
            if (props.encrypted && receivedRequest.publicKey) {
                await encryption.setPartnersPublicKey(receivedRequest.publicKey);
            }
            setReceivedRequest(null);
            setConnected(true);
        }
    };

    const declineChatRequest = (): void => {
        if (receivedRequest?.user) {
            const messageData: MessageData = buildChatRequest(
                me,
                receivedRequest.user,
                null,
            );
            socket?.emit("decline", messageData);
            setReceivedRequest(null);
        }
    };

    const sendChatRequest = async (): Promise<void> => {
        if (partner.id) {
            let messageData: MessageData;
            if (props.encrypted) {
                messageData = buildChatRequest(
                    me,
                    partner,
                    await encryption.exportPublicCryptoKey(),
                );
            } else {
                messageData = buildChatRequest(me, partner, null);
            }
            setSentRequest(buildRequestFromUser(partner));
            socket?.emit("chatRequest", messageData);
        }
    };

    const sendMessage = async (): Promise<void> => {
        if (currentMessage) {
            let encryptedMessage: number[];
            if (props.encrypted) {
                encryptedMessage =
                    await encryption.encryptWithPartnersPublicKey(currentMessage);
            } else {
                encryptedMessage = encryption.stringToNumberArray(currentMessage);
            }
            const message: MessageData = buildMessage(me, partner, encryptedMessage);
            socket?.emit("sendMessage", message);
            message.plainTextMessage = currentMessage;
            setMessageHistory((history) => [...history, message]);
            setCurrentMessage("");
        }
    };

    const disconnect = (): void => {
        setConnected(false);
        setPartner({name: "", id: ""});
        socket?.emit("disconnectFromPartner");
        setMessageHistory([]);
    };

    return (
        <div className="chat">
            {connected ? (
                <ChatWindow
                    me={me}
                    currentMessage={currentMessage}
                    setCurrentMessage={setCurrentMessage}
                    sendMessage={sendMessage}
                    messageHistory={messageHistory}
                    disconnect={disconnect}
                />
            ) : (
                <Controls
                    me={me}
                    setMe={setMe}
                    partner={partner}
                    setPartner={setPartner}
                    sendChatRequest={sendChatRequest}
                />
            )}
            {receivedRequest ? (
                <ReceiveRequest
                    request={receivedRequest}
                    setRequest={setReceivedRequest}
                    acceptChatRequest={acceptChatRequest}
                    declineChatRequest={declineChatRequest}
                />
            ) : sentRequest ? (
                <SendRequest request={sentRequest}/>
            ) : null}
            {partnerDisconnected ? <h2>{partnerDisconnected} disconnected</h2> : null}
        </div>
    );
}
