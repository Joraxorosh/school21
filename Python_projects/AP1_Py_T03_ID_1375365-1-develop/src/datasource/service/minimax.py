from typing import List, Optional, Tuple

from domain.model.mark import Mark

Cells = List[List[int]]

_WINNING_LINES: Tuple[Tuple[Tuple[int, int], ...], ...] = (
    ((0, 0), (0, 1), (0, 2)),
    ((1, 0), (1, 1), (1, 2)),
    ((2, 0), (2, 1), (2, 2)),
    ((0, 0), (1, 0), (2, 0)),
    ((0, 1), (1, 1), (2, 1)),
    ((0, 2), (1, 2), (2, 2)),
    ((0, 0), (1, 1), (2, 2)),
    ((0, 2), (1, 1), (2, 0)),
)


def get_winner(cells: Cells) -> int:
    """Вернуть метку победителя (Mark.PLAYER/Mark.COMPUTER) или Mark.EMPTY, если победителя нет."""
    for line in _WINNING_LINES:
        first_r, first_c = line[0]
        first_value = cells[first_r][first_c]
        if first_value == Mark.EMPTY:
            continue
        if all(cells[r][c] == first_value for r, c in line):
            return first_value
    return Mark.EMPTY.value


def is_board_full(cells: Cells) -> bool:
    return all(cells[r][c] != Mark.EMPTY for r in range(3) for c in range(3))


def _empty_cells(cells: Cells) -> List[Tuple[int, int]]:
    return [(r, c) for r in range(3) for c in range(3) if cells[r][c] == Mark.EMPTY]


def _minimax(cells: Cells, is_maximizing: bool) -> int:
    winner = get_winner(cells)
    if winner == Mark.COMPUTER:
        return 1
    if winner == Mark.PLAYER:
        return -1
    if is_board_full(cells):
        return 0

    mark = Mark.COMPUTER if is_maximizing else Mark.PLAYER
    scores = []
    for r, c in _empty_cells(cells):
        cells[r][c] = mark.value
        scores.append(_minimax(cells, not is_maximizing))
        cells[r][c] = Mark.EMPTY.value
    return max(scores) if is_maximizing else min(scores)


def find_best_move(cells: Cells) -> Optional[Tuple[int, int]]:
    """Найти оптимальный ход компьютера с помощью алгоритма Минимакс."""
    best_score = None
    best_move = None
    for r, c in _empty_cells(cells):
        cells[r][c] = Mark.COMPUTER.value
        score = _minimax(cells, False)
        cells[r][c] = Mark.EMPTY.value
        if best_score is None or score > best_score:
            best_score = score
            best_move = (r, c)
    return best_move
