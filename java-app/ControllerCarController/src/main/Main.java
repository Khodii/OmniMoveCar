package main;

import ch.aplu.xboxcontroller.XboxController;
import ch.aplu.xboxcontroller.XboxControllerAdapter;

public class Main {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		XboxController ps1 = new XboxController(1); 
		XboxController ps2 = new XboxController(2); 
		XboxController ps3 = new XboxController(3); 
		XboxController ps4 = new XboxController(4); 
		ps1.addXboxControllerListener(new XboxControllerAdapter() {
			@Override
			public void buttonA(boolean pressed) {
				// TODO Auto-generated method stub
				//super.buttonA(pressed);
				System.out.println("Controller 1 Button A");
			}@Override
			public void buttonB(boolean pressed) {
				// TODO Auto-generated method stub
				System.out.println("Controller 1 Button B");
				super.buttonB(pressed);
			}
			@Override
			public void buttonX(boolean pressed) {
				// TODO Auto-generated method stub
				System.out.println("Controller 1 Button X");
				super.buttonX(pressed);
			}@Override
			public void buttonY(boolean pressed) {
				// TODO Auto-generated method stub
				System.out.println("Controller 1 Button Y");
				super.buttonY(pressed);
			}
		});
		ps2.addXboxControllerListener(new XboxControllerAdapter() {
			@Override
			public void buttonA(boolean pressed) {
				// TODO Auto-generated method stub
				//super.buttonA(pressed);
				System.out.println("Controller 2 Button A");
			}
		});
		ps3.addXboxControllerListener(new XboxControllerAdapter() {
			@Override
			public void buttonA(boolean pressed) {
				// TODO Auto-generated method stub
				//super.buttonA(pressed);
				System.out.println("Controller 3 Button A");
			}
		});
		ps4.addXboxControllerListener(new XboxControllerAdapter() {
			@Override
			public void buttonA(boolean pressed) {
				// TODO Auto-generated method stub
				//super.buttonA(pressed);
				System.out.println("Controller 4 Button A");
			}
		});
	}

}
