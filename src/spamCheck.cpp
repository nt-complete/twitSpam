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
	      std::cout << "http://www.twitter.com/" << username << "\n";
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

      for(std::set<std::string>::iterator it = spamSet.begin(); it != spamSet.end(); it++)
	{
	  stmtStr = "UPDATE [USERS] SET Spam = 1 WHERE userId = \"" + *it + "\"";
	  std::cout << stmtStr << "\n";
	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << *it << " has been marked as spam.\n";
	    }

	}



      for(std::set<std::string>::iterator it = notSpamSet.begin(); it != notSpamSet.end(); it++)
	{
	  stmtStr = "UPDATE [USERS] SET spam = 0 WHERE userId = \"" + *it + "\"";
	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << *it << " has been marked as not spam.\n";
	    }

	}

      for(std::set<std::string>::iterator it = deleteSet.begin(); it != deleteSet.end(); it++)
	{
	  stmtStr = "DELETE FROM [USERS] WHERE userId = \"" + *it + "\"";
	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << *it << " has been deleted from Users.\n";
	    }

	  stmtStr = "DELETE FROM [Tweets] WHERE userId = \"" + *it + "\"";
	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << *it << " has been deleted from Tweets.\n";
	    }

	  stmtStr = "DELETE FROM [Friends] WHERE userId = \"" + *it + "\" OR friendId = \"" + *it + "\"";
	  if(sqlite3_prepare_v2(database, stmtStr.c_str(), -1, &statement, 0) == SQLITE_OK)
	    {
	      sqlite3_step(statement);
	      sqlite3_finalize(statement);
	      std::cout << *it << " has been deleted from Friends.\n";
	    }

	}

      sqlite3_close(database);
    }
  else
    {
      std::cout << "Error opening database.\n";
      return 0;

    }


}
