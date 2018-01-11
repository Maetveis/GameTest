#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

class AnimationController
{
public:
	AnimationController();
	
	AnimationController(const unsigned length, const double speed, const unsigned startFrame = 0, const bool alternate = false);

	void Update(double delta);
	
	unsigned GetFrame() const;
	unsigned SetFrame(unsigned frame);
	
	double GetSpeed() const;
	void SetSpeed(double s);
	
	unsigned GetLength() const;
	void SetLength();
	
	bool IsAlternating();
	void SetAlternate(bool alt);
protected:
private:
	int length;
	double speed;
	int frame;
	bool alternate;
	double remainder;
}

#endif //ANIMATION_CONTROLLER_H