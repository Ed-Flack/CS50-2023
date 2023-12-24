import React from "react";
import {CopyToClipboard} from "react-copy-to-clipboard";
import "./Controls.css";
import {User} from "@/app/chat/user/User";

interface Props {
    me: User;

    setMe(me: User): void;

    partner: User;

    setPartner(partner: User): void;

    sendChatRequest(): Promise<void>;
}

export default function Controls(props: Props) {
    return (
        <div className="controls">
            <input
                className="name"
                placeholder="Name"
                value={props.me.name}
                onChange={(e) => {
                    props.setMe({name: e.target.value, id: props.me.id});
                }}
            />
            <CopyToClipboard text={props.me.id}>
                <button>Copy ID</button>
            </CopyToClipboard>
            <input
                placeholder="ID to contact"
                value={props.partner.id}
                onChange={(e) =>
                    props.setPartner({name: props.partner.name, id: e.target.value})
                }
            />
            <button onClick={props.sendChatRequest}>Connect</button>
        </div>
    );
}
