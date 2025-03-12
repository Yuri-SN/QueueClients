#include <iostream>

#include "./QueueSimulation.h"

int main() {
  int maxClients{5};

  QueueSimulation simulation(maxClients);

  std::cout << "Начинаем имитацию очереди клиентов..." << std::endl;

  simulation.startSimulation();

  std::cout << "Имитация завершена." << std::endl;

  return 0;
}
