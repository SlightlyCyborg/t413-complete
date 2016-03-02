
#define BAT_VOLTAGE "10"
#define MOTOR_0_DEG "20"
#define MOTOR_120_DEG "21"
#define MOTOR_240_DEG "22"
#define WHEEL_0_DEG "30"
#define WHEEL_120_DEG "31"
#define WHEEL_240_DEG "32"

#include <stdio.h>
#include <Wire.h>
#include "mpu.h"

//Resistor in ohms used to measure the current voltage of the battery
//Needed for undervoltage dropout so that the batteries do not become under charged
float r1=6800.0;
float r2=2000.0;

//Motor pins
int forward_pins[] = {3};
int backward_pins[] = {5};

//Clojure vars
bool clojure_connected = false;

//For the loop
long previous_millis = 0;


void setup() {
  // put your setup code here, to run once:
	Serial.begin(115200); 
	mpu_setup();
}




float get_cur_main_battery_voltage(){
		float rv, v_r2;
		int analog_value;

		rv = 0;

		analog_value = analogRead(A0);

		v_r2 = (analog_value * 5.0) / 1024.0; 
		rv = v_r2 / (r2/(r1+r2));

		if (rv < 0.1) 
		{
			rv=0.0;
		}

		return rv;
}

void change_motor_speed(int motor, float speed){
	//Speed should be a val from -1 to 1 which represents the speed of the motor
	// Positive numbers are forward and negative numbers are backward
	if(speed > 1 || speed < -1){
		throw_exception("Speeds must be [-1,1]");
	}else if(motor < 0 || motor > 2){
		throw_exception("There are only 3 motors");
		//Technically there are 6, but he doesn't need to know that. hehe 
	}else{
		if(speed == 0){
			//Set both forward and backwards to 0 
			analogWrite(forward_pins[motor], 0); 
			analogWrite(backward_pins[motor], 0); 
		}else{
				//Denormalize the speed
				int digital_speed = (int)(speed * 255);

				if(speed > 0){
					analogWrite(backward_pins[motor], 0);
					analogWrite(forward_pins[motor], digital_speed);
				}else{
					analogWrite(forward_pins[motor], 0);
					analogWrite(backward_pins[motor], -1 * digital_speed);
				}
		}
	}
}

void throw_exception(String msg){
	//This function handles exceptions.

	if(clojure_connected){
	//If serial_clojure is connected, then send the proper serial code for an exception

		//Implement this
	}else{ 
	//Else print to the serial in the normal way the exception
		//Serial.print("Exception: ");
		//Serial.println(msg);
	}
}

void test_motors(){
	change_motor_speed(0, .5);
	delay(3000);
	change_motor_speed(0, 0);
	delay(3000);
	change_motor_speed(0, -.5);
	delay(3000);
}

void sendData (String data_id, String data){
	Serial.println("T00I" + data_id + "P" + data);
}

//Timing
int interval_check_voltage = 5000;
unsigned long last_check_voltage = 0;

void send_neccisary_data(unsigned long currentMillis){
  char data_buf[4];
	if((currentMillis - last_check_voltage) > interval_check_voltage){
		sprintf(data_buf, "%04d", (int)(get_cur_main_battery_voltage()*100));
		sendData(BAT_VOLTAGE, data_buf);
		last_check_voltage = currentMillis;
	}
}


void loop() {
  // put your main code here, to run repeatedly:
	unsigned long currentMillis = millis(); // missil Dislexia?

	//Send Data if need be
	send_neccisary_data(currentMillis);
	
	//delay(2000);
	//test_motors();

	//mpu_loop();
}


/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
		//Handle the data
}