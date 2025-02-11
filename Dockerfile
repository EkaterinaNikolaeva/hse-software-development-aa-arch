# docker build -t irsq_benchmark .
# docker run --rm --cpuset-cpus="0" --privileged irsq_benchmark 
FROM ubuntu:latest

RUN apt-get update && apt-get install -y --no-install-recommends \
    cmake g++ gcc make libbenchmark-dev nlohmann-json3-dev \
    libgtest-dev \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN cd /usr/src/googletest && \
    cmake . && \
    make && \
    make install

WORKDIR /app

COPY . .

RUN rm -rf build/CMakeCache.txt build/CMakeFiles

RUN mkdir -p build

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build

CMD ["taskset", "-c", "0", "./build/my_benchmark", "/experiment_environment/configs/config.json"]
