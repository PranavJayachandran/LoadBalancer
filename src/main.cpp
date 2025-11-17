#include "../include/server/grpc_server.h"
// #include "../include/server/http_server.h"
#include <iostream>
#include <string>

int main(int argc, char *argv[]) {
  std::string port = "8000";
  std::cout << "Starting;";
  if (argc > 1) {
    port = argv[1];
  }
  loadbalancer::grpc_server::RunServer(port);

  // To start the http server for calling endpoints.
  // start_http_server();
}
