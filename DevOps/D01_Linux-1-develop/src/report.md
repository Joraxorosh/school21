## Part 1. Установка ОС
- Вывод команды `cat /etc/issue`: <br>
![screenshot](./screenshots/part1.png) <br>

## Part 2. Создание пользователя
- Создаём нового пользователся `new_user` командой `adduser`: <br>
![screenshot](./screenshots/part2_1.png) <br>
- Добавляем нового пользователся в группу `adm` командой `usermod`: <br>
![screenshot](./screenshots/part2_2.png) <br>
- Вывод команды `cat /etc/passwd`: <br>
![screenshot](./screenshots/part2_3.png) <br>
- Проверка состоит ли новый пользователь в группе `adm`.  <br>
Вывод команды `groups new_user`: <br>
![screenshot](./screenshots/part2_4.png)

## Part 3. Настройка сети ОС

- Задай название машины вида user-1. <br>
![screenshot](./screenshots/part3_1.png) <br>
- Установи временную зону, соответствующую твоему текущему местоположению. <br>
![screenshot](./screenshots/part3_2.png) <br>
- Выведи названия сетевых интерфейсов с помощью консольной команды. <br>
![screenshot](./screenshots/part3_3.png) <br>
lo (loopback device) – виртуальный интерфейс, присутствующий по умолчанию в любом Linux. Он используется для отладки сетевых программ и запуска серверных приложений на локальной машине. С этим интерфейсом всегда связан адрес 127.0.0.1. У него есть dns-имя – localhost. Посмотреть привязку можно в файле /etc/hosts.  <br>
- Используя консольную команду, получи ip адрес устройства, на котором ты работаешь, от DHCP-сервера. <br>
![screenshot](./screenshots/part3_4.png) <br>
Вывод сетевых интерфейсов командой `ip a`. Адрес `10.0.2.15/24` получен от DHCP-сервера: <br>
**DHCP** (Dynamic Host Configuration Protocol Протокол динамической настройки узла) - это протокол, в соответствии с которым устройствам в сети автоматически выдаются IP-адреса и другая сетевая информация. <br>
- Определи и выведи на экран внешний ip-адрес шлюза (ip) и внутренний IP-адрес шлюза, он же ip-адрес по умолчанию (gw). <br>
![screenshot](./screenshots/part3_5.png) <br>
Внешний ip-адрес: 89.22.142.113 <br>
![screenshot](./screenshots/part3_6.png) <br>
Внутренний ip-адрес: 10.0.2.2 <br>
- Задай статичные (заданные вручную, а не полученные от DHCP-сервера) настройки ip, gw, dns (используй публичный DNS-серверы, например 1.1.1.1 или 8.8.8.8). <br>
![screenshot](./screenshots/part3_8.png) <br>
![screenshot](./screenshots/part3_7.png) <br>
- Перезагрузи виртуальную машину. Убедись, что статичные сетевые настройки (ip, gw, dns) соответствуют заданным в предыдущем пункте. <br>
![screenshot](./screenshots/part3_8.png) <br>
Перезагрузил `sudo reboot` <br>
- Успешно пропингуй удаленные хосты 1.1.1.1 и ya.ru и вставь в отчёт скрин с выводом команды. В выводе команды должна быть фраза «0% packet loss». <br>
![screenshot](./screenshots/part3_10.png)

## Part 4. Обновление ОС
- Обнови системные пакеты до последней на момент выполнения задания версии. <br>
![screenshot](./screenshots/part4.png) <br>
## Part 5. Использование команды sudo
- Разреши пользователю, созданному в [Part 2],выполнять команду sudo. <br>
![screenshot](./screenshots/part5_1.png) <br>
- Поменяй hostname ОС от имени пользователя, созданного в пункте [Part 2] <br>
![screenshot](./screenshots/part5_2.png) <br>
**sudo** (от **S**ubstitute **U**ser **do**, ) — это команда, позволяющая обычному пользователю временно выполнять команды от имени администратора (root). Она защищает систему от случайных или вредоносных действий и позволяет контролировать, кто и что может выполнять.


## Part 6. Установка и настройка службы времени
- Настрой службу автоматической синхронизации времени.  <br> 
- Выведи время часового пояса, в котором ты сейчас находишься. <br>
- Вывод следующей команды должен содержать `NTPSynchronized=yes`: \
  `timedatectl show` <br>
![screenshot](./screenshots/part6.png) <br>
## Part 7. Установка и использование текстовых редакторов
- Установи текстовые редакторы **VIM** (+ любые два по желанию **NANO**, **MCEDIT**, **JOE** и т. д.)   <br>
![screenshot](./screenshots/part7_1.png) <br>

