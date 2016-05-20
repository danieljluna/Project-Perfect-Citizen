#pragma once

#include "../Engine/updateComponent.h"
#include "../Engine/event.h"
#include "../Engine/subject.h"

#include <SFML/System/Time.hpp>

#include <vector>

namespace ppc {

    class TimerUpdateCmpnt : public UpdateComponent {
    public:

      /////////////////////////////////////////////////////////////////
      // Constructors and Destructor
      /////////////////////////////////////////////////////////////////

        TimerUpdateCmpnt();

        ~TimerUpdateCmpnt();


      /////////////////////////////////////////////////////////////////
      // Timer Manipulation
      /////////////////////////////////////////////////////////////////

        void playTimer(unsigned int timer);

        void pauseTimer(unsigned int timer);
        
        void resetTimer(unsigned int timer, sf::Time newTime);

        void ffwdTimer(unsigned int timer, sf::Time dt);

        void rewindTimer(unsigned int timer, sf::Time dt);

        unsigned int createTimer(sf::Time time, int evKey = -1);

        bool isValidTimer(unsigned int timer);


      /////////////////////////////////////////////////////////////////
      // Event Mapping
      /////////////////////////////////////////////////////////////////

        int mapEvent(ppc::Event ev);

        ppc::Event getMapping(int evKey);

        void setTimerEvent(unsigned int timer, ppc::Event ev);

        void setTimerEvent(unsigned int timer, int evKey);


      /////////////////////////////////////////////////////////////////
      // Subject
      /////////////////////////////////////////////////////////////////

        Subject& onTimer() { return onTimer_; };


      /////////////////////////////////////////////////////////////////
      // Inherited Interface
      /////////////////////////////////////////////////////////////////

        void update(sf::Time& deltaTime) override;

        void recieveMessage(ppc::Event ev) override;


    private:

        void activateTimer(unsigned int timer);

        struct Timer {
            sf::Time timeLeft;
            int eventIndex = -1;
            bool isRunning = true;
        };

        std::vector<ppc::Event> eventVec_;

        std::vector<Timer> timerVec_;

        Subject onTimer_;


    };
};


