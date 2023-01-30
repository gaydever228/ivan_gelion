#include "Timer.h"

Timer::Timer() {

	time = clock.getElapsedTime().asMicroseconds(); //дать прошедшее время в микросекундах

}