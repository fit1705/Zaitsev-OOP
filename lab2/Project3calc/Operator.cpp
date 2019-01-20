#include "Basic.h"
#include <math.h>
#include <string>
#include "Factory.h"
#include "Exceptions.h"
#include "Creator.h"

namespace {
	bool add_commands() noexcept
	{
		AddCreator* add = new AddCreator;
		Factory::get_instance()->make_command("+", add);
		SubCreator* sub = new SubCreator;
		Factory::get_instance()->make_command("-", sub);
		MulCreator* mul = new MulCreator;
		Factory::get_instance()->make_command("*", mul);
		DivCreator* div = new DivCreator;
		Factory::get_instance()->make_command("/", div);
		SqrtCreator* sqrt = new SqrtCreator;
		Factory::get_instance()->make_command("SQRT", sqrt);
		PopCreator* pop = new PopCreator;
		Factory::get_instance()->make_command("POP", pop);
		PrintCreator* print = new PrintCreator;
		Factory::get_instance()->make_command("PRINT", print);
		return 1;
	}

	bool fake = add_commands();
}

//функция проверки числа на наличие лишних символов
void Pop::make_operation(Context& context){
	//если пустой стек
	if (context.size_arg() <= 0)
		throw empty_stack();
	context.pop_arg();
	context.pop_back_();
}

void Print::make_operation(Context& context){
	//если пустой стек
	if (!context.size_arg())
		throw empty_stack();
	std::cout << context.top_arg();
	context.pop_back_();
}


void Add::make_operation(Context& context){
	//если не хватает аргументов для операции
	if (context.size_() < 1 || context.size_arg() < 2)
		throw empty_args();
	double Number = context.top_arg();
	context.pop_arg();
	context.pop_back_();
	context.push_arg(Number + context.top_arg);
	context.pop_arg();
}


void Subtract::make_operation(Context& context) {
	
	//если не хватает аргументов для операции
	if (context.size_() < 1 || context.size_arg() < 2)
		throw empty_args();
	double Number = context.top_arg();
	context.pop_arg();
	context.pop_back_();
	context.push_arg(context.top_arg() - Number);
	context.pop_arg();
}


void Multiplicate::make_operation(Context& context) {
	if (context.size_() < 1 || context.size_arg() < 2)
		throw empty_args();
	double Number = context.top_arg();
	context.pop_arg();
	context.pop_back_();
	context.push_arg(context.top_arg() * Number);
	context.pop_arg();
}


void Division::make_operation(Context& context) {
	if (context.size_() < 1 || context.size_arg() < 2)
		throw empty_args();
	double Number = context.top_arg();
	context.pop_arg();
	if (!Number)
		throw division_by_zero;
	context.pop_back_();
	context.push_arg(context.top_arg() \ Number);
	context.pop_arg();
}

void Sqrt::make_operation(Context& context) {
	if (context.size_() < 1 || context.size_arg() < 1)
		throw empty_args();
	double Number = context.top_arg();
	context.pop_arg();
	if (Number < 0)
		throw negative_number();
	context.pop_back_();
	context.push_arg(sqrt(arg));
	
}
