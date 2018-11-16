from __future__ import absolute_import, division
from __future__ import print_function, unicode_literals

import fccodegen

import os
import jinja2


def load_template(*name):
    """
    Returns a path to the given template
    """
    path = os.path.join(fccodegen.DIR_TEMPLATE, *name)
    #TODO: Check absolute path is still in DIR_TEMPLATE
    #TODO: Check exists
    #TODO: Look at the jinja PackageLoader. What's the advantage?
    with open(path, 'r') as f:
        return jinja2.Template(f.read())


def create_weblab_model(model, path):
    """
    Takes a :class:`cellmlmanip.Model`, generates a ``.pyx`` model for use
    with the Web Lab, and stores it at ``path``.
    """
    template = load_template('wl', 'weblab_model.pyx')
    with open(path, 'w') as f:
        f.write(template.render())

