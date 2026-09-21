from dataclasses import dataclass
from typing import List


@dataclass
class BoardEntity:
    """Представление игрового поля для хранения."""

    cells: List[List[int]]
