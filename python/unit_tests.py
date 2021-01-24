import unittest

class SimpleTestCase(unittest.TestCase):

    def setUp(self):
        """Call before every test case."""
        pass

    def tearDown(self):
        """Call after every test case."""
        pass

    def testA(self):
        """Test case A. note that all test method names must begin with 'test.'"""
        assert 5+8 == 13, "python no sabe sumar"

if __name__ == "__main__":
    unittest.main() # run all tests
