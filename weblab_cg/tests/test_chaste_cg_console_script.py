import sys
import logging
import os
import weblab_cg as cg
import pytest
from unittest import mock
from weblab_cg._command_line_script import chaste_codegen
from weblab_cg.tests.chaste_test_utils import compare_file_against_reference


# Show more logging output
LOGGER = logging.getLogger(__name__)
LOGGER.setLevel(logging.DEBUG)


class TestChasteCommandLineScript(object):
    """ Tests weblab_cg command line script."""

    @pytest.mark.chaste
    def test_script_help(self, capsys):
        LOGGER.info('Testing help for command line script\n')
        testargs = ["chaste_codegen", "-h"]
        with mock.patch.object(sys, 'argv', testargs):
            try:
                chaste_codegen()
            except SystemExit:
                pass  # We expect this to print usage and exit
            captured = capsys.readouterr()
            # compare to expected
            output = str(captured.out)
            expected = open(os.path.join(cg.DATA_DIR, 'tests', 'console_sctipt_help.txt'), 'r').read()
            assert output == expected

    @pytest.mark.chaste
    def test_script_version(self, capsys):
        LOGGER.info('Testing version for command line script\n')
        testargs = ["chaste_codegen", "--version"]
        with mock.patch.object(sys, 'argv', testargs):
            try:
                chaste_codegen()
            except SystemExit:
                pass  # We expect this to print usage and exit
            captured = capsys.readouterr()
            # compare to expected
            output = str(captured.out)
            assert output == 'chaste_codegen ' + cg.__version__ + '\n'

    @pytest.mark.chaste
    def test_script_convert(self, capsys, tmp_path):
        LOGGER.info('Testing regular model conversion for command line script\n')
        tmp_path = str(tmp_path)
        model_name = 'hodgkin_huxley_squid_axon_model_1952_modified'
        model_file = os.path.join(cg.DATA_DIR, 'tests', 'cellml', model_name + '.cellml')
        assert os.path.isfile(model_file)
        testargs = ["chaste_codegen", model_file]
        # Call commandline script
        savedPath = str(os.getcwd())
        os.chdir(tmp_path)
        with mock.patch.object(sys, 'argv', testargs):
            chaste_codegen()
        os.chdir(savedPath)
        # Check output
        reference = os.path.join(os.path.join(cg.DATA_DIR, 'tests'), 'chaste_reference_models', 'Normal')
        compare_file_against_reference(os.path.join(reference, model_name + '.hpp'),
                                       os.path.join(tmp_path, model_name + '.hpp'))
        compare_file_against_reference(os.path.join(reference, model_name + '.cpp'),
                                       os.path.join(tmp_path, model_name + '.cpp'))

    @pytest.mark.chaste
    def test_script_class_convtype_output_dll_loadable(self, capsys, tmp_path):
        LOGGER.info('Testing model with options -t Chaste -c --dynamically-loadable and -o for command line script\n')
        tmp_path = str(tmp_path)
        model_name = 'hodgkin_huxley_squid_axon_model_1952_modified'
        model_file = os.path.join(cg.DATA_DIR, 'tests', 'cellml', model_name + '.cellml')
        assert os.path.isfile(model_file)
        outfile = os.path.join(tmp_path, 'output_class.c')
        # Call commandline script
        testargs = ['chaste_codegen', model_file, '-c', 'Chaste_CG', '-t', 'Chaste', '-o', outfile,
                    '--dynamically-loadable']
        with mock.patch.object(sys, 'argv', testargs):
            chaste_codegen()
        # Check output
        reference = os.path.join(os.path.join(cg.DATA_DIR, 'tests'), 'chaste_reference_models', 'Normal')
        compare_file_against_reference(os.path.join(reference, 'output_class.h'),
                                       os.path.join(tmp_path, 'output_class.h'))
        compare_file_against_reference(os.path.join(reference, 'output_class.c'),
                                       os.path.join(tmp_path, 'output_class.c'))

    @pytest.mark.chaste
    def test_script_output_expose_annotated_variables(self, capsys, tmp_path):
        LOGGER.info('Testing model with options --expose-annotated-variables and -o for command line script\n')
        tmp_path = str(tmp_path)
        # Check options: -o --expose-annotated-variables
        model_name = 'matsuoka_model_2003'
        model_file = os.path.join(cg.DATA_DIR, 'tests', 'cellml', model_name + '.cellml')
        model_file = str(model_file)
        outfile = os.path.join(tmp_path, 'expose_annotated_variables_cellmatsuoka_model_2003.cpp')
        outfile = str(outfile)
        # Call commandline script
        testargs = ['chaste_codegen', model_file, '-o', outfile, '--expose-annotated-variables']
        with mock.patch.object(sys, 'argv', testargs):
            chaste_codegen()
        # Check output
        model_name = 'expose_annotated_variables_cellmatsuoka_model_2003'
        reference = os.path.join(os.path.join(cg.DATA_DIR, 'tests'), 'chaste_reference_models', 'Normal')
        compare_file_against_reference(os.path.join(reference, model_name + '.hpp'),
                                       os.path.join(tmp_path, model_name + '.hpp'))
        compare_file_against_reference(os.path.join(reference, model_name + '.cpp'),
                                       os.path.join(tmp_path, model_name + '.cpp'))

    @pytest.mark.chaste
    def test_script_opt(self, capsys, tmp_path):
        LOGGER.info('Testing model with options -t ChasteOpt and -o for command line script\n')
        tmp_path = str(tmp_path)
        model_name = 'aslanidi_model_2009'
        model_file = os.path.join(cg.DATA_DIR, 'tests', 'cellml', model_name + '.cellml')
        assert os.path.isfile(model_file)
        outfile = os.path.join(tmp_path, 'aslanidi_model_2009.cpp')
        # Call commandline script
        testargs = ['chaste_codegen', model_file, '-t', 'ChasteOpt', '-o', outfile]
        with mock.patch.object(sys, 'argv', testargs):
            chaste_codegen()
        # Check output
        reference = os.path.join(os.path.join(cg.DATA_DIR, 'tests'), 'chaste_reference_models', 'Opt')
        compare_file_against_reference(os.path.join(reference, 'aslanidi_model_2009.hpp'),
                                       os.path.join(tmp_path, 'aslanidi_model_2009.hpp'))
        compare_file_against_reference(os.path.join(reference, 'aslanidi_model_2009.cpp'),
                                       os.path.join(tmp_path, 'aslanidi_model_2009.cpp'))
