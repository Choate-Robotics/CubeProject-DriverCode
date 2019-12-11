#include "Robot.h"
#include "OI.h"
#include "RobotMap.h"
#include "subsystems/conveyor.h"
#include "subsystems/drivetrain.h"
#include "subsystems/intake.h"
#include "subsystems/extake.h"
#include "subsystems/hatchPanel.h"
#include "subsystems/climber.h"
#include <iostream>
#include <frc/commands/Scheduler.h>

#include "frc/smartdashboard/Smartdashboard.h"
#include "networktables/NetworkTable.h"
#include "networktables/NetworkTableInstance.h"

using namespace std;
using namespace RobotMap;

OI *Robot::oi = new OI;

frc::PWMTalonSRX * motor::frontLeft;
frc::PWMTalonSRX * motor::frontRight;
frc::PWMTalonSRX * motor::backLeft;
frc::PWMTalonSRX * motor::backRight;
frc::PWMVictorSPX * motor::conveyor;
frc::PWMVictorSPX * motor::intake;
frc::PWMVictorSPX * motor::intakeTilt;
frc::PWMVictorSPX * motor::extakeTilt;
frc::PWMVictorSPX * motor::extake;
frc::PWMVictorSPX * motor::hatchRoller;
frc::SpeedControllerGroup * motor::left;
frc::SpeedControllerGroup * motor::right;
frc::DifferentialDrive * motor::differentialDrive;

frc::DoubleSolenoid * solenoid::climberBack;
frc::DoubleSolenoid * solenoid::climberFront;
frc::DoubleSolenoid * solenoid::hatchPanel;


subsystem::Conveyor* Robot::conveyor = nullptr;
subsystem::Extake* Robot::extake = nullptr;
subsystem::Drivetrain* Robot::drivetrain = nullptr;
subsystem::Intake* Robot::intake = nullptr;
subsystem::HatchPanel* Robot::hatchPanel = nullptr;
subsystem::Climber* Robot::climber = nullptr;

void Robot::RobotInit()
{

    motor::frontLeft = new frc::PWMTalonSRX{0};
    motor::frontRight = new frc::PWMTalonSRX{1};
    motor::backLeft = new frc::PWMTalonSRX{2};
    motor::backRight = new frc::PWMTalonSRX{3};

    motor::conveyor = new frc::PWMVictorSPX{4};
    motor::intake = new frc::PWMVictorSPX{5};
    motor::intakeTilt = new frc::PWMVictorSPX{6};
    motor::extakeTilt = new frc::PWMVictorSPX{7};
    motor::extake = new frc::PWMVictorSPX{8};
    motor::hatchRoller = new frc::PWMVictorSPX{9};

    motor::left = new frc::SpeedControllerGroup{*motor::frontLeft,*motor::backLeft};
    motor::right = new frc::SpeedControllerGroup{*motor::frontRight,*motor::backRight};
    motor::differentialDrive = new frc::DifferentialDrive{*motor::left, *motor::right};

    solenoid::hatchPanel= new frc::DoubleSolenoid{1, 0};
    solenoid::climberFront= new frc::DoubleSolenoid{2,3};
    solenoid::climberBack=new frc::DoubleSolenoid{4,5};
    solenoid::hatchPanel->Set(frc::DoubleSolenoid::kForward);
    solenoid::climberFront->Set(frc::DoubleSolenoid::kReverse);
    solenoid::climberBack->Set(frc::DoubleSolenoid::kReverse);


    Robot::conveyor = new subsystem::Conveyor("Conveyor");
    Robot::extake = new subsystem::Extake("Extake");
    Robot::drivetrain = new subsystem::Drivetrain("Drivetrain");
    Robot::intake = new subsystem::Intake("Intake");
    Robot::hatchPanel = new subsystem::HatchPanel("Hatch Panel");
    Robot::climber = new subsystem::Climber("Hab Climber");

    frc::Scheduler::GetInstance()->RegisterSubsystem(this->drivetrain);
    frc::Scheduler::GetInstance()->RegisterSubsystem(this->conveyor);
    frc::Scheduler::GetInstance()->RegisterSubsystem(this->extake);
    frc::Scheduler::GetInstance()->RegisterSubsystem(this->intake);
    frc::Scheduler::GetInstance()->RegisterSubsystem(this->hatchPanel);

}

void Robot::RobotPeriodic(){
    frc::Scheduler::GetInstance()->Run();
}
void Robot::DisabledInit(){}
void Robot::DisabledPeriodic(){}
void Robot::AutonomousInit(){}
void Robot::AutonomousPeriodic(){
    frc::Scheduler::GetInstance()->Run();
}
void Robot::TeleopInit(){
}
void Robot::TeleopPeriodic(){
    frc::Scheduler::GetInstance()->Run();

    std::shared_ptr<NetworkTable> table = nt::NetworkTableInstance::GetDefault().GetTable("limelight");
    cout << table->GetNumber("tx", 0.0) << '\n';
}
void Robot::TestPeriodic(){}

int main(){return frc::StartRobot<Robot>();}
