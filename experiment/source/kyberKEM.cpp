/**
 * Crystals-Kyber KEM Benchmark
 * Author: Arnab Ghosh
 * Date: 11/17/2023
 *
 * Benchmarks the encryption and decryption of a payload using the KYBER KEM described in FIPS 203, 204, 205.
 * This is the first post-quantum cryptographic algorithm that we are comparing to traditional ECC (ECIES).
 *
 * We utilize the Open Quantum Safe implementation of Kyber without any CPU optimizations (in line with other benchmarks of this suite).
 *
 *
 */

#define SSBYTES 32

#include <iostream>
#include <fstream>
#include "kyber512_kem.hpp"
#include <algorithm>
#include <array>
#include <cassert>

// Function to encrypt a file chunk using Kyber512_KEM
void encrypt_chunk(std::ifstream& input_file, std::ofstream& encrypted_file,
                   std::array<uint8_t, kyber512_kem::PKEY_LEN>& pkey) {
    std::array<uint8_t, kyber512_kem::CIPHER_LEN> cipher{};
    std::array<uint8_t, SSBYTES> ss{};

    input_file.read(reinterpret_cast<char*>(ss.data()), SSBYTES);
    std::cout << input_file.tellg() / 500000000.0 << std::endl;
    auto skdf = kyber512_kem::encapsulate(ss, pkey, cipher);
    encrypted_file.write(reinterpret_cast<char*>(cipher.data()), kyber512_kem::CIPHER_LEN);
}

// Function to decrypt a file chunk using Kyber512_KEM
void decrypt_chunk(std::ifstream& encrypted_input_file, std::ofstream& decrypted_file,
                   std::array<uint8_t, kyber512_kem::SKEY_LEN>& skey) {
    std::array<uint8_t, kyber512_kem::CIPHER_LEN> cipher{};
    std::array<uint8_t, SSBYTES> ss{};

    encrypted_input_file.read(reinterpret_cast<char*>(cipher.data()), kyber512_kem::CIPHER_LEN);
    auto rkdf = kyber512_kem::decapsulate(skey, cipher);
    rkdf.squeeze(ss);
    decrypted_file.write(reinterpret_cast<char*>(ss.data()), SSBYTES);
}

int main(int argc, char* argv[]) {
    // Arguments
    std::string payload = argv[1];
    std::string encrypted_output_name = payload + "_ENC";
    std::string decrypted_output_name = payload + "_DEC";

    // Key generation (assuming proper PRNG usage)
    std::array<uint8_t, SSBYTES> d{}, z{}; // seeds
    std::array<uint8_t, kyber512_kem::PKEY_LEN> pkey{};
    std::array<uint8_t, kyber512_kem::SKEY_LEN> skey{};
    kyber512_kem::keygen(d, z, pkey, skey);

    // Encryption
    std::ifstream input_file(payload, std::ios::binary);
    std::ofstream encrypted_file(encrypted_output_name, std::ios::binary);

    while (input_file.peek() != EOF) {
        encrypt_chunk(input_file, encrypted_file, pkey);
    }

    input_file.close();
    encrypted_file.close();

    // Decryption
    std::ifstream encrypted_input_file(encrypted_output_name, std::ios::binary);
    std::ofstream decrypted_file(decrypted_output_name, std::ios::binary);

    while (encrypted_input_file.peek() != EOF) {
        decrypt_chunk(encrypted_input_file, decrypted_file, skey);
    }

    encrypted_input_file.close();
    decrypted_file.close();

    std::cout << "Encryption and decryption complete!" << std::endl;
    return 0;
}