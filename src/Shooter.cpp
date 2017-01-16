/*
 * Shooter.cpp
 *
 *  Created on: Jan 12, 2017
 *      Author: RatPack
 */

#include <Shooter.h>

Shooter::Shooter(VictorSP * shooter, VictorSP * intakeLeft, VictorSP * intakeRight, DigitalInput * limitSwitch)
:shooter(shooter),intakeLeft(intakeLeft),intakeRight(intakeRight),limitSwitch(limitSwitch),state(IDLE) {

}

void Shooter::shoot() {
	state = SHOOTING;
}

void Shooter::reset() {
	state = RESETTING;
}

void Shooter::intake() {
	state = INTAKE;
}

void Shooter::stopIntake() {
	state = IDLE;
}

void Shooter::update() {
	intakeRight->Set(0);
	intakeLeft->Set(0);
	switch(state) {
	case SHOOTING :
		shooter->Set(1);
		if (limitSwitch->Get() == 0) {
			state = RESETTING;
		}
		break;

	case RESETTING :
		shooter->Set(1);
		if (limitSwitch->Get() == 1) {
			state = IDLE;
		}
		break;

	case INTAKE :
		shooter->Set(0);
		intakeRight->Set(0.5);
		intakeLeft->Set(-.5);
		break;

	case IDLE :
		shooter->Set(0);
		break;
	}
}

Shooter::~Shooter() {

}

