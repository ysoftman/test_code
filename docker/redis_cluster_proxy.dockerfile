# redis-cluster-proxy
FROM ubuntu:20.04
RUN apt update
RUN apt install -y git make gcc

# 빌드
RUN git clone https://github.com/RedisLabs/redis-cluster-proxy
WORKDIR /redis-cluster-proxy
RUN make && make install
EXPOSE 443 80 9000 7777

# CMD ["/redis-cluster-proxy/src/redis-cluster-proxy", "127.0.0.7:6379"]
CMD ["bash"]
