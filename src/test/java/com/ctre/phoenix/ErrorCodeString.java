package com.ctre.phoenix;

import com.ctre.phoenix.ErrorCode;

class ErrorCodeString {
    public String string;
    public ErrorCode code;
    public ErrorCodeString(ErrorCode inCode, String inString) {
        string = inString;
        code = inCode;
    }
}
