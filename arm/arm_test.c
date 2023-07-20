#include "arm_test.h"

angle ROB_ARM;

int main()
{
	//printf("%f", cos(60*M_PI/180));

	// inti_ROB();
	// ROB_ARM.res_x = 0.3;
	// ROB_ARM.res_y = 0;
	// ROB_ARM.res_z = 3.8;
	// printf("%f,%f,%f,%f\r\n",ROB_ARM.r_x,ROB_ARM.r_y,ROB_ARM.r_z,ROB_ARM.Gamma);
	// printf("%f,%f,%f,%f,%f\r\n",ROB_ARM.theta4,ROB_ARM.theta1,ROB_ARM.theta2,ROB_ARM.theta3,ROB_ARM.Gamma);
	// printf("\n");

	// for (int i = 100; i>0;i--)
	// {
	// 	ROB_GO_STR(&ROB_ARM);
	// 	mo_2(ROB_ARM.r_x,ROB_ARM.r_z);
	// 	//mo_3(ROB_ARM.r_x, ROB_ARM.r_y,ROB_ARM.r_z,0.0f);
	// 	printf("%f,%f,%f,%f\r\n",ROB_ARM.r_x,ROB_ARM.r_y,ROB_ARM.r_z,ROB_ARM.Gamma);
	// 	//printf("%f,%f,%f,%f,%f\r\n",ROB_ARM.theta4,ROB_ARM.theta1,ROB_ARM.theta2,ROB_ARM.theta3,ROB_ARM.Gamma);
	// 	printf("\n");
	// }

	// float a = ((3 * sin((4.6*M_PI)/180) + 0.3) * (3 * sin((4.6*M_PI)/180) + 0.3) + (3.8 - 3 * cos((4.6*M_PI)/180)) * (3.8 - 3 * cos((4.6*M_PI)/180)));
	// printf("%f\n", a);
	// a = ((3 * sin((5.3*M_PI)/180) + 0.3) * (3 * sin((5.3*M_PI)/180) + 0.3) + (3.8 - 3 * cos((5.3*M_PI)/180)) * (3.8 - 3 * cos((5.3*M_PI)/180)));
	// printf("%f\n", a);
	// float b = sin(30*M_PI/180);
	// printf("%f", (180/M_PI)*atan(1));

	mo_2(1, 37);
}

void inti_ROB(void)
{
	ROB_ARM.theta1 = 0.0f;
	ROB_ARM.theta2 = 0.0f;
	ROB_ARM.theta3 = 0.0f;
	ROB_ARM.theta4 = 0.0f;
	ROB_ARM.a1 = 0.1045f;//0.1045f
	ROB_ARM.a2 = 0.0985f;//0.0985f
	ROB_ARM.a3 = 0.268f;//0.268f
	ROB_ARM.r_x = 0.0f;
	ROB_ARM.r_y = 0.0f;
	ROB_ARM.r_z = 0.1045f + 0.0985f + 0.1741f;//0.1045f + 0.0985f + 0.1741f
	ROB_ARM.G_x = 0.0f;
	ROB_ARM.G_y = 0.0f;
	ROB_ARM.G_z = 0.1045f + 0.0985f + 0.1741f;
	ROB_ARM.res_x = 0.0f;
	ROB_ARM.res_y = 0.0f;
	ROB_ARM.res_z = 0.1045f + 0.0985f + 0.1741f;
}

int mo_2(float x, float y)
{
	float a1=10.45f,a2=9.85f,a3=17.41f;
	//float a1 = 2, a2 = 1, a3 = 1;
	float t1 = 0.0, t2 = 0.0, t3 = 0.0;
	float c = (1 - (a1 + a2) * (a1 + a2) - x * x - y * y) / (2 * (a1 + a2));
	printf("%f", c);
	t1 = (180 / M_PI) * 2 * atan((x - sqrt(x * x + y * y - c * c)) / (c - y));
	if(t1<0)t1 = (180 / M_PI) * 2 * atan((x + sqrt(x * x + y * y - c * c)) / (c - y));
	t3 = 90 + t1 - (180 / M_PI)*asin((y - (a1 + a2) * cos(t1 * M_PI / 180)) / a1);
	//printf("%f %f\n", t1,t3);
}

