#include "stdafx.h"
#include "MyCall.h"
#include <iostream>

using namespace std;



MyCall::MyCall(Account &acc, AudioMediaPlayer* player, int call_id)
	: Call(acc, call_id)
{
	sending_player = player;
	play_med = &(Endpoint::instance().audDevManager().getPlaybackDevMedia());
}


MyCall::~MyCall()
{
}

void MyCall::onCallState(OnCallStateParam & prm)
{
	CallInfo ci = getInfo();
	if (ci.state == PJSIP_INV_STATE_DISCONNECTED) {
		/* Delete the call */
		delete this;
	}
}

void MyCall::onCallMediaState(OnCallMediaStateParam & prm)
{
	CallInfo ci = getInfo();
	AudioMedia *aud_med = NULL;

	// Iterate all the call medias and find out which media index is the audio
	for (unsigned i = 0; i<ci.media.size(); ++i) {
		if (ci.media[i].type == PJMEDIA_TYPE_AUDIO) {
			aud_med = (AudioMedia *)getMedia(i);
			break;
		}
	}

	if (aud_med != NULL)
	{
		try {
			cout << "Send stuff to media" << endl;
			
			/*incomingRecoder.createRecorder("incomming.wav");
			outgoingRecoder.createRecorder("outgoing.wav");
*/
			sending_player->startTransmit(*aud_med);
			//player->startTransmit(outgoingRecoder);
			//aud_med->startTransmit(incomingRecoder);
			aud_med->startTransmit(*play_med);
		}
		catch (Error& err) {
		}
	}
}

void MyCall::MakeCall(const std::string &callingNumber) 
{
	CallOpParam prm(true); // Use default call settings
	try {
		this->makeCall(callingNumber, prm);
	}
	catch (Error& err) {
		cout << err.info() << endl;
	}
}

void MyCall::Hangup()
{
	CallOpParam prm(true); // Use default call settings
	try {
		this->hangup(prm);
	}
	catch (Error& err) {
		cout << err.info() << endl;
	}
}
