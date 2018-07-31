package com.ctre.phoenix;

public class ErrorCollection {
    public void NewError(ErrorCode err) {
        _worstError = ErrorCode.worstOne(_worstError, err);
    }
    public void NewError(int err) {
        _worstError = ErrorCode.worstOne(_worstError, ErrorCode.valueOf(err));
    }
    public ErrorCode _worstError;
    public ErrorCollection() {
        _worstError = ErrorCode.OK;
    }
};

