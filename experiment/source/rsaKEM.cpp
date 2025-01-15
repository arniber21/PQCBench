/**
 * RSA-KEM Benchmark
 * Author: Arnab Ghosh
 * Date: 11/17/2023
 *
 * RSA KEM
 */

#include <cryptopp/rsa.h>
#include <cryptopp/osrng.h>
#include <cryptopp/pubkey.h>

#include <iostream>
#include <vector>

// Function for generating a KEM key pair
std::pair<CryptoPP::RSA::PublicKey, CryptoPP::RSA::PrivateKey> GenerateKeyPair(size_t keyLength = 2048) {
    CryptoPP::AutoSeededRandomPool rng;
    CryptoPP::InvertibleRSAFunction params;
    params.GenerateRandomWithKeySize(rng, keyLength);

    CryptoPP::RSA::PublicKey pubKey(params);
    CryptoPP::RSA::PrivateKey privKey(params);

    return {pubKey, privKey};
}

// Function for encapsulating a key with user-provided ciphertext
std::pair<std::vector<CryptoPP::byte>, std::vector<CryptoPP::byte>> Encapsulate(const CryptoPP::RSA::PublicKey& pubKey,
                                                       const std::vector<CryptoPP::byte>& userCiphertext) {
    CryptoPP::AutoSeededRandomPool rng;
    
    // Generate a random plaintext for KEM purposes
    std::vector<CryptoPP::byte> plaintext(pubKey.FixedMaxPlaintextLength());
    rng.GenerateBlock(plaintext.data(), plaintext.size());

    // Encapsulate the plaintext using RSA encryption
    std::vector<CryptoPP::byte> encapsulatedKey(pubKey.FixedCiphertextLength());
    pubKey.ApplyFunction(rng, plaintext.data(), encapsulatedKey.data());

    return {encapsulatedKey, plaintext};
}

// Function for decapsulating a key, now returning both the decapsulated plaintext and the user-provided ciphertext
std::pair<std::vector<CryptoPP::byte>, std::vector<CryptoPP::byte>> Decapsulate(const std::vector<CryptoPP::byte>& encapsulatedKey,
                                                          const CryptoPP::RSA::PrivateKey& privKey) {
    std::vector<CryptoPP::byte> plaintext(privKey.FixedMaxPlaintextLength());
    privKey.CalculateInverse(encapsulatedKey.data(), plaintext.data());

    // Return both the decapsulated plaintext and the original ciphertext
    return {plaintext, encapsulatedKey};
}

// Example usage
int main() {
    auto keyPair = GenerateKeyPair();

    std::vector<CryptoPP::byte> userCiphertext = ...; // Your ciphertext to encrypt
    auto [encapsulatedKey, sharedSecret] = Encapsulate(keyPair.first, userCiphertext);

    auto [decapsulatedPlaintext, recoveredCiphertext] = Decapsulate(encapsulatedKey, keyPair.second);

    if (decapsulatedPlaintext == sharedSecret) {
        std::cout << "Key agreement successful!" << std::endl;
        std::cout << "Recovered ciphertext: " << recoveredCiphertext << std::endl; // Output the recovered ciphertext
    } else {
        std::cout << "Key agreement failed!" << std::endl;
    }

    return 0;
}