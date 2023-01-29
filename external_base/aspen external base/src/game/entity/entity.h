#pragma once

struct playerEntity
{
	UINT32 base;

	char name[20];
	int health;
	vector3 positionHead;
	vector3 positionFeet;
	int team;
};

struct localPlayer
{
	static void setPosition(vector3 _newPosition);
	static vector3 getPosition();

	static vector3 getHeadPosition();

	static void setRotation(vector3 _newPosition);
	static vector3 getRotation();

	static viewMatrix getViewMatrix();
};