/**
 * \class requests/handledelete
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date mar. mai 30 09:58:55 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: mar. mai 30 09:58:55 CEST 2017
 *
 *
 */

#ifndef HANDLEDELETE_HH
#define HANDLEDELETE_HH

#include <utility>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Util/ServerApplication.h>
#include "libAlainPeters.hh"

class HandleDelete: public Poco::Net::HTTPRequestHandler{

private:
  libAlainPeters liba;
  void poco_log(std::string);
  std::pair<std::string,std::string> switch_URI(Poco::Net::HTTPServerRequest& );

  std::string mongo_host="mongostr";
  int mongo_port=27017;
  std::string mongo_stream_base="Streams";
  std::string mongo_rule_base="rules";

  std::string remove_rule(std::string);
  

public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  HandleDelete();

  void handleRequest(Poco::Net::HTTPServerRequest& , Poco::Net::HTTPServerResponse& );

};

#endif // HANDLEDELETE_HH
