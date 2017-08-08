#include "requests/handleget.hh"
#include "Tools.hpp"
#include "files/files.hh"
#include <Poco/URI.h>

#include <iostream>

#include "html/html.hh"
#include "data/time.hh"

#include "database/mongodb.hh"

HandleGet::HandleGet(){
  Files file("/opt/Sati/db.json");
  std::string db_param=file.readFile();
  file.closeFile();
  
  nlohmann::json j=nlohmann::json::parse(db_param);
  mongo_host=j["mongo_host"].get<std::string>();
  mongo_port=j["mongo_port"].get<int>();
  mongo_stream_base=j["streams_collection"].get<std::string>();
  mongo_rule_base=j["rules_collection"].get<std::string>();
}

void HandleGet::handleRequest(Poco::Net::HTTPServerRequest& request,
			      Poco::Net::HTTPServerResponse& response){
  poco_log("Request from " + request.clientAddress().toString()+" URI: "+request.getURI()+" content-type : "+request.getContentType());
  
  Poco::Net::HTMLForm form(request, request.stream()/*, partHandler*/);

  std::pair<std::string,std::string> res=switch_URI(request);
  
  response.setChunkedTransferEncoding(true);
  response.setContentType(res.first);
  std::ostream& ostr = response.send();
  ostr << res.second;
}
void HandleGet::poco_log(std::string log_){
  Poco::Util::Application& app = Poco::Util::Application::instance();
  app.logger().information(log_);
}

std::pair<std::string,std::string> HandleGet::switch_URI(Poco::Net::HTTPServerRequest& request){
  std::string URI_=request.getURI();
  // do a find rule in segment
  Poco::URI uri(request.getURI());
  std::vector < std::string >  segments;
  uri.getPathSegments(segments);
  // for(size_t i(0);i<segments.size();++i)
  //   std::cout<<"segments: "<<segments[i]<<std::endl;

  if(segments.size()==0){
    return std::make_pair("text/html",main_page());
  }
  
  if(segments[0].compare("summary")==0&&segments.size()==2){
    // Time hoi(segments[1],"00:00:00.000");
    // Time yesterday(hoi.get_timestamp_ms()-86400000);
    // std::cout<<"     "<<yesterday.get_day_str()<<std::endl;
    liba.do_what_you_do(segments[1]/*yesterday.get_day_str()*/);
    return std::make_pair("application/json",
			  liba.getDailyReport_as_string());
  }else{
    if(segments[0].compare("rulemanager")==0){
      return std::make_pair("text/html",rulemanager_page());
    }else{
      if(segments[0].compare("rules")==0){
	return std::make_pair("text/html",get_rule_list());
      }
    }
  }
  
  return get_file(URI_);
}
std::string HandleGet::get_rule_list(){
  std::string rule_col=apeters::Mongodb::get_collections(mongo_host,
							 mongo_port,
							 mongo_rule_base);
  nlohmann::json j=nlohmann::json::parse(rule_col);
  nlohmann::json::iterator it = j.begin();
  std::string rule_lst="[]";
  if(it!=j.end())
    rule_lst=apeters::Mongodb::get_rules(mongo_host,
					 mongo_port,
					 it.value().get<std::string>(),
					 mongo_rule_base);
  return "{\"rules\":"+rule_lst+"}";
}

std::pair<std::string,std::string> HandleGet::get_file(const std::string& path_){
  Files file;
  std::string file_path=".";
  std::string content_type="";
  if(path_.find("css")!=std::string::npos){
    content_type="text/css";
  }else{
    if(path_.find("js")!=std::string::npos)
      content_type="application/javascript";
    else{
      if(path_.find("html")!=std::string::npos)
        content_type="text/html";
      else{
        content_type="text/html";
      }
    }
  }
  if(path_.find("/libs")==std::string::npos)
    file_path+="/libs";
  file_path+=path_;
  file.setFileName(file_path);
  return std::make_pair(content_type,file.readFile());
}

