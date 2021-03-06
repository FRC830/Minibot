#include <iostream>
#include <memory>
#include <string>

#include "input/GamepadF310.h"
#include "util/Algorithms.h"
#include <IterativeRobot.h>
#include <LiveWindow/LiveWindow.h>
#include <SmartDashboard/SendableChooser.h>
#include <SmartDashboard/SmartDashboard.h>
#include "Shooter.h"

using namespace Lib830;
class Robot: public frc::IterativeRobot {
	GamepadF310 * pilot;
	float previousSpeed = 0;
	float previousTurn = 0;
public:
	void RobotInit() {
		chooser.AddDefault(autoNameDefault, autoNameDefault);
		chooser.AddObject(autoNameCustom, autoNameCustom);
		frc::SmartDashboard::PutData("Auto Modes", &chooser);
		pilot = new GamepadF310(0);
//		shooter = new VictorSP(SHOOTER_PWM);
//		intakeLeft = new VictorSP(INTAKELEFT_PWM);
//		intakeRight = new VictorSP(INTAKERIGHT_PWM);
		drive = new RobotDrive(
			new VictorSP(LEFT_PWM),
			new VictorSP(RIGHT_PWM)
		);
		shooter = new Shooter(
			new VictorSP(SHOOTER_PWM),
			new VictorSP(INTAKELEFT_PWM),
			new VictorSP(INTAKERIGHT_PWM),
			new DigitalInput(SHOOTER_LIMIT_DIO)
		);
	}
private:
		static const int LEFT_PWM = 4;
		static const int RIGHT_PWM = 3;
		static const int INTAKERIGHT_PWM = 2;
		static const int INTAKELEFT_PWM = 0;
		static const int SHOOTER_PWM = 1;
		static const int SHOOTER_LIMIT_DIO = 0;

		RobotDrive * drive;
//		VictorSP * intakeLeft;
//		VictorSP * intakeRight;
//		VictorSP * shooter;
		Shooter * shooter;


	/*
	 * This autonomous (along with the chooser code above) shows how to select
	 * between different autonomous modes using the dashboard. The sendable
	 * chooser code works with the Java SmartDashboard. If you prefer the
	 * LabVIEW Dashboard, remove all of the chooser code and uncomment the
	 * GetString line to get the auto name from the text box below the Gyro.
	 *
	 * You can add additional auto modes by adding additional comparisons to the
	 * if-else structure below with additional strings. If using the
	 * SendableChooser make sure to add them to the chooser code above as well.
	 */
	void AutonomousInit() override {
		autoSelected = chooser.GetSelected();
		// std::string autoSelected = SmartDashboard::GetString("Auto Selector", autoNameDefault);
		std::cout << "Auto selected: " << autoSelected << std::endl;

		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void AutonomousPeriodic() {
		if (autoSelected == autoNameCustom) {
			// Custom Auto goes here
		} else {
			// Default Auto goes here
		}
	}

	void TeleopInit() {

	}

	void TeleopPeriodic() {
		float targetTurn = pilot->RightX();
		float turn = accel(previousTurn, targetTurn, 20);
		previousTurn = turn;
		float targetForward = pilot->LeftY();
		float speed = accel(previousSpeed, targetForward, 30);
		previousSpeed = speed;
		if (pilot->ButtonState(GamepadF310::BUTTON_LEFT_BUMPER)) {
			drive->ArcadeDrive(speed, turn);
		}
		else {
			drive->ArcadeDrive(speed/2.0,turn/2.0);
		}

		if (pilot->ButtonState(GamepadF310::BUTTON_X))
			shooter->intake();
		else
			shooter->stopIntake();
		shooter->update();
//		SmartDashboard::PutNumber("Right joystick", pilot->RightY());
//		SmartDashboard::PutNumber("Left joystick", pilot->LeftY());
	}

	void TestPeriodic() {
		lw->Run();
		//intakeLeft->Set(pilot->LeftTrigger());

	}

private:
	frc::LiveWindow* lw = LiveWindow::GetInstance();
	frc::SendableChooser<std::string> chooser;
	const std::string autoNameDefault = "Default";
	const std::string autoNameCustom = "My Auto";
	std::string autoSelected;
};

START_ROBOT_CLASS(Robot)
