<div align="center">

# 👋 George Truntsev — Software Developer

### Junior full-stack разработчик · выпускник School 21 (сеть 42)

![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white)
![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white)
![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white)
![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black)
![Docker](https://img.shields.io/badge/Docker-2496ED?style=flat-square&logo=docker&logoColor=white)
![GitLab CI](https://img.shields.io/badge/GitLab_CI-FC6D26?style=flat-square&logo=gitlab&logoColor=white)
![SQL](https://img.shields.io/badge/SQL-4479A1?style=flat-square&logo=postgresql&logoColor=white)
![Git](https://img.shields.io/badge/Git-F05032?style=flat-square&logo=git&logoColor=white)

[Telegram](https://t.me/Meauth) · [Email](mailto:george.truntsev@yandex.ru)

</div>

---

## Обо мне

Прошёл интенсивную программу **School 21** (партнёрская сеть École 42 в России) — обучение построено без лекций и преподавателей: только проекты, код-ревью от других студентов и жёсткие автотесты. Это учит писать код, который реально проходит проверку, а не просто "работает на моей машине".

В этом репозитории — часть выполненных проектов: от низкоуровневого C и собственных реализаций стандартных библиотек до DevOps-практик (Linux, Docker, CI/CD) и бэкенда на Python. Каждый проект принят ревьюерами School 21 по формальному чек-листу требований.

## 🔥 Избранные проекты

| Проект | Стек | Что делает |
|---|---|---|
| [**C7_BrickGame_v1.0**](./C_projects/Tetris) — Тетрис на C | ![C](https://img.shields.io/badge/C-00599C?style=flat-square&logo=c&logoColor=white) | Игровой движок «Тетрис» на конечном автомате + терминальный интерфейс на `ncurses`. Структурное программирование, unit-тесты (`check`) с покрытием ≥80%, полноценный Makefile (`install`, `test`, `gcov_report` и т.д.) |
| [**DO6_CICD**](./DevOps/DO6_CICD_ID_356283-1-develop) — CI/CD пайплайн | ![GitLab CI](https://img.shields.io/badge/GitLab_CI-FC6D26?style=flat-square&logo=gitlab&logoColor=white) | Настроил `.gitlab-ci.yml` с этапами build → codestyle (clang-format) → integration tests → manual deploy по SSH/SCP на отдельную VM |
| [**DO5_SimpleDocker**](./DevOps/DO5_SimpleDocker_ID_356282-1-develop) — Docker | ![Docker](https://img.shields.io/badge/Docker-2496ED?style=flat-square&logo=docker&logoColor=white) | Написал Dockerfile для собственного FastCGI-сервера на C за nginx, собрал multi-service `docker-compose` (внутренняя сеть + прокси), проверил образ линтером Dockle |
| [**AP1_Py_T03**](./Python_projects/AP1_Py_T03.ID_1375365-1-develop) — Крестики-нолики на Flask | ![Python](https://img.shields.io/badge/Python-3776AB?style=flat-square&logo=python&logoColor=white) | Веб-приложение на Flask с ИИ-соперником (алгоритм Минимакс) и слоистой архитектурой (web / domain / datasource / DI-контейнер) |
| [**DO2_LinuxNetwork**](./DevOps/DO2_LinuxNetwork.ID_356275-1-develop) — сети Linux | ![Linux](https://img.shields.io/badge/Linux-FCC624?style=flat-square&logo=linux&logoColor=black) | Подсети и маршрутизация, `iptables`, DHCP, NAT, SSH-туннели, нагрузочное тестирование `iperf3` |
| [**s21_containers**](./CPP_projects/Containers) — контейнеры на C++ | ![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white) | STL-подобная библиотека контейнеров (list, map, vector и др.) с нуля на шаблонах C++ |
| [**3DViewer v2.0**](./CPP_projects/3DViewer) — 3D-визуализатор | ![C++](https://img.shields.io/badge/C++-00599C?style=flat-square&logo=cplusplus&logoColor=white) | Просмотрщик 3D-моделей (.obj) с аффинными преобразованиями (перемещение/вращение/масштаб) |

## Все проекты

### Язык C — низкоуровневое программирование

| Проект | Описание |
|---|---|
| [C7_BrickGame_v1.0](./C_projects/Tetris) | Тетрис: логика на конечном автомате + `ncurses`-интерфейс, юнит-тесты |
| [s21_string+](./C_projects/StringPlus) | Собственная реализация `string.h` с расширениями (аналог `sprintf` и др.) |
| [s21_decimal](./C_projects/Decimal) | Библиотека десятичных чисел (128 бит) с нуля — арифметика, округление, преобразования |
| [s21_matrix](./C_projects/Matrix) | Библиотека операций над матрицами |
| [Simple Bash Utils](./C_projects/SimpleBushUtils) | Реализация утилит `cat` и `grep` с поддержкой ключей POSIX |

### C++ — ООП, шаблоны, алгоритмы

| Проект | Описание |
|---|---|
| [s21_containers](./CPP_projects/Containers) | STL-подобные контейнеры с нуля на шаблонах C++ |
| [s21_matrix_oop](./CPP_projects/Matrix) | Библиотека матриц, переписанная в ООП-парадигме |
| [SimpleNavigator](./CPP_projects/AlgorithmsSimpleNavigator) | Графовые алгоритмы: обход, кратчайший путь, остовное дерево, коммивояжёр |
| [Maze](./CPP_projects/AlgorithmsMaze) | Генерация и решение лабиринтов с визуализацией |
| [3DViewer v2.0](./CPP_projects/3DViewer) | Просмотрщик 3D-моделей с аффинными преобразованиями |
| [BrickGame Змейка](./CPP_projects/Tetris) | Игра «Змейка» — ООП-редизайн движка на конечном автомате из C-проекта |

### DevOps — Linux, сети, контейнеризация, CI/CD

| Проект | Описание |
|---|---|
| [D01_Linux](./DevOps/D01_Linux-1-develop) | Установка и администрирование Linux |
| [DO2_LinuxNetwork](./DevOps/DO2_LinuxNetwork.ID_356275-1-develop) | Подсети, маршрутизация, iptables, DHCP, NAT, SSH-туннели |
| [DO5_SimpleDocker](./DevOps/DO5_SimpleDocker_ID_356282-1-develop) | Dockerfile, docker-compose, линтинг образов (Dockle) |
| [DO6_CICD](./DevOps/DO6_CICD_ID_356283-1-develop) | GitLab CI/CD: build, codestyle, тесты, деплой по SSH |

### Python — алгоритмы, асинхронность, веб

| Проект | Описание |
|---|---|
| [AP1_Py_T01](./Python_projects/AP1_Py_T01.ID_1375362-1-develop) | 10 алгоритмических задач (обработка строк, чисел, файлов) |
| [AP1_Py_T02](./Python_projects/AP1_Py_T02_ID_1375363-1-develop) | Симуляция экзамена на многопроцессности + асинхронная загрузка изображений (`asyncio`) |
| [AP1_Py_T03](./Python_projects/AP1_Py_T03.ID_1375365-1-develop) | Веб-приложение «Крестики-нолики» на Flask с ИИ (Минимакс), слоистая архитектура |

### SQL — базы данных

| Проект | Описание |
|---|---|
| [SQL_beginner Day00–Day09](./SQL) | 10-дневный курс: запросы, джойны, агрегация, подзапросы, хранимые процедуры, индексы, транзакции |
| SQL_beginner Team01, Team_00 | Два командных проекта — совместное проектирование схемы и запросов |

## Стек и инструменты

**Языки:** C, C++, Python, SQL, Bash
**Системное:** Linux, сетевое администрирование, iptables, DHCP, NAT
**Инфраструктура:** Docker, docker-compose, GitLab CI/CD
**Веб:** Flask, REST, asyncio
**Инструменты:** Git, Makefile, clang-format, ncurses, Check (unit-тесты)

## Как устроен репозиторий

Проекты сгруппированы по категориям: `C_projects/`, `CPP_projects/`, `DevOps/`, `Python_projects/`, `SQL/`. В каждой папке проекта лежит `README_RUS.md` с оригинальным заданием School 21 — по нему можно свериться, что именно требовалось реализовать.

## Контакты

Открыт к предложениям о позиции junior/начинающий разработчик.

📩 **Telegram:** [@Meauth](https://t.me/Meauth)
📧 **Email:** [george.truntsev@yandex.ru](mailto:george.truntsev@yandex.ru)
