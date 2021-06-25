//! @file   AudioManager.h
//! @brief  BGMやSEの管理
//! @author 岩井瑞希
//! @date   2021/1/7

#pragma once

#include"../../../ESGLib.h"
#include"../../Data/WordsTable.h"
class AudioManager
{
public:
	AudioManager();
	~AudioManager();
	bool Initialize();
	bool OneSe(std::string tag);
	void MultipleSe(std::string tag);
	void BgmPlay(std::string tag);
	void BgmStop(std::string tag);
	static AudioManager& Instance() {
		static AudioManager instance;
		return instance;
	};
private:
	enum {
		MAX_PLAY = 4,
		ALL_SE = 10
	};
	bool SeTagMatch(std::string tag, int index);
	void SePlay(int index);
	std::map<std::string, MUSIC> _bgm;
	std::map<std::string, SOUND> _onese;
	std::map<std::string, bool> _ispnplay;
	std::string _setag[ALL_SE];
	SOUND _se[ALL_SE][MAX_PLAY];
};