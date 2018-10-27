# -*- coding: utf-8 -*-

import pytest

import pyg_test

from .util import do_constructor_test, do_error_test, do_doc_test

test_data = [
    (pyg_test.TestTuplePair, (1, 3.5)),
    (pyg_test.TestTuplePair, (14, 4.0)),
    (pyg_test.TestTuplePair, (29, 18.8)),
    (pyg_test.TestTupleTuple, (2, 4.8, "foobar")),
    (pyg_test.TestTupleTuple, (4, 3.2, "a")),
    (pyg_test.TestTupleTuple, (5, 1.0, "")),
]

fail_data = [
    (pyg_test.TestTuplePair, TypeError, [1, 2.0]),
    (pyg_test.TestTuplePair, TypeError, (1, 2.0, 3)),
    (pyg_test.TestTuplePair, TypeError, (1,)),
    (pyg_test.TestTupleTuple, TypeError, [1, 2.5, 'foobar']),
    (pyg_test.TestTupleTuple, RuntimeError, (1.5, 2.5, 'foobar')),
    (pyg_test.TestTupleTuple, TypeError, (1, 2, 'foobar', 'baz')),
]

doc_data = [
    (pyg_test.TestTuplePair, 'Tuple[int, float]'),
    (pyg_test.TestTupleTuple, 'Tuple[int, float, str]'),
]


@pytest.mark.parametrize("cls,data", test_data)
def test_constructor(cls, data):
    """Check object is constructed properly."""
    do_constructor_test(cls, data)


@pytest.mark.parametrize("cls,err,data", fail_data)
def test_error(cls, err, data):
    """Check object errors when input has wrong data type."""
    do_error_test(cls, err, data)


@pytest.mark.parametrize("cls,type_str", doc_data)
def test_doc(cls, type_str):
    """Check object has correct doc string."""
    do_doc_test(cls, type_str)
