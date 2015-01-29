#pragma once
static const float PI = 3.14159265f;

static float degToRad(float deg)
{
	return (deg * PI) / 180.0f;
}

static void clamp(float &val, const float &min, const float &max) {
	if (val < min)
		val = min;
	if (val > max)
		val = max;
}