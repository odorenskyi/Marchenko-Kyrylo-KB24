#include <cmath>
#include <stdexcept>

const double EPSILON = 1e-9;

double s_calculation(double x, double y, double z) {
    // Перевірка для виразу |y-z| (щоб уникнути ділення на 0)
    if (std::fabs(y - z) < EPSILON) {
        return NAN;
    }

    // Обчислення першого терму: (x/|y-z|)^3
    double term1 = std::pow(x / std::fabs(y - z), 3);

    // Перевірка для виразу під квадратним коренем у знаменнику другого терму:
    // √(|z+x| * y) - перевіряємо, що y > 0 та |z+x| > 0
    if (y <= 0 || std::fabs(z + x) < EPSILON) {
        return NAN;
    }
    double sqrtDenom = std::sqrt(std::fabs(z + x) * y);
    double term2 = (x * x + z) / sqrtDenom;

    // Перевірка знаменника для третього терму: 2*y + π
    double denominator = 2 * y + M_PI;
    if (std::fabs(denominator) < EPSILON) {
        return NAN;
    }
    double term3 = std::cos(x * z * z) / denominator;

    // Обчислення виразу під квадратним коренем
    double innerExpression = term1 + term2 - term3;
    if (innerExpression < 0) {
        return NAN;
    }

    // Обчислення кінцевого значення S
    double S = 1 + std::sqrt(innerExpression);
    return S;
}
