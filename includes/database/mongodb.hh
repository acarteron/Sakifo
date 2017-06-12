/**
 * \class database/mongodb
 *
 * \brief 
 *
 * \note 
 *
 * \author Adrien Carteron
 *
 * \version 0.1 
 *
 * \date lun. mai 29 16:22:05 CEST 2017 
 *
 * Contact: acarteron@openmailbox.org
 *
 * Created on: lun. mai 29 16:22:05 CEST 2017
 *
 *
 */

#ifndef MONGODB_HH
#define MONGODB_HH

#include "data/streamevent.hh"

#include <vector>
#include <Poco/MongoDB/Document.h>

class Mongodb{

private:
  //static const std::string db_name;

  static Poco::MongoDB::Document::Ptr build_stream_document(StreamEvent&);
public:
  /** \brief Void constructor
   * 
   * add desc 
   * 
   */
  Mongodb();

  static int save_stream_event(const std::string & ,
			       int ,
			       StreamEvent&,
			       const std::string&,
				     const std::string &);
  static int save_rule_result(const std::string & ,
			      int ,
			      const std::string&,
			      const std::string &);
  
};

#endif // MONGODB_HH
