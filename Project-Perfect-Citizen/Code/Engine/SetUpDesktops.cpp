#include "SetUpDesktops.h"

#include "World.h"
#include "desktop.h"
#include "Window.h"

#include "../Game/createDesktop.h"
#include "../Game/createWindow.h"
#include "../Game/endAnimationUpdateComponent.hpp"
#include "../Game/endingAnimationRender.hpp"
#include "../Game/BadCopRenderComponent.hpp"
#include "../Game/BadCopUpdateComponent.hpp"
#include "../Game/bootLoadingUpdateComponent.hpp"
#include "../Game/bootLoadingAnimationRender.hpp"
#include "../Game/textLabelComponent.hpp"

void ppc::setUpLogoDesktop(ppc::Desktop& myDesktop) {

	Window* bootWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

	Entity badCop;

	BadCopRenderComponent* badCopRender = new BadCopRenderComponent(myDesktop.getIconSheet());
	BadCopUpdateComponent* badCopUpdate = new BadCopUpdateComponent(*badCopRender, 0.12f);

	badCop.addComponent(badCopRender);
	badCop.addComponent(badCopUpdate);

	bootWindow->addEntity(badCop);

	myDesktop.addWindow(bootWindow);
}

void ppc::setUpBootDesktop(ppc::Desktop& myDesktop) {

	Window* bootWindow = new Window(1800, 1000, sf::Color(0, 0, 0));

	Entity loading;


	textLabelComponent* textLabel = new textLabelComponent(World::getFont(World::FontList::Consola), 
		sf::Color::Green, 0, 0, 20,
		" PCOS(C) , UNMOS. UNAUTHORIZED USE OF THIS TERMINAL CAN RESULT IN PENALTY BY DEATH. \n   Beginning File System Initialization \n");

	bootLoadingAnimationRender* bootRender = new bootLoadingAnimationRender(myDesktop.getButtonSheet(), *textLabel, 7, 5);

	bootLoadingUpdateComponent* bootUpdate = new bootLoadingUpdateComponent(*bootRender, 0.1f);

	Entity badCop;

	loading.addComponent(bootRender);
	loading.addComponent(bootUpdate);
	loading.addComponent(textLabel);
	bootWindow->addEntity(loading);


	myDesktop.addWindow(bootWindow);

}


void ppc::setUpLoginDesktop(ppc::Desktop& myDesktop) {

	createLoginDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}



void ppc::setUpEndDesktop(ppc::Desktop& myDesktop) {

}


void ppc::setUpPlayerDesktop(ppc::Desktop& myDesktop) {
	createPlayerDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}

void ppc::setUpDummyDesktop(ppc::Desktop& myDesktop) {
	createDummyDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}

void ppc::setUpTeacherDesktop(ppc::Desktop& myDesktop) {
	createTeacherDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}

void ppc::setUpArtistDesktop(ppc::Desktop& myDesktop) {
	createArtistDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}

void ppc::setUpPoliticianDesktop(ppc::Desktop& myDesktop) {
	createPoliticianDesktop(myDesktop, *myDesktop.getDesktopWindow(),
		myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());

}

void ppc::setUpHackerDesktop(ppc::Desktop& myDesktop) {
    createHackerDesktop(myDesktop, *myDesktop.getDesktopWindow(),
        myDesktop.getInputHandler(), myDesktop.getIconSheet(), myDesktop.getButtonSheet());
}

void ppc::setUpPostHackerDesktop(ppc::Desktop& myDesktop) {

}
