/*
 * Shooter.h
 *
 *  Created on: Jan 12, 2017
 *      Author: RatPack
 */
#include "VictorSP.h"
#include "DigitalInput.h"
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include "Timer.h"
using frc::VictorSP;
using frc::DigitalInput;

class Shooter {
public:
	enum State{INTAKE, SHOOTING, RESETTING, IDLE};
	Shooter(VictorSP * shooter, VictorSP * intakeLeft, VictorSP * intakeRight, DigitalInput * limitSwitch);
	virtual ~Shooter();
	VictorSP * shooter;
	VictorSP * intakeLeft;
	VictorSP * intakeRight;
	DigitalInput * limitSwitch;
	Timer timer;
	State state;
	void shoot();
	void reset();
	void intake();
	void update();
	void stopIntake();
};

#endif /* SRC_SHOOTER_H_ */
