#pragma once

#include <condition_variable>
#include <mutex>

class QueueSimulation {
public:
  QueueSimulation(int maxClients);

  void clientThread();
  void operatorThread();
  void startSimulation();

private:
  int m_maxClients;              // Максимальное количество клиентов в очереди
  int m_clientsCount;            // Текущее количество клиентов в очереди
  bool m_stop;                   // Флаг завершения работы
  std::mutex m_mtx;              // Мьютекс для синхронизации доступа к m_clientsCount
  std::condition_variable m_cv;  // Условная переменная для уведомлений
};
