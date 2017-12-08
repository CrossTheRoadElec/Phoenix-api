#pragma once
namespace CTRE { namespace Phoenix { namespace Tasking{
	
class IProcessable {
public:
	virtual ~IProcessable(){}
	virtual void Process() = 0;
};
}}}
