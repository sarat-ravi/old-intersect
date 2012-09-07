# author: Achim Gaedke
# created: January 2002
# file: pygsl/statistics/__init__.py
# $Id: __init__.py,v 1.1 2002/01/23 17:52:41 achimgaedke Exp $

from pygsl.statistics.double import *

__all__ = filter(lambda s:s[0:2]!="__" or s=="double",dir())




