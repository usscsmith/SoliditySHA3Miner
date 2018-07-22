#pragma once
#include "managedObject.h"
#include "../openCLSolver.h"

namespace OpenCLSolver
{
	public ref class Solver : public ManagedObject<openCLSolver>
	{
	public:
		delegate void OnGetWorkPositionDelegate(unsigned __int64 %);
		delegate void OnResetWorkPositionDelegate(unsigned __int64 %);
		delegate void OnIncrementWorkPositionDelegate(unsigned __int64 %, unsigned __int64);
		delegate void OnMessageDelegate(System::String ^, int, System::String ^, System::String ^);
		delegate void OnSolutionDelegate(System::String ^, System::String ^, System::String ^, System::String ^, System::String ^, System::String ^, bool);

		OnGetWorkPositionDelegate ^OnGetWorkPositionHandler;
		OnResetWorkPositionDelegate ^OnResetWorkPositionHandler;
		OnIncrementWorkPositionDelegate ^OnIncrementWorkPositionHandler;
		OnMessageDelegate ^OnMessageHandler;
		OnSolutionDelegate ^OnSolutionHandler;

	private:
		OnGetWorkPositionDelegate ^m_managedOnGetWorkPosition;
		OnResetWorkPositionDelegate ^m_managedOnResetWorkPosition;
		OnIncrementWorkPositionDelegate ^m_managedOnIncrementWorkPosition;
		OnMessageDelegate ^m_managedOnMessage;
		OnSolutionDelegate ^m_managedOnSolution;

	public:
		static void preInitialize(bool allowIntel, System::String ^%errorMessage);
		static System::String ^getPlatformNames();
		static int getDeviceCount(System::String ^platformName, System::String ^%errorMessage);
		static System::String ^getDeviceName(System::String ^platformName, int deviceEnum, System::String ^%errorMessage);

	public:
		// require web3 contract getMethod -> _MAXIMUM_TARGET
		Solver(System::String ^maxDifficulty, System::String ^solutionTemplate, System::String ^kingAddress);
		~Solver();

		void setCustomDifficulty(uint32_t customDifficulty);
		void setSubmitStale(bool submitStale);
		bool assignDevice(System::String ^platformName, int const deviceID, float const intensity);
		bool isAssigned();
		bool isAnyInitialised();
		bool isMining();
		bool isPaused();

		// must be in challenge (byte32) + address (byte20) hexadecimal format with "0x" prefix
		void updatePrefix(System::String ^prefix);
		// must be in byte32 hexadecimal format with "0x" prefix
		void updateTarget(System::String ^target);
		// can be in either numeric or hexadecimal format
		void updateDifficulty(System::String ^difficulty);

		void startFinding();
		void stopFinding();
		void pauseFinding(bool pauseFinding);

		// combined hashrate, in H/s
		uint64_t getTotalHashRate();
		// individual hashrate by deviceID, in H/s
		uint64_t getHashRateByDevice(System::String ^platformName, int const deviceEnum);

	private:
		void OnGetWorkPosition(unsigned __int64 %workPosition);
		void OnResetWorkPosition(unsigned __int64 %lastPosition);
		void OnIncrementWorkPosition(unsigned __int64 %lastPosition, unsigned __int64 increment);
		void OnMessage(System::String ^platformName, int deviceID, System::String ^type, System::String ^message);
		void OnSolution(System::String ^digest, System::String ^address, System::String ^challenge, System::String ^difficulty, System::String ^target, System::String ^solution, bool isCustomDifficulty);
	};
}