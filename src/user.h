#include <twitcurl.h>
#include <iostream>
#include <vector>
#include <string.h>
#include <tinyxml.h>
#include <tinystr.h>


class User
{
 public:
  User(TiXmlHandle);
  std::vector<User*> m_friends;
  std::vector<User*> m_followers;
  long m_id;
  int m_friendsCount, m_followersCount;
  std::string m_name, m_screenName;
  void setFollowers(TiXmlHandle);
  void setFriends(TiXmlHandle);
  std::string printFriendNames();
  std::string getUserXML();
};

std::ostream& operator<< (std::ostream& str, User& user);
