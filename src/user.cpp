#include <stdlib.h>
#include <boost/date_time.hpp>
#include "user.h"


User::User(TiXmlHandle userRootHandle)
{
  
  /** ID **/
  TiXmlNode* idRootNode = userRootHandle.FirstChild("id").ToNode();
   std::string idStr;

  if(idRootNode)
    {
      idStr = idRootNode->ToElement()->GetText();
      m_id = atol(idStr.c_str());
    }
  else
    {
      m_id = 0;
    }

  /** Name **/ 
  TiXmlNode* nameRootNode = userRootHandle.FirstChild("name").ToNode();

  if(nameRootNode)
    {

      m_name = nameRootNode->ToElement()->GetText();
    }
  else
    {
      m_name = "[Unknown Name]";
    }
  

  /** screenName **/
  
  TiXmlNode* screenNameRootNode = userRootHandle.FirstChild("screen_name").ToNode();


  if(screenNameRootNode)
    {
      m_screenName = screenNameRootNode->ToElement()->GetText();
    }
  else
    {
      m_screenName = "[Unknown Screen Name]";
    }



  /** Friends Count **/
  TiXmlNode* friendsCountRootNode = userRootHandle.FirstChild("friends_count").ToNode();
  std::string friendsCountStr;
  
  if(friendsCountRootNode)
    {
      friendsCountStr = friendsCountRootNode->ToElement()->GetText();
      m_friendsCount = atoi(friendsCountStr.c_str());
    }
  else
    {
      m_friendsCount = -1;
    }
 
  /** Followers Count **/
  TiXmlNode* followersCountRootNode = userRootHandle.FirstChild("followers_count").ToNode();
  std::string followersCountStr;
  
  if(followersCountRootNode)
    {
      followersCountStr = followersCountRootNode->ToElement()->GetText();
      m_followersCount = atoi(followersCountStr.c_str());
    }
  else
    {
      m_followersCount = -1;
    }

}


User::User()
{}

void User::setFollowers(TiXmlHandle followersRootHandle)
{
  followersRootHandle = followersRootHandle.FirstChild("users");

  for(int i = 0; i < m_followersCount; i++)
    {
      TiXmlHandle singleFollowerRootHandle = followersRootHandle.Child("user", i);
      User * tmpUser = new User(singleFollowerRootHandle);
      m_followers.push_back(tmpUser);

    }

}


void User::setFriends(TiXmlHandle friendsRootHandle)
{
  friendsRootHandle = friendsRootHandle.FirstChild("users");
  for(int i = 0; i < m_friendsCount; i++)
    {
      TiXmlHandle singleFriendRootHandle = friendsRootHandle.Child("user",i);
      if(singleFriendRootHandle.ToNode())
	{
	  User * tmpUser = new User(singleFriendRootHandle);
	  m_friends.push_back(tmpUser);
	}
    }
}


std::string User::printFriendNames()
{
  std::string friendsNamesStr;

  for(std::vector<User*>::iterator it = m_friends.begin(); 
      it != m_friends.end(); it++)
    {
      friendsNamesStr += "Friend: " + (*it)->m_name + "\n";
    }

  return friendsNamesStr;
}




std::ostream& operator<< (std::ostream& str, User& user)
{
  str << "ScreenName: " << user.m_screenName;
  str << "\nName: " << user.m_name;
  str << "\nId: " << user.m_id;
  str << "\nFriendsCount: " << user.m_friendsCount;
  str << "\nFollowersCount: " << user.m_followersCount;

  return str;
}


