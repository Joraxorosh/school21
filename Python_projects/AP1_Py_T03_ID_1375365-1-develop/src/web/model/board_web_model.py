from dataclasses import dataclass
from typing import Any, List


@dataclass
class BoardWebModel:
    """JSON-представление игрового поля."""

    cells: List[List[int]]

    @staticmethod
    def from_dict(data: Any) -> "BoardWebModel":
        if not isinstance(data, dict) or "cells" not in data:
            raise ValueError("Field 'board.cells' is required")

        cells = data["cells"]
        is_matrix = (
            isinstance(cells, list)
            and len(cells) == 3
            and all(isinstance(row, list) and len(row) == 3 for row in cells)
        )
        if not is_matrix:
            raise ValueError("Field 'board.cells' must be a 3x3 matrix")

        for row in cells:
            for value in row:
                if not isinstance(value, int) or isinstance(value, bool):
                    raise ValueError("Board cells must contain integers only")

        return BoardWebModel(cells=cells)

    def to_dict(self) -> dict:
        return {"cells": self.cells}
