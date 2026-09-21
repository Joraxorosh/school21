"""
Задание 2. Скачивание изображений.

Асинхронный обработчик ссылок: пользователь вводит путь для сохранения, затем
по одной вводит ссылки на изображения. Сразу после ввода ссылки начинается ее
асинхронная загрузка, а пользователю сразу же снова предлагается ввести
следующую ссылку - ждать окончания предыдущей загрузки не нужно. Ввод
завершается пустой строкой.

Сама загрузка (сетевой запрос + запись файла на диск) - блокирующая операция,
поэтому она выполняется в пуле потоков через loop.run_in_executor, а цикл
событий asyncio в это время свободен и продолжает опрашивать пользователя.
Так весь код остается в пределах стандартной библиотеки, без сторонних
зависимостей (requests/aiohttp), что удобно для проверки на любой машине.
"""

import asyncio
import os
from urllib.error import HTTPError, URLError
from urllib.parse import urlparse
from urllib.request import Request, urlopen

STATUS_OK = "Успех"
STATUS_ERROR = "Ошибка"
REQUEST_TIMEOUT = 15


def _pad(text: str, width: int, align: str) -> str:
    text = str(text)
    return f" {text.ljust(width)} " if align == "left" else f" {text.center(width)} "


def draw_table(headers: list, rows: list, aligns: list) -> str:
    widths = [
        max(len(str(value)) for value in ([headers[i]] + [row[i] for row in rows]))
        for i in range(len(headers))
    ]
    separator = "+" + "+".join("-" * (width + 2) for width in widths) + "+"
    lines = [separator, "|" + "|".join(
        _pad(headers[i], widths[i], aligns[i]) for i in range(len(headers))
    ) + "|", separator]
    for row in rows:
        lines.append("|" + "|".join(
            _pad(row[i], widths[i], aligns[i]) for i in range(len(headers))
        ) + "|")
    lines.append(separator)
    return "\n".join(lines)


def is_writable_directory(path: str) -> bool:
    """Проверяет, что по указанному пути можно создать каталог и писать в него."""

    try:
        os.makedirs(path, exist_ok=True)
        probe_path = os.path.join(path, ".write_probe.tmp")
        with open(probe_path, "w", encoding="utf-8") as probe_file:
            probe_file.write("probe")
        os.remove(probe_path)
        return True
    except OSError:
        return False


def fetch_image(url: str) -> bytes:
    """Синхронно скачивает изображение по ссылке. Выполняется в отдельном потоке."""

    request = Request(url, headers={"User-Agent": "Mozilla/5.0"})
    with urlopen(request, timeout=REQUEST_TIMEOUT) as response:
        return response.read()


def save_file(path: str, data: bytes) -> None:
    with open(path, "wb") as file:
        file.write(data)


def build_filename(url: str, index: int) -> str:
    name = os.path.basename(urlparse(url).path) or "image"
    return f"{index:03d}_{name}"


async def download_image(url: str, directory: str, index: int, record: dict) -> None:
    """Скачивает одно изображение и записывает результат в record["status"]."""

    loop = asyncio.get_running_loop()
    try:
        data = await loop.run_in_executor(None, fetch_image, url)
        target_path = os.path.join(directory, build_filename(url, index))
        await loop.run_in_executor(None, save_file, target_path, data)
    except (URLError, HTTPError, OSError, ValueError):
        record["status"] = STATUS_ERROR
    else:
        record["status"] = STATUS_OK


async def ask_save_directory() -> str:
    loop = asyncio.get_running_loop()
    while True:
        raw_path = await loop.run_in_executor(None, input, "Введите путь для сохранения изображений: ")
        path = raw_path.strip()
        if is_writable_directory(path):
            return path
        print("Некорректный путь или нет доступа для сохранения по нему. Попробуйте другой путь.")


async def collect_links(directory: str, records: list) -> list:
    """Опрашивает пользователя, пока он не введет пустую строку, и запускает загрузки."""

    loop = asyncio.get_running_loop()
    tasks = []
    index = 0
    while True:
        raw_url = await loop.run_in_executor(
            None, input, "Введите ссылку на изображение (пустая строка - завершить ввод): "
        )
        url = raw_url.strip()
        if not url:
            break
        index += 1
        record = {"url": url, "status": None}
        records.append(record)
        tasks.append(asyncio.create_task(download_image(url, directory, index, record)))
    return tasks


async def main() -> None:
    directory = await ask_save_directory()

    records: list = []
    tasks = await collect_links(directory, records)

    if any(not task.done() for task in tasks):
        print("Не все изображения еще загружены. Ожидание завершения загрузки...")
    if tasks:
        await asyncio.gather(*tasks)

    rows = [(record["url"], record["status"]) for record in records]
    print(draw_table(["Ссылка", "Статус"], rows, ["left", "center"]))


if __name__ == "__main__":
    asyncio.run(main())
