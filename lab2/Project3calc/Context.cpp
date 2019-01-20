#include "Calculator.h"
#include <string>
#include <iostream>
#include "Context.h"
#include "Creator.h"
#include "Factory.h"
#include "Basic.h"
#include "Exceptions.h"
#include <stack>
#include <string>

using std::string;
void Context::get_arg(std::string &buffer) {
	//добавляем аргементы в лист
	int j = 0;
	string comand = "";
	for (int i = 0; i < buffer.length(); i++)
	{
		if (buffer[i] == ' ' || buffer[i + 1] == '\0')
		{
			if (buffer[i + 1] == '\0')
				i++;
			comand = buffer.substr(j, i - j);
			args.push_back(comand);
			j = i + 1;

		}
		if (comand=="PUSH" || comand=="POP" || comand=="PRINT" || comand=="SQRT")
			args.push_back(comand);
		if (comand=="+" || comand =="-" || comand == "*" || comand == "/")
		{
			args.push_back(comand);
			i++;
			comand ="";
			while (buffer[i] != ' ' || buffer [i+1] != '\0')
			{
				if (buffer[i + 1] == '\0')
					i++;
				comand = buffer.substr(j, i - j);	//пушим число
				args.push_back(comand);
				j = i + 1;
			}
			if (comand =="")
				throw empty_args();
		}
		if (comand == "DEFINE")
		{
			string What_Define ="";
			i++;
			while (buffer[i] != ' ' || buffer [i+1] != '\0')
			{
				if (buffer[i + 1] == '\0')
					throw empty_args();
				comand = buffer.substr(j, i - j);	//нашли что заменять
				j = i + 1;
			}
			if (comand =="")
				throw empty_args();
			else{
				i++;
				while (buffer[i] != ' ' || buffer [i+1] != '\0')
				{
					if (buffer[i + 1] == '\0')
						i++;
					What_Define = buffer.substr(j, i - j);	//нашли на что заменять
					j = i + 1;
				}
				if (What_Define =="")
					throw empty_args();
				else 
					context.add_var(comand, std::stod(What_Define));
			}
		}

	}
	
}

//получение первого элемента листа
std::string Context::front_() {

	return args.front();
}

//получение последнего элемента листа
std::string& Context::back_()
{
	return args.back();
}

//удаление первого элемента листа
void Context::pop_front_() {

	args.pop_front();
}

//удаление последнего элемента листа
void Context::pop_back_() {

	args.pop_back();
}

//
int Context::size_() {

	return args.size();
}

//добавление в стек значений
void Context::push_arg(double arg) {

	arg_stack.push(arg);
	stack_size++;
}

//удаление из стека значений 
void Context::pop_arg() {
	if (!size_arg())
		throw empty_stack();
	double arg = arg_stack.top();
	arg_stack.pop();
	stack_size--;
}

//возвращение размера стека
int Context::size_arg() {

	return stack_size;
}

//возвращение верхнего элемента стека
double Context::top_arg() {
	if (!size_arg())
		throw empty_stack();
	return arg_stack.top();
}


//проверка количества элементов в мапе
bool Context::is_empty_var()
{
	return variables.empty();
}


//поиск в map
double Context::find_var(std::string& name)
{
	if (!variables.size())
		throw nodefinition();
	if (variables.find(name) != variables.end())
		return variables[name];
	return DBL_MIN;
}

//добавление в map
void Context::add_var(std::string name, double value) {

	variables[name] = value;
}
