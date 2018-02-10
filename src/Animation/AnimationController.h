#ifndef ANIMATION_CONTROLLER_H
#define ANIMATION_CONTROLLER_H

class AnimationController
{
public:
	AnimationController();
	
	AnimationController(const int endFrame, const double speed, const int startFrame = 0, const bool alternate = false);

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
	const int startFrame;
	const int endFrame;
	
	int frame;
	double speed;
	double remainder;
	bool alternate;
}

#endif //ANIMATION_CONTROLLER_H