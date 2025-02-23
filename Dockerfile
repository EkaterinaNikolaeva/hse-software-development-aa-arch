FROM ubuntu:22.04

RUN apt-get update && \
    apt-get install -y --no-install-recommends \
    cmake=3.22.1-1ubuntu1.22.04.2 g++=4:11.2.0-1ubuntu1 \
    gcc=4:11.2.0-1ubuntu1 make=4.3-4.1build1 \
    libbenchmark-dev=1.6.1-1 \
    nlohmann-json3-dev=3.10.5-2 \
    libgtest-dev=1.11.0-3 \
    && apt-get clean && rm -rf /var/lib/apt/lists/*

RUN cmake -S /usr/src/googletest -B /usr/src/googletest/build -DCMAKE_INSTALL_PREFIX=/usr/local && \
    cmake --build /usr/src/googletest/build --parallel $(nproc) && \
    cmake --install /usr/src/googletest/build

WORKDIR /app

COPY . .

RUN rm -rf build && mkdir -p build

RUN cmake -S . -B build -DCMAKE_BUILD_TYPE=Release && \
    cmake --build build --parallel $(nproc)

CMD ["taskset", "-c", "0", "./build/my_benchmark", "/experiment_environment/configs/config.json"]
