#include <iostream>

#include "./QueueSimulation.h"

QueueSimulation::QueueSimulation(int maxClients) : m_maxClients(maxClients), m_clientsCount(0), m_stop(false) {}

void QueueSimulation::clientThread() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(1));  // Клиент приходит каждую секунду

    std::unique_lock<std::mutex> lock(m_mtx);

    if (m_stop) {
      std::cout << "Клиентский поток завершает работу." << std::endl;
      break;
    }

    if (m_clientsCount >= m_maxClients) {
      std::cout << "Максимальное количество клиентов достигнуто. Очередь заполнена." << std::endl;
      continue;
    }

    ++m_clientsCount;

    std::cout << "Клиент пришёл. В очереди клиентов: " << m_clientsCount << "." << std::endl;

    m_cv.notify_one();  // Уведомляем операциониста, что в очереди есть клиенты
  }
}

void QueueSimulation::operatorThread() {
  while (true) {
    std::this_thread::sleep_for(std::chrono::seconds(2));  // Операционист обслуживает каждые 2 секунды

    std::unique_lock<std::mutex> lock(m_mtx);

    m_cv.wait(lock, [this]() { return m_clientsCount > 0 || m_stop; });  // Ждём, пока появятся клиенты

    if (m_stop && m_clientsCount == 0) {
      std::cout << "Очередь пуста. Операционист завершает работу." << std::endl;
      break;
    }

    --m_clientsCount;

    std::cout << "Операционист обслужил клиента. В очереди осталось клиентов: " << m_clientsCount << "." << std::endl;
  }
}

void QueueSimulation::startSimulation() {
  std::thread client(&QueueSimulation::clientThread, this);
  std::thread operatorT(&QueueSimulation::operatorThread, this);

  // Даём время для имитации работы
  std::this_thread::sleep_for(std::chrono::seconds(15));

  {
    std::lock_guard<std::mutex> lock(m_mtx);
    m_stop = true;  // Сигнализируем о завершении
  }

  m_cv.notify_all();  // Просыпаем все потоки, чтобы они могли завершиться

  client.join();
  operatorT.join();
}
