#include "../../include/server/grpc_server.h"
#include <grpcpp/ext/proto_server_reflection_plugin.h>
#include <iostream>

namespace loadbalancer::grpc_server {

grpc::Status LoadBalancerService::GetNodes(grpc::ServerContext *ctx,
                                           const loadbalancer::Empty *request,
                                           loadbalancer::Response *response) {
  response->set_ip("Hello from LoadBalancer!");
  return grpc::Status::OK;
}

void RunServer() {
  std::string address("0.0.0.0:50051");
  LoadBalancerService service;

  grpc::EnableDefaultHealthCheckService(true);
  grpc::reflection::InitProtoReflectionServerBuilderPlugin();

  grpc::ServerBuilder builder;
  builder.AddListeningPort(address, grpc::InsecureServerCredentials());
  builder.RegisterService(&service);

  std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
  std::cout << "Server listening on " << address << std::endl;
  server->Wait();
}

} // namespace loadbalancer::grpc_server
