// REMOVE: #define BOOST_TEST_MODULE SideMadeTests
#define BOOST_TEST_DYN_LINK
#include <Eigen/Dense>
#include <boost/test/unit_test.hpp>
#include <fstream>
#include "matrixIO.hpp"

using namespace Eigen;
using namespace matrixIO;

struct MatrixIOFixture {
  MatrixIOFixture()
  {
    // Create a test matrix
    matrix = MatrixXd(2, 2);
    matrix << 1, 2, 3, 4;

    filename = "test_matrix.csv";
    saveData(filename, matrix);
  }

  ~MatrixIOFixture()
  {
    // Clean up test file after each test
    std::remove(filename.c_str());
  }

  MatrixXd    matrix;
  std::string filename;
};

// Define the test suite
BOOST_FIXTURE_TEST_SUITE(MatrixIOTests, MatrixIOFixture)

BOOST_AUTO_TEST_CASE(OpenData_ValidFile)
{
  MatrixXd loadedMatrix = openData(filename, 2);
  BOOST_TEST((loadedMatrix - matrix).norm() < 1e-12);
}

BOOST_AUTO_TEST_CASE(OpenData_InvalidFile)
{
  BOOST_CHECK_THROW(openData("non_existent.csv", 2), std::runtime_error);
}

BOOST_AUTO_TEST_SUITE_END()