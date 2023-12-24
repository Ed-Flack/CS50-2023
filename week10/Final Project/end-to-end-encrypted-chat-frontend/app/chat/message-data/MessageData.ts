import {User} from "@/app/chat/user/User";

export interface MessageData {
    sourceClient: User;
    targetClient: User;
    plainTextMessage: string | null;
    encryptedMessage: ArrayBuffer | number[] | null;
    time: string | null;
    publicKey: string | null;
}