std::string HandleGet::rulemanager_page(){
  html page; 
  page.set_head("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
  page.set_head("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">");
  page.set_head("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  page.set_head("<title>Zamzama</title>\n");

  page.set_head("<script src=\"js/vendor/modernizr-2.8.3-respond-1.4.2.min.js\"></script>");
  
  page.set_css_link("//maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css");
  page.set_css_link("https://cdn.rawgit.com/FezVrasta/dropdown.js/master/jquery.dropdown.css");

  page.set_css_link("//fezvrasta.github.io/snackbarjs/dist/snackbar.min.css");
  page.set_script_link("//code.jquery.com/jquery-1.10.2.min.js");

  page.set_script_link("libs/js/Utils.js");
  page.set_script_link("libs/js/summary.js");
  page.set_script_link("libs/js/Modal.js");
  page.set_script_link("libs/js/Formular.js");
  page.set_script_link("libs/js/rulemanagement.js");

  
  page.set_script_link("https://cdnjs.cloudflare.com/ajax/libs/numeric/1.2.6/numeric.min.js");

  page.set_css_link("libs/css/bootstrap-material-design.css");
  page.set_css_link("libs/css/ripples.min.css");
  page.set_css_link("libs/css/loading.css");
  page.set_css_link("libs/css/own.css");

  // page.set_css_link("libs/css/roboto.css");

  std::string begin="<html class=\"no-js\">";
  begin+=page.get_head();
  //<body onload="loadUsers() ">
  std::string body=R"(
<body >
<div class="container-fluid main">
<div class="row"> 


<div class="navbar navbar-default">
  <div class="container-fluid">
    <div class="navbar-header">
      <button type="button" class="navbar-toggle" data-toggle="collapse" data-target=".navbar-responsive-collapse">
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href="rulemanager">Zamzama</a>
    </div>
    <div class="navbar-collapse collapse navbar-responsive-collapse">
      <ul class="nav navbar-nav">
        <li><a href="/rulemanager">Add rule</a></li>
        <li><a href="javascript:void(0) ">Edit rule</a></li>
        <li><a href="javascript:removeRules() ">Remove rule</a></li>
      </ul>
    </div>
  </div>
</div>
<div id="about" class="well page active">

<div id="rulemngr">
<div class="panel panel-default"><div class="panel-heading">
<h4 class="panel-title">Write rule</h4></div>
<div class="container-fluid">
<div class="togglebutton">
              <label>
                Force write rule
                <input type="checkbox" id="fwrite" checked>
              </label>
            </div>
<div class="form-group label-floating">
    <label for="Nameform" class="control-label">Rule name</label>
    <input class="form-control" id="Nameform" type="text">
  </div>
<div class="form-group label-floating">
    <label for="ASTform" class="control-label">AST form rule</label>
    <input class="form-control" id="ASTform" type="text">
    <span class="help-block">code style <code>Operator(Operator(leaf,leaf),leaf)</code></span>
  </div>
<div class="form-group label-floating">
<label for="EPLform" class="control-label">EPL Esper form rule</label>
        <textarea class="form-control" rows="10" id="EPLform"></textarea>
        <span class="help-block">code style <code>select things from pattern [ sequences ]</code></span>
      </div>
<a href="javascript:loadRuleAST() " class="btn btn-raised btn-default">Compile</a>
</div>
</div>
</div>
  <div id="demo">

</div>
</div>
</div>
</div>

<div id="modals">
</div>
    <script type="application/javascript" src="//cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.6/js/bootstrap.min.js"></script>
    <script type="application/javascript" src="https://cdn.rawgit.com/FezVrasta/dropdown.js/master/jquery.dropdown.js"></script>
    <script type="application/javascript" src="libs/js/material.js"></script>
    <script type="application/javascript" src="libs/js/ripples.min.js"></script>
     <script>
    	$.material.init();
  </script>
    </body></html>
      )";  
begin+=body;
return begin;
}



std::string HandleGet::main_page(){
  html page;
  std::string today=Utils::getDay();
  Time hoi(today,"00:00:00.000");
  Time yesterday(hoi.get_timestamp_ms()-86400000);

  
  page.set_head("<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n");
  page.set_head("<meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge,chrome=1\">");
  page.set_head("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\">");
  page.set_head("<title>Sakifo</title>\n");

  page.set_head("<script src=\"js/vendor/modernizr-2.8.3-respond-1.4.2.min.js\"></script>");
  
  page.set_css_link("//maxcdn.bootstrapcdn.com/bootstrap/3.3.6/css/bootstrap.min.css");
  page.set_css_link("https://cdn.rawgit.com/FezVrasta/dropdown.js/master/jquery.dropdown.css");

  page.set_css_link("//fezvrasta.github.io/snackbarjs/dist/snackbar.min.css");
  page.set_script_link("//code.jquery.com/jquery-1.10.2.min.js");

  page.set_script_link("libs/js/Utils.js");
  page.set_script_link("libs/js/summary.js");
  
  page.set_script_link("https://cdnjs.cloudflare.com/ajax/libs/numeric/1.2.6/numeric.min.js");

  page.set_css_link("libs/css/bootstrap-material-design.css");
  page.set_css_link("libs/css/ripples.min.css");
  page.set_css_link("libs/css/loading.css");

  // page.set_css_link("libs/css/roboto.css");

  std::string begin="<html class=\"no-js\">";
  begin+=page.get_head();
  //<body onload="loadUsers() ">
  std::string body=R"(
<body >
<div class="container-fluid main">
<div class="row"> 
<div id="about" class="well page active">
  <ul class="pager">
  <li class="previous"><a class="withripple" href="javascript:getPrev() ">← Older</a></li><li><h2><div id=date_yesterday>)";
  // std::string title=yesterday.get_day_str();


     std::string body2=R"(
</div></h2></li>
  <li class="next"><a class="withripple" href="javascript:getNext() ">Newer →</a></li>
</ul>
  <div id="demo">
</div>
</div>
</div>
</div>
<div id="modals">
</div>
    <script type="application/javascript" src="//cdnjs.cloudflare.com/ajax/libs/twitter-bootstrap/3.3.6/js/bootstrap.min.js"></script>
    <script type="application/javascript" src="https://cdn.rawgit.com/FezVrasta/dropdown.js/master/jquery.dropdown.js"></script>
    <script type="application/javascript" src="libs/js/material.js"></script>
    <script type="application/javascript" src="libs/js/ripples.min.js"></script>
     <script>
    	$.material.init();
     loadWhatTheShit();
  </script>
    </body></html>
      )";  
begin+=body+body2;
return begin;
}
