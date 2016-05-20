#pragma once

#include "../Engine/updateComponent.h"
#include "../Engine/event.h"

#include <SFML/System/Time.hpp>

#include <vector>
#include <map>

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


      /////////////////////////////////////////////////////////////////
      // Event Mapping
      /////////////////////////////////////////////////////////////////

        int mapEvent(ppc::Event ev);

        ppc::Event getMapping(int key);

        void setTimerEvent(unsigned int timer, ppc::Event ev);

        void setTimerEvent(unsigned int timer, int key);


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

        std::map<int, ppc::Event> eventMap_;

        std::vector<Timer> timerVec_;


    };
};


