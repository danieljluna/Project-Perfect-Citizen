#pragma once

#include "../Engine/inputComponent.h"

namespace ppc {
	class TextCharacterUpdate;
	class ReportScreenInput : public ppc::InputComponent {

	private:

		TextCharacterUpdate* tcu_;

	public:

		ReportScreenInput();
		ReportScreenInput(InputHandler&);
		~ReportScreenInput();

		void setTextCharacterUpdate(TextCharacterUpdate&);
		void setInputHandle(InputHandler&);
		virtual bool registerInput(ppc::Event ev) override;

	};
};