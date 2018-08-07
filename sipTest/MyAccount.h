#include <pjsua2.hpp>
using namespace pj;



class MyAccount : public Account
{
	typedef void(*callArrived)(int callId, MyAccount account);
	 callArrived CallArrivedCallBack;
public:
	MyAccount(callArrived callArrivedCallBack);
	virtual void onRegState(OnRegStateParam &prm);
	virtual void onIncomingCall(OnIncomingCallParam &iprm);
};

