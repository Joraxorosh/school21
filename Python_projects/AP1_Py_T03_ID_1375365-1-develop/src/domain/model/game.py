import uuid
from dataclasses import dataclass

from domain.model.board import Board


@dataclass
class Game:
    """Текущая игра: её уникальный идентификатор и игровое поле."""

    id: uuid.UUID
    board: Board
