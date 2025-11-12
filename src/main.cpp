#include "../include/server/grpc_server.h";
#include "../include/server/http_server.h";
#include <iostream>
int main() {
  std::cout << "Starting;";
  loadbalancer::grpc_server::RunServer();

  // To start the http server for calling endpoints.
  // start_http_server();
}
