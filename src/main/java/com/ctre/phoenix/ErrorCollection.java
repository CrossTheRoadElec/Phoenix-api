package com.ctre.phoenix;

/**
 * Class to handle multiple error codes
 */
public class ErrorCollection {
    /**
     * Add error to error collection
     * @param err Error to add to collection
     */
    public void NewError(ErrorCode err) {
        _worstError = ErrorCode.worstOne(_worstError, err);
    }
    /**
     * Add error to error collection
     * @param err Error to add to collection
     */
    public void NewError(int err) {
        _worstError = ErrorCode.worstOne(_worstError, ErrorCode.valueOf(err));
    }
    /**
     * Worst error of all in collection
     */
    public ErrorCode _worstError;
    public ErrorCollection() {
        _worstError = ErrorCode.OK;
    }
};

