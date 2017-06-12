/**
 * \class handlepost
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date lun. mai 29 15:41:12 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: lun. mai 29 15:41:12 CEST 2017
 *
 *
 */

#ifndef HANDLEPOST_HH
#define HANDLEPOST_HH

#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/Util/ServerApplication.h>

class HandlePost: public Poco::Net::HTTPRequestHandler{

private:
  void poco_log(std::string);
  bool switch_URI(Poco::Net::HTTPServerRequest& );
  bool check_content_type(std::string,std::string);
  
  std::string mongo_host="mongostr";
  int mongo_port=27017;
  std::string mongo_base="Streams";
  
public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  HandlePost();

  void handleRequest(Poco::Net::HTTPServerRequest& , Poco::Net::HTTPServerResponse& );

};

#endif // HANDLEPOST_HH
