#pragma once

namespace visuals
{
	enum class espType
	{
		name,
		box,
		boxF,
		health,
		lines,
		flags

	};

	inline bool FilledBox;

	void colorGradient(int _health);
	void drawEntitiesEsp(espType _type, int _distance);
}