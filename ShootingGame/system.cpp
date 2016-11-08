#include "system.h"
#include <time.h>
#include <math.h>
#include <random>

//////////////////////////////////////////////////////////////////////////
//概略:
//	乱数を発生させる
//引数:
//	int max_of_randvalue:発生させたい乱数の最大値
//	int min_of_randvalue:発生させたい乱数の最小値
//戻り値:発生させた乱数
//////////////////////////////////////////////////////////////////////////
int GenerateRandValue(int max_of_randvalue , int min_of_randvalue)
{
	static unsigned int randvalue = 0;			//発生させた乱数値を保存しておくための変数
	static unsigned int randcount = 0;				//発生させる乱数値の規則性を乱すための変数
	
	//初期のシード値設定
	if(randvalue == 0)
	{
		srand((unsigned int)time(NULL));
	}
	//乱数を使用してシード値を再設定
	else
	{
		srand((unsigned int)(randvalue + randcount++));
	}

	//発生させた乱数を保存する
	randvalue = rand();

	if(min_of_randvalue >= 0)
	{
		return randvalue % ((max_of_randvalue + 1) - min_of_randvalue) + min_of_randvalue;
	}
	else
	{
		if(rand() % 2 == 0)
		{
			return randvalue % ((max_of_randvalue + 1) - min_of_randvalue) + min_of_randvalue;			
		}
		else
		{
			return -((int)randvalue % ((max_of_randvalue + 1) - min_of_randvalue) + min_of_randvalue);
		}
	}
}

