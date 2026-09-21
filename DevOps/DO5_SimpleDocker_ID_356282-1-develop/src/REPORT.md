# Отчёт по проекту Simple Docker

## Part 1. Готовый докер

- Скачан официальный образ `nginx` командой `docker pull nginx`.
- Проверено наличие образа командой `docker images`.
- Запущен контейнер командой `docker run -d nginx`.
- Проверен запуск контейнера командой `docker ps`.
- Получена информация о контейнере командой `docker inspect [container_id]`.
- Из вывода `docker inspect` определены:
  - размер контейнера: `SizeRw` = 81920 байт (80 KB, RW-слой контейнера), `SizeRootFs` = 183496704 байт (≈175 MB, с учётом базового образа nginx);
  - список замапленных портов: `80/tcp` объявлен в образе (`ExposedPorts`), но не замаплен на локальную машину (`PortBindings` пуст, контейнер запущен без `-p`);
  - IP-адрес контейнера: `172.17.0.2` (сеть `bridge`).
- Контейнер остановлен командой `docker stop [container_id]`.
- Проверена остановка контейнера командой `docker ps`.
- Запущен контейнер с портами 80 и 443, замапленными на локальную машину: `docker run -d -p 80:80 -p 443:443 nginx`.
- Проверена доступность стартовой страницы nginx по адресу `localhost:80`.
- Контейнер перезапущен командой `docker restart [container_id]`.
- Проверен повторный запуск контейнера.

**Скриншоты:**

