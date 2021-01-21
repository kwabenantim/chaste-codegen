import pytest
from cellmlmanip.rdf import create_rdf_node

from chaste_codegen._rdf import (
    BQBIOL,
    OXMETA,
    PRED_IS,
    PRED_IS_VERSION_OF,
    get_variables_transitively,
)


def test_namespaces():
    assert OXMETA == 'https://chaste.comlab.ox.ac.uk/cellml/ns/oxford-metadata#'
    assert BQBIOL == 'http://biomodels.net/biology-qualifiers/'

    assert PRED_IS == create_rdf_node((BQBIOL, 'is'))
    assert PRED_IS_VERSION_OF == create_rdf_node((BQBIOL, 'isVersionOf'))


def test_wrong_params1(s_model):
    with pytest.raises(AssertionError, match="Expecting term to be a namespace tuple"):
        get_variables_transitively(s_model, None)


def test_wrong_params2():
    with pytest.raises(AssertionError, match="Expecting model to be a cellmlmanip Model"):
        get_variables_transitively(None, (OXMETA, 'IonicCurrent'))


def test_rdf(s_model):
    all_currents = get_variables_transitively(s_model, (OXMETA, 'IonicCurrent'))
    print(all_currents)
    assert str(all_currents) == ("[_cell$i_Stim, _INa$i_Na, _INab$i_Nab, _IKr$i_Kr, _IKs$i_Ks, _Itos$i_tos, "
                                 "_Itof$i_tof, _IK1$i_K1, _IClb$i_Clb, _ICaL$i_CaL, _INaCa$i_NaCa, "
                                 "_ICap$i_Cap, _ICab$i_Cab, _Jrel_SR$j_rel_SR]")
