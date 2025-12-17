#pragma once
#include <map>
#include <string>

class Interface_command {
public:
	virtual int execute(const std::map<std::string, int>& args) = 0;
	virtual ~Interface_command() = default;
};