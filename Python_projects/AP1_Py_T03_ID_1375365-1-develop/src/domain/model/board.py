from typing import List, Optional


class Board:
    """Игровое поле в виде целочисленной матрицы 3x3."""

    SIZE = 3

    def __init__(self, cells: Optional[List[List[int]]] = None):
        if cells is None:
            cells = [[0] * Board.SIZE for _ in range(Board.SIZE)]
        self._validate_shape(cells)
        self.cells = cells

    @staticmethod
    def _validate_shape(cells: List[List[int]]) -> None:
        if len(cells) != Board.SIZE or any(len(row) != Board.SIZE for row in cells):
            raise ValueError(f"Board must be a {Board.SIZE}x{Board.SIZE} matrix")

    def copy(self) -> "Board":
        return Board([row[:] for row in self.cells])

    def __eq__(self, other: object) -> bool:
        return isinstance(other, Board) and self.cells == other.cells

    def __repr__(self) -> str:
        return f"Board(cells={self.cells})"
