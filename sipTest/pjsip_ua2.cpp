#include "stdafx.h"
#include <pjsua2.hpp>
#include <iostream>
#include "MyCall.h"
#include "MyAccount.h"
#include "config.h"
#include "CustomLogger.h"

using namespace std;
using namespace pj;

MyCall* gCall;
AudioMediaPlayer player;

void MakeCall(MyAccount * acc);
void CallArrived(int callId, MyAccount account);



int main()
{
	Endpoint ep;

	ep.libCreate();

	// Initialize endpoint
	EpConfig ep_cfg;

	//ep_cfg.logConfig.filename =  "testlogfile";
	//ep_cfg.logConfig.fileFlags = PJ_O_APPEND;
	//ep_cfg.logConfig.consoleLevel = 0;
	CustomLogger customAfinitiLogger;
	ep_cfg.logConfig.writer = &customAfinitiLogger;

	ep.libInit(ep_cfg);

	// Create SIP transport. Error handling sample is shown
	TransportConfig tcfg;
	tcfg.port = ListeingPort;
	try {
		ep.transportCreate(PJSIP_TRANSPORT_UDP, tcfg);
	}
	catch (Error &err) {
		cout << err.info() << endl;
		system("Pause");
		return 1;
	}

	// Start the library (worker threads etc)
	ep.libStart();
	cout << "*** PJSUA2 STARTED ***" << endl;

	player.createPlayer("ewt.wav");

	// Configure an AccountConfig
	AccountConfig acfg;
	//acfg.idUri = "sip:5001";

	acfg.idUri = "sip:5001@10.34.21.191";
	acfg.regConfig.registrarUri = "sip:10.34.21.191";
	AuthCredInfo cred("digest", "*", "5001", 0, "test1234");
	acfg.sipConfig.authCreds.push_back(cred);

	/*acfg.idUri = "sip:4001@10.32.5.168";
	acfg.regConfig.registrarUri = "sip:10.32.5.168";
	AuthCredInfo cred("digest", "*", "4001", 0, "4001");
	acfg.sipConfig.authCreds.push_back(cred);*/

	// Create the account
	MyAccount *acc = new MyAccount(&CallArrived);
	acc->create(acfg);
	
	pj_thread_sleep(10000);
	MakeCall(acc);
	
	// Here we don't have anything else to do..
	system("Pause");

	// This will implicitly shutdown the library
	return 0;
}

void MakeCall(MyAccount * acc)
{
		MyCall *call = NULL;
		try
		{
			call = new MyCall(*acc, &player, 2);
			//call->MakeCall("sip:89890011@10.32.7.215");
			call->MakeCall("sip:5001@10.32.5.168");
			//call->MakeCall("sip:2000@10.34.21.154"); 
		}
		catch (Error &err) {
			cout << err.info() << endl;
		}

		pj_thread_sleep(50000);
		cout << "Wait complete hanging up call " << endl;
		if (call != NULL)
			call->Hangup();
}

void CallArrived(int callId, MyAccount account)
{
		cout << "Answering call ... " << endl;
		gCall = new MyCall(account, &player, callId);
		CallOpParam prm;
		prm.statusCode = PJSIP_SC_OK;
		gCall->answer(prm);
}
