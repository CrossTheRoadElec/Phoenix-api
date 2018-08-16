package com.ctre.phoenix;

public class ParamEnumParameters {
    public String name;
    public double min;
    public double max;
    public double equalsResolutionCheck;

    public ParamEnumParameters(String name, double min, double max, double equalsResolutionCheck) {
        this.name = name;
        this.min = min;
        this.max = max;
        this.equalsResolutionCheck = equalsResolutionCheck;
    }
}
