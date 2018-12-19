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
		//��������� ������
		std::getline(in, buffer, '\n');
		//� ��������� ������� ���� 
		//��������� ������ �� ��������� � ���������� � ����
		context.get_arg(buffer);
		//������� ������ ������� ����� � ������� ���
		operation = context.front_();
		context.pop_front_();

		
		//������ ������� ������	
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
