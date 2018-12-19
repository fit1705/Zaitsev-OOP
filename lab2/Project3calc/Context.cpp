#include "Calculator.h"
#include <string>
#include <iostream>
#include "Context.h"
#include "Creator.h"
#include "Factory.h"
#include "Basic.h"
#include "Exceptions.h"
#include <stack>

void Context::get_arg(std::string &buffer) {
	//��������� ��������� � ����
	int j = 0;
	for (int i = 0; i < buffer.length(); i++)
	{
		if (buffer[i] == ' ')
		{
			args.push_back(buffer.substr(j, i - j));
			j = i + 1;
		}

	}
	if (j < buffer.length())
		args.push_back(buffer.substr(j, buffer.length() - j));
}

//��������� ������� �������� �����
std::string Context::front_() {

	return args.front();
}

//��������� ���������� �������� �����
std::string& Context::back_()
{
	return args.back();
}

//�������� ������� �������� �����
void Context::pop_front_() {

	args.pop_front();
}

//�������� ���������� �������� �����
void Context::pop_back_() {

	args.pop_back();
}

//
int Context::size_() {

	return args.size();
}

//���������� � ���� ��������
void Context::push_arg(double arg) {

	arg_stack.push(arg);
	stack_size++;
}

//�������� �� ����� �������� 
void Context::pop_arg() {
	if (!size_arg())
		throw empty_stack();
	double arg = arg_stack.top();
	arg_stack.pop();
	stack_size--;
}

//����������� ������� �����
int Context::size_arg() {

	return stack_size;
}

//����������� �������� �������� �����
double Context::top_arg() {
	if (!size_arg())
		throw empty_stack();
	return arg_stack.top();
}


//�������� ���������� ��������� � ����
bool Context::is_empty_var()
{
	return variables.empty();
}


//����� � map
double Context::find_var(std::string& name)
{
	if (!variables.size())
		throw nodefinition();
	if (variables.find(name) != variables.end())
		return variables[name];
	return DBL_MIN;
}

//���������� � map
void Context::add_var(std::string name, double value) {

	variables[name] = value;
}