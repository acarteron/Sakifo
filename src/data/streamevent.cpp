#include "data/streamevent.hh"

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include "Utils.hpp"


StreamEvent& StreamEvent::affect(const StreamEvent & streamevent_){
  role=streamevent_.role;
  event=streamevent_.event;
  return * this;
}

StreamEvent::StreamEvent(){
  role=nullptr;
  event=nullptr;
}

StreamEvent::StreamEvent(std::shared_ptr<Event> event_,
	    std::shared_ptr<Role> role_){
  event=event_;
  role=role_;
}

StreamEvent::StreamEvent(std::string streamevent_str){
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Object::Ptr str_obj;
  Poco::Dynamic::Var      streamevent_var;
  Poco::JSON::Object::Ptr streamevent_obj;
  Poco::Dynamic::Var      role_var;
  Poco::JSON::Object::Ptr role_obj;
  // Poco::Dynamic::Var      status_var;
  // Poco::Dynamic::Var      timestamp_var;
  // Poco::Dynamic::Var      user_var;
  str_var = parser.parse(streamevent_str);
  parser.reset();
  str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
  // streamevent_var = str_obj->get("StreamEvent");
  // streamevent_obj = streamevent_var.extract<Poco::JSON::Object::Ptr>();  
  role_var = str_obj->get("Role");//streamevent_obj->get("Role");
  role_obj = role_var.extract<Poco::JSON::Object::Ptr>();
  
  // status_var= str_obj->get("status");
  // timestamp_var= str_obj->get("timestamp");
  // user_var= str_obj->get("user");
  
  role=std::make_shared<Role>(Role(role_var.toString()));
  
  event=std::make_shared<Event>(streamevent_str);

  // status=status_var.toString();
  // timestamp=Time(Utils::stringTo<unsigned long>(timestamp_var.toString()));
  // user=user_var.toString();
}

StreamEvent::StreamEvent(const StreamEvent & streamevent_){
  affect(streamevent_);
}

unsigned long StreamEvent::getTimestamp(){return event->getTimestamp();}
unsigned long StreamEvent::getDailyTime(){return event->getDailyTime();}
std::shared_ptr<Time> StreamEvent::getTime(){
  return event->getTime();
}

std::string StreamEvent::getUser(){return event!=nullptr?event->getUser():"";}
std::string StreamEvent::getStatus(){return event!=nullptr?event->getStatus():"";}
std::string StreamEvent::getLocation(){return role!=nullptr?role->getLocation():"";}
std::string StreamEvent::getKind(){return role!=nullptr?role->getKind():"";}
bool StreamEvent::equals(StreamEvent se_){
  if(role==nullptr&&se_.role==nullptr&&event==nullptr&&se_.event==nullptr)
    return true;
  else{
    if(role==nullptr||se_.role==nullptr||event==nullptr||se_.event==nullptr)
      return false;
  }
  return role->equals(*(se_.role)) &&
    event->equals(*(se_.event));
}

std::string StreamEvent::toString(){
  return "{\"StreamEvent\":{"+role->toString()+",\"status\":\""+getStatus()+"\",\"timestamp\":\""+Utils::toString<unsigned long>(getTimestamp())+"\",\"user\":\""+getUser()+"\"}}";
}
