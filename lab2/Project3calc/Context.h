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
	//работа с листом аргументов
	std::string front_();
	std::string& back_();
	void pop_front_();	
	void pop_back_();
	int size_();
	//работа со стеком значений
	void push_arg(double);
	void pop_arg();
	int size_arg();
	double top_arg();
	int size_arg();
	//работа с map
	bool is_empty_var();
	double find_var(std::string&);	
	void add_var(std::string, double);
};

#endif

