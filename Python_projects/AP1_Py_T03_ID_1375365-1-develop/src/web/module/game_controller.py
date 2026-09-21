from typing import Any, Tuple

from domain.service.game_service import GameService
from web.mapper.game_web_mapper import GameWebMapper
from web.model.game_web_model import GameWebModel


class GameController:
    """Обрабатывает HTTP-запрос хода: разбор, валидация, вызов сервиса, ответ."""

    def __init__(self, game_service: GameService):
        self._game_service = game_service

    def make_move(self, path_game_id: str, payload: Any) -> Tuple[dict, int]:
        try:
            web_model = GameWebModel.from_dict(payload)
        except ValueError as error:
            return {"error": str(error)}, 400

        if web_model.id != path_game_id:
            return {"error": "Game id in the URL does not match the id in the request body"}, 400

        try:
            game = GameWebMapper.to_domain(web_model)
        except ValueError as error:
            return {"error": str(error)}, 400

        if not self._game_service.validate_board(game):
            return {
                "error": (
                    "Invalid game board: previous moves were changed, the submitted "
                    "move is illegal, or the game is already finished"
                )
            }, 400

        updated_game = self._game_service.get_next_move(game)
        finished = self._game_service.is_game_over(updated_game)
        response_model = GameWebMapper.to_web(updated_game, finished)
        return response_model.to_dict(), 200
