/**
 * \class request
 *
 * \brief 
 *
 * \note 
 *
 * \author : Adrien Carteron$
 *
 * \version : 0.1 $
 *
 * \date : jeu. déc. 10 11:36:35 CET 2015 $
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: jeu. déc. 10 11:36:35 CET 2015
 *
 *
 */

#ifndef REQUEST_HH
#define REQUEST_HH

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/Net/HTTPCredentials.h>
#include <Poco/Net/HTMLForm.h>
#include <Poco/StreamCopier.h>
#include <Poco/NullStream.h>
#include <Poco/Path.h>
#include <Poco/URI.h>
#include <Poco/Exception.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/Dynamic/Var.h>
#include <map>

class Request{

private:
  Poco::Net::HTTPClientSession cli_session;
  Poco::Net::HTTPRequest request;
  Poco::Net::HTTPResponse response; 
  
  std::string get_path(std::string);
  std::string server_url;
  std::string get_response();
public:

  void setHeaders(std::map<std::string,std::string>);
  void setServer(std::string);
  void setPathAndQuery(std::string);
  void setGET();
  void setPOST();
  void setPUT();

  //void set
  void init(std::string);
  std::string send_request();
  std::string send_request(std::string);
  

  
};

#endif // REQUEST_HH
