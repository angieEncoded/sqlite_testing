#include "database.h"
#include <sqlite3.h>
#include <string>
#include <iostream>
#include <stdio.h>
#include <format> // CPP 20...
#include "Task.h"

// helper function
static int callback(void* NotUsed, int argc, char** argv, char** azColName) {
    for (int i = 0; i < argc; i++) {
        std::cout << azColName[i] << ": " << argv[i] << std::endl;
    }
    std::cout << std::endl;
    return 0;
};


int Database::createDatabase(const char* dbname) {
    sqlite3* db;
    int exit = 0;
    exit = sqlite3_open(dbname, &db);
    sqlite3_close(db);
    return 0;
}

int Database::createTable(const char *tablename, const char *dbname, std::string query) {
    sqlite3* db;

    try {
        int exit = 0;
        exit = sqlite3_open(dbname, &db);

        char* messageError;
        exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);

        if (exit != SQLITE_OK) {
            std::cerr << "Error creating table:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        } else {
            std::cout << "Table created successfully" << std::endl;
        }
        sqlite3_close(db);
    } catch (const std::exception & error) {
        std::cerr << error.what() << std::endl;;
    }

    return 0;
}

int Database::insertRowIntoTasks(const char* dbname, const char* description, int done, int list_loc) {

    // TODO - some cleaning up of the incoming data, ensure safe characters, etc.

    sqlite3 * db;

    try {
        int exit = 0;
        char* messageError;
        exit = sqlite3_open(dbname, &db);
    
        // create the sql statement
        std::string query = std::format("INSERT INTO tasks (description, done, list_loc) VALUES ('{}', '{}', '{}')", description, done, list_loc); // cpp 20, most similar to javascript string interpolation

        exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error creating record:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        } else {
            std::cout << "Record created successfully" << std::endl;
        }
        sqlite3_close(db);
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;;
    }

    return 0;
}

int Database::selectAllFromTable(const char* dbname, const char* tablename) {
    sqlite3* db;

    try {

        int exit = 0;
        char* messageError;
        exit = sqlite3_open(dbname, &db);

        std::string query = std::format("select * from '{}' WHERE deleted = 0;", tablename); // get the data from the tablename

        // database handle, sql query, the callback, 1st arg to callback, error message
        exit = sqlite3_exec(db, query.c_str(), callback, NULL, &messageError);  
        if (exit != SQLITE_OK) {
            std::cerr << "Error querying the database:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        }
        sqlite3_close(db);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
}

int Database::updateTask(const char* dbname, Task const *task, int id) {
    sqlite3* db;
    try {
        char* messageError;
        int exit = sqlite3_open(dbname, &db);
        std::string query = std::format("UPDATE tasks SET description = '{}', done = '{}', list_loc = '{}', deleted = '{}' WHERE id = '{}'", task->m_description, (int)task->m_done, task->m_list_loc, task->m_deleted, id);
        std::cout << query << std::endl;
        //return 0;
        exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error querying the database:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        }
        sqlite3_close(db);
        return 0;

    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }
}

int Database::paranoidDeleteTaskById(const char* dbname, int id) {
    sqlite3* db;
    try {
        char* messageError;
        int exit = sqlite3_open(dbname, &db);
        std::string query = std::format("UPDATE tasks SET deleted = '1' WHERE id = '{}'", id);
        exit = sqlite3_exec(db, query.c_str(), NULL, 0, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error deleting the record:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        }
        sqlite3_close(db);
        return 0;

    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    return 0;
}

int Database::selectTaskById(const char* dbname, const char * tablename, int id) {
    sqlite3* db;

    try {

        int exit = 0;
        char* messageError;
        exit = sqlite3_open(dbname, &db);

        std::string query = std::format("select * from '{}' WHERE id = '{}';", tablename, id); // get the data from the tablename

        // database handle, sql query, the callback, 1st arg to callback, error message
        exit = sqlite3_exec(db, query.c_str(), callback, NULL, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error querying the database:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        }
        sqlite3_close(db);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }

    return 0;
}

int Database::selectAllDeletedFromTable(const char* dbname, const char* tablename) {

    sqlite3* db;

    try {

        int exit = 0;
        char* messageError;
        exit = sqlite3_open(dbname, &db);

        std::string query = std::format("select * from '{}' WHERE deleted = 1;", tablename); // get the data from the tablename

        // database handle, sql query, the callback, 1st arg to callback, error message
        exit = sqlite3_exec(db, query.c_str(), callback, NULL, &messageError);
        if (exit != SQLITE_OK) {
            std::cerr << "Error querying the database:\n" << messageError << std::endl;
            sqlite3_free(messageError);
        }
        sqlite3_close(db);
        return 0;
    } catch (const std::exception& error) {
        std::cerr << error.what() << std::endl;
        return 1;
    }




    return 0;
}


//int sqlite3_prepare_v2(
    //sqlite3* db,            /* Database handle */
    //const char* zSql,       /* SQL statement, UTF-8 encoded */
    //int nByte,              /* Maximum length of zSql in bytes. */
    //sqlite3_stmt** ppStmt,  /* OUT: Statement handle */
    //const char** pzTail     /* OUT: Pointer to unused portion of zSql */
//);



int Database::insertRowIntoTasksPreparedStatement(const char* dbname, const char* tablename, Task const* task) {









    return 0;
}