- ![docker pull nginx — образ nginx скачан / актуален](screenshots/part1-01-pull.png)
- ![docker images — nginx присутствует в списке образов](screenshots/part1-02-images.png)
- ![docker run -d nginx — контейнер запущен, выведен его ID](screenshots/part1-03-run.png)
- ![docker ps — контейнер nginx работает (Up)](screenshots/part1-04-ps-running.png)
- ![docker inspect --size ... | grep -i size — размер, для IP и портов см. полный docker inspect выше по тексту](screenshots/part1-05-inspect.png)
- ![docker stop charming_ritchie — контейнер остановлен](screenshots/part1-06-stop.png)
- ![docker ps — список пуст, контейнер остановлен](screenshots/part1-07-ps-stopped.png)
- ![docker run -d -p 80:80 -p 443:443 nginx — контейнер запущен с проброшенными портами](screenshots/part1-08-run-ports.png)
- ![стартовая страница nginx в браузере на http://localhost/](screenshots/part1-09-browser.png)
- ![docker restart d36b92b5faac — контейнер перезапущен](screenshots/part1-10-restart.png)
- ![docker ps — контейнер снова Up после restart, оба порта (80, 443) замаплены](screenshots/part1-11-ps-after-restart.png)

## Part 2. Операции с контейнером

- Прочитан конфигурационный файл `nginx.conf` внутри контейнера командой `docker exec [container_id] cat /etc/nginx/nginx.conf`.
- На локальной машине создан файл `nginx.conf` с блоком `location /status { stub_status on; }`.
- Файл скопирован внутрь контейнера командой `docker cp nginx.conf [container_id]:/etc/nginx/nginx.conf`.
- nginx перезапущен внутри контейнера командой `docker exec [container_id] nginx -s reload`.
- Проверена отдача страницы статуса по адресу `localhost:80/status`.
- Контейнер экспортирован в файл `container.tar` командой `docker export [container_id] -o container.tar`.
- Контейнер остановлен.
- Предпринята попытка удалить образ командой `docker rmi nginx` без удаления контейнеров — Docker отказал с ошибкой `conflict: unable to delete ... (must be forced) - container ... is using its referenced image`, так как остановленные контейнеры всё ещё ссылались на образ.
- Остановленные контейнеры (`charming_ritchie`, `upbeat_solomon`) удалены командой `docker rm`, после чего образ успешно удалён повторной командой `docker rmi nginx`.
- Из файла `container.tar` создан образ командой `docker import container.tar my-nginx:from-tar`.
- Создан и запущен контейнер на основе импортированного образа.
- Проверена отдача страницы статуса по адресу `localhost:80/status` в новом контейнере.

**Скриншоты:**

- ![docker exec upbeat_solomon cat /etc/nginx/nginx.conf — оригинальный конфиг nginx внутри контейнера](screenshots/part2-01-exec-cat.png)
- ![содержимое созданного локального nginx.conf с добавленным блоком location /status](screenshots/part2-02-nginx-conf-content.png)
- ![docker cp part2-nginx.conf upbeat_solomon:/etc/nginx/nginx.conf — файл успешно скопирован в контейнер](screenshots/part2-03-docker-cp.png)
- ![docker exec upbeat_solomon nginx -s reload — конфиг перечитан (есть безобидный warning про дублирующийся server_name, наш блок побеждает)](screenshots/part2-04-exec-reload.png)
- ![страница статуса nginx на http://localhost/status](screenshots/part2-05-status-page.png)
- ![docker export upbeat_solomon -o container.tar — контейнер экспортирован (157M, вне репозитория)](screenshots/part2-06-export.png)
- ![docker stop upbeat_solomon — контейнер остановлен](screenshots/part2-07-stop.png)
- ![docker rmi nginx — отказ: образ используется остановленным контейнером](screenshots/part2-08-rmi-conflict.png)
- ![docker rm charming_ritchie upbeat_solomon — оба контейнера удалены](screenshots/part2-09-rm-containers.png)
- ![docker rmi nginx (повторно) — образ успешно удалён (Untagged, Deleted)](screenshots/part2-10-rmi-success.png)
- ![docker import container.tar my-nginx:from-tar — новый образ создан из архива](screenshots/part2-11-import.png)
- ![docker run -d -p 80:80 my-nginx:from-tar nginx -g 'daemon off;' — контейнер запущен из импортированного образа (команда указана явно, т.к. import не сохраняет CMD)](screenshots/part2-12-run-imported.png)
- ![страница статуса nginx на http://localhost/status в контейнере из импортированного образа](screenshots/part2-13-status-after-import.png)

## Part 3. Мини веб-сервер

- Мини-сервер на C и FastCGI написан в [src/server/main.c](server/main.c), собирается через [src/server/Makefile](server/Makefile).
- Сервер запускается через `spawn-fcgi -a 127.0.0.1 -p 8080 -- ./server`.
- Конфигурация [src/nginx/nginx.conf](nginx/nginx.conf) проксирует запросы с порта 81 на `127.0.0.1:8080`.
- nginx с этой конфигурацией запускается локально командой `nginx -c $(pwd)/nginx.conf -p $(pwd)`.
- Проверена отдача страницы `Hello, World!` по адресу `localhost:81`.

**Скриншоты:**

- ![make — мини-сервер скомпилирован](screenshots/part3-01-make.png)
- ![spawn-fcgi -a 127.0.0.1 -p 8080 -- ./server — сервер запущен на порту 8080](screenshots/part3-02-spawn-fcgi.png)
- ![sudo nginx -c nginx.conf — nginx запущен локально с нашей конфигурацией (слушает порт 81)](screenshots/part3-03-nginx-start.png)
- ![страница Hello, World! в браузере на http://localhost:81/](screenshots/part3-04-browser.png)

## Part 4. Свой докер

- Написан [src/Dockerfile](Dockerfile), который:
  - собирает исходники мини-сервера из Part 3 в отдельном build-стейдже (`debian:bookworm-slim` + `gcc`/`make`/`libfcgi-dev`);
  - в финальном стейдже (`debian:bookworm-slim` + `nginx`, `spawn-fcgi`) копирует бинарник сервера и `nginx.conf`;
  - запускает сервер через `spawn-fcgi` на порту 8080 и nginx на порту 81 инструкцией `CMD`;
  - работает от непривилегированного пользователя `www-data`.
- Образ собран командой (из папки `src`) `docker build -t simple-docker:v1 .`.
- Через `docker images` проверено, что образ собрался корректно.
- Образ запущен командой (из папки `src`):
  `docker run -d -p 80:81 -v $(pwd)/nginx:/etc/nginx simple-docker:v1`.
- Проверена доступность страницы мини-сервера по адресу `localhost:80`.
- В `nginx.conf` добавлен `location /status { stub_status on; }`.
- Образ пересобран, проверено автоматическое обновление конфигурации при перезапуске контейнера (конфиг подключён как volume).
- Проверена отдача страницы статуса по адресу `localhost:80/status`.

**Скриншоты:**

- ![docker build -t simple-docker:v1 . — образ собран успешно](screenshots/part4-01-build.png)
- ![docker images — simple-docker:v1 присутствует в списке](screenshots/part4-02-images.png)
- ![docker run -d --name simple-docker -p 80:81 -v "$(pwd)/nginx:/etc/nginx" simple-docker:v1 — контейнер запущен](screenshots/part4-03-run.png)
- ![страница Hello, World! на http://localhost/ (отдаётся нашим собственным сервером)](screenshots/part4-04-browser-helloworld.png)
- ![страница статуса nginx на http://localhost/status](screenshots/part4-05-status.png)

## Part 5. Dockle

- Образ из Part 4 просканирован командой `dockle simple-docker:v1`.
- Первое сканирование показало `FATAL CIS-DI-0010` ("credential in environment variables") — ложное срабатывание на слое официального образа `nginx`/`nginx-unprivileged`, где в скрипте загрузки GPG-ключей встречается переменная `NGINX_GPGKEYS`.
- Чтобы избавиться от этого слоя, Dockerfile переписан: финальный стейдж собран на чистом `debian:bookworm-slim` с установкой `nginx` через `apt`, а не на основе официального docker-образа nginx.
- Дополнительно добавлены: непривилегированный пользователь `www-data`, `HEALTHCHECK`, зафиксированные версии базовых образов, удаление кешей пакетного менеджера.
- После доработки повторное сканирование `dockle simple-docker:v1` (в т. ч. с `--exit-level warn`, код возврата `0`) не выдаёт ни одной ошибки (`FATAL`) и ни одного предупреждения (`WARN`) — остаются только два `INFO`-пункта (Content Trust и стандартные setuid/setgid-бинарники Debian), которые не относятся к ошибкам/предупреждениям.

**Скриншоты:**

- ![dockle simple-docker:v1 — 0 FATAL, 0 WARN, только два безопасных INFO-пункта](screenshots/part5-01-dockle-clean.png)

## Part 6. Базовый Docker Compose

- Написан [src/docker-compose.yml](docker-compose.yml), поднимающий два сервиса:
  - `app` — контейнер из Part 5, работает только во внутренней docker-сети (без `EXPOSE` и без маппинга портов на локальную машину);
  - `proxy` — контейнер с nginx ([src/nginx-proxy/nginx.conf](nginx-proxy/nginx.conf)), проксирующий запросы с порта 8080 на порт 81 сервиса `app`, порт 8080 которого замаплен на 80 порт локальной машины.
- Все ранее запущенные контейнеры остановлены.
- Проект собран и запущен командами `docker compose build` и `docker compose up`.
- Проверена отдача страницы мини-сервера по адресу `localhost:80`.

**Скриншоты:**

- ![docker compose build — образ app собран успешно](screenshots/part6-01-compose-build.png)
- ![docker compose up -d — оба контейнера (app, proxy) запущены](screenshots/part6-02-compose-up.png)
- ![страница Hello, World! на http://localhost/ через связку app+proxy](screenshots/part6-03-browser.png)
