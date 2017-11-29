#ifndef DIVISION_KERNEL_H
#define DIVISION_KERNEL_H

#include "WindowManager.h"

namespace Division
{
	class Kernel
	{
	public:
		Kernel();
		~Kernel();
		void initialize();
	private:
		WindowManager* windowManager_;
	};
}

#endif // !DIVISION_KERNEL_H