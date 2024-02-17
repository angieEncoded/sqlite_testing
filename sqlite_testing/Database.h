#pragma once
#include <string>
#include "Task.h"
class Database {


public:
	// single instance of this class, this is a static class
	static Database& Get() {
		static Database instance;
		return instance;
	}

	int createDatabase(const char* dbname);
	int createTable(const char* tablename, const char * dbname, std::string query);
	int insertRowIntoTasks(const char* dbname, const char* description, int done, int list_loc);
	int selectAllFromTable(const char* dbname, const char* tablename);
	int updateTask(const char* dbname, Task const *task, int id);
	int paranoidDeleteTaskById(const char* dbname, int id);
	int selectTaskById(const char* dbname, const char * tablename, int id);
	int selectAllDeletedFromTable(const char* dbname, const char* tablename);
	int insertRowIntoTasksPreparedStatement(const char* dbname, const char* tablename, Task const* task);


};

