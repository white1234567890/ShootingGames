#include "system.h"
#include <time.h>
#include <math.h>

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
	POSITION Box1Position = box1->GetPosition();	//box1の位置
	POSITION Box2Position = box2->GetPosition();	//box2の位置
	VARIABLE_VERTEX Box1Vertex;	//box1の頂点
	VARIABLE_VERTEX Box2Vertex;	//box2の頂点
	for(int i = 0 ; i < 4 ; i++)
	{
		Box1Vertex.m_VertexPosition.push_back(Box1Position);
		Box2Vertex.m_VertexPosition.push_back(Box2Position);
	}
	Box1Vertex = box1->GetVertex();
	Box2Vertex = box2->GetVertex();
	THREE_DIMENSION_VECTOR Box1SemiLongVector = box1->GetSemiLongVector();	//box1の半長軸ベクトル
	THREE_DIMENSION_VECTOR Box2SemiLongVector = box2->GetSemiLongVector();	//box2の半長軸ベクトル
	THREE_DIMENSION_VECTOR Box1SemiShortVector = box1->GetSemiShortVector();	//box1の半短軸ベクトル
	THREE_DIMENSION_VECTOR Box2SemiShortVector = box2->GetSemiShortVector();	//box2の半短軸ベクトル

	//お互いが当たる可能性があるかを判定する
	if(abs(Box1Position.m_Vector.x - Box2Position.m_Vector.x) < box1->GetSemiLongAxis() + box2->GetSemiLongAxis() &&
		abs(Box1Position.m_Vector.y - Box2Position.m_Vector.y) < box1->GetSemiShortAxis() + box2->GetSemiLongAxis())
	{
		POSITION LocalVertex_of_Box1Looking_from_Box2;	//box2から見たbox1の頂点
		POSITION LocalVertex_of_Box2Looking_from_Box1;	//box1から見たbox2の頂点
		double length;	//距離

		//box2からbox1の頂点を見る場合
		 length = GetDistance(&Box1Position , &Box2Position);	//box1とbox2の距離

		//どの頂点が一番近いかを考える
		for(int i = 0 ; i < 4 ; i++)
		{
			if(length < GetDistance(&Box1Vertex.m_VertexPosition[i], &Box2Position))
			{
				//一番近い頂点のローカル座標を出す
				LocalVertex_of_Box1Looking_from_Box2.m_Vector = Box1Vertex.m_VertexPosition[i].m_Vector - Box2Position.m_Vector;

				//lengthの更新
				length = GetDistance(&Box1Vertex.m_VertexPosition[i] , &Box2Position);
			}
		}

		//box2から見たbox1の頂点のx成分がy成分より大きいとき
		if(abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.x) > abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.y))
		{
			//box2から見たbox1の頂点のx成分がbox2の半長軸長より小さい
			//かつ
			//box2から見たbox1の頂点のy成分がbox2の半短軸長より小さいとき
			if(abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.x) < box2->GetSemiLongAxis() &&
				abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.y) < box2->GetSemiShortAxis())
			{
				//swapしてメモリを開放する
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//trueを返す
				return true;
			}
		}
		//box2から見たbox1の頂点のy成分がx成分より大きいとき
		else
		{
			//box2から見たbox1の頂点のx成分がbox2の半短軸長より小さい
			//かつ
			//box2から見たbox1の頂点のy成分がbox2の半長軸長より小さいとき
			if(abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.x) < box2->GetSemiShortAxis() &&
				abs(LocalVertex_of_Box1Looking_from_Box2.m_Vector.y) < box2->GetSemiLongAxis())
			{
				//swapしてメモリを開放する
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//trueを返す
				return true;
			}
		}

		//box1からbox2の頂点を見る場合
		 length = GetDistance(&Box2Position , &Box1Position);	//box1とbox2の距離

		//どの頂点が一番近いかを考える
		for(int i = 1 ; i <= 4 ; i++)
		{
			if(length < GetDistance(&Box2Vertex.m_VertexPosition[i], &Box1Position))
			{
				//一番近い頂点のローカル座標を出す
				LocalVertex_of_Box2Looking_from_Box1.m_Vector = Box2Vertex.m_VertexPosition[i].m_Vector - Box1Position.m_Vector;

				//lengthの更新
				length = GetDistance(&Box2Vertex.m_VertexPosition[i] , &Box1Position);
			}
		}
			
		//box1から見たbox2の頂点のx成分がy成分より大きいとき
		if(abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.x) > abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.y))
		{
			//box1から見たbox2の頂点のx成分がbox1の半長軸長より小さい
			//かつ
			//box1から見たbox2の頂点のy成分がbox1の半短軸長より小さいとき
			if(abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.x) < box1->GetSemiLongAxis() &&
				abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.y) < box1->GetSemiShortAxis())
			{
				//swapしてメモリを開放する
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//trueを返す
				return true;
			}
		}
		//box1から見たbox2の頂点のy成分がx成分より大きいとき
		else
		{
			//box1から見たbox2の頂点のx成分がbox1の半短軸長より小さい
			//かつ
			//box1から見たbox2の頂点のy成分がbox1の半長軸長より小さいとき
			if(abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.x) < box1->GetSemiShortAxis() &&
				abs(LocalVertex_of_Box2Looking_from_Box1.m_Vector.y) < box1->GetSemiLongAxis())
			{
				//swapしてメモリを開放する
				std::vector<POSITION> NullVector1;
				Box1Vertex.m_VertexPosition.swap(NullVector1);
				std::vector<POSITION> NullVector2;
				Box2Vertex.m_VertexPosition.swap(NullVector2);
				//trueを返す
				return true;
			}
		}

	}
	//swapしてメモリを開放する
	std::vector<POSITION> NullVector1;
	Box1Vertex.m_VertexPosition.swap(NullVector1);
	std::vector<POSITION> NullVector2;
	Box2Vertex.m_VertexPosition.swap(NullVector2);
	//falseを返す
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
		VARIABLE_VERTEX Box1Vertex;
		for(int i = 0 ; i < 4 ; i++)
		{
			Box1Vertex.m_VertexPosition.push_back(Box1Position);
		}
		Box1Vertex = box1->GetVertex();
		THREE_DIMENSION_VECTOR Box1SemiLongVector = box1->GetSemiLongVector();
		THREE_DIMENSION_VECTOR Box1SemiShortVector = box1->GetSemiShortVector();

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

			//	switch (i)
			//	{
			//	case 1:
			//		if(length < GetDistance(&box1->m_vertex.vertex1 , &circle1->m_position))
			//		{
			//			//box1.vertex1の判定
			//			//box1.vertex1のローカル座標を出す
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex1.x - circle1->m_position.x;	//x座標
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex1.y - circle1->m_position.y;	//y座標

			//			//lengthの更新
			//			length = GetDistance(&box1->m_vertex.vertex1 , &circle1->m_position);
			//		}
			//		break;

			//	case 2:
			//		if(length < GetDistance(&box1->m_vertex.vertex2 , &circle1->m_position))
			//		{
			//			//box1.vertex2の判定
			//			//box1.vertex2のローカル座標を出す
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex2.x - circle1->m_position.x;	//x座標
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex2.y - circle1->m_position.y;	//y座標

			//			//lengthの更新
			//			length = GetDistance(&box1->m_vertex.vertex2 , &circle1->m_position);
			//		}
			//		break;

			//	case 3:
			//		if(length < GetDistance(&box1->m_vertex.vertex3 , &circle1->m_position))
			//		{
			//			//box1.vertex3の判定
			//			//box1.vertex3のローカル座標を出す
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex3.x - circle1->m_position.x;	//x座標
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex3.y - circle1->m_position.y;	//y座標

			//			//lengthの更新
			//			length = GetDistance(&box1->m_vertex.vertex3 , &circle1->m_position);		//		}
			//		break;

			//	case 4:
			//		if(length < GetDistance(&box1->m_vertex.vertex4 , &circle1->m_position))
			//		{
			//			//box1.vertex4の判定
			//			//box1.vertex4のローカル座標を出す
			//			LocalVertex_of_Box1Looking_from_Circle1.x = box1->m_vertex.vertex4.x - circle1->m_position.x;	//x座標
			//			LocalVertex_of_Box1Looking_from_Circle1.y = box1->m_vertex.vertex4.y - circle1->m_position.y;	//y座標

			//			//lengthの更新
			//			length = GetDistance(&box1->m_vertex.vertex4 , &circle1->m_position);
			//		}
			//		break;
			//	}
		}

		//頂点と当たっているか確認する
		if(LocalVertex_of_Box1Looking_from_Circle1.m_Vector.Magnitude() < circle1->GetRadius())
		{
			std::vector<POSITION> NullVector;
			Box1Vertex.m_VertexPosition.swap(NullVector);
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
				std::vector<POSITION> NullVector;
				Box1Vertex.m_VertexPosition.swap(NullVector);
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
				std::vector<POSITION> NullVector;
				Box1Vertex.m_VertexPosition.swap(NullVector);
				return true;
			}
		}
		
		std::vector<POSITION> NullVector;
		Box1Vertex.m_VertexPosition.swap(NullVector);
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
double InnerProduct(THREE_DIMENSION_VECTOR *vector1 , THREE_DIMENSION_VECTOR *vector2)
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
THREE_DIMENSION_VECTOR CrossProduct(THREE_DIMENSION_VECTOR *vector1 , THREE_DIMENSION_VECTOR *vector2)
{
	THREE_DIMENSION_VECTOR ret;
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
//	2次元ベクトルを回転させる
//引数:
//	double& x:ベクトルのx成分
//	double& y:ベクトルのy成分
//	double angle:回転させる角度(ラジアン)
//////////////////////////////////////////////////////////////////////////////
void RotateVector2(double& x ,double& y ,double angle)
{
	double TempX = x;	//一時的にx座標を入れるための変数
	double TempY = y;	//一時的にy座標を入れるための変数

	//行列計算
	x = TempX * cos(angle) - TempY * sin(angle);
	y = TempX * sin(angle) + TempY * cos(angle);
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

template<class T>
void ReleaseVector(std::vector<T> &obj)
{
	std::vector<T> NullVector;
	obj.swap(NullVector);
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesX(double value)
{
	return 2.0 * value / WINDOW_WIDTH - 1.0;
}

double Convert_to_RelativeCoordinates_from_AbusoluteCoordinatesY(double value)
{
	return 2.0 * value / WINDOW_HEIGHT - 1.0;
}