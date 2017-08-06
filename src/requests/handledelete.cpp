#include "requests/handledelete.hh"
#include "Tools.hpp"
#include "files/files.hh"
#include <Poco/URI.h>

#include <iostream>

#include "html/html.hh"
#include "data/time.hh"

#include "database/mongodb.hh"

HandleDelete::HandleDelete(){
  Files file("/opt/Sati/db.json");
  std::string db_param=file.readFile();
  file.closeFile();
  
  nlohmann::json j=nlohmann::json::parse(db_param);
  mongo_host=j["mongo_host"].get<std::string>();
  mongo_port=j["mongo_port"].get<int>();
  mongo_stream_base=j["streams_collection"].get<std::string>();
  mongo_rule_base=j["rules_collection"].get<std::string>();
}

void HandleDelete::handleRequest(Poco::Net::HTTPServerRequest& request,
			      Poco::Net::HTTPServerResponse& response){
  poco_log("Request from " + request.clientAddress().toString()+" URI: "+request.getURI()+" content-type : "+request.getContentType());
  
  Poco::Net::HTMLForm form(request, request.stream()/*, partHandler*/);

  std::pair<std::string,std::string> res=switch_URI(request);
  
  response.setChunkedTransferEncoding(true);
  response.setContentType(res.first);
  std::ostream& ostr = response.send();
  ostr << res.second;
}
void HandleDelete::poco_log(std::string log_){
  Poco::Util::Application& app = Poco::Util::Application::instance();
  app.logger().information(log_);
}

std::pair<std::string,std::string> HandleDelete::switch_URI(Poco::Net::HTTPServerRequest& request){
  std::string URI_=request.getURI();
  // do a find rule in segment
  Poco::URI uri(request.getURI());
  std::vector < std::string >  segments;
  uri.getPathSegments(segments);
  if(segments[0].compare("rule")==0&&segments.size()==2){
    return std::make_pair("application/json",
			  remove_rule(segments[1]));
  }
  return std::make_pair("application/json",
			"{\"request\":\"false\"}");
}
std::string HandleDelete::remove_rule(std::string rulename){
  std::string rule_col=apeters::Mongodb::get_collections(mongo_host,
							 mongo_port,
							 mongo_rule_base);
  nlohmann::json j=nlohmann::json::parse(rule_col);
  nlohmann::json::iterator it = j.begin();
  int del_res=apeters::Mongodb::remove_rules(mongo_host,
					     mongo_port,
					     it.value().get<std::string>(),
					     mongo_rule_base,
					     rulename);
  if(del_res==0)
    return "{\"request\":\""+rulename+"\"}";
  return "{\"request\":\"false\"}";
}
