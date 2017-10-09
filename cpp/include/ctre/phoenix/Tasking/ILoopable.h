#pragma once

namespace CTRE { namespace Tasking{
	
class ILoopable{
public:
	virtual ~ILoopable(){}
	virtual void OnStart() = 0;
	virtual void OnLoop() = 0;
	virtual bool IsDone() = 0;
	virtual void OnStop() = 0;
};
}}
