#ifndef SCALED_DELTA_TIMER_H
#define SCALED_DELTA_TIMER_H

#include <cstdint>

class ScaledDeltaTimer
{
public:
	ScaledDeltaTimer() = default;
	ScaledDeltaTimer(const ScaledDeltaTimer&) = default;
	ScaledDeltaTimer& operator=(const ScaledDeltaTimer& t) = default;
	
	void Start();
	void Update();
	void SetScaleFactor(const double newScale);
	
	double GetScaleFactor() const;
	double GetScaledTime() const;
	double GetUnscaledTime() const;
	std::uint32_t GetFrameStart() const;
protected:
private:
	double timeScale;
	double unscaledDelta;
	double scaledDelta;
	std::uint32_t lastFrameTime;
};

#endif //SCALED_DELTA_TIMER_H