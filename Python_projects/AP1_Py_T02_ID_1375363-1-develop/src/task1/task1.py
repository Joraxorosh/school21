"""
Задание 1. Экзамен.

Моделирование сдачи экзамена несколькими студентами у нескольких экзаменаторов,
принимающих экзамен параллельно, каждый в своем процессе (модуль multiprocessing).

Используемые парадигмы:
    - ООП: классы Person/Student/Examiner/Question описывают предметную область
      и инкапсулируют присущее им поведение (выбор слова студентом, вынесение
      вердикта экзаменатором и т.д.).
    - Функциональный подход: чтение и разбор входных файлов через map, отбор и
      поиск "лучших" через max/min/filter с ключевыми функциями.
    - Процедурный/параллельный подход: оркестрация процессов, общая память
      (multiprocessing.Manager) и циклы отображения таблиц.
"""

import multiprocessing
import os
import random
import time
from dataclasses import dataclass
from pathlib import Path

BASE_DIR = Path(__file__).resolve().parent

PHI = (1 + 5 ** 0.5) / 2               # пропорция золотого сечения
QUESTIONS_PER_EXAM = 3                 # сколько вопросов задается одному студенту
LUNCH_AFTER_SECONDS = 30               # через сколько секунд после начала можно уйти на обед
LUNCH_MIN_SECONDS = 12
LUNCH_MAX_SECONDS = 18
PASS_RATE_THRESHOLD = 0.85             # выше какой доли сдавших экзамен считается удавшимся
REFRESH_INTERVAL = 0.3                 # с какой частотой перерисовывать таблицы, сек.

STATUS_QUEUE = "Очередь"
STATUS_PASSED = "Сдал"
STATUS_FAILED = "Провалил"
STATUS_ORDER = {STATUS_QUEUE: 0, STATUS_PASSED: 1, STATUS_FAILED: 2}


# --------------------------------------------------------------------------- #
# Модели предметной области (ООП)
# --------------------------------------------------------------------------- #

@dataclass(frozen=True)
class Person:
    """Общие данные человека, участвующего в экзамене: имя и пол."""

    name: str
    gender: str

    @classmethod
    def from_line(cls, line: str) -> "Person":
        """Создает объект из строки вида "Имя П", где П - буква пола (М/Ж)."""

        name, gender = line.strip().rsplit(maxsplit=1)
        return cls(name=name, gender=gender)


@dataclass(frozen=True)
class Question:
    """Вопрос из банка вопросов."""

    text: str

    @property
    def words(self) -> list:
        return self.text.split()


@dataclass(frozen=True)
class Student(Person):
    """Студент, отвечающий на вопросы экзаменатора."""

    def choose_word(self, question: Question) -> str:
        """
        Выбирает слово из вопроса согласно закону золотого сечения.
        Мальчики чаще выбирают слова ближе к началу вопроса, девочки - к концу.
        """

        weights = _golden_ratio_weights(len(question.words))
        if self.gender == "Ж":
            weights = list(reversed(weights))
        return random.choices(question.words, weights=weights, k=1)[0]


@dataclass(frozen=True)
class Examiner(Person):
    """Экзаменатор, принимающий экзамен."""

    @property
    def exam_duration(self) -> float:
        """Время приема экзамена у одного студента зависит от длины имени."""

        length = len(self.name)
        return random.uniform(length - 1, length + 1)

    @staticmethod
    def pick_correct_words(question: Question) -> set:
        """
        Экзаменатор не знает ответа заранее и наугад считает верными одно или
        несколько слов вопроса: первое выбирается всегда, каждое следующее -
        с вероятностью 1/3, пока не кончатся слова или не выпадет отказ.
        """

        remaining = list(question.words)
        random.shuffle(remaining)
        correct = {remaining.pop()}
        while remaining and random.random() < 1 / 3:
            correct.add(remaining.pop())
        return correct

    @staticmethod
    def grade(correct_count: int, incorrect_count: int) -> bool:
        """
        Итоговое решение зависит от настроения экзаменатора:
        1/8 - всегда не сдал, 1/4 - всегда сдал, 5/8 - объективно по счету.
        """

        mood = random.random()
        if mood < 1 / 8:
            return False
        if mood < 1 / 8 + 1 / 4:
            return True
        return correct_count > incorrect_count


