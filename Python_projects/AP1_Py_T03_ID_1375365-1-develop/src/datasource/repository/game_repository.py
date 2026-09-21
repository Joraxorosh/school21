import uuid
from abc import ABC, abstractmethod
from typing import Optional

from domain.model.game import Game


class GameRepository(ABC):
    """Контракт для чтения и записи игр через класс-хранилище."""

    @abstractmethod
    def save_game(self, game: Game) -> None:
        raise NotImplementedError

    @abstractmethod
    def get_game(self, game_id: uuid.UUID) -> Optional[Game]:
        raise NotImplementedError
