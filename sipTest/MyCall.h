#include <pjsua2.hpp>

using namespace pj;

class MyCall : public Call
{
private:
	AudioMediaPlayer *sending_player;
	AudioMedia *play_med;
	//AudioMediaRecorder incomingRecoder;
	//AudioMediaRecorder outgoingRecoder;
public:
	//MyCall();
	MyCall(Account &acc, AudioMediaPlayer* player, int call_id = PJSUA_INVALID_ID);
	~MyCall();

	// Notification when call's state has changed.
	virtual void onCallState(OnCallStateParam &prm);

	// Notification when call's media state has changed.
	virtual void onCallMediaState(OnCallMediaStateParam &prm);

	void MakeCall(const std::string &callingNumber);
	void Hangup();
};

