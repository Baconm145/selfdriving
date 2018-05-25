#include <iostream>
#include <wiringPi.h>
#include "libSonar.h"

using namespace std;

int trigger_left = 25;
int echo_left = 29;

int trigger_right = 24;
int echo_right = 28;

int main()
{
    if (wiringPiSetup() == -1)
        return -1;

    Sonar sonar_left;
	Sonar sonar_right;
	
    sonar_left.init( trigger_left, echo_left );
	sonar_right.init( trigger_right, echo_right );

    while(1){
        cout << "Distance for left is" << sonar_left.distance( 30000 ) << " cm." << endl;
		cout << "Distance for right is" << sonar_right.distance( 30000 ) << " cm." << endl;
    }
}
