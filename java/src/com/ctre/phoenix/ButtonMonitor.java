package com.ctre.phoenix;

import edu.wpi.first.wpilibj.GenericHID;

public class ButtonMonitor implements ILoopable
{
	GenericHID  _gameCntrlr;
	int _btnIdx;
	IButtonPressEventHandler  _handler;
	boolean _isDown = false;
	
	public interface IButtonPressEventHandler {
		void OnButtonPress(int idx, boolean isDown);
	};

	public ButtonMonitor(GenericHID controller, int buttonIndex,
			IButtonPressEventHandler ButtonPressEventHandler) {
		_gameCntrlr = controller;
		_btnIdx = buttonIndex;
		_handler = ButtonPressEventHandler;
	}

	public void Process() {
		boolean down = _gameCntrlr.getRawButton(_btnIdx);

		if (!_isDown && down){
			_handler.OnButtonPress(_btnIdx, down);
		}

		_isDown = down;
	}

	public void OnStart() {
	}
	public void OnLoop() {
		Process();
	}
	public boolean IsDone() {
		return false;
	}
	public void OnStop() {
	}
}
