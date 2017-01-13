/*
 * Shooter.h
 *
 *  Created on: Jan 12, 2017
 *      Author: RatPack
 */
#include "VictorSP.h"
#ifndef SRC_SHOOTER_H_
#define SRC_SHOOTER_H_
#include "Timer.h"
using frc::VictorSP;

class Shooter {
public:
	enum State{INTAKE, SHOOTING, RESETTING, IDLE};
	Shooter(VictorSP * shooter, VictorSP * intakeLeft, VictorSP * intakeRight);
	virtual ~Shooter();
	VictorSP * shooter;
	VictorSP * intakeLeft;
	VictorSP * intakeRight;
	Timer timer;
	State state;
	void shoot();
	void reset();
	void intake();
	void update();
	void stopIntake();
};

#endif /* SRC_SHOOTER_H_ */
