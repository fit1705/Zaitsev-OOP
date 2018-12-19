#pragma once

#ifndef CONTEXT_H
#define CONTEXT_H
#include <string>
#include <list>
#include <map>
#include <stack>
#include <iostream>
#include <float.h>
class Context{
	std::stack <double> arg_stack; //стек значений
	std::map <std::string, double> variables; //define map
	std::list <std::string> args; //лист аргументов
	int stack_size = 0;
public:
	
	void get_arg(std::string&);
	void pop_front_();	
	void pop_back_();
	std::string front_();
	std::string& back_();
	bool is_empty_var();
	int size_arg();
	double find_var(std::string&);
	double top_arg();
	void push_arg(double);
	void pop_arg();
	int size_();
	void add_var(std::string, double);
};

#endif

