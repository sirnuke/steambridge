// Steam Testing Header

#include <iostream>

//#define VERSION_SAFE_STEAM_API_INTERFACES
#include <steam_api.h>

using namespace std;

class TestCB
{
	public:
		TestCB()
		{
		}

		void callback(SteamServersConnected_t *cb2)
		{
			cout << "Callback!" << (int)(cb2) << endl;
		}
};

class TestCB2 : protected CCallbackBase
{
	public:
		TestCB2()
		{
			m_nCallbackFlags = 0;
			m_iCallback = 0;

			a = NULL;
			c = NULL;
			d = NULL;
			b = 0;
		}

		virtual void Run(void *pvParam)
		{
		}

		virtual void Run(void *pvParam, bool bIOFailure, SteamAPICall_t hSteamAPICall)
		{
		}

		virtual int GetCallbackSizeBytes()
		{
			return sizeof(SteamServersConnected_t);
		}

		virtual void doRegister(int callback)
		{
			SteamAPI_RegisterCallback(this, callback);
		}

	private:
		void *a;
		int b;
		void *c;
		void *d;
};

int main()
{
	SteamAPI_Init();

	TestCB cb;

	CCallbackManual<TestCB, SteamServersConnected_t, false> callback = CCallbackManual<TestCB, SteamServersConnected_t, false>();
	//(&cb, &TestCB::callback);

	callback.Register(&cb, &TestCB::callback);

	TestCB2 cb2 = TestCB2();
	cb2.doRegister(SteamServersConnected_t::k_iCallback);

	SteamAPI_Shutdown();
	return 0;
}
