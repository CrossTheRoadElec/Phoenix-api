package com.ctre.phoenix;

import com.ctre.phoenix.ErrorCodeString;

class ErrorCodeDoubleString extends ErrorCodeString {
    
    public double value;

    public ErrorCodeDoubleString(double value, ErrorCode code, String string) {
        super(code, string);
        this.value = value;
    }
}
