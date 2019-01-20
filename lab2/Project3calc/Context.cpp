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
			j = i + 1;

		}
		if ( comand=="POP" || comand=="PRINT" || comand=="SQRT")
			args.push_back(comand);
		if (comand=="PUSH" ||comand=="+" || comand =="-" || comand == "*" || comand == "/")
		{
			if(comand!="PUSH")
				args.push_back(comand);
			i++;
			double Number = 0;
			while (buffer[i] != ' ' || buffer [i+1] != '\0')
			{
				if (buffer[i + 1] == '\0')
					i++;
				if (!context.is_empty_var())		//поиск define
					Number = context.find_var(buffer.substr(j, i - j));
				if (Number == DBL_MIN)
				{
					//если в числе хранятся постронние символы
					if (!check(buffer.substr(j, i - j)))
						throw invalid_arg();	
					Number = std::stod(buffer.substr(j, i - j));
					
				}
				push_arg(Number);	//пушим число
				j = i + 1;
			}
			if ( Number == 0)
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
		comand ="";

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
	arg_stack.pop();
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

//функция проверки числа на наличие лишних символов
bool check(std::string buffer){
	int i = 0;
	while (buffer[i] >= 48 && buffer[i] <= 57 || buffer[i] == '.')
		i++;
	if (i == buffer.length() - 1)
		return 1;
	return 0;
}
