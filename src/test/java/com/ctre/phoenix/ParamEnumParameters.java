package com.ctre.phoenix;

public class ParamEnumParameters {
    public String name;
    public double value;
    public int subValue;
    public int ordinal;
    public double min;
    public double max;
    public double equalsResolutionCheck;

    public ParamEnumParameters(String name, double value, int subValue, int ordinal, double min, double max, double equalsResolutionCheck) {
        this.name = name;
        this.value = value;
        this.subValue = subValue;
        this.ordinal = ordinal;
        this.min = min;
        this.max = max;
        this.equalsResolutionCheck = equalsResolutionCheck;
    }
}
