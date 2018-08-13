package com.ctre.phoenix;

public class CTREJNIWrapper {
  static boolean libraryLoaded = false;
  
  static {
    if (!libraryLoaded) {
      try {
        System.loadLibrary("CTRE_PhoenixCCI");
      } catch (UnsatisfiedLinkError e) {
        e.printStackTrace();
        System.exit(1);
      }
      libraryLoaded = true;
    }
  }
}
