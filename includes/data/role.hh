#ifndef ROLE_HH
#define ROLE_HH

#include <string>


class Role {

private:
  std::string location;
  std::string kind;
  Role& affect(const Role &);
  void create(std::string,unsigned int);

public:
  Role(){}

  Role(std::string);

  Role(std::string,std::string);
  std::string getLocation() const;
  std::string getKind() const;
  bool equals(const Role&);
  std::string toString();
  
  Role& operator=(const Role &);
  bool operator<(const Role&);

};

#endif // ROLE_HH
