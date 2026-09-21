import uuid
from dataclasses import dataclass

from datasource.model.board_entity import BoardEntity


@dataclass
class GameEntity:
    """Представление текущей игры для хранения."""

    id: uuid.UUID
    board: BoardEntity
