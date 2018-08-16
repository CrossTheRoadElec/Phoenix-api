package com.ctre.phoenix;

import com.ctre.phoenix.ErrorCode;

class ErrorCodeString {
    public String string;
    public ErrorCode code;
    public ErrorCodeString(ErrorCode code, String string) {
        this.string = string;
        this.code = code;
    }
}
