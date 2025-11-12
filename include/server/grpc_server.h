#pragma once
#include "../../src/loadbalancer.grpc.pb.h"
#include <grpcpp/grpcpp.h>
#include <iostream>

namespace loadbalancer::grpc_server {
class LoadBalancerService final
    : public loadbalancer::LoadBalancerService::Service {
public:
  grpc::Status GetNodes(grpc::ServerContext *ctx,
                        const loadbalancer::Empty *request,
                        loadbalancer::Response *response) override;
};
void RunServer();
} // namespace loadbalancer::grpc_server
