#include"AudioManager.h"
#include"../ResouceManager/ResouceManager.h"
AudioManager::AudioManager()
{
}

AudioManager::~AudioManager()
{
}
bool AudioManager::Initialize()
{
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/punchshot.wav"), _se[0],MAX_PLAY,false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/indestructible.wav"), _se[1], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/destruction.wav"), _se[2], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/pointaddition.wav"), _se[3], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/explosion.wav"), _se[4], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/Item/powerup.wav"), _se[5], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/Item/noitem.wav"), _se[6], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/Item/thunder.wav"), _se[7], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/select.wav"), _se[8], MAX_PLAY, false);
	SoundDevice.CreateSharedSoundFromFile(_T("Audio/SoundEffect/Cancel.wav"), _se[9], MAX_PLAY, false);

	auto whistle        = ResouceManager::Instance().LordSoundFile(_T("Audio/SoundEffect/whistle.wav"));
	auto signal         = ResouceManager::Instance().LordSoundFile(_T("Audio/SoundEffect/signal.wav"));
	auto dramroll       = ResouceManager::Instance().LordSoundFile(_T("Audio/SoundEffect/dramroll.wav"));
	auto cracker        = ResouceManager::Instance().LordSoundFile(_T("Audio/SoundEffect/cracker.wav"));

	auto titlebgm       = ResouceManager::Instance().LordMusicFile(_T("Audio/Bgm/title.wav"));
	auto mainbgm        = ResouceManager::Instance().LordMusicFile(_T("Audio/Bgm/main.wav"));
	auto speedupmainbgm = ResouceManager::Instance().LordMusicFile(_T("Audio/Bgm/mainspeedup.wav"));
	auto resultbgm      = ResouceManager::Instance().LordMusicFile(_T("Audio/Bgm/result.wav"));
	_bgm.insert(std::make_pair(TITLE, std::move(titlebgm)));
	_bgm.insert(std::make_pair(MAIN, std::move(mainbgm)));
	_bgm.insert(std::make_pair(SPEEDUPMAIN, std::move(speedupmainbgm)));
	_bgm.insert(std::make_pair(RESULT, std::move(resultbgm)));

	std::string oneplaytag[] = { WHISTLE ,SIGNAL,DRAMROLL,CRACKER};
	SOUND onese[] = { whistle,signal,dramroll,cracker };
	for (int i = 0; i < sizeof(onese) / sizeof(onese[0]); i++)
	{
		_onese.insert(std::make_pair(oneplaytag[i], std::move(onese[i])));
		_ispnplay.insert(std::make_pair(oneplaytag[i], std::move(false)));
	}


	_setag[0] = PUNCH_SHOOT_SE;
	_setag[1] = INDESCTIBLE_SE;
	_setag[2] = DESTRUCTION_SE;
	_setag[3] = POINTADDITION_SE;
	_setag[4] = EXPLOSION_SE;
	_setag[5] = POWERUP‗SE;
	_setag[6] = POWERDOWN_SE;
	_setag[7] = THUNDER_SE;
	_setag[8] = SELECT‗SE;
	_setag[9] = CANCEL_SE;
	return true;
}
/**
 * @fn 　　SE
 * @brief  1回のみ再生するSE
 * @param  (std::string tag) 再生するSEのタグ
 * @return 再生されたかの可否
 */
bool AudioManager::OneSe(std::string tag)
{
	if (_ispnplay.at(tag))return _onese.at(tag)->IsPlaying();
		_onese.at(tag)->Play();
		_ispnplay.at(tag) = true;
}
/**
 * @fn    SE
 * @brief 複数回再生するSE
 * @param (std::string tag) 再生するSEのタグ
 */
void AudioManager::MultipleSe(std::string tag)
{
	for (int i = 0; i < ALL_SE; i++)
	{
		if (SeTagMatch(tag,i))SePlay(i);
	}
}

/**
 * @fn    BGM
 * @brief BGMの再生
 * @param (std::string tag) 再生するBGMのタグ
 */
void AudioManager::BgmPlay(std::string tag)
{
	BgmStop(tag);
	if(!_bgm.at(tag)->IsPlaying())
	_bgm.at(tag)->Play();
}

/**
 * @fn    BGM
 * @brief BGMの停止
 * @param (std::string tag) 停止するBGMのタグ
 */
void AudioManager::BgmStop(std::string tag)
{
	for (auto& sound : _bgm)
	{
		if (sound.first != tag)sound.second->Stop();
	}
}

/**
 * @fn     タグ検索
 * @brief  引数で設定したタグが一致しているか
 * @param  (std::string tag) 
 * @return タグの一致の可否
 */
bool AudioManager::SeTagMatch(std::string tag,int index)
{
	return tag == _setag[index];
}

/**
 * @fn    SE
 * @brief 引数で設定したSEが再生されていない時に再生する
 * @param (std::string tag) 再生したいSEの添え字
 */
void AudioManager::SePlay(int index)
{
	for (auto& sound : _se[index])
	{
		if (!sound->IsPlaying())
		{
			sound->Play();
			break;
		}
	}
}
