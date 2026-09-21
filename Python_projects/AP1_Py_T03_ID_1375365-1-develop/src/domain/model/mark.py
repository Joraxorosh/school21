from enum import IntEnum


class Mark(IntEnum):
    """Возможные значения одной клетки игрового поля крестиков-ноликов."""

    EMPTY = 0
    PLAYER = 1
    COMPUTER = 2