///////////////////////////////////////////////////////////////////////////
//概略:
//	円と円の当たり判定
//引数:
//	circle1:円の構造体へのポインタ1
//	circle2:円の構造体へのポインタ2
//戻り値:
//	true:当たった
//	false:当たっていない
///////////////////////////////////////////////////////////////////////////
bool CheckHitCircleandCircle(CircleClass *circle1 , CircleClass *circle2)
{
	POSITION Circle1Position = circle1->GetPosition();
	POSITION Circle2Position = circle2->GetPosition();
	double Circle1Radius = circle1->GetRadius();
	double Circle2Radius = circle2->GetRadius();

	//ピタゴラスの定理を利用して判定を行う
	if((Circle2Position.m_Vector.x - Circle1Position.m_Vector.x) * (Circle2Position.m_Vector.x - Circle1Position.m_Vector.x) +
		(Circle2Position.m_Vector.y - Circle1Position.m_Vector.y) * (Circle2Position.m_Vector.y - Circle1Position.m_Vector.y) +
		(Circle2Position.m_Vector.z - Circle1Position.m_Vector.z) * (Circle2Position.m_Vector.z - Circle1Position.m_Vector.z) <=
		(Circle2Radius + Circle1Radius) * (Circle2Radius + Circle1Radius))
	{
		return true;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	矩形と矩形のあたり判定
//引数:
//	BOX* box1:矩形の構造体へのポインタ1
//	BOX* box2:矩形の構造体へのポインタ2
//戻り値:	
//	int TRUE:当たった
//	NO_HIT:当たらなかった
//////////////////////////////////////////////////////////////////////////////
bool CheckHitBoxandBox(BoxClass *box1 , BoxClass *box2)
{
	//当たり判定を取るべきか調べる
	THREE_DIMENSIONAL_VECTOR SemiDiagonalVector_of_Box1 = box1->GetSemiLongVector() + box1->GetSemiShortVector();
	THREE_DIMENSIONAL_VECTOR SemiDiagonalVector_of_Box2 = box2->GetSemiLongVector() + box2->GetSemiShortVector();

	//当たり判定を取るべきか調べる
	if(GetDistance(&box1->GetPosition() , &box2->GetPosition()) <= SemiDiagonalVector_of_Box1.Magnitude() + SemiDiagonalVector_of_Box2.Magnitude())
	{
		//box1からみたbox2を調べる
		double TempDistance = 0;	//一時的に距離を入れる変数
		THREE_DIMENSIONAL_VECTOR TempVector;	//一時的にベクトルを入れる変数
		int ExcludeVertex = -1;	//一番遠い頂点を記憶する変数

		//一番遠い頂点を除外する
		for(int i = 0 ; i < 4 ; i++)
		{
			//box1の位置とbox2の頂点の距離を比べる
			if(GetDistance(&box1->GetPosition() , &box2->GetVertex(i)) > TempDistance)
			{
				//一番遠い点の距離を保存する
				TempDistance = GetDistance(&box1->GetPosition() , &box2->GetVertex(i));

				//一番遠い点の配列番号を保存する
				ExcludeVertex = i;
			}
		}
		
		//box2の頂点がbox1の面積内にいるか調べる
		for(int i = 0 ; i < 4 ; i++)
		{
			//除外した頂点じゃないとき
			if(i != ExcludeVertex)
			{
				TempVector = box2->GetVertex(i).m_Vector - box1->GetPosition().m_Vector;

				//box1が回転していないとき
				if(box1->GetAngle() != 0)
				{
					//縦の方が長いとき
					if(box1->GetSemiLongVector().x == 0)
					{
						//box1の中心からbox2の頂点へのベクトルのx,y成分が
						//box1の半長軸長、半短軸長より小さいことを調べる
						if(abs(TempVector.x) <= box1->GetSemiShortAxis() && abs(TempVector.y) <= box1->GetSemiLongAxis())
						{
							return true;
						}
					}
					//横の方が長いとき
					else
					{
						//box1の中心からbox2の頂点へのベクトルのx,y成分が
						//box1の半長軸長、半短軸長より小さいことを調べる
						if(abs(TempVector.x) <= box1->GetSemiLongAxis() && abs(TempVector.y) <= box1->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
				//box１が回転しているとき
				else
				{
					//box1の中心からbox２の頂点へのベクトルを回転させる
					THREE_DIMENSIONAL_VECTOR RotatedVector = RotateVector2(&TempVector , -box1->GetAngle());
					//box１の半長軸ベクトルも回転させる
					THREE_DIMENSIONAL_VECTOR RotatedSemiLongVector = RotateVector2(&box1->GetSemiLongVector() , -box1->GetAngle());

					//縦の方が長いとき
					if(RotatedSemiLongVector.x == 0)
					{
						//box1の中心からbox2の頂点へのベクトルのx,y成分が
						//box1の半長軸長、半短軸長より小さいことを調べる
						if(abs(RotatedVector.x) <= box1->GetSemiShortAxis() && abs(RotatedVector.y) <= box1->GetSemiLongAxis())
						{
							return true;
						}
					}
					//横の方が長いとき
					else
					{
						//box1の中心からbox2の頂点へのベクトルのx,y成分が
						//box1の半長軸長、半短軸長より小さいことを調べる
						if(abs(RotatedVector.x) <= box1->GetSemiLongAxis() && abs(RotatedVector.y) <= box1->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
			}
		}

		//box2からみたbox1を調べる
		TempDistance = 0;	//一時的に距離を入れる変数
		ExcludeVertex = -1;	//一番遠い頂点を記憶する変数

		//一番遠い頂点を除外する
		for(int i = 0 ; i < 4 ; i++)
		{
			//box2の位置とbox1の頂点の距離を比べる
			if(GetDistance(&box2->GetPosition() , &box1->GetVertex(i)) > TempDistance)
			{
				//一番遠い点の距離を保存する
				TempDistance = GetDistance(&box2->GetPosition() , &box1->GetVertex(i));

				//一番遠い点の配列番号を保存する
				ExcludeVertex = i;
			}
		}

		//box2の頂点がbox1の面積内にいるか調べる
		for(int i = 0 ; i < 4 ; i++)
		{
			//除外した頂点じゃないとき
			if(i != ExcludeVertex)
			{
				TempVector = box2->GetVertex(i).m_Vector - box1->GetPosition().m_Vector;

				//box2が回転していないとき
				if(box2->GetAngle() != 0)
				{
					//縦の方が長いとき
					if(box2->GetSemiLongVector().x == 0)
					{
						//box2の中心からbox1の頂点へのベクトルのx,y成分が
						//box2の半長軸長、半短軸長より小さいことを調べる
						if(abs(TempVector.x) <= box2->GetSemiShortAxis() && abs(TempVector.y) <= box2->GetSemiLongAxis())
						{
							return true;
						}
					}
					//横の方が長いとき
					else
					{
						//box2の中心からbox1の頂点へのベクトルのx,y成分が
						//box2の半長軸長、半短軸長より小さいことを調べる
						if(abs(TempVector.x) <= box2->GetSemiLongAxis() && abs(TempVector.y) <= box2->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
				//box2が回転しているとき
				else
				{
					//box2の中心からbox1の頂点へのベクトルを回転させる
					THREE_DIMENSIONAL_VECTOR RotatedVector = RotateVector2(&TempVector , -box2->GetAngle());
					//box2の半長軸ベクトルも回転させる
					THREE_DIMENSIONAL_VECTOR RotatedSemiLongVector = RotateVector2(&box2->GetSemiLongVector() , -box2->GetAngle());

					//縦の方が長いとき
					if(RotatedSemiLongVector.x == 0)
					{
						//box2の中心からbox1の頂点へのベクトルのx,y成分が
						//box2の半長軸長、半短軸長より小さいことを調べる
						if(abs(RotatedVector.x) <= box2->GetSemiShortAxis() && abs(RotatedVector.y) <= box2->GetSemiLongAxis())
						{
							return true;
						}
					}
					//横の方が長いとき
					else
					{
						//box2の中心からbox1の頂点へのベクトルのx,y成分が
						//box2の半長軸長、半短軸長より小さいことを調べる
						if(abs(RotatedVector.x) <= box2->GetSemiLongAxis() && abs(RotatedVector.y) <= box2->GetSemiShortAxis())
						{
							return true;
						}
					}
				}
			}
		}
	}
	return false;
}

///////////////////////////////////////////////////////////////////////////
//概略:
//	円と矩形のあたり判定
//引数:
//	CIRCLE* circle1:円
//	BOX* box1:矩形
//戻り値:	
//	int TRUE:当たった
//	NO_HIT:当たらなかった
///////////////////////////////////////////////////////////////////////////
bool CheckHitCircleandBox(CircleClass *circle1 , BoxClass *box1)
{
	//お互いが当たる可能性があるかを判定する
	if(HitBoxandRangeContact(&circle1->GetPosition() , &box1->GetPosition() , circle1->GetRadius() + box1->GetSemiLongAxis()))
	{
		POSITION Circle1Position = circle1->GetPosition();

		POSITION Box1Position = box1->GetPosition();
		FOUR_VERTEX Box1Vertex;

		Box1Vertex = box1->GetVertex();
		THREE_DIMENSIONAL_VECTOR Box1SemiLongVector = box1->GetSemiLongVector();
		THREE_DIMENSIONAL_VECTOR Box1SemiShortVector = box1->GetSemiShortVector();

		POSITION LocalVertex_of_Box1Looking_from_Circle1;
		double length;

		//circle1からbox1の頂点を見る
		length = GetDistance(&Circle1Position , &Box1Position);

		//頂点と当たっているか確認する
		//一番近い頂点を調べる
		for(int i = 1 ; i <= 4 ; i++)
		{
			if(length < GetDistance(&Box1Vertex.m_VertexPosition[i] , &Circle1Position))
			{
				//頂点のローカル座標を出す
				LocalVertex_of_Box1Looking_from_Circle1.m_Vector.x = Box1Vertex.m_VertexPosition[i].m_Vector.x - Circle1Position.m_Vector.x;	//x座標
				LocalVertex_of_Box1Looking_from_Circle1.m_Vector.y = Box1Vertex.m_VertexPosition[i].m_Vector.y - Circle1Position.m_Vector.y;	//y座標

				//lengthの更新
				length = GetDistance(&Box1Vertex.m_VertexPosition[i] , &Circle1Position);
			}
		}

		//頂点と当たっているか確認する
		if(LocalVertex_of_Box1Looking_from_Circle1.m_Vector.Magnitude() < circle1->GetRadius())
		{
			return true;
		}

		//辺と当たっているか確認する
		//上下辺とのあたり判定を確認する
		if(Circle1Position.m_Vector.x < Box1Position.m_Vector.x + abs(Box1SemiLongVector.x + Box1SemiShortVector.x) &&
			Circle1Position.m_Vector.x > Box1Position.m_Vector.x - abs(Box1SemiLongVector.x + Box1SemiShortVector.x))
		{
			if((Circle1Position.m_Vector.y - Box1Position.m_Vector.y) * (Circle1Position.m_Vector.y - Box1Position.m_Vector.y) <
				(circle1->GetRadius() + abs(Box1SemiLongVector.y + Box1SemiShortVector.y)) *
				(circle1->GetRadius() + abs(Box1SemiLongVector.y + Box1SemiShortVector.y)))
			{
				return true;
			}
		}
		//左右辺とのあたり判定を確認する
		else if(Circle1Position.m_Vector.y < Box1Position.m_Vector.y + abs(Box1SemiLongVector.y + Box1SemiShortVector.y) &&
			Circle1Position.m_Vector.y > Box1Position.m_Vector.y - abs(Box1SemiLongVector.y + Box1SemiShortVector.y))
		{
			if((Circle1Position.m_Vector.x - Box1Position.m_Vector.x) * (Circle1Position.m_Vector.x - Box1Position.m_Vector.x) <
				(circle1->GetRadius() + abs(Box1SemiLongVector.x + Box1SemiShortVector.x)) *
				(circle1->GetRadius() + abs(Box1SemiLongVector.x + Box1SemiShortVector.x)))
			{
				return true;
			}
		}
				
		return false;
	}

	return false;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	2点間の距離を取る
//引数:
//	position1:点1の座標へのポインタ
//	position2:点2の座標へのポインタ
//戻り値:
//	2点間の距離
//////////////////////////////////////////////////////////////////////////////
double GetDistance(POSITION *position1 , POSITION *position2)
{
	return sqrt((position1->m_Vector.x - position2->m_Vector.x) * (position1->m_Vector.x - position2->m_Vector.x) +
		(position1->m_Vector.y - position2->m_Vector.y) * (position1->m_Vector.y - position2->m_Vector.y) +
		(position1->m_Vector.z - position2->m_Vector.z) * (position1->m_Vector.z - position2->m_Vector.z));
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	内積計算
//引数:
//	*vector1:ベクトル1
//	*vector2:ベクトル2
//戻り値:
//	内積した値
//////////////////////////////////////////////////////////////////////////////
double InnerProduct(THREE_DIMENSIONAL_VECTOR *vector1 , THREE_DIMENSIONAL_VECTOR *vector2)
{
	return vector1->x * vector2->x + vector1->y * vector2->y + vector1->z *vector2->z;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	外積計算
//引数:
//	*vector1:ベクトル1
//	*vector2:ベクトル2
//戻り値:
//	外積した値
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSIONAL_VECTOR CrossProduct(THREE_DIMENSIONAL_VECTOR *vector1 , THREE_DIMENSIONAL_VECTOR *vector2)
{
	THREE_DIMENSIONAL_VECTOR ret;
	ret.x = vector1->y * vector2->z - vector1->z * vector2->y;
	ret.y = vector1->z * vector2->x - vector1->x * vector2->z;
	ret.z = vector1->x * vector2->y - vector1->y * vector2->x;
	return ret;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	当たり判定を取る範囲を限定する
//引数:
//	POSITION* objact1:オブジェクト1の位置ベクトル
//	POSITION* object2:オブジェクト2の位置ベクトル
//	double range:限定する範囲の半径
//戻り値:
//	bool true:範囲内にいる
//	bool false:範囲内にいない
//////////////////////////////////////////////////////////////////////////////
bool HitBoxandRangeContact(POSITION* object1 , POSITION* object2 , double range)
{
	if(GetDistance(object1 , object2) > range)
	{
		return false;
	}
	else
	{
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	2次元ベクトルを回転させたベクトルを求める
//引数:
//	THREE_DIMENSIONAL_VECTOR *vector:元のベクトル
//	double angle:回転させる角度(ラジアン)
//////////////////////////////////////////////////////////////////////////////
THREE_DIMENSIONAL_VECTOR RotateVector2(THREE_DIMENSIONAL_VECTOR *vector , double angle)
{
	double TempX = vector->x;	//一時的にx座標を入れるための変数
	double TempY = vector->y;	//一時的にy座標を入れるための変数
	THREE_DIMENSIONAL_VECTOR ret;

	//行列計算
	ret.x = TempX * cos(angle) - TempY * sin(angle);
	ret.y = TempX * sin(angle) + TempY * cos(angle);

	return ret;
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	2次元ベクトルを回転させる
//引数:
//	THREE_DIMENSIONAL_VECTOR &vector:回転させるベクトル
//	double angle:回転させる角度(ラジアン)
//////////////////////////////////////////////////////////////////////////////
void RotateVector2(THREE_DIMENSIONAL_VECTOR &vector , double angle)
{
	double TempX = vector.x;	//一時的にx座標を入れるための変数
	double TempY = vector.y;	//一時的にy座標を入れるための変数

	//行列計算
	vector.x = TempX * cos(angle) - TempY * sin(angle);
	vector.y = TempX * sin(angle) + TempY * cos(angle);
}

//////////////////////////////////////////////////////////////////////////////
//概略:
//	二次元ベクトルの角度を取る
//引数:
//	double x:ベクトルのx成分
//	double y:ベクトルのy成分
//戻り値:
//	double angle:ベクトルの角度
//////////////////////////////////////////////////////////////////////////////
double GetVector2Angle(double x , double y)
{
	return atan2(y , x);
}


double InterSectionTime(POSITION* Position_of_Object1 , VELOCITY* Velocity_of_Object1 , POSITION* Position_of_Object2 , VELOCITY* Velocity_of_Object2)
{
	double det = 0;
	if((det = Velocity_of_Object1->m_Vector.y * Velocity_of_Object2->m_Vector.x - Velocity_of_Object1->m_Vector.x * Velocity_of_Object2->m_Vector.y) == 0) return -1;
	double con = Velocity_of_Object2->m_Vector.x * (Position_of_Object2->m_Vector.y - Position_of_Object1->m_Vector.y) - Velocity_of_Object2->m_Vector.y * (Position_of_Object2->m_Vector.x - Position_of_Object1->m_Vector.x);

	double t = con / det;

	return t;
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(double value)
{
	return 2.0 * value / WINDOW_WIDTH - 1.0;
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(double value)
{
	return 2.0 * value / WINDOW_HEIGHT - 1.0;
}