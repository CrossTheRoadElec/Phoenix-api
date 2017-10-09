#pragma once

namespace CTRE { namespace Tasking{
	
class IProcessable {
public:
	virtual ~IProcessable(){}
	virtual void Process() = 0;
};
}}
