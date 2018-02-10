#incldue "AnimationController.h"

AnimationController::AnimationController() :
{
}

AnimationController(const int l, const double s, const int sF, const bool a) :
	length(l),
	speed(s),
	frame(sF),
	alternate(a),
	remainder(0)
{
}

void Update(unsigned double delta)
{
	if(speed != 0)
		
	remainder += delta;
	int advance = static_cast<int>(remainder * speed);
	remainder = std::fmod(remainder, speed);
}

unsigned GetFrame() const
{
	return frame;
}

unsigned SetFrame(unsigned f)
{
	frame = f;
}

double GetSpeed() const
{
	return speed;
}

void SetSpeed()
{
	speed = s;
}

unsigned GetLength() const
{
	return length;
}
void SetLength();

bool IsAlternating();
void SetAlternate(bool alt);