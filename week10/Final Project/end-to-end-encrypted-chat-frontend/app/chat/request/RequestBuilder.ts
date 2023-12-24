import {Request} from "@/app/chat/request/Request";
import {MessageData} from "@/app/chat/message-data/MessageData";
import {User} from "@/app/chat/user/User";

export const buildRequestFromMessageData = (
    data: MessageData,
): Request | null => {
    if (data.sourceClient) {
        return {
            user: data.sourceClient,
            publicKey: data.publicKey,
            declined: false,
        };
    }
    return null;
};

export const buildRequestFromUser = (user: User): Request | null => {
    return {
        user: user,
        publicKey: null,
        declined: false,
    };
};
