#include "Angie.h"
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <functional>
#include <chrono>
#include <thread>
#include <stdio.h>
#include "Database.h"
#include "sql/create_statements.h"

Angie console;

void populateDatabase() {
	// populate with dummy data
	for (int i = 0; i < 100; i++) {
		Database::Get().insertRowIntoTasks("testing.db", "whatever description doesnt matter much", i % 2 == 0, i);
	}
}



int main(int argc, char* argv[]) {
	
	console.log(argc);
	if (argc >= 1) {
		for (int i = 0; i < argc; i++) {
			console.log(argv[i]); // print out the arguments that came through
		}
	}


	//Database::Get().createDatabase("testing.db");
	//Database::Get().createTable("testTable", "testing.db", create_statements::Get().createTasksTable);
	//Database::Get().insertRowIntoTasks("testing.db", "This is a test of the description", 0, 1);
	//populateDatabase();
	//Database::Get().selectAllFromTable("testing.db", "tasks");

	// looks like CPP is a-ok with null getting sent into the constructor 
							  //id,   description, done,           list_loc, deleted, done
	Task * testTask = new Task(NULL, "Babs is getting too fat!!!", 1,        500,     0);
	std::cout << testTask->m_description << std::endl;
	
	int id = 5;
	int idToDelete = 1;
	Database::Get().updateTask("testing.db", testTask, id);
	delete testTask;

	//Database::Get().paranoidDeleteTaskById("testing.db", idToDelete);
	//Database::Get().selectTaskById("testing.db", "tasks", 5);
	//Database::Get().selectAllDeletedFromTable("testing.db", "tasks");
	


	//console.log("test");

}
