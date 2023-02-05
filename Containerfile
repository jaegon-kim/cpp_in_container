ARG BUILD_ENV_BASE_IMAGE

FROM ${BUILD_ENV_BASE_IMAGE} AS build-env
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates clang clang-format cmake curl g++ gcc-multilib git \
        libboost-all-dev libelf-dev libfmt-dev libgtest-dev libhiredis-dev \
        libmsgsl-dev libpcap-dev libspdlog-dev liburcu-dev llvm make \
        pkg-config redis-server vim




