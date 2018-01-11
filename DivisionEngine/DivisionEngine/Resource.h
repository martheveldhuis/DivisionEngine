#ifndef DIVISION_RESOURCE_H
#define DIVISION_RESOURCE_H

namespace Division 
{
	/**
		Interface for resource objects that are used by the resource manager
		and entities.
	*/
	class Resource
	{
	public:
		virtual ~Resource() = 0 {};
	};
}

#endif
