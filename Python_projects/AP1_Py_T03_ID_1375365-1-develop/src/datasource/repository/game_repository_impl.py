import uuid
from typing import Optional

from datasource.mapper.game_mapper import GameMapper
from datasource.repository.game_repository import GameRepository
from datasource.storage.game_storage import GameStorage
from domain.model.game import Game


class GameRepositoryImpl(GameRepository):
    """Репозиторий для работы с потокобезопасным хранилищем игр."""

    def __init__(self, storage: GameStorage):
        self._storage = storage

    def save_game(self, game: Game) -> None:
        self._storage.save(GameMapper.to_entity(game))

    def get_game(self, game_id: uuid.UUID) -> Optional[Game]:
        entity = self._storage.get(game_id)
        return GameMapper.to_domain(entity) if entity is not None else None
