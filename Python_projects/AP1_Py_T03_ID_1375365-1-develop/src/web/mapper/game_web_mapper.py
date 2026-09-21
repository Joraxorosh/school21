import uuid

from domain.model.game import Game
from web.mapper.board_web_mapper import BoardWebMapper
from web.model.game_web_model import GameWebModel


class GameWebMapper:
    """Преобразует текущую игру между domain-слоем и web-слоем."""

    @staticmethod
    def to_domain(web_model: GameWebModel) -> Game:
        try:
            game_id = uuid.UUID(web_model.id)
        except (ValueError, AttributeError, TypeError) as error:
            raise ValueError(f"'{web_model.id}' is not a valid UUID") from error
        return Game(id=game_id, board=BoardWebMapper.to_domain(web_model.board))

    @staticmethod
    def to_web(game: Game, finished: bool) -> GameWebModel:
        return GameWebModel(
            id=str(game.id),
            board=BoardWebMapper.to_web(game.board),
            finished=finished,
        )
