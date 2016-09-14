/**
	James Bilbrey
	JRobot.h
	CMSC 411 Fall 2015 Project 1
	
	Prototype Interpreter user
**/

class JRobot {
	
	public:
		void tick();
		void setSpeed(uint32_t spd);
		void setAngle(uint32_t angle);
		uint32_t getSpeed();
		uint32_t getSpeed();
	private:
		uint32_t speed;
		uint32_t angle;
}
