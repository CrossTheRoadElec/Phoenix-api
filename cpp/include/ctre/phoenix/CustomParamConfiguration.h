#pragma once

#include <string>

namespace ctre {
namespace phoenix {
struct CustomParamConfiguration {
	int customParam_0;	
	int customParam_1;	
	CustomParamConfiguration() :
		customParam_0(0),
		customParam_1(0)
	{
	}
    std::string toString(std::string &prependString) {
        std::string retstr = prependString + ".customParam_0 = " + std::to_string(customParam_0) + ";\n";
        retstr += prependString + ".customParam_1 = " + std::to_string(customParam_1) + ";\n";
        
        return retstr;
    }
};
}
}