def _golden_ratio_weights(count: int) -> list:
    """Возвращает список вероятностей a, b, c, ... по закону золотого сечения."""

    weights = []
    remaining = 1.0
    for _ in range(count - 1):
        share = remaining / PHI
        weights.append(share)
        remaining -= share
    weights.append(remaining)
    return weights


def pick_exam_questions(questions: list) -> list:
    """Выбирает QUESTIONS_PER_EXAM вопросов из банка (без повторов, если банк большой)."""

    if len(questions) >= QUESTIONS_PER_EXAM:
        return random.sample(questions, QUESTIONS_PER_EXAM)
    return random.choices(questions, k=QUESTIONS_PER_EXAM)


# --------------------------------------------------------------------------- #
# Чтение входных данных (функциональный подход)
# --------------------------------------------------------------------------- #

def read_lines(path: Path) -> list:
    with path.open(encoding="utf-8") as file:
        return [line.strip() for line in file if line.strip()]


def load_people(path: Path, cls):
    return list(map(cls.from_line, read_lines(path)))


def load_questions(path: Path) -> list:
    return list(map(Question, read_lines(path)))


# --------------------------------------------------------------------------- #
# Отрисовка таблиц
# --------------------------------------------------------------------------- #

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


def clear_screen() -> None:
    os.system("cls" if os.name == "nt" else "clear")


# --------------------------------------------------------------------------- #
# Работа экзаменатора в отдельном процессе
# --------------------------------------------------------------------------- #

def examiner_process(
    examiner: Examiner,
    students: dict,
    questions: list,
    queue,
    queue_lock,
    students_state,
    examiners_state,
    question_stats,
    state_lock,
    start_time: float,
) -> None:
    """Цикл работы одного экзаменатора: берет из очереди студентов, пока они есть."""

    had_lunch = False

    while True:
        with queue_lock:
            if not queue:
                break

        if not had_lunch and (time.time() - start_time) >= LUNCH_AFTER_SECONDS:
            had_lunch = True
            time.sleep(random.uniform(LUNCH_MIN_SECONDS, LUNCH_MAX_SECONDS))

        with queue_lock:
            if not queue:
                break
            student_name = queue.pop(0)

        with state_lock:
            entry = examiners_state[examiner.name]
            entry["current"] = student_name
            examiners_state[examiner.name] = entry

        student = students[student_name]
        duration = examiner.exam_duration
        correct = incorrect = 0

        for question in pick_exam_questions(questions):
            correct_words = Examiner.pick_correct_words(question)
            answer = student.choose_word(question)
            if answer in correct_words:
                correct += 1
                with state_lock:
                    question_stats[question.text] = question_stats.get(question.text, 0) + 1
            else:
                incorrect += 1

        time.sleep(duration)
        passed = Examiner.grade(correct, incorrect)
        finish_time = time.time() - start_time

        with state_lock:
            students_state[student_name] = {
                "status": STATUS_PASSED if passed else STATUS_FAILED,
                "time": duration,
                "finish": finish_time,
            }
            entry = examiners_state[examiner.name]
            entry["current"] = "-"
            entry["total"] += 1
            entry["failed"] += 0 if passed else 1
            entry["worktime"] += duration
            examiners_state[examiner.name] = entry


# --------------------------------------------------------------------------- #
# Отображение состояния экзамена
# --------------------------------------------------------------------------- #

def render_progress(students, examiners, students_state, examiners_state, queue, start_time) -> None:
    clear_screen()

    queue_snapshot = list(queue)
    rows = [(name, STATUS_QUEUE) for name in queue_snapshot]
    for student in students:
        state = students_state[student.name]
        if state["status"] != STATUS_QUEUE:
            rows.append((student.name, state["status"]))
    rows.sort(key=lambda row: STATUS_ORDER[row[1]])
    print(draw_table(["Студент", "Статус"], rows, ["left", "center"]))
    print()

    examiner_rows = []
    for examiner in examiners:
        info = examiners_state[examiner.name]
        examiner_rows.append((
            examiner.name, info["current"], info["total"], info["failed"], f'{info["worktime"]:.2f}',
        ))
    print(draw_table(
        ["Экзаменатор", "Текущий студент", "Всего студентов", "Завалил", "Время работы"],
        examiner_rows, ["left", "left", "center", "center", "center"],
    ))
    print()
    print(f"Осталось в очереди: {len(queue_snapshot)} из {len(students)}")
    print(f"Время с момента начала экзамена: {time.time() - start_time:.2f}")


