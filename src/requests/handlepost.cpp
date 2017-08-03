#include "requests/handlepost.hh"
#include "requests/request.hh"

#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "Utils.hpp"
#include "files/files.hh"
#include "libzamzama.hh"
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
  std::string res_switch=switch_URI(request);
  std::vector<std::string> splited;
  std::vector<std::string> splited_=Utils::splitString(res_switch,'\n');
  for(size_t i(0);i<splited_.size();++i){
    if(splited_[i].compare("")!=0)
      splited.push_back(splited_[i]);
  }
  res_switch="[";
  for(size_t i(0);i<splited.size()-1;++i)
    res_switch+="\""+splited[i]+"\",";
  res_switch+="\""+splited[splited.size()-1]+"\"]";
  response_str="{\"request\":"+res_switch+"}";

  
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
std::string HandlePost::send_request(std::string req){
  Request rule_to_srv;
  rule_to_srv.setServer(esper_srv);
  rule_to_srv.setPUT();
  return rule_to_srv.send_request(req);  
}
std::string HandlePost::setRule(std::string stream){
  std::cout<<"Stream "<<stream<<std::endl;
    Poco::JSON::Parser      parser;
    Poco::Dynamic::Var      str_var;
    Poco::JSON::Object::Ptr str_obj;
    Poco::Dynamic::Var      rule_name_var;
    Poco::Dynamic::Var      expression_var;
    Poco::Dynamic::Var      kind_var;
    Poco::Dynamic::Var      force_var;
    str_var = parser.parse(stream);
    parser.reset();
    str_obj = str_var.extract<Poco::JSON::Object::Ptr>();

    rule_name_var = str_obj->get("name");
    expression_var = str_obj->get("expression");
    kind_var = str_obj->get("kind");
    force_var = str_obj->get("force");

    std::cout<<" "<<rule_name_var.toString()<<" "<<force_var.toString()<<" "<<kind_var.toString()<<std::endl;
    std::vector<std::string> splited;
    std::vector<std::string> splited_=Utils::splitString(expression_var.toString(),'\n');

    //remove spaces
    for(size_t i(0);i<splited_.size();++i){
      if(splited_[i].compare("")!=0)
	splited.push_back(splited_[i]);
    }

    
    std::string req="{\"source\":\"rule\",\"type\":\"rule\",\"name\":";
    req+="\""+rule_name_var.toString()+"\",";
    req+="\"force_write\":\"";
    req+=force_var.toString()+"\",";
    req+="\"expression\":[";
    
    if(kind_var.toString().compare("ast")==0){
      std::cout<<splited[0]<<std::endl;
      std::pair<std::vector<std::string>,
		std::vector<std::string>> res=
	zamzama::compile(rule_name_var.toString(),splited[0]);
      std::vector<std::string> rules=res.first;
      std::vector<std::string> err=res.second;

      std::cout<<"lol "<<err.size()<<std::endl;

      if(err.size()>0){
	std::string ret="";
	for(size_t i(0);i<err.size();++i){
	  std::cout<<err[i]<<std::endl;
	  ret+=err[i]+"\n";
	}
	std::cout<<ret<<std::endl;
	      
	return ret;
      }
      
      std::string frule="";
      for(size_t i(0);i<rules.size()-1;++i)
        req+="\""+rules[i]+"\",";
      req+="\""+rules[rules.size()-1]+"\"";
     
    }else{
      if(kind_var.toString().compare("epl")==0){
	for(size_t i(0);i<splited.size()-1;++i)
	  req+="\""+splited[i]+"\",";
	req+="\""+splited[splited.size()-1]+"\"";
      }
    }
    req+="]}";
    std::cout<<req<<std::endl;
    return send_request(req);
      
}

std::string HandlePost::switch_URI(Poco::Net::HTTPServerRequest& request){
  std::string URI_=request.getURI();
  // do a find rule in segment
  Poco::URI uri(request.getURI());
  std::vector < std::string >  segments;
  uri.getPathSegments(segments);
  // for(size_t i(0);i<segments.size();++i)
  //   std::cout<<segments[i]<<std::endl;
  // std::cout<<"time "<<Utils::getTime()<<std::endl;

  std::istream& istr = request.stream();
  std::string str(std::istreambuf_iterator<char>(istr), {});

  if(segments[0].compare("rulemanager")==0){
    return setRule(str);    
  }else{
    if(Utils::find_in_vector_str(segments,"StreamEvent")==0){
      StreamEvent ev(data::Utils::extract_StreamType(str,"StreamEvent"));
      //std::cout<<ev.toString()<<std::endl;
      if(Mongodb::save_stream_event(mongo_host,mongo_port,ev,"StreamEvent",mongo_base)==0)
	return "true";
      else
	return "false";
    }else{
      if(Utils::find_in_vector_str(segments,"CommFailure")==0){
	StreamEvent ev(data::Utils::extract_StreamType(str,"CommFailure"));
	//std::cout<<ev.toString()<<std::endl;

	if(Mongodb::save_stream_event(mongo_host,mongo_port,ev,"CommFailure",mongo_base)==0)
	  return "true";
	else
	  return "false";
      }else{
	if(Utils::find_in_vector_str(segments,"BatteryLevel")==0){
	  StreamEvent ev(data::Utils::extract_StreamType(str,"BatteryLevel"));
	  //std::cout<<ev.toString()<<std::endl;
	  if(Mongodb::save_stream_event(mongo_host,mongo_port,ev,"BatteryLevel",mongo_base)==0)
	    return "true";
	  else
	    return "false";
	}else{
	  if(Utils::find_in_vector_str(segments,"Events")==0){
	    if(Mongodb::save_rule_result(mongo_host,mongo_port,str,mongo_base)==0)
	      return "true";
	    else{
	      return "false";
	    }
	  }else{
	    return "false";
	  }
	}
      }
    }
  }
  // return false;
}
