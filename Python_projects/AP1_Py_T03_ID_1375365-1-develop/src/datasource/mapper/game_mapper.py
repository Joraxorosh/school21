from datasource.mapper.board_mapper import BoardMapper
from datasource.model.game_entity import GameEntity
from domain.model.game import Game


class GameMapper:
    """Преобразует текущую игру между domain-слоем и datasource-слоем."""

    @staticmethod
    def to_domain(entity: GameEntity) -> Game:
        return Game(id=entity.id, board=BoardMapper.to_domain(entity.board))

    @staticmethod
    def to_entity(game: Game) -> GameEntity:
        return GameEntity(id=game.id, board=BoardMapper.to_entity(game.board))
