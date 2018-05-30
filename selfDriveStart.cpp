#include <iostream>
#include <wiringPi.h>
#include "libSonar.h"

using namespace std;

void start_right_forward() {
	system( "echo \"23=0.35\" > /dev/pi-blaster" );
	system( "echo \"24=0\" > /dev/pi-blaster" );
}

void start_left_forward() {
	system( "echo \"22=0.35\" > /dev/pi-blaster" );	
	system( "echo \"17=0\" > /dev/pi-blaster" );
}

void start_right_backward() {
	system( "echo \"23=0\" > /dev/pi-blaster" );
	system( "echo \"24=0.35\" > /dev/pi-blaster" );
}

void start_left_backward() {
	system( "echo \"22=0\" > /dev/pi-blaster" );
	system( "echo \"17=0.35\" > /dev/pi-blaster" );
}

void stop_right() {
	system( "echo \"23=0\" > /dev/pi-blaster" );	
	system( "echo \"14=0\" > /dev/pi-blaster" );
}

void stop_left() {
	system( "echo \"22=0\" > /dev/pi-blaster" );	
	system( "echo \"17=0\" > /dev/pi-blaster" );
}

void rotate_right() {
	start_right_backward();
	start_left_forward();
}

void rotate_left() {
	start_right_forward();
	start_left_backward();
}

void rotate_stop() {
	stop_left();
	stop_right();
}

int trigger_left = 25;
int echo_left = 29;

int trigger_right = 24;
int echo_right = 28;

int main() {
    if (wiringPiSetup() == -1)
        return -1;

    Sonar sonar_left;
	Sonar sonar_right;
	
	int sum_left;
	int sum_right;
	
	double left_dis;
	double right_dis;
	
    sonar_left.init( trigger_left, echo_left );
	sonar_right.init( trigger_right, echo_right );
	
	while ( 1 ) {
		
		sum_left = 0;
		for ( int i = 0; i < 20; i++ ) {
			sum_left += sonar_left.distance( 30000 );
		}
		left_dis = sum_left / 20;
		
		sum_right = 0;
		for ( int i = 0; i < 20; i++ ) {
			sum_right += sonar_left.distance( 30000 );
		}
		right_dis = sum_right / 20;
		
		if ( left_dis < 10 && right_dis < 10 ) {
			start_right_forward();
			start_left_forward();
			continue;
		}
		
		if ( left_dis < 10 ) {
			rotate_right();
			continue;
		}
		
		if ( right_dis < 10 ) {
			rotate_left();
			continue;
		}
	}	
}
