import {User} from "@/app/chat/user/User";

export interface Request {
    user: User | null;
    publicKey: string | null;
    declined: boolean;
}
