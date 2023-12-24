import Chat from "@/app/chat/Chat";
import "./page.css";

// noinspection JSUnusedGlobalSymbols
export default function Home() {
    return (
        <div className="home">
            <h1>End-To-End Encrypted Chat</h1>
            <Chat encrypted={true}/>
        </div>
    );
}
