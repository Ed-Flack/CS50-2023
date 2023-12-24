import {MessageData} from "@/app/chat/message-data/MessageData";
import {User} from "@/app/chat/user/User";

export const buildMessage = (
    sourceClient: User,
    targetClient: User,
    encryptedMessage: number[],
): MessageData => {
    return {
        sourceClient: sourceClient,
        targetClient: targetClient,
        plainTextMessage: null,
        encryptedMessage: encryptedMessage,
        time:
            new Date(Date.now()).getHours().toString().padStart(2, "0") +
            ":" +
            new Date(Date.now()).getMinutes().toString().padStart(2, "0"),
        publicKey: null,
    };
};

export const buildChatRequest = (
    sourceClient: User,
    targetClient: User,
    publicKey: string | null,
): MessageData => {
    return {
        sourceClient: sourceClient,
        targetClient: targetClient,
        plainTextMessage: null,
        encryptedMessage: null,
        time: null,
        publicKey: publicKey,
    };
};
