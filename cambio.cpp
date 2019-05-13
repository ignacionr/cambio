#include <iomanip>
#include <iostream>
#include <map>
#include <functional>
#include <algorithm>

typedef std::map<float,int, std::greater<float>> Monedas;

template <typename T> T& operator<<(T& stream, std::pair<float,int> const &item) {
  stream << "$ " << item.first << ": " << item.second;
  return stream;
}

template <typename T> T& operator<<(T& stream, Monedas &monedas) {
  std::for_each(monedas.begin(), monedas.end(), [&stream](auto m) { stream << m; });
  return stream;
}

bool dar_cambio(float &saldo, Monedas &monedas, std::function<void(float)> dar) {
  while (saldo > 0.001) { // por la forma en que se manejan los float, puede quedar un resabio
    Monedas::iterator elegida { monedas.lower_bound(saldo) };
    if (elegida == monedas.end()) {
      return false;
    }
    auto k = elegida->first;
    dar(k);
    saldo -= k;
    if (--elegida->second == 0) {
      monedas.erase(k);
    }
  }
  return true;
}

int main() {
  Monedas monedas { {2, 5}, {1, 7}, {0.5, 8}, {0.2, 10}, {0.1, 20}, {0.05, 10}, {0.01, 10}};
  std::cout << "Cuento con las siguientes monedas:" << std::endl;
  std::cout << std::fixed << std::setprecision(2) << monedas << std::endl << std::endl;
  std::cout << "Dime el importe: >";
  float saldo;
  std::cin >> saldo;

  if (!dar_cambio(saldo, monedas, [](float f) { std::cout << "Te doy una de $ " << f << std::endl; })) {
    std::cout << "lo siento, aun te debere " << saldo << std::endl;
  }
  std::cout << "Y me quedan: " << monedas << std::endl;
}
