import {Request} from "@/app/chat/request/Request";

interface Props {
    request: Request;
}

export default function SendRequest(props: Props) {
    return (
        <div className="request">
            {!props.request.user ? (
                <h2>Invalid ID</h2>
            ) : props.request.declined ? (
                <h2>Request declined</h2>
            ) : (
                <h2>Sending request to {props.request.user.id}</h2>
            )}
        </div>
    );
}