int mo_3(float x, float y, float z, float Gamma)
{
	if (x * x + y * y + z * z > 0.1422f)
	{
		return 0;
	}
	u8 Lo_Flag = 0;

	ROB_ARM.theta4 = (180.0f / M_PI) * atan2(y, x);
	x = sqrt(x * x + y * y);
	do
	{
		Lo_Flag = 0;
		ROB_ARM.Gamma = Gamma;

		ROB_ARM.Gamma_r = ROB_ARM.Gamma / (180.0f / M_PI);
		ROB_ARM.Bx = x - ROB_ARM.a3 * cos(ROB_ARM.Gamma_r);
		ROB_ARM.By = z - ROB_ARM.a3 * sin(ROB_ARM.Gamma_r);
		ROB_ARM.L_bo = sqrt(ROB_ARM.Bx * ROB_ARM.Bx + ROB_ARM.By * ROB_ARM.By);
		if (((ROB_ARM.a1 + ROB_ARM.a2) < ROB_ARM.L_bo) || ((ROB_ARM.a1 - ROB_ARM.a2) >= ROB_ARM.L_bo))
		{
			Lo_Flag = 1;
			Gamma++;

			if (Gamma > 100)
			{
				return 0;
			}
		}
	} while (Lo_Flag);
	ROB_ARM.theta2 = (180.0f / M_PI) * acos((ROB_ARM.Bx * ROB_ARM.Bx + ROB_ARM.By * ROB_ARM.By - ROB_ARM.a1 * ROB_ARM.a1 - ROB_ARM.a2 * ROB_ARM.a2) / (2.0f * ROB_ARM.a1 * ROB_ARM.a2));
	ROB_ARM.alpha = acos((ROB_ARM.a1 * ROB_ARM.a1 + ROB_ARM.Bx * ROB_ARM.Bx + ROB_ARM.By * ROB_ARM.By - ROB_ARM.a2 * ROB_ARM.a2) / (2 * ROB_ARM.a1 * ROB_ARM.L_bo));
	ROB_ARM.beta = atan2(ROB_ARM.By, ROB_ARM.Bx);
	ROB_ARM.theta1 = 90 - (180.0f / M_PI) * (ROB_ARM.alpha + ROB_ARM.beta);
	ROB_ARM.theta3 = 90 - ROB_ARM.Gamma - ROB_ARM.theta2 - ROB_ARM.theta1;

	if (ROB_ARM.theta1 > 90.0f)
		ROB_ARM.theta1 = 90.0f;
	else if (ROB_ARM.theta1 < -90.0f)
		ROB_ARM.theta1 = -90.0f;

	if (ROB_ARM.theta2 > 135.0f)
		ROB_ARM.theta2 = 135.0f;
	else if (ROB_ARM.theta2 < -135.0f)
		ROB_ARM.theta2 = -135.0f;

	if (ROB_ARM.theta3 > 135.0f)
		ROB_ARM.theta3 = 135.0f;
	else if (ROB_ARM.theta3 < -135.0f)
		ROB_ARM.theta3 = -135.0f;

	if (ROB_ARM.theta4 > 135.0f)
		ROB_ARM.theta4 = 135.0f;
	else if (ROB_ARM.theta4 < -135.0f)
		ROB_ARM.theta4 = -135.0f;
	//	printf("%f,%f,%f,%f,%f\n", ROB_ARM.theta1, ROB_ARM.theta2, ROB_ARM.theta3, ROB_ARM.theta4, ROB_ARM.Gamma);

	return 1;
}

int ROB_GO_STR(angle *state)
{
	float temp_IN_ERR;

	if (cal_flag)
	{
		state->G_x = state->res_x;
		state->G_y = state->res_y;
		state->G_z = state->res_z;

		Sx = state->G_x - state->r_x;
		Sy = state->G_y - state->r_y;
		Sz = state->G_z - state->r_z;

		_S = Sx;
		_G = state->G_x;
		ROB_R = state->r_x;

		if ((_S < 0.0005f) && (_S > -0.0005f))
		{
			state->r_x = state->G_x;
			_S = Sy;
			_G = state->G_y;
			ROB_R = state->r_y;

			if ((_S < 0.0005f) && (_S > -0.0005f))
			{
				state->r_y = state->G_y;
				_S = Sz;
				_G = state->G_z;
				ROB_R = state->r_z;
			}

			if ((_S < 0.0005f) && (_S > -0.0005f))
			{
				state->r_z = state->G_z;
				return 0;
			}
		}
		cal_flag = 0;
	}
	if (_S > 0)
	{
		ROB_R += 0.0002;
	}
	else
	{
		ROB_R -= 0.0002;
	}

	T_temp = (ROB_R - _G) / _S;
	state->r_x = Sx * T_temp + state->G_x;
	state->r_y = Sy * T_temp + state->G_y;
	state->r_z = Sz * T_temp + state->G_z;

	if (((ROB_R - _G) <= 0.0008) && ((ROB_R - _G) >= -0.0008))
	{
		ROB_R = _G;
	}
	// printf("ROB: %f",ROB_R);

	// printf("%f,%f,%f\n", state->r_x, state->r_y, state->r_z);

	return 1;
}