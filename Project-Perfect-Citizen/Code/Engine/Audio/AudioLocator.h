#pragma once

namespace ppc {

    class Audio;
    class NullAudio;

	//////////////////////////////////////////////////
	///@brief AudioLocator class. Acts almost like a
	///singleton. The purpose of AudioLocator is to 
	///decouple Audio from its children. Is entirely static.
	///@details It serves as a sort of socket for the audio engine. You 
	///"plug" the child of audio that you want active
	///into AudioLocator in order to play it. 
	///This is done through assign(); A user can get
	///the currently plugged in audio service by way of
	/// getAudio()
	//////////////////////////////////////////////////
	class AudioLocator {
	private:
		//////////////////////////////////////////////////
		///@brief Currently activated service. Defaults to
		///the nullService once initialized() is called
		//////////////////////////////////////////////////
		static ppc::Audio* service_;
		//////////////////////////////////////////////////
		///@brief copy of the nullService the locator can
		///reference at any time
		///@details The purpose of this nullService is to
		///be able to turn off sound at will, as the 
		///nullService techincally does nothing. Bonus:
		///this gaurantees that service will never return a
		///nullptr. 
		//////////////////////////////////////////////////
		static ppc::NullAudio nullService_;
	public:
		//////////////////////////////////////////////////
		///@brief Returns service_
		///@details used to assign to an pcc::Audio* pointer
		///example: Audio* audio = AudioLocator::getAudio();
		//////////////////////////////////////////////////
		static ppc::Audio* getAudio();
		//////////////////////////////////////////////////
		///@brief sets the service_ variable
		///@details "plugs in" the service the progammer
		///wants to use. This service is then requested
		///by getAudio(). In case of mistakes, will default
		/// the nullAudio
		//////////////////////////////////////////////////
		static void assign(ppc::Audio* service);
		//////////////////////////////////////////////////
		///@brief IMPORTANT must be called before any part
		///of the audio engine is used. Defaults everything
		///to nullAudio;
		//////////////////////////////////////////////////
		static void initialize();
	};
};