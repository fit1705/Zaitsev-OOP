#include "Calculator.h"
#include <string>
#include <iostream>
#include "Context.h"
#include "Creator.h"
#include "Factory.h"
#include "Basic.h"
#include "Exceptions.h"

void Calculator::complete(std::ifstream &in, std::ofstream &out) {
	
	Context context;
	std::string buffer, operation;
	OperatorCreater creator;
	while (!in.eof()) {
		//считываем строку
		std::getline(in, buffer, '\n');
		//в контексте создает лист 
		//разбивает строку на аргументы и записывает в лист
		context.get_arg(buffer);
		//достаем первый элемент листа и удаляем его
		operation = context.front_();
		context.pop_front_();

		
		//первый элемент строки	
		if (operation.front() != '#') {
			try {

				std::auto_ptr<Operator> some_oper(Factory::get_instance()->get_operator(operation));
				some_oper->make_operation(context);
			}
			catch (calc_except& exc)
			{
				out << exc.what() << "\n";
			}
			
		}

	}
		
}
