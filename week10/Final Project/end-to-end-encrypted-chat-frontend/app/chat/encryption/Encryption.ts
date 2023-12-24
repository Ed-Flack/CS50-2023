async function generateKeyPair(): Promise<CryptoKeyPair> {
    if (!window.crypto || !window.crypto.subtle) {
        throw new Error(
            "Web Cryptography API is not available in this environment",
        );
    }
    return await window.crypto.subtle.generateKey(
        {
            name: "RSA-OAEP",
            modulusLength: 2048,
            publicExponent: new Uint8Array([0x01, 0x00, 0x01]),
            hash: {name: "SHA-256"},
        },
        true,
        ["encrypt", "decrypt"],
    );
}

export class Encryption {
    publicKey: CryptoKey | undefined;
    privateKey: CryptoKey | undefined;
    partnersPublicKey: CryptoKey | undefined;

    constructor() {
        generateKeyPair()
            .then((keyPair) => {
                this.publicKey = keyPair.publicKey;
                this.privateKey = keyPair.privateKey;
                // You can now use keyPair.publicKey and keyPair.privateKey
            })
            .catch((error) => {
                console.error("Error generating key pair:", error);
            });
    }

    async setPartnersPublicKey(partnersPublicKey: string): Promise<void> {
        const jwk = JSON.parse(partnersPublicKey);
        const algorithm = {
            name: "RSA-OAEP",
            hash: {name: "SHA-256"},
        };
        const keyUsages = ["encrypt"];

        this.partnersPublicKey = await window.crypto.subtle.importKey(
            "jwk" as any,
            jwk,
            algorithm,
            false,
            keyUsages as any,
        );
    }

    async encryptWithPartnersPublicKey(data: string): Promise<number[]> {
        if (this.partnersPublicKey) {
            return Array.from(
                new Uint8Array(
                    await this.encryptWithPartnersPublicKeyInternal(
                        this.partnersPublicKey,
                        data,
                    ),
                ),
            );
        } else {
            throw new Error("Partner's public key not set");
        }
    }

    async decryptWithPrivateKey(encryptedData: ArrayBuffer): Promise<string> {
        if (this.privateKey) {
            const buffer = new Uint8Array(encryptedData).slice(1).buffer;
            return await this.decryptWithPrivateKeyInternal(this.privateKey, buffer);
        } else {
            throw new Error("Private key not set");
        }
    }

    async exportPublicCryptoKey(): Promise<string> {
        if (this.publicKey) {
            return this.exportCryptoKeyToInternal(this.publicKey);
        } else {
            throw new Error("Public key not set");
        }
    }

    private async encryptWithPartnersPublicKeyInternal(
        publicKey: CryptoKey,
        data: string,
    ): Promise<ArrayBuffer> {
        const encodedData = new TextEncoder().encode(data);
        return await window.crypto.subtle.encrypt(
            {
                name: "RSA-OAEP",
            },
            publicKey, // from generateKeyPair
            encodedData,
        );
    }

    private async decryptWithPrivateKeyInternal(
        privateKey: CryptoKey,
        encryptedData: ArrayBuffer,
    ): Promise<string> {
        const decryptedData = await window.crypto.subtle.decrypt(
            {
                name: "RSA-OAEP",
            },
            privateKey, // from generateKeyPair
            encryptedData,
        );
        return new TextDecoder().decode(decryptedData);
    }

    private async exportCryptoKeyToInternal(
        cryptoKey: CryptoKey,
    ): Promise<string> {
        const jwk = await window.crypto.subtle.exportKey("jwk", cryptoKey);
        return JSON.stringify(jwk);
    }

    public arrayBufferToString(buffer: ArrayBuffer): string {
        const decoder = new TextDecoder(); // Default is 'utf-8' encoding
        return decoder.decode(buffer).slice(1);
    }

    public stringToNumberArray(data: string): number[] {
        const encoder = new TextEncoder();
        return Array.from(new Uint8Array(encoder.encode(data)));
    }
}
