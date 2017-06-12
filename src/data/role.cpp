#include "data/role.hh"

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>

Role::Role(std::string kind_,std::string location_){
  location=location_;
  kind=kind_;
}
void Role::create(std::string role_str,unsigned int mod){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      role_var;
  Poco::JSON::Object::Ptr role_obj;
  Poco::Dynamic::Var      location_var;
  Poco::Dynamic::Var      kind_var;
  switch(mod){
  default:
    role_var = parser.parse(role_str);
    parser.reset();
    role_obj = role_var.extract<Poco::JSON::Object::Ptr>();
    location_var = role_obj->get("location");
    kind_var = role_obj->get("kind");
    location=location_var.toString();
    kind=kind_var.toString();
  }
}
Role::Role(std::string role_str){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Object::Ptr str_obj;
  Poco::Dynamic::Var      streamevent_var;
  Poco::JSON::Object::Ptr streamevent_obj;
  Poco::Dynamic::Var      role_var;
  Poco::JSON::Object::Ptr role_obj;
  Poco::Dynamic::Var      status_var;
  Poco::Dynamic::Var      timestamp_var;
  Poco::Dynamic::Var      user_var;

  // str_var = parser.parse(role_str);
  // parser.reset();
  // str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
  // streamevent_var = str_obj->get("StreamEvent");
  // streamevent_obj = streamevent_var.extract<Poco::JSON::Object::Ptr>();  
  // role_var = streamevent_obj->get("Role");
  // role_obj = role_var.extract<Poco::JSON::Object::Ptr>();
    create(role_str/*.toString()*/,0);
}
Role& Role::affect(const Role &role_){
  kind=role_.kind;
  location=role_.location;
  return *this;
}


std::string Role::getLocation()const{return location;}
std::string Role::getKind()const{return kind;}
bool Role::equals(const Role & role_){
  return getLocation().compare(role_.getLocation())==0 && getKind().compare(role_.getKind())==0;
}
std::string Role::toString(){
  return "\"Role\":{\"location\":\""+location+"\",\"kind\":\""+kind+"\"}";
}

Role& Role::operator=(const Role & role_){
  return affect(role_);
}
bool Role::operator<(const Role& role_){
  if(getLocation().compare(role_.getLocation())<0)
    return true;
  else{
    if(getLocation().compare(role_.getLocation())==0)
      if(getKind().compare(role_.getKind())<0)
	return true;
  }
  return false;
}
