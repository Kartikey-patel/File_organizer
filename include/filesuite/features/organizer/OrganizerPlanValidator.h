
#pragma once

#include "filesuite/features/organizer/OrganizerPlan.h"

namespace filesuite::features::organizer {

class OrganizerPlanValidator {
public:
    void validate(OrganizerPlan& plan) const;
};

}
