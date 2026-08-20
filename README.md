# C++ Concurrency Labs

![C++17](https://img.shields.io/badge/C%2B%2B-17-00599C?logo=cplusplus&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-3.16%2B-064F8C?logo=cmake&logoColor=white)
[![MIT](https://img.shields.io/badge/license-MIT-blue.svg)](LICENSE)

Учебные задачи по многопоточному программированию на C++17: диагностика livelock, сравнение способов синхронизации и реализация асинхронного логгера.

## Состав

| Каталог | Тема | Реализации |
|---|---|---|
| `task-concurrency-1` | Livelock | исходная демонстрация, `std::scoped_lock`, randomized backoff |
| `task-concurrency-2` | Параллельная гистограмма | mutex, atomic counters, thread-local counters |
| `task-concurrency-3` | Async logger | очередь, `condition_variable`, фоновая запись, graceful shutdown |

## Сборка и запуск

Каждая задача собирается отдельно:

```bash
cmake -S task-concurrency-1 -B task-concurrency-1/build
cmake --build task-concurrency-1/build -j

cmake -S task-concurrency-2 -B task-concurrency-2/build
cmake --build task-concurrency-2/build -j

cmake -S task-concurrency-3 -B task-concurrency-3/build
cmake --build task-concurrency-3/build -j
```

Примеры запуска:

```bash
./task-concurrency-1/build/fix_scoped_lock
./task-concurrency-1/build/fix_backoff
./task-concurrency-2/build/histogram_local 100000000
./task-concurrency-3/build/test_concurrent
```

Подробные условия и ожидаемый вывод приведены в README каждой задачи.

## Что проверено

- обе livelock-реализации завершаются с `Operations: 20000`;
- mutex, atomic и local histogram возвращают `Correct: true`;
- async logger проходит базовый тест, конкурентную запись 100 сообщений и graceful shutdown на 1000 сообщениях.

## Автор и лицензия

Автор — Андрей Бромбин, [Telegram](https://t.me/devbrombin).

Код распространяется по [MIT License](LICENSE).
