from domain.model.board import Board
from web.model.board_web_model import BoardWebModel


class BoardWebMapper:
    """Преобразует игровое поле между domain-слоем и web-слоем."""

    @staticmethod
    def to_domain(web_model: BoardWebModel) -> Board:
        return Board([row[:] for row in web_model.cells])

    @staticmethod
    def to_web(board: Board) -> BoardWebModel:
        return BoardWebModel(cells=[row[:] for row in board.cells])
