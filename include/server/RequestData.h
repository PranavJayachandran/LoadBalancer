#pragma once
#include <string>
#include "external/json.hpp"

class RequestData{

  public:
  std::string key, value;

  RequestData(){}
  RequestData(const std::string& key, const std::string& value) : key(key), value(value){}

  static RequestData from_json(const nlohmann::json& j){
    RequestData data;
    if(j.contains("key"))  j.at("key").get_to(data.key);
    if(j.contains("value")) j.at("value").get_to(data.value);

    return data;
  }

  nlohmann::json to_json() const{
    return {
      {"key", key},
      {"value", value}
    };
  }
};
