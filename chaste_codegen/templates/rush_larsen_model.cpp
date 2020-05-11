{% include "Shared/cpp/header_comments" %}
{% include "Shared/cpp/includes" %}
{% include "Shared/cpp/UseCellMLDefaultStimulus" %}
{% include "Shared/cpp/GetIntracellularCalciumConcentration" %}
{% include "RL/cpp/constructor_declaration" %}
{% include "Shared/cpp/constructor_body" %}
{% include "Shared/cpp/destructor" %}
{% include "Shared/cpp/VerifyStateVariables" %}
{% include "Shared/cpp/GetIIonic" %}
{% include "RL/cpp/EvaluateEquations" %}
{% include "RL/cpp/ComputeOneStepExceptVoltage" %}
{%- include "Shared/cpp/ComputeDerivedQuantities" %}
{% include "Shared/cpp/OdeSystemInformation" %}
{% include "Shared/cpp/CHASTE_CLASS_EXPORT" %}