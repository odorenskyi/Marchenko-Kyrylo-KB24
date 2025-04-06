#include <iostream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "ModulesMarchenko.h"

using namespace std;

string doubleToString(double value, int precision = 5) {
    ostringstream oss;
    oss << fixed << setprecision(precision) << value;
    return oss.str();
}

void test_s_calculation() {
    double x[5] = {2, 2, 0, 3, 1};
    double y[5] = {3, 3, 4, 10, 0};
    double z[5] = {1, 3, -1, 2, 2};
    double expected_results[5] = {2.64687, NAN, NAN, 2.25376, NAN};

    for (short i = 0; i < 5; i++) {
        double result = s_calculation(x[i], y[i], z[i]);
        string resultStr = doubleToString(result);
        string expectedStr = doubleToString(expected_results[i]);
        bool passed = false;

        if (std::isnan(result) && std::isnan(expected_results[i])) {
            passed = true;
        } else if (resultStr == expectedStr) {
            passed = true;
        }

        cout << "Test case #" << i+1 << ": s_calculation("
             << x[i] << ", " << y[i] << ", " << z[i] << ") = "
             << resultStr << " == " << expectedStr
             << " --> " << (passed ? "passed" : "failed") << endl;
    }
}

int main() {
    test_s_calculation();
    return 0;
}
