from datasource.model.board_entity import BoardEntity
from domain.model.board import Board


class BoardMapper:
    """Преобразует игровое поле между domain-слоем и datasource-слоем."""

    @staticmethod
    def to_domain(entity: BoardEntity) -> Board:
        return Board([row[:] for row in entity.cells])

    @staticmethod
    def to_entity(board: Board) -> BoardEntity:
        return BoardEntity(cells=[row[:] for row in board.cells])
