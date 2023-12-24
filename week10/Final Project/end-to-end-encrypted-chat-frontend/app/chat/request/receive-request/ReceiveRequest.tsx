import {Request} from "@/app/chat/request/Request";
import "./ReceiveRequest.css";

interface Props {
    request: Request;

    setRequest(request: Request | null): void;

    acceptChatRequest(): void;

    declineChatRequest(): void;
}

export default function ReceiveRequest(props: Props) {
    return (
        <div className="request">
            <h2>
                Chat request from{" "}
                {props.request.user?.name ? props.request.user.name : "Unknown"}
            </h2>
            <button onClick={props.acceptChatRequest}>Accept</button>
            <button onClick={props.declineChatRequest}>Decline</button>
        </div>
    );
}
