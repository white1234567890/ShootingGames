#include "WaveManagerClass.h"

#include <fstream>
#include <iostream>
#include <sstream>

#include "system.h"

//実体化
WaveManagerClass* cl_WaveManager;

//コンストラクタ
WaveManagerClass::WaveManagerClass(void)
{
}

//デストラクタ
WaveManagerClass::~WaveManagerClass(void)
{
}

//////////////////////////////////////////////////////////////////////////////
//private関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//ウェーブ生成
//引数:
//	enemy_manager:エネミーマネージャー
//	now_stage:今のステージ
//	noe_wave:今のウェーブ
//戻り値:
//	true:生成成功
//	false:生成失敗
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::CreateWave(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave)
{
	//ウェーブデータをロード
	if(!LoadWaveData(enemy_manager , now_stage , now_wave)) return false;
	//次のウェーブの準備
	m_WaveCounter++;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//ウェーブデータのロード
//引数:
//	enemy_manager:エネミーマネージャー
//	now_stage:今のステージ
//	noe_wave:今のウェーブ
//戻り値:
//	true:生成成功
//	false:生成失敗
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::LoadWaveData(EnemyManagerClass *enemy_manager , std::string now_stage , std::string now_wave)
{
	//読み込むファイル名を指定
	std::string NowStageWave = "data/" + now_stage + "/wave/" + now_wave + ".csv"; 

#ifdef DEBUG
	std::cout << NowStageWave << std::endl;
#endif // DEBUG

	//ファイルをオープン
	std::ifstream ifs(NowStageWave);

	//開けなかったらfalse
	if(ifs.fail()) return false;

#ifdef DEBUG
	std::cout << "Success!" << std::endl;
#endif // DEBUG

	std::string WaveData;	//読み込むデータ
	
	//最初の1行は無視する
	std::getline(ifs , WaveData);

	std::vector<double> TempVector;	//変換データ
	
	//1行ずつ読み込む
	while (std::getline(ifs , WaveData))
	{
		std::string token;	//データ取り出し
		std::istringstream stream(WaveData);	//データ読み込み

		//','が来るたびにデータを取り出す
		while(getline(stream , token , ','))
		{
			//文字から数値へ変換
			TempVector.push_back(std::stod(token));
		}

		//取り出したデータから敵を生成
		enemy_manager->CreateEnemy(this , (int)TempVector[0] , &POSITION(TempVector[1] * WINDOW_WIDTH , TempVector[2] * WINDOW_HEIGHT));

		//変換配列を消去
		TempVector.clear();
	}

	//変換配列を開放
	ReleaseVector(TempVector);
	
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//ウェーブの最大値をロード
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::LoadMaxWave()
{
	//読み込むファイル名を指定
	std::string FileName = "data/" + m_NowStage + "/wave/maxwave.txt"; 

	//ファイルをオープン
	std::ifstream ifs(FileName);

#ifdef DEBUG
	std::cout << FileName << std::endl;
#endif // DEBUG

	//開けなかったらfalse
	if(ifs.fail()) return false;

#ifdef DEBUG
	std::cout << "Success!" << std::endl;
#endif // DEBUG

	std::string MaxWaveNumber;	//データ読み込み

	//データを取り出す
	std::getline(ifs , MaxWaveNumber);

	//文字を数値に変換
	m_MaxWave = std::stoi(MaxWaveNumber);

	return true;
}

//////////////////////////////////////////////////////////////////////////////
//public関数
//////////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////////
//今のステージを調べる
//戻り値:
//	今のステージ
//////////////////////////////////////////////////////////////////////////////
std::string WaveManagerClass::GetNowStage()
{
	return m_NowStage;
}

//////////////////////////////////////////////////////////////////////////////
//初期化
//引数:
//	now_stage:今のステージ番号
//戻り値:
//	true:成功
//	false:データのロードに失敗
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::Initiarize(int now_stage)
{
	//今のステージを文字列として記憶
	m_NowStage = "stage" + std::to_string(now_stage);

	//ウェーブ番号を0に
	m_WaveCounter = 0;

	//ウェーブの最大値を取得
	if(!LoadMaxWave()) return false;
	return true;
}

//////////////////////////////////////////////////////////////////////////////
//更新
//引数:
//	enemy_manager:エネミーマネージャー
//引数:
//	true:更新成功
//////////////////////////////////////////////////////////////////////////////
bool WaveManagerClass::Update(EnemyManagerClass *enemy_manager)
{
	//30秒ごとにウェーブ生成
	if(GetCounter() == 1800 * m_WaveCounter && m_WaveCounter < m_MaxWave)
	{
		//ウェーブ番号を文字列として記憶
		m_NowWave = "wave" + std::to_string(m_WaveCounter + 1);

		//ウェーブ生成
		CreateWave(enemy_manager , m_NowStage , m_NowWave);
	}

	//時間をカウント
	TimeCount();

	return true;
}