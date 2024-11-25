FROM debian:10.7

# Install necessary packages
RUN apt-get update && \
    apt-get install --yes --no-install-recommends \
    valgrind clang ca-certificates lsb-release autoconf libtool automake make git curl jq python3 python3-venv

# Clone Francinette repository and install
RUN git clone https://github.com/xicodomingues/francinette.git /opt/francinette && \
    cd /opt/francinette && \
    ./bin/install.sh

# Set the working directory
WORKDIR /workspace

# Start a shell session
CMD ["bash"]
