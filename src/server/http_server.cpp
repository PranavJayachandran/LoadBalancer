#include "../../include/external/httplib.h"
#include "../../include/external/json.hpp"
#include "../../include/server/RequestData.h"
#include "../../include/server/http_server.h"

RequestData get_parsed_data_from_request(const httplib::Request &req) {
  nlohmann::json j = nlohmann::json::parse(req.body);
  return RequestData::from_json(j);
}

void start_http_server() {
  httplib::Server svr;
  svr.Post("/insert", [&](const httplib::Request &req, httplib::Response &res) {
    RequestData data = get_parsed_data_from_request(req);
    res.set_content(data.key, "text/plain");
  });

  svr.Put("/update", [&](const httplib::Request &req, httplib::Response &res) {
    RequestData data = get_parsed_data_from_request(req);
    res.set_content(data.key, "text/plain");
  });

  svr.Delete("/delete",
             [&](const httplib::Request &req, httplib::Response &res) {
               RequestData data = get_parsed_data_from_request(req);
               res.set_content(data.key, "text/plain");
             });

  svr.Get("/get", [&](const httplib::Request &req, httplib::Response &res) {
    if (req.has_param("key")) {
      std::string key = req.get_param_value("key");
      res.set_content(key, "text/plain");
    }
  });
  svr.listen("0.0.0.0", 8000);
}
