#include "Task.h"

Task::Task(int id, std::string description, bool done, int list_loc, int deleted) : m_id(id), m_description(description), m_done(done), m_list_loc(list_loc), m_deleted(deleted) {
}

Task::~Task() {
}
