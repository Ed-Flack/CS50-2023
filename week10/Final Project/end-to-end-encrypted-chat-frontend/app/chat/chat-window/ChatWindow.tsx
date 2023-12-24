import BasicScrollToBottom from "react-scroll-to-bottom";
import "./ChatWindow.css";
import {MessageData} from "@/app/chat/message-data/MessageData";
import {User} from "@/app/chat/user/User";

interface Props {
    me: User;
    currentMessage: string;

    setCurrentMessage(message: string): void;

    sendMessage(): void;

    messageHistory: any[];

    disconnect(): void;
}

export default function ChatWindow(props: Props) {
    return (
        <div className="chat-window">
            <div className="chat-title">
                <p>Chat</p>
            </div>
            <BasicScrollToBottom className="chat-content">
                {props.messageHistory.map((messageData: MessageData) => {
                    return (
                        <div
                            className="message"
                            id={
                                messageData.sourceClient.id === props.me.id ? "you" : "partner"
                            }
                        >
                            <div className="message-content">
                                {typeof messageData.plainTextMessage === "string" ? (
                                    <p>{messageData.plainTextMessage}</p>
                                ) : null}
                            </div>
                            <div className="message-metadata">
                <span>
                  {messageData.sourceClient.name
                      ? messageData.sourceClient.name + " - " + messageData.time
                      : messageData.time}
                </span>
                            </div>
                        </div>
                    );
                })}
            </BasicScrollToBottom>
            <div className="chat-content-container">
                <input
                    className="chat-message"
                    type="text"
                    placeholder="Enter message..."
                    value={props.currentMessage}
                    onChange={(event) => props.setCurrentMessage(event.target.value)}
                    onKeyDown={(event) => {
                        if (event.key === "Enter") {
                            props.sendMessage();
                        }
                    }}
                />
                <button className="send" onClick={props.sendMessage}>
                    Send
                </button>
            </div>
            <button className="disconnect" onClick={props.disconnect}>
                Disconnect
            </button>
        </div>
    );
}