def render_final_report(students, examiners, students_state, examiners_state, question_stats, questions, total_time) -> None:
    clear_screen()

    rows = [(student.name, students_state[student.name]["status"]) for student in students]
    rows.sort(key=lambda row: STATUS_ORDER[row[1]])
    print(draw_table(["Студент", "Статус"], rows, ["left", "center"]))
    print()

    examiner_rows = [
        (examiner.name, examiners_state[examiner.name]["total"], examiners_state[examiner.name]["failed"],
         f'{examiners_state[examiner.name]["worktime"]:.2f}')
        for examiner in examiners
    ]
    print(draw_table(
        ["Экзаменатор", "Всего студентов", "Завалил", "Время работы"],
        examiner_rows, ["left", "center", "center", "center"],
    ))
    print()
    print(f"Время с момента начала экзамена и до момента и его завершения: {total_time:.2f}")

    passed_students = list(filter(lambda s: students_state[s.name]["status"] == STATUS_PASSED, students))
    best_students = []
    if passed_students:
        best_time = min(map(lambda s: students_state[s.name]["time"], passed_students))
        best_students = list(map(
            lambda s: s.name,
            filter(lambda s: students_state[s.name]["time"] == best_time, passed_students),
        ))
    print(f"Имена лучших студентов: {', '.join(best_students)}")

    fail_rate = lambda e: examiners_state[e.name]["failed"] / examiners_state[e.name]["total"]
    examined = list(filter(lambda e: examiners_state[e.name]["total"] > 0, examiners))
    best_examiners = []
    if examined:
        best_rate = min(map(fail_rate, examined))
        best_examiners = list(map(lambda e: e.name, filter(lambda e: fail_rate(e) == best_rate, examined)))
    print(f"Имена лучших экзаменаторов: {', '.join(best_examiners)}")

    failed_students = list(filter(lambda s: students_state[s.name]["status"] == STATUS_FAILED, students))
    expelled = []
    if failed_students:
        earliest = min(map(lambda s: students_state[s.name]["finish"], failed_students))
        expelled = list(map(
            lambda s: s.name,
            filter(lambda s: students_state[s.name]["finish"] == earliest, failed_students),
        ))
    print(f"Имена студентов, которых после экзамена отчислят: {', '.join(expelled)}")

    best_questions = []
    if questions:
        best_count = max(map(lambda q: question_stats.get(q.text, 0), questions))
        best_questions = list(map(
            lambda q: q.text,
            filter(lambda q: question_stats.get(q.text, 0) == best_count, questions),
        ))
    print(f"Лучшие вопросы: {', '.join(best_questions)}")

    pass_rate = len(passed_students) / len(students) if students else 0
    verdict = "экзамен удался" if pass_rate > PASS_RATE_THRESHOLD else "экзамен не удался"
    print(f"Вывод: {verdict}")


# --------------------------------------------------------------------------- #
# Точка входа
# --------------------------------------------------------------------------- #

def main() -> None:
    examiners = load_people(BASE_DIR / "examiners.txt", Examiner)
    students = load_people(BASE_DIR / "students.txt", Student)
    questions = load_questions(BASE_DIR / "questions.txt")
    students_lookup = {student.name: student for student in students}

    manager = multiprocessing.Manager()
    queue = manager.list([student.name for student in students])
    queue_lock = manager.Lock()
    state_lock = manager.Lock()
    students_state = manager.dict({
        student.name: {"status": STATUS_QUEUE, "time": None, "finish": None} for student in students
    })
    examiners_state = manager.dict({
        examiner.name: {"current": "-", "total": 0, "failed": 0, "worktime": 0.0} for examiner in examiners
    })
    question_stats = manager.dict()

    start_time = time.time()
    processes = [
        multiprocessing.Process(
            target=examiner_process,
            args=(examiner, students_lookup, questions, queue, queue_lock,
                  students_state, examiners_state, question_stats, state_lock, start_time),
        )
        for examiner in examiners
    ]
    for process in processes:
        process.start()

    while any(process.is_alive() for process in processes):
        render_progress(students, examiners, students_state, examiners_state, queue, start_time)
        time.sleep(REFRESH_INTERVAL)

    for process in processes:
        process.join()

    total_time = time.time() - start_time
    render_final_report(students, examiners, students_state, examiners_state, question_stats, questions, total_time)


if __name__ == "__main__":
    main()
