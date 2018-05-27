#include <iostream>
#include <wiringPi.h>
#include "libSonar.h"

using namespace std;

int trigger_left = 25;
int echo_left = 29;

int trigger_right = 24;
int echo_right = 28;

int main() {
    if (wiringPiSetup() == -1)
        return -1;

    Sonar sonar_left;
	Sonar sonar_right;
	
	int left_dis;
	int right_dis;
	
    sonar_left.init( trigger_left, echo_left );
	sonar_right.init( trigger_right, echo_right );
	
	while ( 1 ) {
		left_dis = sonar_left.distance( 30000 );
		right_dis = sonar_right.distance( 30000 );
		if ( left_dis > 5 && right_dis > 5 ) {
			system( "echo \"23=0.4\" > /dev/pi-blaster" );
			system( "echo \"24=0\" > /dev/pi-blaster" );
			system( "echo \"17=0\" > /dev/pi-blaster" );
			system( "echo \"22=0.4\" > /dev/pi-blaster" );
			cout << "Distance for left is " << left_dis << " cm." << endl;
			cout << "Distance for right is " << right_dis << " cm." << endl;
		} else {
			system( "echo \"23=0\" > /dev/pi-blaster" );
			system( "echo \"24=0\" > /dev/pi-blaster" );
			system( "echo \"17=0\" > /dev/pi-blaster" );
			system( "echo \"22=0\" > /dev/pi-blaster" );
		}
	}	
}
