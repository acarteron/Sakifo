#include "requests/request.hh"
#include <sstream>
void Request::setHeaders(std::map<std::string,std::string> headers){
  for(std::map<std::string,std::string>::iterator it = headers.begin();
      it != headers.end(); it++) {
    request.set(it->first, it->second);
  }
}
void Request::setServer(std::string url_){
  server_url=url_;
  Poco::URI uri(server_url);
  cli_session.setHost(uri.getHost());
  cli_session.setPort(uri.getPort());
  request.setVersion(Poco::Net::HTTPMessage::HTTP_1_1);
}
void Request::setPathAndQuery(std::string path){
  std::string srv=server_url;
  srv+=path;
  Poco::URI uri(srv);
  request.setURI(get_path(uri.getPathAndQuery()));
  request.setContentType("application/json");
  //std::cout<<uri.getHost()<<" "<<uri.getPathAndQuery()<<" "<<uri.getPath()<<" "<<uri.getQuery()<<std::endl;
}

void Request::setGET(){
  request.setMethod(Poco::Net::HTTPRequest::HTTP_GET);
}
void Request::setPOST(){
  request.setMethod(Poco::Net::HTTPRequest::HTTP_POST);
}
void Request::setPUT(){
  request.setMethod(Poco::Net::HTTPRequest::HTTP_PUT);
}
std::string Request::get_response(){
  // Poco::JSON::Parser parser;
  // Poco::Dynamic::Var results;

  //request.write(std::cout);

  //std::cout<<response.getStatus()<<" "<<response.getReason()<<" "<<response.getContentType()<<"  "<<std::endl;
  std::istream& rs = cli_session.receiveResponse(response);
  std::string s(std::istreambuf_iterator<char>(rs), {});
  //std::cout<<s<<std::endl;
  return s;
  // if(rs.rdstate()){
    
  //   results=parser.parse(s);
  // }
  // return results;
}
std::string Request::send_request(){
  cli_session.sendRequest(request);
  return get_response();
}
std::string Request::send_request(std::string req){
  request.setContentLength( req.length() );
  std::ostream & ostr=cli_session.sendRequest(request);
  ostr<<req;
  request.setKeepAlive(true);
  return get_response();
}

std::string Request::get_path(std::string path_){
  std::string path=path_;
  if (path.empty()) path = "/";
  return path;
}
