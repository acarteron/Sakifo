#include "requests/handlepost.hh"

#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "Utils.hpp"
#include "files/files.hh"
#include <Poco/URI.h>

#include <iostream>

HandlePost::HandlePost(){
  Files file("data/db.json");
  std::string db_param=file.readFile();
  file.closeFile();
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Object::Ptr str_obj;
  
  str_var = parser.parse(db_param);
  str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
  str_var = str_obj->get("host");
  mongo_host=str_var.toString();
  str_var=str_obj->get("port");
  mongo_port=Utils::stringTo<int>(str_var.toString());
  str_var=str_obj->get("name");
  mongo_base=str_var.toString();  
}
void HandlePost::handleRequest(Poco::Net::HTTPServerRequest& request,
			       Poco::Net::HTTPServerResponse& response){
  // poco_log("Request from " + request.clientAddress().toString()+" URI: "+request.getURI()+" content-type : "+request.getContentType());

  std::string response_str="";
  if(switch_URI(request)){
    response_str="{\"request\":true}";
  }else{
    response_str="{\"request\":false}";
  }
  
  Poco::Net::HTMLForm form(request, request.stream()/*, partHandler*/);

  response.setChunkedTransferEncoding(true);
  response.setContentType("application/json");
  
  std::ostream& ostr = response.send();
  ostr << response_str;
}


void HandlePost::poco_log(std::string log_){
  Poco::Util::Application& app = Poco::Util::Application::instance();
  app.logger().information(log_);
}
bool HandlePost::check_content_type(std::string content_type,
				    std::string usr_def_content_type){
  return (content_type.compare(usr_def_content_type)==0);
}

bool HandlePost::switch_URI(Poco::Net::HTTPServerRequest& request){
  std::string URI_=request.getURI();
  // do a find rule in segment
  Poco::URI uri(request.getURI());
  std::vector < std::string >  segments;
  uri.getPathSegments(segments);
  // for(size_t i(0);i<segments.size();++i)
  //   std::cout<<segments[i]<<std::endl;

  // std::cout<<"time "<<Utils::getTime()<<std::endl;
  
  // if(URI_.find("StreamEvent")!=std::string::npos||
  //    URI_.find("BatteryLevel")!=std::string::npos||
  //    URI_.find("CommFailure")!=std::string::npos){
  
  std::istream& istr = request.stream();
  std::string str(std::istreambuf_iterator<char>(istr), {});
    
  if(Utils::find_in_vector_str(segments,"StreamEvent")==0){
    StreamEvent ev(data::Utils::extract_StreamType(str,"StreamEvent"));
    //std::cout<<ev.toString()<<std::endl;
	
    if(Mongodb::save_stream_event(mongo_host,mongo_port,ev,"StreamEvent",mongo_base)==0)
      return true;
    else
      return false;
  }else{
    if(Utils::find_in_vector_str(segments,"CommFailure")==0){
      StreamEvent ev(data::Utils::extract_StreamType(str,"CommFailure"));
      //std::cout<<ev.toString()<<std::endl;

      if(Mongodb::save_stream_event(mongo_host,mongo_port,ev,"CommFailure",mongo_base)==0)
	return true;
      else
	return false;
    }else{
      if(Utils::find_in_vector_str(segments,"BatteryLevel")==0){
	StreamEvent ev(data::Utils::extract_StreamType(str,"BatteryLevel"));
	//std::cout<<ev.toString()<<std::endl;
	if(Mongodb::save_stream_event(mongo_host,mongo_port,ev,"BatteryLevel",mongo_base)==0)
	  return true;
	else
	  return false;
      }else{
	if(Utils::find_in_vector_str(segments,"Events")==0){
	  if(Mongodb::save_rule_result(mongo_host,mongo_port,str,mongo_base)==0)
	    return true;
	  else{
	    return false;
	  }
	}else{
	  return false;
	}
      }
    }
  }
  // }
  // return false;
}
