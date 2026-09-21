from datasource.repository.game_repository import GameRepository
from datasource.service.minimax import find_best_move, get_winner, is_board_full
from domain.model.board import Board
from domain.model.game import Game
from domain.model.mark import Mark
from domain.service.game_service import GameService


class GameServiceImpl(GameService):
    """Конкретная реализация GameService поверх GameRepository."""

    def __init__(self, repository: GameRepository):
        self._repository = repository

    def get_next_move(self, game: Game) -> Game:
        if self.is_game_over(game):
            # Играть больше некуда: просто сохраняем финальное состояние от игрока.
            self._repository.save_game(game)
            return game

        cells = [row[:] for row in game.board.cells]
        move = find_best_move(cells)
        if move is not None:
            row, col = move
            cells[row][col] = Mark.COMPUTER.value

        updated_game = Game(id=game.id, board=Board(cells))
        self._repository.save_game(updated_game)
        return updated_game

    def validate_board(self, game: Game) -> bool:
        stored_game = self._repository.get_game(game.id)
        previous_cells = (
            stored_game.board.cells if stored_game is not None else Board().cells
        )
        new_cells = game.board.cells

        added_player_moves = 0
        for row in range(Board.SIZE):
            for col in range(Board.SIZE):
                previous_value = previous_cells[row][col]
                new_value = new_cells[row][col]

                if new_value not in (Mark.EMPTY, Mark.PLAYER, Mark.COMPUTER):
                    return False

                if previous_value != Mark.EMPTY and new_value != previous_value:
                    return False  # предыдущий ход был перезаписан или стёрт

                if previous_value == Mark.EMPTY and new_value != Mark.EMPTY:
                    if new_value != Mark.PLAYER:
                        return False  # новую метку разрешено ставить только игроку
                    added_player_moves += 1

        if added_player_moves != 1:
            return False  # за один запрос игрок должен добавить ровно один новый ход

        if stored_game is not None and self.is_game_over(stored_game):
            return False  # сохранённая игра уже была завершена

        return True

    def is_game_over(self, game: Game) -> bool:
        cells = game.board.cells
        return get_winner(cells) != Mark.EMPTY or is_board_full(cells)
