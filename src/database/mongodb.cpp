#include "database/mongodb.hh"
#include "data/Utils.hpp"
#include "Utils.hpp"

#include <Poco/MongoDB/MongoDB.h>
#include <Poco/MongoDB/Connection.h>
#include <Poco/MongoDB/Database.h>
#include <Poco/MongoDB/Cursor.h>
#include <Poco/MongoDB/Array.h>
#include <Poco/MongoDB/Element.h>

#include <Poco/Dynamic/Var.h>
#include <Poco/JSON/JSON.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Array.h>

#include <iostream>

//const std::string Mongodb::db_name="Streams-tests";


Poco::MongoDB::Document::Ptr Mongodb::build_stream_document(StreamEvent& se){
  Poco::MongoDB::Document::Ptr roleDoc=new Poco::MongoDB::Document;
  roleDoc->add("location",se.getLocation());
  roleDoc->add("kind",se.getKind());
  Poco::MongoDB::Document::Ptr stream=new Poco::MongoDB::Document;
  stream->add("role",roleDoc);
  stream->add("status",se.getStatus());
  stream->add("timestamp",(long)se.getTimestamp());
  stream->add("user",se.getUser());
  return stream;
}

Mongodb::Mongodb(){
}

int Mongodb::save_stream_event(const std::string & host,
			       int port,
			       StreamEvent & se,
			       const std::string& streamname,
			       const std::string & db_name){
      
  Poco::MongoDB::Connection connection(host, port);
  try{
    Poco::MongoDB::Database db(db_name);
    Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertStreamRequest = db.createInsertRequest("_"+se.getUser());
    
    insertStreamRequest->addNewDocument()
      .add(streamname,build_stream_document(se));

    Poco::MongoDB::Document::Vector vect=insertStreamRequest->documents();
    connection.sendRequest(*insertStreamRequest);
    //std::cout<<streamname<<" "<< stream->toString()<<std::endl;
    std::string lastError = db.getLastError(connection);
    if (!lastError.empty()){
      std::cout << "Last Error: " << db.getLastError(connection) << std::endl;
      return -2;
    }
    return 0;
  }
  catch (Poco::Exception& exc){
    std::cerr << exc.displayText() << std::endl;
    return -1;
  }
}
int Mongodb::save_rule_result(const std::string & host,
			      int port,
			      const std::string & rule_streams,
			      const std::string & db_name){
  std::cout<<rule_streams<<std::endl;
  //decrypt rule_stream
  Poco::JSON::Parser      parser;
  Poco::Dynamic::Var      str_var;
  Poco::JSON::Object::Ptr str_obj;
  Poco::Dynamic::Var      ruletimestamp_var;
  Poco::JSON::Object::Ptr rule_obj;
  Poco::Dynamic::Var      rule_var;
  Poco::JSON::Array::Ptr  event_array;
  Poco::Dynamic::Var      event_var;
  str_var = parser.parse(rule_streams);
  parser.reset();
  str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
  ruletimestamp_var = str_obj->get("timestamp");
  rule_var = str_obj->get("rule");
  event_var = str_obj->get("events");
  event_array = event_var.extract<Poco::JSON::Array::Ptr>();
  //std::cout<<ruletimestamp_var.toString()<<" "<<rule_var.toString()<<std::endl;
  Poco::MongoDB::Array::Ptr stream_array = new Poco::MongoDB::Array();
  std::string user="";
  Poco::Dynamic::Array da = *event_array;
  for(size_t i(0);i<da.size();++i){
    //std::cout<<da[i].toString()<<std::endl;
    str_var = parser.parse(da[i].toString());
    parser.reset();
    str_obj = str_var.extract<Poco::JSON::Object::Ptr>();
    std::vector < std::string > names;
    str_obj->getNames(names);
    for(size_t j(0);j<names.size();++j){
      event_var.empty();
      event_var=str_obj->get(names[j]);
      //std::cout<<"name "<<j<<" : "<<names[j]<<std::endl;
      StreamEvent ev(event_var.toString());
      user=ev.getUser();
      //std::cout<<ev.toString()<<std::endl;
      Poco::MongoDB::Document::Ptr doc = new Poco::MongoDB::Document();
      doc=build_stream_document(ev);
      // std::cout<<"lolilol"<<doc->toString()<<std::endl;
      Poco::MongoDB::Document::Ptr Se = new Poco::MongoDB::Document();
      Se->add(names[j],doc);
      
      stream_array->add(names[j],Se);
    }
  }
  
  Poco::MongoDB::Connection connection(host, port);
  try{
    Poco::MongoDB::Database db(db_name);
    Poco::SharedPtr<Poco::MongoDB::InsertRequest> insertStreamRequest = db.createInsertRequest("_"+user);
    insertStreamRequest->addNewDocument()
      .add("rule",rule_var.toString())
      .add("timestamp",(long)Utils::stringTo<long>(ruletimestamp_var.toString()))
      .add("events",stream_array);
    connection.sendRequest(*insertStreamRequest);    
    std::string lastError = db.getLastError(connection);
    if (!lastError.empty()){
      std::cout << "Last Error: " << db.getLastError(connection) << std::endl;
      return -2;
    }
    return 0;
  }
  catch (Poco::Exception& exc){
    std::cerr << exc.displayText() << std::endl;
    return -1;
  }
}
