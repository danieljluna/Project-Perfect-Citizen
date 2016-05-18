#include "ReportScreenObsvr.h"
#include "../Engine/desktop.h"
#include "CreateReportScreen.h"
#include "../Engine/SuspiciousFileHolder.h"

ppc::ReportScreenObsvr::ReportScreenObsvr() {
}

ppc::ReportScreenObsvr::~ReportScreenObsvr() {
}

ppc::ReportScreenObsvr::ReportScreenObsvr(Desktop &d) {
	dt = &d;
}

void ppc::ReportScreenObsvr::setDesktop(Desktop &d) {
	dt = &d;
}

bool ppc::ReportScreenObsvr::eventHandler(Event ev) {
	if (ev.type == ppc::Event::SubmissionType) {
		if (ev.submission.type == ev.submission.Submit && 
			(SuspiciousFileHolder::getBftVector().size() == 3)) {
			createReportScreen(*dt);
		}
	}

	return false;
}
