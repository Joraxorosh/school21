import threading
import uuid
from typing import Dict, Optional

from datasource.model.game_entity import GameEntity


class GameStorage:
    """Потокобезопасное хранилище текущих игр в памяти."""

    def __init__(self):
        self._lock = threading.RLock()
        self._games: Dict[uuid.UUID, GameEntity] = {}

    def save(self, game_entity: GameEntity) -> None:
        with self._lock:
            self._games[game_entity.id] = game_entity

    def get(self, game_id: uuid.UUID) -> Optional[GameEntity]:
        with self._lock:
            return self._games.get(game_id)
