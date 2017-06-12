#include "requests/requesthandlerfactory.hh"

#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/MessageHeader.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Exception.h>
#include <Poco/Util/ServerApplication.h>
#include <Poco/Util/Option.h>
#include <Poco/Util/OptionSet.h>
#include <Poco/Util/HelpFormatter.h>

#include <iostream>

#include "libAlainPeters.hh"

class HTTPFormServer: public Poco::Util::ServerApplication{
public:
  HTTPFormServer(): _helpRequested(false){
  }	
  ~HTTPFormServer(){
  }

protected:
  void initialize(Application& self){
    loadConfiguration(); // load default configuration files, if present
    ServerApplication::initialize(self);
  }
		
  void uninitialize(){
    ServerApplication::uninitialize();
  }

  void defineOptions(Poco::Util::OptionSet& options){
    ServerApplication::defineOptions(options);		
    options.addOption(
		      Poco::Util::Option("help", "h", "display help information on command line arguments")
		      .required(false)
		      .repeatable(false));
  }

  void handleOption(const std::string& name, const std::string& value){
    ServerApplication::handleOption(name, value);

    if (name == "help")
      _helpRequested = true;
  }

  void displayHelp(){
    Poco::Util::HelpFormatter helpFormatter(options());
    helpFormatter.setCommand(commandName());
    helpFormatter.setUsage("OPTIONS");
    helpFormatter.setHeader("A web server that shows how to work with HTML forms.");
    helpFormatter.format(std::cout);
  }

  int main(const std::vector<std::string>& args){
    if (_helpRequested){
      displayHelp();
    }
    else{		 
      unsigned short port = (unsigned short) config().getInt("HTTPFormServer.port", 9089);		
      // set-up a server socket
      Poco::Net::ServerSocket svs(port);
      // set-up a HTTPServer instance
      Poco::Net::HTTPServer srv(new RequestHandlerFactory, svs, new Poco::Net::HTTPServerParams);
      // start the HTTPServer
      srv.start();
      // wait for CTRL-C or kill
      waitForTerminationRequest();		
      // Stop the HTTPServer
      srv.stop();
    }
    return Application::EXIT_OK;
  }
	
private:
  bool _helpRequested;
  
};


int main(int argc, char** argv){
  HTTPFormServer app;
  return app.run(argc, argv);
}
/** \mainpage : 
 * \author adcarter
 * \version : 0.0 $
 * \date : lun. mai 29 10:39:17 CEST 2017 $
 * \section intro_sec Introduction
 * Contact: acarteron@openmailbox.org
 * Created on: lun. mai 29 10:39:17 CEST 2017
 *
 * \section install_sec Installation
 *
 * This is f***** easy
 *
 * \subsection step1 Step 1 : Compile
 *
 *  Run this command to the project root
 *  <br/>
 *  <code>make</code>
 *
 * \subsection step2 Step 2 : Launch
 *
 *  Compiled program can be found in the subfolder <code>./bin</code>, it is called <code></code>.
 * 
 *  \subsection step3 Step 3 : Otherwise
 *  
 *  You can read the file <code>README.RTFM</code> if it exists
 */