- Используя каждый из трех выбранных редакторов, создай файл *test_X.txt*, где X — название редактора, в котором создан файл. Напиши в нём свой никнейм, закрой файл с сохранением изменений. <br>
VIM: <br>
Создать файл sudo vim test_vim.txt <br>
![screenshot](./screenshots/part7_2.png) <br>
NANO: <br>
Создать файл sudo nano test_vim.txt <br>
![screenshot](./screenshots/part7_3.png) <br>
MCEDIT: <br>
Создать файл sudo mcedit test_vim.txt <br>
![screenshot](./screenshots/part7_4.png) <br>
- В отчёте укажи, что сделал для выхода с сохранением изменений. <br>
vim выход: esc + :wq <br>
nano выход: ctrl+X + y + enter <br>
mcedit выход: F2 + F10 <br>

- Используя каждый из трех выбранных редакторов, открой файл на редактирование, отредактируй файл, заменив никнейм на строку «21 School 21», закрой файл без сохранения изменений. <br>
VIM: <br>
![screenshot](./screenshots/part7_5.png) <br>
NANO: <br>
![screenshot](./screenshots/part7_6.png) <br>
MCEDIT: <br>
![screenshot](./screenshots/part7_7.png) <br>
- В отчёте укажи, что сделал для выхода без сохранения изменений. <br>
vim выход :q! <br>
nano выход: ctrl + x + n <br>
mcedit выход: F10 <br>


- Используя каждый из трех выбранных редакторов, отредактируй файл ещё раз (по аналогии с предыдущим пунктом), а затем освой функции поиска по содержимому файла (слово) и замены слова на любое другое.<br>
Из каждого редактора с результатами поиска слова.<br>
VIM поиск "/" <br>
![screenshot](./screenshots/part7_8.png) <br>
NANO поиск - ctrl w <br>
![screenshot](./screenshots/part7_10.png) <br>
mcedit поиск -f7, вводим запрос, и нажимаем find all <br>
![screenshot](./screenshots/part7_12.png) <br>
- Из каждого редактора с командами, введёнными для замены слова на другое. <br>
vim замена ":%s:/старое слово/новое слово/g"   <br>
![screenshot](./screenshots/part7_9.png) <br>
nano замена - Ctrl + W для перехода к панели поиска, далее Ctrl + R<br>
nano Далее вводим слово на что хотим заменить, enter + Y <br>
![screenshot](./screenshots/part7_11.png) <br>
mcedit замена - F4 <br>
![screenshot](./screenshots/part7_13.png)

## Part 8. Установка и базовая настройка сервиса SSHD
- Установи службу SSHd.   <br>
![screenshot](./screenshots/part8_1.png) <br>
- Добавь автостарт службы при загрузке системы.  <br>
![screenshot](./screenshots/part8_2.png)  <br>
- Перенастрой службу SSHd на порт 2022.  <br>
![screenshot](./screenshots/part8_3.png)  <br>
- Используя команду ps, покажи наличие процесса sshd. Для этого к команде нужно подобрать ключи. <br>
![screenshot](./screenshots/part8_4.png)  <br>
- В отчёте объясни значение команды и каждого ключа в ней.  <br>
Ключ **e** используется для вывода всех процессов, а **f** для расширения формата выводимой информации. grep выводит записи содержащие "sshd". <br>
- Перезагрузи систему.  <br>
`sudo reboot` для перезагрузки виртуальной машины <br>

- Вывод команды netstat -tan должен содержать  \
`tcp 0 0 0.0.0.0:2022 0.0.0.0:* LISTEN`  \ <br>
![screenshot](./screenshots/part8_5.png)  <br>
- В отчёте объясни значение ключей -tan, значение каждого столбца вывода, значение 0.0.0.0.  <br>
`-t` показать только TCP-соединения, <br>`-a` показать все подключения (и прослушивание, и установленные)<br> `-n` показать IP-адреса и номера портов в числовом виде, без DNS-имен <br>

***Proto*** - протокол соединения  <br>
***Recv-Q/Send-Q*** - кол-во полученных/отправленных байтов в очереди  <br>
***Local Adress*** - локальный адрес и порт, где sshd слушает подключения <br>
***Foreign Adress*** - удалённый адрес <br>
***State*** - текущее состояние соединения <br>
**Значение 0.0.0.0.**: это «универсальный адрес» — SSH слушает на всех интерфейсах, т.е. доступен с любого IP-адреса машины

## Part 9. Установка и использование утилит top, htop
- По выводу команды top определи и напиши в отчёте: <br>
![screenshot](./screenshots/part9_1.png) 
  - uptime - 9min
  - количество авторизованных пользователей - 1 user
  - среднюю загрузку системы - 0,00, 0,02, 0,01
  - общее количество процессов - 102 
  - загрузку cpu - 0%
  - загрузку памяти - Всего: 3919,9 МБ, Свободно: 3539,0 МБ, Использовано: 154,4 МБ, Кэш/буфер: 226,5 МБ,
  - pid процесса занимающего больше всего памяти - 1
  - pid процесса, занимающего больше всего процессорного времени - 174

