ARG BUILD_ENV_BASE_IMAGE

FROM ${BUILD_ENV_BASE_IMAGE} AS build-env
RUN apt-get update && \
    DEBIAN_FRONTEND=noninteractive apt-get install -y --no-install-recommends \
        ca-certificates clang clang-format cmake curl g++ gcc-multilib git \
        libboost-all-dev libelf-dev libfmt-dev libgtest-dev libhiredis-dev \
        libmsgsl-dev libpcap-dev libspdlog-dev liburcu-dev llvm make \
        pkg-config redis-server vim
RUN echo /lib64 > /etc/ld.so.conf.d/lib64.conf && ldconfig

FROM build-env AS binary
ARG PROJECT
WORKDIR /root/${PROJECT}
COPY src/ ./src/
COPY Makefile VERSION ./
ENV AT_CONTAINER=true
RUN make build

FROM ${BUILD_ENV_BASE_IMAGE} AS image
ARG PROJECT
ARG OUTPUT_DIR
COPY --from=binary \
        /usr/lib/x86_64-linux-gnu/libfmt.so.8.1.1 \
        /usr/lib/x86_64-linux-gnu/libboost_program_options.so.1.74.0 \
    /usr/lib/x86_64-linux-gnu/
RUN echo /lib64 > /etc/ld.so.conf.d/lib64.conf && ldconfig
COPY --from=binary \
        /root/${PROJECT}/${OUTPUT_DIR} \
    /opt/${PROJECT}/
ENV PATH=/opt/${PROJECT}:$PATH
