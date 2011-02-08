#include <iostream>
#include <sqlite3.h>
#include <set>


int main()
{
  sqlite3 *database;
  sqlite3_stmt *statement;
  std::string stmtStr, username, userId;
  std::set<std::string> spamSet, notSpamSet, deleteSet;
  char input;
  

  if(sqlite3_open("../twitSpam.db", &database) == SQLITE_OK)
    {
      stmtStr = "SELECT * FROM [USERS] WHERE SPAM IS NULL";
      if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	{
	  while( sqlite3_step(statement) == SQLITE_ROW && input != 'q')
	    {
	      username = (char*)sqlite3_column_text(statement, 2);
	      userId = (char*)sqlite3_column_text(statement, 0);
	      std::cout << "http://www.twitter.com/" << username << "#!\n";
	      std::cout << "Input (s)pam, (n)ot spam, (d)elete, or (q)uit: ";
	      std::cin >> input;
	      switch(input){
	      case 's':
		std::cout << "Added to spam set!\n";
		spamSet.insert(userId);
		break;
	      case 'n':
		std::cout << "Added to not spam set!\n";
		notSpamSet.insert(userId);
		break;
	      case 'd':
		std::cout << "Added to delete set!\n";
		deleteSet.insert(userId);
		break;
	      case 'q':
		break;

	      }

	    }
	  
	}
    }
}