- В отчёт вставь скрин с выводом команды htop: <br>
![screenshot](./screenshots/part9_2.png)  <br>
- отсортированному по PID, PERCENT_CPU, PERCENT_MEM, TIME; <br>
  ![screenshot](./screenshots/part9_3.png) 
  ![screenshot](./screenshots/part9_4.png) 
  ![screenshot](./screenshots/part9_5.png) 
  ![screenshot](./screenshots/part9_6.png) 
- отфильтрованному для процесса sshd; <br>
  ![screenshot](./screenshots/part9_7.png) 
- с процессом syslog, найденным, используя поиск; <br>
  ![screenshot](./screenshots/part9_8.png) 
- с добавленным выводом hostname, clock и uptime.  <br>
  ![screenshot](./screenshots/part9_9.png) 

## Part 10. Использование утилиты fdisk

- Запусти команду fdisk -l. <br>
![screenshot](./screenshots/part10_1.png) 
- В отчёте напиши название жесткого диска, его размер и количество секторов, а также размер swap. <br>
***название жесткого диска***: /dev/sda  <br>
***размер жесткого диска***: 25 GiB <br>
***количество секторов***: 52428800 <br>
![screenshot](./screenshots/part10_2.png) 
***размер swap***: 2,2 G <br>

## Part 11. Использование утилиты df

- Запусти команду df.  <br>
![screenshot](./screenshots/part11_1.png) 
- В отчёте напиши для корневого раздела (/): <br>
![screenshot](./screenshots/part11_2.png) 
  - размер раздела - 11758760
  - размер занятого пространства - 4955284
  - размер свободного пространства - 6184368
  - процент использования - 45%
- Определи и напиши в отчёт единицу измерения в выводе.  
  - В выводе используются килобайты


- Запусти команду df -Th. <br>
![screenshot](./screenshots/part11_3.png) 
- В отчёте напиши для корневого раздела (/): <br>
![screenshot](./screenshots/part11_4.png) 
    - размер раздела - 12G
    - размер занятого пространства - 4,8G
    - размер свободного пространства - 5,9G
    - процент использования - 45%
- Определи и напиши в отчёт тип файловой системы для раздела.
ext4


## Part 12. Использование утилиты du
- Запусти команду du. <br>
![screenshot](./screenshots/part12_1.png) 
- Выведи размер папок /home, /var, /var/log (в байтах, в человекочитаемом виде). <br>
![screenshot](./screenshots/part12_2.png) 
![screenshot](./screenshots/part12_3.png) 
- Выведи размер всего содержимого в /var/log (не общее, а каждого вложенного элемента, используя *). <br>
![screenshot](./screenshots/part12_4.png) 

## Part 13. Установка и использование утилиты ncdu
- Установи утилиту ncdu. <br>
![screenshot](./screenshots/part13_1.png) 
- Выведи размер папок /home, /var, /var/log. <br>
- `sudo ncdu /home`  <br>
![screenshot](./screenshots/part13_2.png) 
- `sudo ncdu /var`  <br>
![screenshot](./screenshots/part13_3.png) 
- `sudo ncdu /var/log` <br>
![screenshot](./screenshots/part13_4.png) 

## Part 14. Работа с системными журналами

- Открой для просмотра:
- 1. /var/log/dmesg <br>
![screenshot](./screenshots/part14_1.png) 
- 2. /var/log/syslog <br>
![screenshot](./screenshots/part14_2.png) 
- 3. /var/log/auth.log  <br>
![screenshot](./screenshots/part14_3.png)  


- Напиши в отчёте время последней успешной авторизации, имя пользователя и метод входа в систему. <br>
  - Jun 2 10:52:34 newuser sudo <br>
- Перезапусти службу SSHd. <br>
![screenshot](./screenshots/part14_4.png) 
- Вставь в отчёт скрин с сообщением о рестарте службы (искать в логах). <br>
![screenshot](./screenshots/part14_5.png) 
## Part 15. Использование планировщика заданий CRON


- Используя планировщик заданий, запусти команду uptime через каждые 2 минуты. <br>
![screenshot](./screenshots/part15_1.png) 
  - Найди в системных журналах строчки (минимум две в заданном временном диапазоне) о выполнении. <br>
  ![screenshot](./screenshots/part15_2.png) 
  - Выведи на экран список текущих заданий для CRON. <br>
  ![screenshot](./screenshots/part15_3.png) 

- Удали все задания из планировщика заданий. <br>
 ![screenshot](./screenshots/part15_4.png) 