# Build script for PQCBench

# ----- Payload ----- #
g++ -Wall -std=c++20 source/payload.cpp -o binaries/payload


# ----- eccKEM ------ #
# Note that eccKEM uses CryptoPP libraries and requires a special compilation command
g++ -Wall -std=c++20 source/eccKEM.cpp -o binaries/eccKEM -l:libcryptopp.a

# ---- Benchmark ---- #
g++ -Wall -std=c++20 source/benchmark.cpp -o binaries/benchmark