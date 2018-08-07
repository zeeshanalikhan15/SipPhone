#include "stdafx.h"
#include "MyAccount.h"
#include <iostream>
#include "MyCall.h"

using namespace std;


MyAccount::MyAccount(callArrived callArrivedCallBack)
{
	CallArrivedCallBack = callArrivedCallBack;
}

void MyAccount :: onRegState(OnRegStateParam &prm) {
	AccountInfo ai = getInfo();
	cout << (ai.regIsActive ? "*** Register:" : "*** Unregister:")
		<< " code=" << prm.code << endl;
}


void MyAccount::onIncomingCall(OnIncomingCallParam &iprm) 
{
	(*CallArrivedCallBack)(iprm.callId, *this);
}
