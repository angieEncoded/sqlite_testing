#pragma once
#include <string>
#include <vector>

class Task {
public:
	int m_id;
	std::string m_description;
	bool m_done;
	int m_list_loc;
	int m_deleted;

	Task(int id, std::string description, bool done, int list_loc, int deleted);
	~Task();

};


