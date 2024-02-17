#include <string>

class create_statements {
public:
	static create_statements& Get() {
		static create_statements statements;
		return statements;
	}
	std::string createTasksTable = "CREATE TABLE IF NOT EXISTS tasks("
		"id INTEGER PRIMARY KEY AUTOINCREMENT,"
		"description TEXT NOT NULL,"
		"done TINYINT NOT NULL,"
		"list_loc INTEGER NOT NULL,"
		"deleted INTEGER NOT NULL DEFAULT 0"
		");";




};