#ifdef CHASTE_CVODE
{% include "Shared/hpp/header_comments" %}
{% include "Shared/hpp/includes" %}
#include "AbstractCvodeCellWithDataClamp.hpp"
{% with %}{% set base_class = "AbstractCvodeCellWithDataClamp" %}{% include "Shared/hpp/class_declaration" %}{% endwith %}
{% include "Cvode/hpp/public" %}