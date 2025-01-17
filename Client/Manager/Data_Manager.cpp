#include "Data_Manager.h"

Data_Manager* Data_Manager::instance = nullptr;

Data_Manager::Data_Manager()
{
	instance = this;
}

Data_Manager::~Data_Manager()
{
}

void Data_Manager::Draw()
{

}
