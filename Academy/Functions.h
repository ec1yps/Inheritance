#pragma once
#include "stdafx.h"
#include "Human.h"

std::ostream& operator<<(std::ostream& os, const Human& obj);
void Print(Human* group[], const int n);
void Clear(Human* group[], const int n);