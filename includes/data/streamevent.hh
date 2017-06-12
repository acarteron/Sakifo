#ifndef STREAMEVENT_HH
#define STREAMEVENT_HH

#include "data/role.hh"
#include "data/event.hh"

#include <memory>

class StreamEvent{

private:
  std::shared_ptr<Event> event;
  std::shared_ptr<Role> role;
  
  StreamEvent& affect(const StreamEvent &);
  
public:
  StreamEvent();
  StreamEvent(std::string);
  StreamEvent(std::shared_ptr<Event>,std::shared_ptr<Role>);
  StreamEvent(const StreamEvent &);
  
  unsigned long getTimestamp();
  unsigned long getDailyTime();
  std::shared_ptr<Time> getTime();

  std::string getStatus();
  std::string getLocation();
  std::shared_ptr<Role> getRole(){return role;}
  std::string getKind();
  std::string getUser();
  bool equals(StreamEvent);
  std::string toString();
};


#endif // STREAMEVENT_HH
