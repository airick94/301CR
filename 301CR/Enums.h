#pragma once

enum MoveState
{
	MS_Stop,
	MS_Left,
	MS_Right,
	MS_Jump
};

enum ObjectType
{
	OT_Ground,
	OT_Crosshair,
	OT_Player,
	OT_Projectile,
	OT_NewGround
};