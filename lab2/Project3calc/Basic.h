#pragma once
#ifndef BASIC_H
#define BASIC_H

#include "Operator.h"

class Add : public Operator
{
public:
	void make_operation(Context&) override;
	~Add() override {};
};

class Subtract : public Operator
{
public:
	void make_operation(Context&) override;
	~Subtract() override {};

};

class Multiplicate : public Operator
{
public:
	void make_operation(Context&) override;
	~Multiplicate() override {};

};

class Division : public Operator
{
public:
	void make_operation(Context&) override;
	~Division() override {};

};

class Sqrt : public Operator
{
public:
	void make_operation(Context&) override;
	~Sqrt() override {};

};

class Pop : public Operator
{
public:
	void make_operation(Context&) override;
	~Pop() override {};

};

class Push : public Operator
{
public:
	void make_operation(Context&) override;
	~Push() override {};

};

class Print : public Operator
{
public:
	void make_operation(Context&) override;
	~Print() override {};

};

class Define : public Operator
{
public:
	void make_operation(Context&) override;
	~Define() override {};

};

#endif 