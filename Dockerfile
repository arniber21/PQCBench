FROM ubuntu as build
WORKDIR /app
COPY . .
RUN apt update && \
  apt install cmake libssl-dev openssl libcrypto++8 libcrypto++-dev libcrypto++-utils build-essential -y --no-install-recommends
WORKDIR /app/experiment

RUN rm /app/experiment/CMakeCache.txt && \
cmake /app/experiment/CMakeLists.txt && \
make


WORKDIR /app/experiment/binaries
RUN ./payload 0_5gb_test 500 && \
./payload 1gb_test 1000 && \
./payload 2gb_test 2000 && \
./payload 4gb_test 4000 && \
./payload 8gb_test 8000 && \
./payload 16gb_test 16000 

FROM ubuntu as runtime
COPY --from=build /app/binaries /binaries
WORKDIR /binaries
RUN ./benchmark ./eccKEM 0_5gb_test && \
./benchmark ./eccKEM 1gb_test && \
./benchmark ./eccKEM 2gb_test && \
./benchmark ./eccKEM 4gb_test && \
./benchmark ./eccKEM 8gb_test && \
./benchmark ./eccKEM 16gb_test && \
./benchmark ./kyberKEM 0_5gb_test && \
./benchmark ./kyberKEM 1gb_test && \
./benchmark ./kyberKEM 2gb_test && \
./benchmark ./kyberKEM 4gb_test && \
./benchmark ./kyberKEM 8gb_test && \
./benchmark ./kyberKEM 16gb_test 
